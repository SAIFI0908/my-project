#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ---------- Board Class ----------
class Board {
private:
    char grid[3][4];
    bool revealed[3][4];
    int safeCount;

public:
    Board() {
        safeCount = 0;

        // initialize board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                grid[i][j] = 'S';
                revealed[i][j] = false;
            }
        }

        // place 2 bombs
        int bombs = 0;
        while (bombs < 2) {
            int r = rand() % 3;
            int c = rand() % 4;

            if (grid[r][c] != 'B') {
                grid[r][c] = 'B';
                bombs++;
            }
        }
    }

    void display() {
        int num = 1;

        cout << "\n+----+----+----+----+\n";

        for (int i = 0; i < 3; i++) {
            cout << "|";
            for (int j = 0; j < 4; j++) {
                if (revealed[i][j])
                    cout << " " << grid[i][j] << "  |";
                else {
                    if (num < 10)
                        cout << " " << num << "  |";
                    else
                        cout << " " << num << " |";
                }
                num++;
            }
            cout << "\n+----+----+----+----+\n";
        }
    }

    int checkCell(int cell) {
        if (cell < 1 || cell > 12)
            return -1;

        int row = (cell - 1) / 4;
        int col = (cell - 1) % 4;

        if (revealed[row][col])
            return -1;

        revealed[row][col] = true;

        if (grid[row][col] == 'B')
            return 1;

        safeCount++;
        return 0;
    }

    bool win() {
        return safeCount == 10;
    }

    void revealAll() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                revealed[i][j] = true;
    }
};

// ---------- Game Class ----------
class Game {
private:
    Board b;
    int score;

public:
    Game() {
        score = 0;
    }

    void header() {
        cout << "=================================\n";
        cout << "       BOMB DODGE GAME\n";
        cout << "=================================\n";
        cout << " B = Bomb (Lose)\n";
        cout << " S = Safe (+1 Score)\n";
        cout << " Find all safe cells to win!\n";
        cout << "=================================\n";
    }

    void play() {
        int choice;

        header();

        while (true) {
            cout << "\nCurrent Score = " << score << endl;

            b.display();

            cout << "\nEnter cell number (1-12): ";
            cin >> choice;

            int result = b.checkCell(choice);

            if (result == -1) {
                cout << "\nInvalid choice! Try again.\n";
            }
            else if (result == 1) {
                b.revealAll();
                b.display();

                cout << "\n***** BOOM! *****\n";
                cout << "Game Over!\n";
                cout << "Final Score = " << score << endl;
                break;
            }
            else {
                score++;
                cout << "\nSafe! Score = " << score << endl;

                if (b.win()) {
                    b.revealAll();
                    b.display();

                    cout << "\n***** YOU WIN! *****\n";
                    cout << "Final Score = " << score << endl;
                    break;
                }
            }
        }
    }
};

// ---------- Main ----------
int main() {
    srand(time(0));

    Game g;
    g.play();

    return 0;
}