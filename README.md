# Application : Mesure de la qualité de l'air du CERI
Ce projet est dans le cadre de la diminution de la propagation du Covid-19 dans les environnements intérieurs notamment les universités, L’objectif étant de développer un système de gestion continue de la qualité de l’air dans un environnement intérieure. Le périmètre concerné est le Centre d’Enseignement et de Recherche en Informatique. 


# Description
## 1. Fonctionnalité et résultats attendues
- Une station de mesure des polluants CO2 et COV, Ces mesures sont à corréler à la température et au taux d'humidité dans l'air. 

- La collecte des données de la station et les achemine vers le réseau local. 

- Les informations devront être "historisées", accessibles visuellement localement (afficheur ou écran LCD) et à distance. 

- Les seuils limites doivent pouvoir être fixés localement et à distance. 

- Un système d'alerte en cas de dépassement des valeurs limites doit être présent et une action sur l'aération sera menée (ventilation naturelle et/ou mécanique forcée).
#
## 2. Matériels et Technologies utilisées
- Langage de programmation C, Python, Javascript.
- Carte Arduino THE THINGS UNO. 
- Carte Raspberry Pi 2B. 
- Une passerelle LoRa The Things Network. 
- Des capteurs IAQ Core C et DHT22. 
- Accès Internet. 
- Afficheur ou écran LCD


```bash
pip install foobar
```
# Sommaire
- Branchement des capteurs. 
- Récupération des mesures des différents capteurs.
- Envoie des mesures au serveurs The Things Network (TTN).
- Réception et Décodages des données au niveau du serveur TTN.
- Affichage sur l'interface graphique.
# Usage
## 1. Branchement des capteurs
Les capteurs IAQ-Core C et DHT22 sont reliés à la carte Raspberry PI via le module « Pi 2 click shield »
(Capteur.jpg)

## 2.Récupération des mesures des différents capteurs.
#### Dépendances requises :
Installer les modules suivants sur votre Raspberry :
- Installer ```Python 3``` :
```bash 
sudo apt-get update 
sudo apt install python3
```
- Installer la librairie ```CircuitPython Libraries``` :
```bash 
sudo pip3 install --upgrade adafruit-python-shell
```
#### Fonctionnement :
A partir de la Raspberry lancez le script ```mesure.py```
```bash 
python3 mesure.py
```
## 3. Envoie des mesures au serveurs The Things Network (TTN).
Le module LoRa (carte Arduino) reçoit en port série les données qui viennent de la raspberry, puis les acheminées vers le serveur TTN.
#### Dépendances requises :
- Téléchargez et installez l'IDE [ARDUINO](https://www.arduino.cc/en/software)
- Télécharger et installer la librairie ```<TheThingsNetwork>``` à partir d'Arduino :
```Croquis --> Inclure une bibliothèque --> Gérer les bibliothèques``` puis recherchez ```<TheThingsNetwork>```
#### Fonctionnement :
A partir de votre PC et sur l'IDE Arduino :
- Choisissez le type de votre carte : ```Outils --> Type de carte --> Arduino Leonardo```
- Choisissez le port de communication : ```Outils --> Port```
- Lancez le code Arduino :  ```LoRa.ino```
## 4. Réception et Décodages des données au niveau du serveur TTN.
Les données reçues au niveau du serveur TTN devraient être décoder.
#### Fonctionnement :
- Accédez à la table de bord du serveur TTN.
- Copiez le code ```décoder.js``` dans le ```Payload formatters```, dans le champs ```Uplink```.
- Choisissez le ```formatter type``` à Javascript. 

## 5. Affichage sur l'interface graphique.
A partir de la Raspberry :
- Récupérer l'adresse IP de la Raspberry.
- Lancez Node-RED 
```bash
node-red-start
```
- Accédez à l'interface web du Node-RED par : ```@IP_Raspberry:1880```
#### Dépendances requises :
A partir de ```Manage palette``` installez :
- node-red-dashboard
- node-red-contrib-boolean-logic
- node-red-contrib-ui-led
- node-red-node-serialport
#### Fonctionnement :
Il existe 2 types d'interfaces :
- Interface de supervision complète.
- Interface de supervision lite (adapté pour petits écrans).

Pour accéder à l'interface complète :
- Importer le fichier ```UI.json```.
- Désactiver le flux de l'interface lite ```UI_Lite```.
- Déployer le fichier.
- Accédez à l'interface par le lien : ```@IP_Raspberry:1880/ui```


(UI_comp.jpg)

Pour accéder à l'interface lite:
- Importer le fichier ```UI.json```.
- Désactiver le flux de l'interface complète ```UI_Comp```.
- Déployer le fichier.
- Accédez à l'interface par le lien : ```@IP_Raspberry:1880/ui```


(UI_lite.jpg)


# Contributeur
#### Etudiants
- Bouferroum Aymen Salah Eddine.
- Kracheni Zakaria.
#### Encadrants
- Gozlan Philippe.
- Silanus Marc.

# License
Open Source
