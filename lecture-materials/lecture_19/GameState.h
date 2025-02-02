#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

// Define the Vec structure here to represent coordinates
struct Vec {
    int x;
    int y;

    Vec() : x(0), y(0) {}

    Vec(int x, int y) : x(x), y(y) {}

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

std::ostream& operator<<(std::ostream& os, const Vec& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

// Forward declaration of helper function to find best move.
Vec findBestMove(GameState game);

struct GameState {
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;
    bool done;
    Vec lastMove;

    GameState() : size(3), currentTurn(0), turnCount(0), done(false), lastMove(-1, -1) {
        grid = new int*[size];
        for (int i = 0; i < size; i++) {
            grid[i] = new int[size];
            for (int j = 0; j < size; j++) {
                grid[i][j] = -1;
            }
        }
    }

    GameState(int size) : size(size), currentTurn(0), turnCount(0), done(false), lastMove(-1, -1) {
        grid = new int*[size];
        for (int i = 0; i < size; i++) {
            grid[i] = new int[size];
            for (int j = 0; j < size; j++) {
                grid[i][j] = -1;
            }
        }
    }

    GameState(const GameState& other) : size(other.size), currentTurn(other.currentTurn), turnCount(other.turnCount),
                                        done(other.done), lastMove(other.lastMove) {
        grid = new int*[size];
        for (int i = 0; i < size; i++) {
            grid[i] = new int[size];
            for (int j = 0; j < size; j++) {
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    GameState& operator=(const GameState& other) {
        if (this != &other) {
            for (int i = 0; i < size; i++) {
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;
            grid = new int*[size];
            for (int i = 0; i < size; i++) {
                grid[i] = new int[size];
                for (int j = 0; j < size; j++) {
                    grid[i][j] = other.grid[i][j];
                }
            }

            currentTurn = other.currentTurn;
            turnCount = other.turnCount;
            done = other.done;
            lastMove = other.lastMove;
        }

        return *this;
    }

    bool hasWon(int player) const {
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == player) {
                    count++;
                }
            }
            if (count == size) {
                return true;
            }
        }
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (grid[j][i] == player) {
                    count++;
                }
            }
            if (count == size) {
                return true;
            }
        }
        int mainDiagCount = 0;
        for (int i = 0; i < size; i++) {
            if (grid[i][i] == player) {
                mainDiagCount++;
            }
        }
        if (mainDiagCount == size) {
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++) {
            if (grid[i][size - 1 - i] == player) {
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size) {
            return true;
        }
        return false;
    }

    bool play(int x, int y) {
        if (grid[x][y] != -1) {
            return false;
        }

        grid[x][y] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(x, y);

        if (turnCount == size * size) {
            done = true;
        } else if (hasWon(0) || hasWon(1)) {
            done = true;
        }

        if (!currentTurn && !done) {
            Vec computerMove = findBestMove(*this);
            play(computerMove.x, computerMove.y);
        }

        return true;
    }

    bool isDone() const { 
        return done;
    }

    int getCurrentTurn() const { 
        return currentTurn; 
    }

    ~GameState() {
        for (int i = 0; i < size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
};

std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << "   ";
    for (int j = 0; j < state.size; j++) {
        os << " " << char(j + 65) << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++) {
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < state.size; i++) {
        os << i + 1 << " ";
        for (int j = 0; j < state.size; j++) {
            char c = ' ';
            if (state.grid[i][j] == 0) {
                c = 'X';
            } else if (state.grid[i][j] == 1) {
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++) {
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif
