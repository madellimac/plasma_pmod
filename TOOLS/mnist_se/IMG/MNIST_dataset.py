import os
import numpy as np
import tensorflow as tf
from tensorflow.keras.datasets import mnist
import imageio

# Charger le dataset MNIST
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Créer les dossiers d'enregistrement
save_folder_train = './mnist_images/train'
save_folder_test = './mnist_images/test'

# Créer les dossiers s'ils n'existent pas déjà
os.makedirs(save_folder_train, exist_ok=True)
os.makedirs(save_folder_test, exist_ok=True)

# Fonction pour enregistrer les images au format PGM
def save_images_pgm(images, labels, folder):
    for i, (image, label) in enumerate(zip(images, labels)):
        # Enregistrement au format PGM
        image_path = os.path.join(folder, f"{label}_{i}.pgm")
        imageio.imwrite(image_path, image.astype(np.uint8))

# Enregistrer les images d'entraînement au format PGM
save_images_pgm(x_train, y_train, save_folder_train)

# Enregistrer les images de test au format PGM
save_images_pgm(x_test, y_test, save_folder_test)