#include <iostream>
#include <stdexcept>
#include <string>
#include "ArrayList.h"
#include "TimeSupport.h"

using namespace std;

string reverse(string& word){
    string result = "";

    for (int i = word.length()-1; i >= 0; i--){
        result += word[i];
    }

    return result;
}

struct Node{
    string data;
    Node* left;
    Node* right;

    Node(){
        data = "";
        left = nullptr;
        right = nullptr;
    }
    Node(string s){
        data = s;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, std::string data){
    if (root == nullptr){
        root = new Node(data);
    }
    else {
        if (data < root->data){
            root->left = insert(root->left, data);
        }
        else{
            root->right = insert(root->right, data);
        }
    }

    return root;
}

bool search(Node* root, std::string value){
    if (root == nullptr){
        return false;
    }
    else{
        if (root->data == value){
            return true;
        }
        else if (value < root->data){
            return search(root->left, value);
        }
        else {
            return search(root->right, value);
        }
    }
}

string findMin(Node* root){
    if (root == nullptr){
        throw logic_error("Can't find the min of an empty tree");
    }
    else{
        if (root->left == nullptr){
            return root->data;
        }
        else {
            return findMin(root->left);
        }
    }
}


int main(){

    ArrayList<string> words;
    Node* root = nullptr;

    string word;
    while (getline(cin, word)){
        words.append(word);
        root = insert(root, word);
    }

    Timestamp start;

    int count = 0;
    for (int i = 0; i < words.size(); i++){
        string current = words[i];
        string inverse = reverse(current);

        if (search(root, inverse)){
            count++;
        }
    }

    Timestamp end;

    string s = root->data;

    // Increase the number of searches by a lot compared to before
    for (int x = 0; x < 100000; x++){
        s = findMin(root);
    }

    Timestamp findMinEnd;

    int findMinDuration = findMinEnd - end;

    cout << "Count: " << count << " words." << endl;
    cout << "Duration: " << end - start << " ms." << endl;
    cout << "Min was: " << s << endl;
    cout << "Took " << findMinDuration << " ms.  to find min" << endl;

    return 0;
}