#pragma once
#include <fstream>
#include <string>

void WriteScore(int score){

    std::ofstream file;
    file.open("score.txt", std::ios::out);

    if (file.is_open()) {
        file << score;
        file.close();
    }
}

int ReadScore(){
    std::fstream file;
    file.open("score.txt", std::ios::in);
    int score = -1;
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        score = std::stoi(line);
        
        file.close(); 
    }return score;
}