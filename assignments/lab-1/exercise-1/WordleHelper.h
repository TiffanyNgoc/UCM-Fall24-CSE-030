#ifndef WORDLE_HELPER_H
#define WORDLE_HELPER_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

class WordleHelper{
 
    std::vector<std::string> allowed;
    std::vector<std::string> answers;

    std::vector<std::string> green;
    std::vector<std::string> yellow;
    std::vector<std::string> gray;


    bool contains(std::string word, char c){
        for (int i = 0; i < word.length(); i++){
            if (word[i] == c){
                return true;
            }
        }

        return false;
    }

public:
    WordleHelper(){
        std::string answersFile = "answers.txt";
        std::string allowedFile = "allowed.txt";

        std::fstream newfile;

        newfile.open(answersFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                answers.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + answersFile + ".");
        }

        newfile.open(allowedFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                allowed.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + allowedFile + ".");
        }
    }

    void addGreen(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Green feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Green feedback must contain only lowercase letters or underscores");
        }

        green.push_back(feedback);
    }

    void addYellow(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Yellow feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters or underscores");
        }

        yellow.push_back(feedback);
    }

    void addGray(std::string feedback){
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c < 'a' && c > 'z';
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters");
        }

        gray.push_back(feedback);
    }

    std::vector<std::string>possibleSolutions(){
        // Your code here...
        std::vector<std::string> possible; // Vector to store valid solutions

        // Iterate over each word in the answers list
        for (const auto& word : answers) {
            bool valid = true;

            // Check the green constraints
            for (size_t i = 0; i < green.size(); i++) {
                const std::string& greenWord = green[i];
                for (int j = 0; j < 5; j++) {
                    if (greenWord[j] != '_' && word[j] != greenWord[j]) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }

            if (!valid) continue; // Skip word if it doesn't match green constraints

            // Check the yellow constraints (literally same thing)
            for (size_t i = 0; i < yellow.size(); i++) {
                const std::string& yellowWord = yellow[i];
                for (int j = 0; j < 5; j++) {
                    if (yellowWord[j] != '_') {
                        // The letter must be present in the word but not in the same position
                        if (word[j] == yellowWord[j] || !contains(word, yellowWord[j])) {
                            valid = false;
                            break;;
                        }
                    }
                }
                if (!valid) break;
            }

            if (!valid) continue; // Skip word if it doesn't match yellow constraints

            // Check the gray constraints
            for (size_t i = 0; i < gray.size(); i++) {
                for (char grayLetter : gray[i]) {
                    if (contains(word, grayLetter)) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }

            // If the word is valid, add it to the possible solutions
            if (valid) {
                possible.push_back(word);
            }
        }
        return possible;
        // return {"these", "words", "there"};
    }

    std::vector<std::string> suggest(){
        // Optionally, your code here...
        return {"bring", "words", "close"};
    }

    ~WordleHelper(){

    }

    friend struct WordleTester;

};

#endif
