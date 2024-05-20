### README - Projet IN104 ENSTA Paris

---

## Projet: MazeSolver en QLearning et Tic Tac Toe en SARSA

### Introduction

Ce projet fait partie du cours IN104 de l'ENSTA Paris et se concentre sur l'apprentissage par renforcement. Il comprend deux parties principales :
1. Un résolveur de labyrinthe utilisant l'algorithme Q-Learning.
2. Un jeu de Tic Tac Toe utilisant l'algorithme SARSA avec la bibliothèque Raylib pour l'interface graphique.

### Prérequis

Pour exécuter ce projet, vous aurez besoin des éléments suivants :

- Un compilateur C (gcc recommandé)
- La bibliothèque `Raylib` (pour le Tic Tac Toe)

### Installation

1. Clonez le dépôt du projet sur votre machine locale :
   ```bash
   git clone https://github.com/Ismail-El-Moufakir/Maze_Solver
### Accédez au répertoire du projet :
```bash
  cd Maze_Solver
```
### installation Raylib
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
sudo make install
```
### Structure de Projet 
```plaintext
MazeSolver/
│
├── RLMaze/
│   ├── data
      |maze.txt
│   ├──include
      |dfs.h
      |functions.h
      |mazeEnv.h
│   ├──src
      |QLearning.c
│   
│
├── Tic_Tac_Toe/
│   ├── Tic.c
│   ├── Tic.h
│ 
│
└── README.md
```
### Auteurs
  - Ismail El Moufakir
  - Adam Miraoui


