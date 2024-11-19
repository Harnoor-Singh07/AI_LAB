#include <iostream>
#include <vector>
#include <climits> 
using namespace std;

vector<int> board(9, 2);
int User = 3;
int Computer = 5;
int turn = 1;
bool userFirst = true;
int maxDepth = 8;
int recursionCount = 0;

void display() {
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) cout << endl;
        cout << (board[i] == User ? "X " : (board[i] == Computer ? "O " : "- "));
    }
    cout << endl;
}

int checkWin(const vector<int>& board, int player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) ||
            (board[i] == player && board[i + 3] == player && board[i + 6] == player)) {
            return 10;
        }
    }
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return 10;
    }
    return 0;
}

bool isDraw() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) return false;
    }
    return true;
}

vector<int> moves_left(const vector<int>& board) {
    vector<int> moves;
    for (int i = 8; i >= 0; i--) {
        if (board[i] == 2) {
            moves.push_back(i);
        }
    }
    return moves;
}

int alphaBeta(vector<int>& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    recursionCount++;
    int userWin = checkWin(board, User);
    int computerWin = checkWin(board, Computer);

    if (computerWin == 10) return 10 - depth;
    if (userWin == 10) return depth - 10;
    if (isDraw()) return 0;

    vector<int> moves = moves_left(board);

    if (maximizingPlayer) { 
        int bestScore = INT_MIN;
        for (int move : moves) {
            board[move] = Computer;
            int score = alphaBeta(board, depth + 1, alpha, beta, false);
            board[move] = 2;
            bestScore = max(bestScore, score);
            alpha = max(alpha, bestScore);
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return bestScore;
    } else { 
        int bestScore = INT_MAX;
        for (int move : moves) {
            board[move] = User;
            int score = alphaBeta(board, depth + 1, alpha, beta, true);
            board[move] = 2;
            bestScore = min(bestScore, score);
            beta = min(beta, bestScore);
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return bestScore;
    }
}

void computerTurn() {
    int bestScore = INT_MIN;
    int bestMove = -1;
    for (int move : moves_left(board)) {
        board[move] = Computer;
        int score = alphaBeta(board, 0, INT_MIN, INT_MAX, false);
        board[move] = 2;
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    if (bestMove != -1) {
        board[bestMove] = Computer;
    }
}

void userTurn() {
    int n;
    while (true) {
        cout << "Enter the block number for your move (1-9): ";
        cin >> n;
        if (n >= 1 && n <= 9 && board[n - 1] == 2) {
            board[n - 1] = User;
            break;
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
    }
}

int main() {
    cout << "Do you want to play first? (yes/no): ";
    string choice;
    cin >> choice;
    userFirst = (choice == "yes");

    while (turn <= 9) {
        display();
        if ((turn % 2 == 1 && userFirst) || (turn % 2 == 0 && !userFirst)) {
            userTurn();
        } else {
            cout << endl << "Computer's move:" << endl;
            computerTurn();
            display();
        }

        int userResult = checkWin(board, User);
        int computerResult = checkWin(board, Computer);
        if (userResult == 10) {
            cout << "User wins!" << endl;
            break;
        } else if (computerResult == 10) {
            cout << "Computer wins!" << endl;
            break;
        } else if (isDraw()) {
            cout << "It's a draw!" << endl;
            break;
        }
        turn++;
    }
    cout << "Total recursion steps: " << recursionCount << endl;
    return 0;
}
