#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "Tic.h"

// fonction pour réinitialiser le jeu
void ResetGame(TicTacToe *game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            game->board[i][j] = 0;
        }
    }
    game->currentPlayer = 2;  // IA commence en premier
}

// fonction effectue un mouvement si la case spécifiée est vide.
bool MakeMove(TicTacToe *game, int row, int col) {
    if (game->board[row][col] == 0) {
        game->board[row][col] = game->currentPlayer;
        game->currentPlayer = 3 - game->currentPlayer;
        return true;
    }
    return false;
}

// vérifier et retourner le gagnant
int CheckWinner(TicTacToe *game) {
    for (int player = 1; player <= 2; player++) {
        for (int i = 0; i < 3; i++) {
            if (game->board[i][0] == player && game->board[i][1] == player && game->board[i][2] == player)
                return player;
            if (game->board[0][i] == player && game->board[1][i] == player && game->board[2][i] == player)
                return player;
        }
        if (game->board[0][0] == player && game->board[1][1] == player && game->board[2][2] == player)
            return player;
        if (game->board[0][2] == player && game->board[1][1] == player && game->board[2][0] == player)
            return player;
    }
    return 0;
}

bool IsBoardFull(TicTacToe *game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

double Q[3][3][9]; // QTable initialisé

void InitializeQ() {
    srand(time(NULL));  // module de génération de nombre aléatoire
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                Q[i][j][k] = ((double)rand() / RAND_MAX) / 100.0; // petites valeurs aléatoires pour que la situation au début soit toujours random
            }
        }
    }
}

// choix d'action en utilisant epsilon greedy
int ChooseAction(TicTacToe *game) {
    if ((rand() / (double)RAND_MAX) < EPSILON) {
        return rand() % 9;
    } else {
        int bestAction = -1;
        double bestValue = -1e9;
        for (int action = 0; action < 9; action++) {
            int row = action / 3;
            int col = action % 3;
            if (game->board[row][col] == 0 && Q[row][col][action] > bestValue) {
                bestValue = Q[row][col][action];
                bestAction = action;
            }
        }
        return bestAction;
    }
}

// modification des valeurs de tableau de Q
void UpdateQ(TicTacToe *game, int prevAction, int reward, int nextAction) {
    int prevRow = prevAction / 3;
    int prevCol = prevAction % 3;
    int nextRow = nextAction / 3;
    int nextCol = nextAction % 3;
    Q[prevRow][prevCol][prevAction] += ALPHA * (reward + GAMMA * Q[nextRow][nextCol][nextAction] - Q[prevRow][prevCol][prevAction]);
}

// fonction pour évaluer l'état actuel du jeu et appliquer les pénalités
int EvaluateGameState(TicTacToe *game, int player) {
    int winner = CheckWinner(game);
    if (winner == player) return 10; // Récompense de 10 pour une victoire
    if (winner == 3 - player) return -10; // Pénalité de -10 pour une défaite

    // Pénalité pour des actions non stratégiques (par exemple, jouer dans un coin déjà occupé)
    for (int i = 0; i < 3; i++) {
        if ((game->board[i][0] == 3 - player && game->board[i][1] == 3 - player && game->board[i][2] == 0) ||
            (game->board[i][0] == 0 && game->board[i][1] == 3 - player && game->board[i][2] == 3 - player) ||
            (game->board[i][0] == 3 - player && game->board[i][1] == 0 && game->board[i][2] == 3 - player)) {
            return -5; // Pénalité de -5 pour laisser une opportunité à l'adversaire
        }
        if ((game->board[0][i] == 3 - player && game->board[1][i] == 3 - player && game->board[2][i] == 0) ||
            (game->board[0][i] == 0 && game->board[1][i] == 3 - player && game->board[2][i] == 3 - player) ||
            (game->board[0][i] == 3 - player && game->board[1][i] == 0 && game->board[2][i] == 3 - player)) {
            return -5; // Pénalité de -5 pour laisser une opportunité à l'adversaire
        }
    }
    if ((game->board[0][0] == 3 - player && game->board[1][1] == 3 - player && game->board[2][2] == 0) ||
        (game->board[0][0] == 0 && game->board[1][1] == 3 - player && game->board[2][2] == 3 - player) ||
        (game->board[0][0] == 3 - player && game->board[1][1] == 0 && game->board[2][2] == 3 - player)) {
        return -5; // Pénalité de -5 pour laisser une opportunité à l'adversaire
    }
    if ((game->board[0][2] == 3 - player && game->board[1][1] == 3 - player && game->board[2][0] == 0) ||
        (game->board[0][2] == 0 && game->board[1][1] == 3 - player && game->board[2][0] == 3 - player) ||
        (game->board[0][2] == 3 - player && game->board[1][1] == 0 && game->board[2][0] == 3 - player)) {
        return -5; // Pénalité de -5 pour laisser une opportunité à l'adversaire
    }
    return 0; // Aucune récompense ni pénalité si le jeu n'est pas encore terminé ou s'il n'y a pas d'opportunité critique pour l'adversaire
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
    SetTargetFPS(60);

    TicTacToe game;
    ResetGame(&game);
    InitializeQ();

    int prevAction = -1;
    int reward = 0;

    // IA commence le jeu
    int action = ChooseAction(&game);
    int row = action / 3;
    int col = action % 3;
    MakeMove(&game, row, col);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 1; i < 3; i++) {
            DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT, BLACK);
            DrawLine(0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE, BLACK);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game.board[i][j] == 1) {
                    DrawText("X", j * CELL_SIZE + CELL_SIZE / 2 - 20, i * CELL_SIZE + CELL_SIZE / 2 - 20, 60, RED);
                } else if (game.board[i][j] == 2) {
                    DrawText("O", j * CELL_SIZE + CELL_SIZE / 2 - 20, i * CELL_SIZE + CELL_SIZE / 2 - 20, 60, BLUE);
                }
            }
        }

        if (game.currentPlayer == 1) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;
                if (MakeMove(&game, row, col)) {
                    int winner = CheckWinner(&game);
                    if (winner != 0 || IsBoardFull(&game)) {
                        if (winner != 0) {
                            reward = (winner == 1) ? 10 : -10;
                        } else {
                            reward = 0;
                        }
                        ResetGame(&game);
                        prevAction = -1;

                        // L'IA fait le premier mouvement à nouveau
                        action = ChooseAction(&game);
                        row = action / 3;
                        col = action % 3;
                        MakeMove(&game, row, col);
                    }
                }
            }
        } else {
            action = ChooseAction(&game);
            row = action / 3;
            col = action % 3;
            if (MakeMove(&game, row, col)) {
                if (prevAction != -1) {
                    int nextAction = action;
                    UpdateQ(&game, prevAction, reward, nextAction);
                }
                prevAction = action;
                reward = EvaluateGameState(&game, 2);

                int winner = CheckWinner(&game);
                if (winner != 0 || IsBoardFull(&game)) {
                    if (winner != 0) {
                        reward = (winner == 2) ? 10 : -10;
                    } else {
                        reward = 0;
                    }
                    ResetGame(&game);
                    prevAction = -1;

                    // L'IA fait le premier mouvement à nouveau
                    action = ChooseAction(&game);
                    row = action / 3;
                    col = action % 3;
                    MakeMove(&game, row, col);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
