#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>

void loadMatrix(std::string filename, bool directed = true) {
    std::vector<std::vector<int> > data;
    std::string line;
    std::ifstream in(filename.c_str());
    
    if(!in) {
        std::cout << "Error\n";
        return;
    }

    while(std::getline(in, line)) {
        data.push_back(std::vector<int>());
        for(int i=0; i<line.size(); i++){
            if (line[i] != 32)
            data.back().push_back((int)line[i] - (int)'0');
        }
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++)
            std::cout << data[i][j] << ' ';
        std::cout << '\n';
    }
}

int main() {
    char switcher;
    std::string fileNames[4] = {
        "graphMatrix_directed.txt",
        "graphMatrix_not_directed.txt",
        "graphList_directed.txt",
        "graphList_not_directed.txt"
    };

    while(switcher != 27) {
        system("cls");
        std::cout << "1 - Matrix (Directed)\n"
            << "2 - Matrix (Undirected)\n"
            << "3 - List (Directed)\n"
            << "4 - List (Undirected)\n"
            << "ESC - Quit\n";
        switcher = getch();
        int switcherToIndex = switcher - '0' - 1;
        if (switcherToIndex >= 0 && switcherToIndex < 4) {
            std::cout << "-------------\n";
            loadMatrix(fileNames[switcherToIndex]);
            std::cout << "-------------\n";
            system("pause");
        }
    }
    
    return 0;
}