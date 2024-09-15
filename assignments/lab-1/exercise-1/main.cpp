#include <iostream>
#include <string>
#include <vector>
#include "WordleHelper.h"

using namespace std;

int main(){
    WordleHelper wh;

    // Adding test case: LOFTY scenario
    cout << "Test case: LOFTY\n";

    // Input constraints (similar to TestPossibleSolutionsLofty)
    wh.addGreen("_____"); // No green letters
    wh.addYellow("____o"); // 'o' is present but not in 4th position
    wh.addGray("audi"); // 'a', 'u', 'd', 'i' are not in the word

    wh.addGreen("_o__y"); // 'o' is in the 2nd position, 'y' in the 5th position
    wh.addYellow("__tl_"); // 't' and 'l' are present but not in these position
    wh.addGray("h"); // 'h' is not in the word

    // Find possible solutions
    vector<string> solutions = wh.possibleSolutions();

    // Display the possible solutions
    if (solutions.empty()) {
        std::cout << "No possible solutions found.\n";
    } else {
        std::cout << "Possible solutions:\n";
        for (const auto& word : solutions) {
            std::cout << word << std::endl;
        }
    }

    // Adding another test case: CLASS scenario
    std::cout << "\nTest case: CLASS\n";

    // Resetting constraints for a new case
    wh = WordleHelper(); // Reset the WordlHelper object

    // Input constraints (similar to TestPossibleSolutionsClass)
    wh.addGreen("c_a__"); // 'c' in 1st position, 'a' in 3rd position
    wh.addYellow("__s__"); // 's' is present but not in the 3rd position
    wh.addGray("rnepoit"); // 'r', 'n', 'e', 'o', 'i', 't' are not in the word

    // Find possible solutions
    solutions = wh.possibleSolutions();

    // Display the possible solutions
    if (solutions.empty()) {
        std::cout << "No possible solutions found.\n";
    } else {
        std::cout << "Possible solutions:\n";
        for (const auto& word : solutions) {
            std::cout << word << std::endl;
        }
    }
    return 0;

}
