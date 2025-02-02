#ifndef BST_H
#define BST_H
#include <cstddef>
#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int x){
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree{
    Node* root;

    Node* search_helper(Node* r, int x){
        if (r == nullptr){
            return nullptr;
        }
        else{
            if (r->data == x){
                return r;
            }
            else{
                if (x < r->data){
                    return search_helper(r->left, x);
                }
                else{
                    return search_helper(r->right, x);
                }
            }
        }
    }

    // A function to display the tree graphically
    void displayTree(Node* r, int level, int direction){
        // Don't worry about this function, just use it
        if (r != NULL){
            displayTree(r->right, level+1, 1);
            
            for (int i = 0; i < level-1; i++) {
                std::cout << "   ";
            }
            if (level > 0 ){
                if (direction == 1){
                    std::cout << " /--";
                }
                else{
                    std::cout << " \\--";
                }
            }
            std::cout << r->data;
            std::cout << std::endl;
            level++;
            
            displayTree(r->left, level, -1);
        }
    }

    Node* insert_helper(Node* root, int data){
        if (root == nullptr){
            root = new Node(data);
        }
        else {
            if (data < root->data){
                root->left = insert_helper(root->left, data);
            }
            else{
                root->right = insert_helper(root->right, data);
            }
        }

        return root;
    }

    Node* min_helper(Node* root){
        if (root == nullptr){
            throw std::logic_error("Can't find the min of an empty tree");
        }
        else{
            if (root->left == nullptr){
                return root;
            }
            else {
                return min_helper(root->left);
            }
        }
    }

    void traverse_helper(Node* root){
        if (root != nullptr){
            traverse_helper(root->left);
            std::cout << root->data << " ";
            traverse_helper(root->right);
        }
    }
    
public:
    BinarySearchTree(){
        root = nullptr;
    }

    BinarySearchTree(const BinarySearchTree& other){
        // Your code here

        // In here we need to implement a correct copy constructor
        // which results in a deep (independent) copy
        // This requires the tree to be reconstructed to appear as the other one
    }

    void insert(int x){
        // Your code here
        root = insert_helper(root, x);
        //             ^
        //             |
        //     This returns: new Node(...);
    }

    void traverse(){
        // Your code here
        traverse_helper(root);
        std::cout << std::endl;
    }

    Node* search(int x){
        return search_helper(root, x);
    }

    Node* min(){
        // Your code here
        return min_helper(root);
    }

    Node* max(){
        // Your code here
        return nullptr;
    }

    Node* successor(Node* start){
        if (start == nullptr){
            return nullptr;
        }
        if (start->right == nullptr){
            Node* parent = findParent(start);
            if (parent == nullptr){
                return nullptr;
            }
            else{
                while (parent != nullptr && start == parent->right) {
                    start = parent;
                    parent = findParent(start);
                }
                return parent;
            }
        }
        else{
            return min_helper(start->right);
        }
    }

    Node* findParent(Node* start){
        if (start == nullptr){
            return nullptr;
        }
        if (start == root){
            return nullptr;
        }

        Node* temp = root;
        Node* parent = root;

        while (temp != start){
            parent = temp;
            if (start->data < temp->data){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        return parent;
    }

    void remove(Node* node){
        // Your code here...
        if (node->left == nullptr && node->right == nullptr){
            // Node has no children
        }
        else if (node->left != nullptr && node->right == nullptr){
            // Node has only a left child
        }
        else if (node->left == nullptr && node->right != nullptr){
            // Node has only a right child
        }
        else if (node->left != nullptr && node->right != nullptr){
            // Node has both children
        }
    }

    // Call the function to display the tree and leave some space afterwards
    void draw(){
        displayTree(root, 0, 0);
        std::cout << std::endl << std::endl;
    }

};

#endif