# Getting started

## Implantation du Plasma

1 Générer le plasma : `make plasma`
2 Dans Vivado télécharger le bitstream généré

## Envoi du programme

1 Compiler le projet : `make project`
2 Envoyer le programme = `make send`


## Envoi de l'image et les coefficients du réseau:

1 Se placer dans le répertoire TOOLS/mnist_se : `cd TOOLS/mnist_se`
2 Envoyer l'image : `python3 push_image_weight.py`
3 Envoyer les points : `python3 push_image_weights.py -weights`
4 Une fois tous les coefficients reçus, appuyer sur le bouton central
5 L'image filtrée doit apparaitre sur l'écran RGB OLED


## Générer le dataset

Il est possible de prendre une image au hasard dans le dataset. Pour cela il faut d'abord télécharger le dataset.

1 Se placer dans le répertoire TOOLS/mnist_se/IMG = `cd TOOLS/mnist_se`
2 Télécharger le dataset mnist : `python3 MNIST_dataset.py`

NB : Pour que le script fonctionne, il faut installer tensor flow au préalable

Une fois le dataset généré, on peut envoyer une image au hasard avec la commande suivante `python3 push_image_weights.py -rnd_img`

## Entrainement du réseau

Tous les éléments nécessaires pour entrainer le CNN et obtenir les poids (en virgule flottante et fixe) se trouvent dans le répertoire TOOLS/mnist_se/TRAINING