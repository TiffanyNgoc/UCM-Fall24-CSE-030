#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <ostream>
#include <fstream>
#include "GameState.h"
#include "Graph.h"
#include "Queue.h"

bool yes = false;

inline Vec validMove(GameState game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return Vec(i, j);
            }
        }
    }
    return Vec(0, 0);
}

inline Vec findBestMove(GameState game) {
    Graph<GameState> stateSpace;
    Vertex<GameState>* start = new Vertex<GameState>(game);

    stateSpace.addVertex(start);

    Queue<Vertex<GameState>*> q;
    q.enqueue(start);

    while (!q.isEmpty()) {
        Vertex<GameState>* curr = q.dequeue();
        if (!curr->data.done) {
            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (curr->data.grid[i][j] == -1) {
                        GameState next = curr->data;
                        next.play(i, j);
                        Vertex<GameState>* successor = new Vertex<GameState>(next);
                        stateSpace.addVertex(successor);
                        stateSpace.addDirectedEdge(curr, successor, 0);
                        curr->addNeighbor(successor, 0); // Add neighbor with required arguments

                        if (!successor->data.done) {
                            q.enqueue(successor);
                        }
                    }
                }
            }
        }
    }
    return Vec(0, 0);  // Return the computed move (or default)
}

inline int chooseSize() {
    int option;
    system("clear");
    while (option != 1 && option != 2) {
        std::cout << "=========================" << std::endl;
        std::cout << "       SELECT SIZE       " << std::endl;
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        std::cout << "1. 3x3" << std::endl;
        std::cout << "2. 4x4" << std::endl;
        std::cout << std::endl;
        std::cout << "SELECT AN OPTION: ";
        std::cin >> option;
    }

    switch (option) {
        case(1): return 3;
        case(2): return 4;
    }
    return 3;
}

inline int readStats(std::string player) {
    int x, o;
    std::ifstream MyReadFile("stats.txt");

    while (MyReadFile >> x >> o) {
    }

    if (player == "x") {
        return x;
    } else {
        return o;
    }
}

inline void clearStatsFile() {
    std::ofstream outFile("stats.txt", std::ofstream::trunc);
    outFile << "";
}

inline void updateStatistics(char winner) {
    int xWins = readStats("x");
    int oWins = readStats("o");

    clearStatsFile();

    if (winner == 'X') {
        xWins += 1;
    }
    else if (winner == 'O') {
        oWins += 1;
    }

    std::ofstream outFile("stats.txt", std::ios::app);
    outFile << xWins << " " << oWins;
}

inline void showStatistics(int& xWins, int& oWins) {
    system("clear");
    int x = 0;
    int o = 0;
    std::cout << "=========================" << std::endl;
    std::cout << "     STATISTICS PAGE     " << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << std::endl;
    std::cout << "Player 1 has WON " << xWins << " times" << std::endl;
    std::cout << "Player 2 has WON " << oWins << " times" << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------" << std::endl << std::endl;
    if (yes) {
        std::cout << "The statistics have been reset." << std::endl;
    }
    std::cout << "Press [ENTER] to go back to menu: ";
    std::cin.ignore();
    std::string empty;
    getline(std::cin, empty);
}

inline void resetStatistics() {
    yes = true;
    clearStatsFile();
    std::ofstream outFile("stats.txt", std::ios::app);
    outFile << "0 0";
    int xWins = 0;
    int oWins = 0;
    showStatistics(xWins, oWins);
    yes = false;
}

#endif
