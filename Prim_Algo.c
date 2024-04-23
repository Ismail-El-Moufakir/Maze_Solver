#include "Maze_Prim.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

void AddToFrontier(Frontier *frontier, Cell cell, maze *mz) {
    int rows = mz->height / CELL_H;
    int cols = mz->width / CELL_W;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Directions: top, bottom, left, right
    for (int k = 0; k < 4; k++) {
        int ni = cell.i + directions[k][0];
        int nj = cell.j + directions[k][1];

        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !mz->MazeCells[ni][nj].In_Maze && !mz->MazeCells[ni][nj].visited) {
            frontier->cells[frontier->size++] = mz->MazeCells[ni][nj];
            mz->MazeCells[ni][nj].visited = 1;
        }
    }
}

void RemoveFromFrontier(Frontier *frontier, int index) {
    frontier->cells[index] = frontier->cells[--frontier->size];
}

void RemoveWalls(Cell *c1, Cell *c2) {
    int xDiff = c2->i - c1->i;
    int yDiff = c2->j - c1->j;

    if (xDiff == 1) { c1->Walls[1] = 0; c2->Walls[0] = 0; }
    else if (xDiff == -1) { c1->Walls[0] = 0; c2->Walls[1] = 0; }
    else if (yDiff == 1) { c1->Walls[3] = 0; c2->Walls[2] = 0; }
    else if (yDiff == -1) { c1->Walls[2] = 0; c2->Walls[3] = 0; }
}

void InitializeMaze(maze *mz) {
    mz->height = HEIGHT;
    mz->width = WIDTH;
    int rows = mz->height / CELL_H;
    int cols = mz->width / CELL_W;
    mz->MazeCells = (Cell**)malloc(rows * sizeof(Cell*));

    for (int i = 0; i < rows; i++) {
        mz->MazeCells[i] = (Cell*)malloc(cols * sizeof(Cell));
        for (int j = 0; j < cols; j++) {
            Cell cell = {i, j, 0, 0, {1, 1, 1, 1}}; // Initialize each cell with walls intact
            mz->MazeCells[i][j] = cell;
        }
    }
}

void GenerateMaze(maze *mz, Frontier *frontier) {
    Cell start = mz->MazeCells[0][0];
    start.In_Maze = 1;
    start.visited = 1;
    mz->MazeCells[0][0] = start;
    AddToFrontier(frontier, start, mz);

    while (frontier->size > 0) {
        int randIndex = GetRandomValue(0, frontier->size - 1);
        Cell current = frontier->cells[randIndex];
        RemoveFromFrontier(frontier, randIndex);

        int neighborsAdded = 0;
        Cell *neighbor = NULL;
        for (int i = 0; i < 4; i++) {
            int ni = current.i + (i == 0 ? -1 : (i == 1 ? 1 : 0));
            int nj = current.j + (i == 2 ? -1 : (i == 3 ? 1 : 0));
            if (ni >= 0 && ni < mz->height / CELL_H && nj >= 0 && nj < mz->width / CELL_W && mz->MazeCells[ni][nj].In_Maze) {
                neighborsAdded++;
                neighbor = &mz->MazeCells[ni][nj];
            }
        }

        if (neighborsAdded > 0) {
            RemoveWalls(&current, neighbor);
        }

        current.In_Maze = 1;
        mz->MazeCells[current.i][current.j] = current;
        AddToFrontier(frontier, current, mz);
    }
}

void DrawMaze(maze *mz) {
    int rows = mz->height / CELL_H;
    int cols = mz->width / CELL_W;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Cell cell = mz->MazeCells[i][j];
            int x = j * CELL_W;
            int y = i * CELL_H;
            if (cell.Walls[0]) DrawLine(x, y, x + CELL_W, y, BLACK);
            if (cell.Walls[1]) DrawLine(x, y + CELL_H, x + CELL_W, y + CELL_H, BLACK);
            if (cell.Walls[2]) DrawLine(x, y, x, y + CELL_H, BLACK);
            if (cell.Walls[3]) DrawLine(x + CELL_W, y, x + CELL_W, y + CELL_H, BLACK);
        }
    }
}

int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Maze Generator");
    SetTargetFPS(60);
    maze mz;
    InitializeMaze(&mz);
    Frontier frontier = {0};

    GenerateMaze(&mz, &frontier);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMaze(&mz);
        EndDrawing();
    }

    CloseWindow();
    // Free memory for maze
    for (int i = 0; i < mz.height / CELL_H; i++) {
        free(mz.MazeCells[i]);
    }
    free(mz.MazeCells);
    return 0;
}
