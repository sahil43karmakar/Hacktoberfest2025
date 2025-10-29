#include <iostream>
#include <vector>
#include <limits>
using namespace std;

char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'O') return +10;
            else if (board[i][0] == 'X') return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'O') return +10;
            else if (board[0][i] == 'X') return -10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        else if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        else if (board[0][2] == 'X') return -10;
    }

    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
        return best;
    }
}

pair<int, int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
    return bestMove;
}

bool checkWin(char player) {
    return evaluate() == (player == 'O' ? 10 : -10);
}

int main() {
    cout << "🎮 Tic-Tac-Toe vs AI (You = X, AI = O)\n";
    printBoard();

    while (true) {
        int x, y;
        cout << "Enter your move (row and column: 0-2): ";
        cin >> x >> y;
        if (board[x][y] != ' ') {
            cout << "❌ Invalid move. Try again.\n";
            continue;
        }
        board[x][y] = 'X';
        printBoard();

        if (checkWin('X')) {
            cout << "🎉 You win!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "🤝 It's a draw!\n";
            break;
        }

        pair<int, int> aiMove = findBestMove();
        board[aiMove.first][aiMove.second] = 'O';
        cout << "🤖 AI played:\n";
        printBoard();

        if (checkWin('O')) {
            cout << "💻 AI wins!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "🤝 It's a draw!\n";
            break;
        }
    }

    return 0;
}
