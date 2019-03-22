#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <stack>

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
            if (i == 0) continue;
            if (line[i] != 32) {
                directedList.back().push_back((int)line[i] - (int)'0');
            }         
        }
    }

    for (int i = 0; i < directedList.size(); i++) {        
        for (int j = 0; j < directedList[i].size(); j++) {
                undirectedList[i].push_back(directedList[i][j]);
                undirectedList[directedList[i][j]].push_back(i);
            
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
    vector<int> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = 0;
    }
    q.push(start);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        nodes[node] = 2;//Посещена
        for (int i = 0; i < n; i++) {
            if (graph[node][i] == 1 && nodes[i] == 0) {
                q.push(i);
                nodes[i] = 1;//Обнаружена
            }
        }
        cout << verticesNames[node] << " ";
    }
    cout << endl;   
}

void dfs_matrix(vector <vector<int> > graph, int start) {
    int n = graph.size(); 
    stack<int> s;
    vector<bool> visited(n, false);
    s.push(start);
    while (!s.empty()) {
        start = s.top();
        s.pop();
        if (!visited[start]) {
            cout << verticesNames[start] << " ";
            visited[start] = true;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[start][i] != 0) {
                s.push(i);
            }
        }
    }
    cout << endl;   
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
                cout << "BFS:\n";
                for (int i = 0; i < 5; i++)
                    bfs_matrix(directedMatrix, i);
                cout << "DFS:\n";
                for (int i = 0; i < 5; i++)
                    dfs_matrix(directedMatrix, i);
            break;
            case '2': 
                printGraph(undirectedMatrix);
                cout << "BFS:\n";
                for (int i = 0; i < 5; i++)
                    bfs_matrix(undirectedMatrix, i);
                cout << "DFS:\n";
                for (int i = 0; i < 5; i++)
                    dfs_matrix(undirectedMatrix, i);
            break;
            case '3': 
                printGraph(directedList);
                // cout << "BFS:\n";
                // for (int i = 0; i < 5; i++)
                //     bfs_matrix(directedList, i);
                // cout << "DFS:\n";
                // for (int i = 0; i < 5; i++)
                //     dfs_matrix(directedList, i);
            break;
            case '4': 
                printGraph(undirectedList);
                // cout << "BFS:\n";
                // for (int i = 0; i < 5; i++)
                //     bfs_matrix(undirectedList, i);
                // cout << "DFS:\n";
                // for (int i = 0; i < 5; i++)
                //     dfs_matrix(undirectedList, i);
            break;
        }
        system("pause");
    }    
    return 0;
}