# Fil rouge du projet GPS PMOD pour Plasma

développé sur processeur softcore [Plasma](https://opencores.org/project,plasma "Plasma's Homepage") afin de pouvoir gérer les modules PMOD GPS sur les cartes de développement Nexys-4 de Digilent.

* [Plus d'infos sur le plasma](README.md)

## A faire :

* Ajouter un composant uart concurent au [plasma](HDL/PLASMA/plasma.vhd)  en actualisant le [top level du plasma](HDL/PLASMA/top_plasma.vhd).

* Mettre à jour le [XDC](SYNTHESIS/nexys4.xdc) (sur le connecteur *JC*).

* Créer le fichier source (C/C++) (et *header* eventuel) pour le gps utilisant l'uart pmod.

## Fait :

* Comprendre.
