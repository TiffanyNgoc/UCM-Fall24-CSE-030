#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main(){
    
    BinarySearchTree myTree;

    myTree.insert(5);
    myTree.insert(3);
    myTree.insert(7);
    myTree.insert(1);

    myTree.draw();

    myTree.traverse();

    return 0;
}