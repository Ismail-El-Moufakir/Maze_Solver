// Constants
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE 200
#define EPSILON 0.1
#define ALPHA 0.1
#define GAMMA 0.9
#define TRAINING_ITERATIONS 1000000

// Struct to represent the game state
typedef struct {
    int board[3][3];
    int currentPlayer;
} TicTacToe;

// Function declarations
void ResetGame(TicTacToe *game);
bool MakeMove(TicTacToe *game, int row, int col);
int CheckWinner(TicTacToe *game);
bool IsBoardFull(TicTacToe *game);
void InitializeQ();
int ChooseAction(TicTacToe *game);
void UpdateQ(TicTacToe *game, int prevAction, int reward, int nextAction);
int EvaluateGameState(TicTacToe *game, int player);
void TrainAgent(int iterations);

// QTable
double Q[3][3][9]; 
