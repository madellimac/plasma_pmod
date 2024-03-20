import cv2
import serial
import matplotlib.pyplot as plt
import numpy as np
import os
import argparse
import re
import time

from random import randrange
from PIL import Image


parser = argparse.ArgumentParser()
parser.add_argument("-n", "--number", type=int)
parser.add_argument("-he", "--height", type=int)
parser.add_argument("-w", "--width", type=int)
args = parser.parse_args()

images_number = args.number

# Constants
IMG_HEIGHT = args.height
IMG_WIDTH = args.width
SCALING_FACTOR = 1

list_dataset = os.listdir('./IMG/mnist_images/train')
data_name = []
for data in (list_dataset) :
    data_name.append(data)

image_line = list()

image_line.append(images_number)


for i in range(images_number):
    data_chosen = data_name[randrange(len(data_name))-1]
    FILEPATH_TARGET = f"./IMG/mnist_images/train/{data_chosen}"

    image = Image.open(FILEPATH_TARGET)

    image_resized = image.resize((IMG_WIDTH,IMG_HEIGHT), resample=Image.BILINEAR)

    OUTPUT_FILEPATH = "MNIST_data.pgm"
    # Enregistrer l'image redimensionnée
    image_resized.save(OUTPUT_FILEPATH)

    # Opening and treating image #
    image = cv2.imread("MNIST_data.pgm")
    # Remember, opencv by default reads images in BGR rather than RGB
    # So we fix that by the following
    image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
    # https://stackoverflow.com/questions/4101576/importing-ppm-images-with-python-and-pil-module

    image = SCALING_FACTOR*image
    #plt.imshow(image)
    plt.savefig("test.png")
    #plt.clf()
    #https://www.statology.org/numpy-array-to-int/
    image = (np.rint(image)).astype(int)

    # reordering RGB pixels

    for i in range(IMG_HEIGHT):
        for j in range(IMG_WIDTH):
            image_line.append(image[i,j,0]) # R
            image_line.append(image[i,j,1]) # G
            image_line.append(image[i,j,2]) # B

# serializing data
image_line = bytearray(image_line)

# Définition du port série
port = '/dev/ttyUSB1'

# Définition de la vitesse de communication
baudrate = 115200

# Liste d'octets à envoyer
byte_list = [0x01, 0x02, 0x03, 0x04, 0x05]

try:
    # Ouverture du port série
    ser = serial.Serial(port, baudrate)
    
    # Attente pour laisser le temps à la communication de s'établir
    time.sleep(1)

    # Envoi des octets de la liste
    for byte in image_line:
        # Envoi de l'octet sur le port série
        ser.write(bytes([byte]))
        
        # Attente de 1 seconde entre chaque envoi
        time.sleep(0.001)
    
    # Fermeture du port série
    ser.close()

except serial.SerialException as e:
    print("Erreur lors de l'ouverture du port série :", e)

weight_line = list()

