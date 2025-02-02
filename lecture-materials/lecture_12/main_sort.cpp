#include <iostream>
#include "ArrayList.h"
#include "LinkedList.h"
#include "TimeSupport.h"
#include "RandomSupport.h"

using namespace std;

string reverse(string& word){
    string result = "";

    for (int i = word.length()-1; i >= 0; i--){
        result += word[i];
    }

    return result;
}


int main(int argc, char* argv[]){

    ArrayList<string> words;

    string word;
    while (getline(cin, word)){
        words.append(word);
    }


    Timestamp start;

    words.quick_sort();

    int count = 0;
    for (int i = 0; i < words.size(); i++){
        string inverse = reverse(words[i]);
        
        if (words.binary_search(inverse) != -1){
            count++;
        }
    }

    Timestamp end;

    int duration = end - start;
    cout << "Count: " << count << endl;
    cout << "Took " << duration << " ms." << endl;
    return 0;
}