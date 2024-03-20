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
