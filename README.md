# CY-TRUCK-FM

Bienvenue dans le projet CY TRUCK ! Ce script Shell et le programme C associé ont pour but d'analyser des données de trajets routiers et de générer des graphiques résumant l'activité de votre société de transport routier.

## Fonctionnalités

- Analyse des données de trajets routiers
- Génération de graphiques récapitulatifs
- Traitement efficace des données volumineuses

## Installation

1. Cloner le dépôt : `git clone https://github.com/giinko/Cy-truck-FM.git`

2. Exectuer le Makefile : `make'

## Traitements

#### Traitement [D1] : Conducteurs avec le plus de trajets
```bash
./main.sh <chemin_du_fichier> -d1
```
Récupère la liste des 10 conducteurs avec le plus de trajets, puis crée un histogramme horizontal.

#### Traitement [D2] : Conducteurs et la plus grande distance
```bash
./main.sh <chemin_du_fichier> -d2
```
Calcule la distance totale parcourue par chaque conducteur, puis crée un histogramme horizontal.

#### Traitement [L] : Les 10 trajets les plus longs
```bash
./main.sh <chemin_du_fichier> -l
```
Récupère les 10 trajets avec la plus grande distance totale et crée un histogramme vertical.

#### Traitement [T] : Les 10 villes les plus traversées
```bash
./main.sh <chemin_du_fichier> -t
```
Compte le nombre de trajets traversant chaque ville et crée un histogramme regroupé.

#### Traitement [S] : Statistiques sur les étapes
```bash
./main.sh <chemin_du_fichier> -s
```
Calcule les distances minimales, maximales et moyennes des étapes pour chaque trajet, puis crée un graphique de type courbes min-max-moyenne.

## Auteurs

- Fares BEN MABROUK : [@fares-ben](https://www.github.com/fares-ben)
- Maxime CLEMENT : [@giinko](https://www.github.com/giinko)
  
<img src="https://upload.wikimedia.org/wikipedia/commons/4/4a/CY_Tech.png" alt="Logo" width="200"/>
