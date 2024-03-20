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

def pick_random_image(data_name) :

    data_chosen = data_name[randrange(len(data_name))-1]
    FILEPATH_TARGET = f"./IMG/mnist_images/train/{data_chosen}"

    image = Image.open(FILEPATH_TARGET)

    image_resized = image.resize((IMG_WIDTH,IMG_HEIGHT), resample=Image.BILINEAR)

    OUTPUT_FILEPATH = "MNIST_data.pgm"
    # Enregistrer l'image redimensionnée
    image_resized.save(OUTPUT_FILEPATH)

def populate_image_line() :
    
    # Opening and treating image #
    image = cv2.imread("MNIST_data.pgm")
    # Remember, opencv by default reads images in BGR rather than RGB
    # So we fix that by the following
    image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
    # https://stackoverflow.com/questions/4101576/importing-ppm-images-with-python-and-pil-module

    image = SCALING_FACTOR*image
    #plt.imshow(image)
    #plt.savefig("test.png")
    #plt.clf()
    #https://www.statology.org/numpy-array-to-int/
    image = (np.rint(image)).astype(int)

    # reordering RGB pixels

    for i in range(IMG_HEIGHT):
        for j in range(IMG_WIDTH):
            image_line.append(image[i,j,0]) # R
            image_line.append(image[i,j,1]) # G
            image_line.append(image[i,j,2]) # B


parser = argparse.ArgumentParser()
#parser.add_argument("-n", "--number", type=int, default='1')
parser.add_argument("-height", "--height", type=int, default='28', help="Image height (pixels), default=28." )
parser.add_argument("-width", "--width", type=int, default='28', help="Image width (pixels), default=28.")
parser.add_argument("-rnd_img", "--random_image", action='store_true', help="Pick a random image in the dataset, default=disabled.")
parser.add_argument("-weights", "--cnn_weights", action='store_true', help="Push the weights after the image is pushed, default=disabled")

args = parser.parse_args()

# Constants
IMG_HEIGHT = args.height
IMG_WIDTH = args.width
SCALING_FACTOR = 1

image_line = list()

# pickup random images
if args.random_image :
    #images_number = args.number
    images_number = 1
    list_dataset = os.listdir('./IMG/mnist_images/train')
    data_name = []
    for data in (list_dataset) :
        data_name.append(data)

    image_line.append(images_number)

    for i in range(images_number):
        pick_random_image(data_name)
        populate_image_line()

# single image
else :
    images_number = 1
    image_line.append(images_number)
    populate_image_line()


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



if args.cnn_weights :
    print("Send CNN weights")
    
    weight_line = list()

    # Open a binary file
    with open("weights_fixed.bin", "rb") as f:

            fixed_t = f.read(1)
            fixed_t_int = int.from_bytes(fixed_t, "big")
            weight_line.append(fixed_t_int)
            while fixed_t:
                fixed_t = f.read(1)

                # converting to int
                # byteorder is big where MSB is at start
                fixed_t_int = int.from_bytes(fixed_t, "big")
                weight_line.append(fixed_t_int)

    # Définition du port série
    port = '/dev/ttyUSB1'

    # Définition de la vitesse de communication
    baudrate = 115200

    try:
        # Ouverture du port série
        ser = serial.Serial(port, baudrate)
        
        # Attente de 2 secondes pour laisser le temps à la communication de s'établir
        time.sleep(1)

        # Envoi des octets de la liste
        for byte in weight_line:
            # Envoi de l'octet sur le port série
            ser.write(bytes([byte]))
            
            # Attente de 1 seconde entre chaque envoi
            time.sleep(0.0005)
        
        # Fermeture du port série
        ser.close()

    except serial.SerialException as e:
        print("Erreur lors de l'ouverture du port série :", e)
