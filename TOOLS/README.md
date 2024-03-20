# Getting started

## Implantation du Plasma

1 Générer le plasma : `make plasma`
2 Dans Vivado télécharger le bitstream généré

## Envoi du programme

1 Compiler le projet : `make project`
2 Envoyer le programme = `make send`


## Générer le dataset

1 Se placer dans le répertoire TOOLS/mnist_se/IMG = `cd TOOLS/mnist_se`
2 Télécharger le dataset mnist : `python3 MNIST_dataset.py`

NB : Pour que le script fonctionne, il faut installer tensor flow au préalable


## Envoi de l'image :

1 Se placer dans le répertoire TOOLS/mnist_se : `cd TOOLS/mnist_se`
2 Envoyer l'image : `python3 push_image_multiple.py`

## Envoi des coef

1 Se placer dans le répertoire TOOLS/mnist_se : `cd TOOLS/mnist_se`
2 Envoyer les points : `python3 push_weights.py`