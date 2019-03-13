#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <queue>

using namespace std;

const char verticesNames[5] = { 'A', 'B', 'C', 'D', 'E'};
vector<vector<int> > directedMatrix;
vector<vector<int> > undirectedMatrix;  
vector<vector<int> > directedList;  
vector<vector<int> > undirectedList;    

void loadMatrix() {
    string line;
    ifstream matrixStream("graphMatrix_directed.txt");
    
    if(!matrixStream) {
        cout << "Error\n";
        return;
    }

    while(getline(matrixStream, line)) {
        directedMatrix.push_back(vector<int>());
        undirectedMatrix.push_back(vector<int>());

        for(int i=0; i < line.size(); i++) {
            if (line[i] != 32) {
                directedMatrix.back().push_back((int)line[i] - (int)'0');
                undirectedMatrix.back().push_back(0);
            }            
        }
    }

    for (int i = 0; i < directedMatrix.size(); i++) {
        for (int j = 0; j < directedMatrix[i].size(); j++) {
            if (directedMatrix[i][j] == 1) {
                undirectedMatrix[i][j] = 1;
                undirectedMatrix[j][i] = 1;
            }
        }
    }

    
    ifstream listStream("graphList_directed.txt");
    
    if(!listStream) {
        cout << "Error\n";
        return;
    }

    while(getline(listStream, line)) {
        directedList.push_back(vector<int>());
        undirectedList.push_back(vector<int>());

        for(int i = 0; i < line.size(); i++) {
            if (line[i] != 32) {
                directedList.back().push_back((int)line[i] - (int)'0');
            }         
        }
    }

    for (int i = 0; i < directedList.size(); i++) {
        undirectedList[i].push_back(directedList[i][0]);
    }
    for (int i = 0; i < directedList.size(); i++) {        
        for (int j = 0; j < directedList[i].size(); j++) {
            if (j > 0) {
                undirectedList[i].push_back(directedList[i][j]);
                undirectedList[directedList[i][j]].push_back(directedList[i][0]);
                
            }
        }
    }

}

void printGraph(vector <vector<int> > graph) {
    cout << "-------------\n";
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++)
            cout << graph[i][j] << ' ';
        cout << '\n';
    }
    cout << "-------------\n";

}

void bfs_matrix(vector <vector<int> > graph, int start) {
    queue<int> q;
    int n = graph.size();
    q.push(start);
    vector<bool> used (n);
    vector<int> d(n), p(n);
    used[start] = true;
    p[start] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i=0; i<graph[v].size(); ++i) {
            int to = graph[v][i];
            if (!used[to]) {
                used[to] = true;
                q.push (to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }   

    for (int i = 0; i < used.size(); i++) {
        cout << used[i] << "-->";
    }


}

int main() {
    char switcher;
    loadMatrix();
    while(switcher != 27) {
        system("cls");
        cout << "1 - Matrix (Directed)\n"
            << "2 - Matrix (Undirected)\n"
            << "3 - List (Directed)\n"
            << "4 - List (Undirected)\n"
            << "ESC - Quit\n";
        switcher = getch();

        switch(switcher) {
            case '1': 
                printGraph(directedMatrix);
                bfs_matrix(directedMatrix, 2);
            break;
            case '2': 
                printGraph(undirectedMatrix);
                bfs_matrix(undirectedMatrix, 0);
            break;
            case '3': 
                printGraph(directedList);
            break;
            case '4': 
                printGraph(undirectedList);
            break;
        }
        system("pause");

    }
    
    return 0;
}