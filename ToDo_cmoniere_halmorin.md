# Fil rouge du projet GPS PMOD pour Plasma

développé sur processeur softcore [Plasma](https://opencores.org/project,plasma "Plasma's Homepage") afin de pouvoir gérer les modules PMOD GPS sur les cartes de développement Nexys-4 de Digilent.

* [Plus d'infos sur le plasma](README.md)

## A faire :

* Créer le fichier source (*C* pour le support, *C++* peut être plus tard) (et *header* éventuel) pour le gps utilisant l'uart pmod.

## En cours :

* Mettre à jour le [XDC](SYNTHESIS/nexys4.xdc) (sur le connecteur *JC*).

## Fait :

* Ajouter un composant uart concurrent dans [plasma.vhd](HDL/PLASMA/plasma.vhd)  en actualisant le [top level du plasma](HDL/PLASMA/top_plasma.vhd). (cmoniere)

* Modifications du [plasma.vhd](HDL/PLASMA/plasma.vhd) avec ajout du commentaire ***--UART_PMOD MODIF HERE*** ou ***--UART_PMOD HEAVY MODIF HERE !!*** en fonction de la criticité du changement.

* Ajouter les adresse de l'uart pmod dans [plasma.h](C/shared/plasma.h).

* Comprendre.
