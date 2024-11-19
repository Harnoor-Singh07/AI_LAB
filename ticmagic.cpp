#include <iostream>
#include <vector>
using namespace std;

vector<int> board(10, 2);
int turn = 1; 
bool userStarts = false; 

void printBoard() {
    for (int i = 1; i <= 9; i++) {
        if (board[i] == 2) cout << "_ "; 
        else if (board[i] == 3) cout << "X "; 
        else if (board[i] == 5) cout << "O "; 

        if (i % 3 == 0) cout << endl; 
    }
    cout << endl;
}

bool checkWin(int p) {
    int magicSquare[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};

    vector<int> playerMoves;

    for (int i = 1; i <= 9; i++) {
        if (board[i] == p) {
            playerMoves.push_back(magicSquare[i - 1]);
        }
    }

    int size = playerMoves.size();
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            for (int k = j + 1; k < size; k++) {
                if (playerMoves[i] + playerMoves[j] + playerMoves[k] == 15) {
                    return true;
                }
            }
        }
    }
    return false;
}

int posswin(int p) {
    int winPatterns[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, 
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, 
        {1, 5, 9}, {3, 5, 7}
    };
    for (int i = 0; i < 8; i++) {
        int product = board[winPatterns[i][0]] * board[winPatterns[i][1]] * board[winPatterns[i][2]];
        if (product == p * p * 2) {
            for (int j = 0; j < 3; j++) {
                if (board[winPatterns[i][j]] == 2) {
                    return winPatterns[i][j];
                }
            }
        }
    }
    return 0;
}

void go(int n) {
    board[n] = (turn % 2 == 1) ? 3 : 5; 
    turn++;
}

int make2() {
    if (board[5] == 2) return 5; 
    int possibleSquares[4] = {2, 4, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[possibleSquares[i]] == 2) {
            return possibleSquares[i];
        }
    }
    return 0;
}

void play() {
    int move;
    if (turn % 2 == 1 && userStarts) {
        int userMove;
        cout << "Your turn (X). Enter the position (1-9): ";
        cin >> userMove;
        while (board[userMove] != 2) {
            cout << "Invalid move! Choose an empty square: ";
            cin >> userMove;
        }
        go(userMove);
    }
    else if (turn % 2 == 0 && !userStarts) {
        int userMove;
        cout << "Your turn (O). Enter the position (1-9): ";
        cin >> userMove;
        while (board[userMove] != 2) {
            cout << "Invalid move! Choose an empty square: ";
            cin >> userMove;
        }
        go(userMove);
    }
    else {
        if (turn == 1) go(1);
        else if (turn == 2) {
            if (board[5] == 2) go(5);
            else go(1);
        }
        else if (turn == 3) {
            if (board[9] == 2) go(9);
            else go(3);
        }
        else if (turn == 4) {
            if ((move = posswin(3)) != 0) go(move);
            else if ((move = posswin(5)) != 0) go(move);
            else go(make2());
        }
        else if (turn == 5) {
            if ((move = posswin(3)) != 0) go(move);
            else if ((move = posswin(5)) != 0) go(move);
            else if (board[7] == 2) go(7);
            else go(3);
        }
        else if (turn == 6) {
            if ((move = posswin(5)) != 0) go(move);
            else if ((move = posswin(3)) != 0) go(move);
            else go(make2());
        }
        else if (turn == 7 || turn == 9) {
            if ((move = posswin(3)) != 0) go(move);
            else if ((move = posswin(5)) != 0) go(move);
            else for (int i = 1; i <= 9; i++) if (board[i] == 2) { go(i); break; }
        }
        else if (turn == 8) {
            if ((move = posswin(5)) != 0) go(move);
            else if ((move = posswin(3)) != 0) go(move);
            else for (int i = 1; i <= 9; i++) if (board[i] == 2) { go(i); break; }
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe Game\n";
    char choice;
    cout << "Do you want to start the game? (y/n): ";
    cin >> choice;
    userStarts = (choice == 'y' || choice == 'Y');

    while (turn <= 9) {
        printBoard();
        play();
        if (checkWin(3)) { printBoard(); cout << "X wins!\n"; break; }
        if (checkWin(5)) { printBoard(); cout << "O wins!\n"; break; }
    }

    if (turn == 10) {
        printBoard();
        cout << "It's a draw!\n";
    }

    return 0;
}
