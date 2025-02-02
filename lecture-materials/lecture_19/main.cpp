#include <iostream>
#include <system_error>
#include "GameState.h"
#include "Graph.h"
#include "Vertex.h"
#include "Helper.h"
#include "Queue.h"

using namespace std;

// Menu function to display the options
void menu() {
    std::cout << "Menu: 1. Play 2. Difficulty 3. Rules 4. Stats 5. Reset 6. Exit\n";
}

// Function for Human Mode gameplay
void playHumanMode(int& xWins, int& oWins) {
    std::cout << "Playing in Human Mode\n";
    // Implement gameplay logic here
}

// Function to choose the difficulty level
void chooseDifficulty() {
    std::cout << "Choose Difficulty (1: Easy, 2: Hard)\n";
    // Implement difficulty selection logic here
}

// Function to print the game rules
void printRules() {
    std::cout << "Tic Tac Toe Rules: \n";
    std::cout << "1. Two players take turns.\n";
    std::cout << "2. Player X starts the game.\n";
    std::cout << "3. The first player to get 3 in a row wins.\n";
    // Add more rules if necessary
}

int main() {
    GameState game;

    int option;
    int xWins = readStats("x");
    int oWins = readStats("o");

    // Print Menu Options
    menu();

    while (cin >> option) {
        system("clear");
        switch (option) {
            case 1:
                // User selects humanMode
                playHumanMode(xWins, oWins);
                break;
            case 2:
                // User selects between easyMode or hardMode
                chooseDifficulty();
                break;
            case 3:
                // Prints Rules of Tic-Tac-Toe
                system("clear");
                printRules();
                break;
            case 4:
                // Displays statistics page
                xWins = readStats("x");
                oWins = readStats("o");
                showStatistics(xWins, oWins);
                break;
            case 5:
                // Clears Statistics
                system("clear");
                resetStatistics();
                break;
            case 6:
                // Exits program
                system("clear");
                return 0;
        }
        menu();  // Print the menu again after performing the action
    }
    return 0;
}
