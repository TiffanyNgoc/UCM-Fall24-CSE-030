#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "LinkedList.h"

using namespace std;

int maxReward(Vertex<GameState>* node, int player){
    if (node->edgeList.size() == 0){
        if (node->data.hasWon(player)){
            return 100;
        }
        else if (node->data.hasWon(!player)){
            return -100;
        }
        else{
            return 0;
        }
    }
    else{
        int reward = maxReward(node->edgeList[0]->to, player);
        for (int i = 1; i < node->edgeList.size(); i++){
            int curr = maxReward(node->edgeList[i]->to, player);
            if (node->data.currentTurn == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else {
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }
}

Vec findBestMove(Graph<GameState>& gameTree, Vertex<GameState>* root, int player) {
    int bestValue = -1000;
    Vec bestMove(-1, -1);

    for (int i = 0; i < root->edgeList.size(); ++i) {
        int moveValue = maxReward(root->edgeList[i]->to, player);
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = root->edgeList[i]->to->data.lastMove;
        }
    }
    return bestMove;
}

void generateGameTree(Graph<GameState>& gameTree, Vertex<GameState>* root, int depth, int maxDepth) {
    if (depth >= maxDepth || root->data.done) return;

    for (int i = 0; i < root->data.size; ++i) {
        for (int j = 0; j < root->data.size; ++j) {
            if (root->data.grid[i][j] == -1) { // Empty spot
                GameState childState = root->data;
                childState.play(i, j);
                Vertex<GameState>* childVertex = new Vertex<GameState>(childState);
                gameTree.addVertex(childVertex);
                gameTree.addDirectedEdge(root, childVertex, 0);

                generateGameTree(gameTree, childVertex, depth + 1, maxDepth);
            }
        }
    }
}


int main(){
    bool gameOver = 0;
    //bool playerFirst = 1;

    system("clear");

    while (!gameOver) {

    int gridSize;
    cout << "Enter grid size (e.g. 3 for 3x3, 4 for 4x4, etc): ";
    cin >> gridSize;

    //char alvin;
    //bool yay = 1;
    //cout << "Do you want to go first (y/n)?: ";
    //cin >> alvin;

    GameState game(gridSize);

    while (!game.done){
        system("clear");

        //if (alvin == 'n' && yay == true) {
            //Graph<GameState> gameTree; 
            //Vertex<GameState>* root = new Vertex<GameState>(game);
            //gameTree.addVertex(root);

            //generateGameTree(gameTree, root, 0, 5);

            //int bestValue = -1000;
            //Vec bestMove;

            //for (int i = 0; i < root->edgeList.size(); ++i) {
                //int value = maxReward(root->edgeList[i]->to, 1);
                //if (value > bestValue) {
                    //bestValue = value;
                    //bestMove = root->edgeList[i]->to->data.lastMove;
                //}
            //}

            //game.play(bestMove.x, bestMove.y);

            //if (game.hasWon(0) || game.hasWon(1) || game.turnCount == game.size * game.size) {
                //game.done = true;
                //break;
            //}

            //yay = false;
        //}

        cout << game << endl;

        int x, y;

        cout << "Enter coordinates (" << (game.currentTurn ? "O" : "X") << "): ";
        cin >> x >> y;

        //std::cout << x << " " << y << std::endl;

        if (x < 0 || x >= game.size || y < 0 || y >= game.size || game.grid[x][y] != -1) {
            cout << "Invalid move! Please try again." << endl;
            continue;
        }

        game.play(x,y);

        if (game.hasWon(0) || game.hasWon(1)||game.turnCount == game.size * game.size) {
            game.done = true;
            break;
        }

        Graph<GameState> gameTree; 
        Vertex<GameState>* root = new Vertex<GameState>(game);
        gameTree.addVertex(root);

        //std::cout << "test" << std::endl;

        if (gridSize <= 3) {
            generateGameTree(gameTree, root, 0, 5);
        } else if (gridSize > 3) {
            generateGameTree(gameTree, root, 0, 4);
        }

        int bestValue = -1000;
        Vec bestMove;

        for (int i = 0; i < root->edgeList.size(); ++i) {
            int value = maxReward(root->edgeList[i]->to, 1);
            if (value > bestValue) {
                bestValue = value;
                bestMove = root->edgeList[i]->to->data.lastMove;
            }
        }

        game.play(bestMove.x, bestMove.y);

        if (game.hasWon(0) || game.hasWon(1) || game.turnCount == game.size * game.size) {
            game.done = true;
            break;
        }

    }

    system("clear");
    cout << game << endl;

    if (game.hasWon(0)){
        cout << "X wins" << endl;
    }
    else if (game.hasWon(1)){
        cout << "O wins" << endl;
    }
    else {
        cout << "It's a tie" << endl;
    }
    cout << endl;
    
    bool tiffany = 0;

    while (!tiffany) {
        cout << "Do you wish to go again (y/n)?: ";

        char jet;
        cin >> jet;

        if (jet == 'n') {
            gameOver = 1;
            break;
        } else if (jet == 'y') {
            break;
        } else {
            cout << "Invalid response. Please type 'y' for yes or 'n' for no" << endl;
        }
    }

    system("clear");
}

return 0;
}