#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> board(9, 2); 

void display() {
    int i = 0;
    while (i < 9) {
        if (i == 3 || i == 6) cout << endl;
        cout << (board[i] == 3 ? "X " : (board[i] == 5 ? "O " : "- "));
        i++;
    }
    cout << endl;
}

int checkWin(const vector<int>& board) {
    int i = 0;
    while (i < 3) {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            if (board[i * 3] == 3) return 10; 
            else if (board[i * 3] == 5) return -10; 
        }
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == 3) return 10; 
            else if (board[i] == 5) return -10; 
        }
        i++;
    }
    
    if (board[0] == board[4] && board[4] == board[8]) {
        if (board[0] == 3) return 10; 
        else if (board[0] == 5) return -10; 
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        if (board[2] == 3) return 10; 
        else if (board[2] == 5) return -10; 
    }

    return 0; 
}

bool isDraw() {
    int i = 0;
    while (i < 9) {
        if (board[i] == 2) return false; 
        i++;
    }
    return true; 
}

int rate(const vector<int>& b) {
    int score = 0;
    
    if (b[4] == 3) score += 4; 
    if (b[4] == 5) score -= 4; 

    int corners[] = {b[0], b[2], b[6], b[8]};
    int i = 0;
    while (i < 4) {
        if (corners[i] == 3) score += 3; 
        if (corners[i] == 5) score -= 3;
        i++;
    }

    int edges[] = {b[1], b[3], b[5], b[7]};
    i = 0;
    while (i < 4) {
        if (edges[i] == 3) score += 1;
        if (edges[i] == 5) score -= 1;
        i++;
    }

    return score;
}

vector<int> move_gen(const vector<int>& board) {
    vector<int> moves;
    int i = 0;
    while (i < 9) {
        if (board[i] == 2) {
            moves.push_back(i);
        }
        i++;
    }
    return moves;
}

int minimax(vector<int>& board, int depth, bool isMaximizing, int maxDepth) {
    int score = checkWin(board);
    if (score != 0) return score; 
    if (isDraw()) return 0; 
    if (depth >= maxDepth) return rate(board); 

    if (isMaximizing) {
        int bestScore = -1000;
        vector<int> moves = move_gen(board);
        int i = 0;
        while (i < moves.size()) {
            board[moves[i]] = 3; 
            bestScore = max(bestScore, minimax(board, depth + 1, false, maxDepth));
            board[moves[i]] = 2; 
            i++;
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        vector<int> moves = move_gen(board);
        int i = 0;
        while (i < moves.size()) {
            board[moves[i]] = 5; 
            bestScore = min(bestScore, minimax(board, depth + 1, true, maxDepth));
            board[moves[i]] = 2; 
            i++;
        }
        return bestScore;
    }
}

void computermove(int maxDepth) {
    int bestScore = -1000;
    int bestMove = -1;
    int i = 0;
    while (i < 9) {
        if (board[i] == 2) {
            board[i] = 3; 
            int score = minimax(board, 0, false, maxDepth);
            board[i] = 2; 
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
        i++;
    }
    if (bestMove != -1) {
        board[bestMove] = 3; 
    }
    display();
    if (checkWin(board) == 10) {
        cout << "Computer (X) wins!" << endl;
    } else if (isDraw()) {
        cout << "It's a draw!" << endl;
    }
}

void usermove() {
    int n;
    while (true) {
        cout << endl;
        cout << "Enter the block number for your move (1-9): ";
        cin >> n;

        n--; 
        if (board[n] == 2) {
            board[n] = 5; 
            display();
            if (checkWin(board) == -10) {
                cout << "You (O) win!" << endl;
                return; 
            }
            if (isDraw()) {
                cout << "It's a draw!" << endl;
                return; 
            }
            cout << endl << "Computer's move:" << endl;
            computermove(5); 
            if (checkWin(board) == 10) {
                cout << "Computer (X) wins!" << endl;
                return; 
            }
            if (isDraw()) {
                cout << "It's a draw!" << endl;
                return; 
            }
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
    }
}

int main() {
    char firstMove;
    cout << "Do you want to move first? (y/n): ";
    cin >> firstMove;

    if (firstMove == 'y' || firstMove == 'Y') {
        usermove(); 
    } else {
        computermove(1); 
        usermove(); 
    }

    return 0;
}
