#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 15
#define WIN_CONDITION 5
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// Structure to store coordinates
typedef struct {
    int row;
    int col;
} Position;

// Structure for queue operations in path finding
typedef struct {
    Position positions[BOARD_SIZE * BOARD_SIZE];
    int front;
    int rear;
} Queue;

// Initialize the game board
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Initialize a queue
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
bool isQueueEmpty(Queue *q) {
    return q->front == -1;
}

// Add position to queue
void enqueue(Queue *q, Position pos) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->positions[q->rear] = pos;
}

// Remove and return position from queue
Position dequeue(Queue *q) {
    Position pos = q->positions[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return pos;
}

// Check if a position has been visited
bool isVisited(bool visited[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return visited[row][col];
}

// Mark a position as visited
void markVisited(bool visited[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    visited[row][col] = true;
}

// Check if position is within board boundaries
bool isValidPosition(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

// Find connected symbols using BFS
int findConnectedSymbols(char board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, char symbol) {
    // Initialize visited array
    bool visited[BOARD_SIZE][BOARD_SIZE] = {false};
    Queue queue;
    initQueue(&queue);

    // Define all possible directions (including diagonals)
    int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},  // Top-left, Top, Top-right
            {0, -1},           {0, 1},    // Left, Right
            {1, -1},  {1, 0},  {1, 1}     // Bottom-left, Bottom, Bottom-right
    };

    // Start BFS from the initial position
    Position start = {startRow, startCol};
    enqueue(&queue, start);
    markVisited(visited, startRow, startCol);
    int connectedCount = 1;  // Count includes the starting position

    // Process queue
    while (!isQueueEmpty(&queue)) {
        Position current = dequeue(&queue);

        // Check all adjacent positions (including diagonals)
        for (int i = 0; i < 8; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];

            // Check if the new position is valid and contains the same symbol
            if (isValidPosition(newRow, newCol) &&
                !isVisited(visited, newRow, newCol) &&
                board[newRow][newCol] == symbol) {

                Position newPos = {newRow, newCol};
                enqueue(&queue, newPos);
                markVisited(visited, newRow, newCol);
                connectedCount++;

                // If we found enough connected symbols, return early
                if (connectedCount >= WIN_CONDITION) {
                    return connectedCount;
                }
            }
        }
    }

    return connectedCount;
}

// Display the game board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %2d ", i + 1);
    }
    printf("\n");

    printf("   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("----");
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("----");
        }
        printf("\n");
    }
}

// Check if a move is valid
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return isValidPosition(row, col) && board[row][col] == EMPTY;
}

// Check if the board is full
bool isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer = PLAYER_X;
    bool gameWon = false;
    int row, col;

    initializeBoard(board);

    printf("Welcome to 15x15 Tic Tac Toe!\n");
    printf("To win, connect %d marks in any connected pattern\n", WIN_CONDITION);
    printf("Connections can be made in any direction, including zigzag patterns!\n");

    while (!gameWon && !isBoardFull(board)) {
        displayBoard(board);

        printf("\nPlayer %c's turn\n", currentPlayer);
        do {
            printf("Enter row (1-%d): ", BOARD_SIZE);
            scanf("%d", &row);
            printf("Enter column (1-%d): ", BOARD_SIZE);
            scanf("%d", &col);

            // Convert to 0-based indexing
            row--;
            col--;

            if (!isValidMove(board, row, col)) {
                printf("Invalid move! Try again.\n");
            }
        } while (!isValidMove(board, row, col));

        // Make the move
        board[row][col] = currentPlayer;

        // Check for win using the new connected symbols detection
        int connectedCount = findConnectedSymbols(board, row, col, currentPlayer);
        if (connectedCount >= WIN_CONDITION) {
            displayBoard(board);
            printf("\nPlayer %c wins with %d connected symbols!\n",
                currentPlayer, connectedCount);
            gameWon = true;
        } else {
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
    }

    if (!gameWon) {
        displayBoard(board);
        printf("\nGame Over! It's a draw!\n");
    }

    return 0;
}