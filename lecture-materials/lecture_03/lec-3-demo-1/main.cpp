#include <iostream>
#include <string>
#include <vector>
#include "WordleHelper.h"

using namespace std;

int main(){

    WordleHelper wh;
  //             "three"
    wh.addGreen ("tak__"); 


    wh.addYellow("st___");   
    wh.addYellow("___t_");
    wh.addGray("eamboid");

    vector<string> words = wh.possibleSolutions();

    for (int i = 0; i < words.size(); i++){
        cout << words[i] << endl;
    }

    return 0;

}
