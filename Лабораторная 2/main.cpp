#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std;

const char verticesNames[5] = { 'A', 'B', 'C', 'D', 'E'};
vector<vector<int> > directedMatrix;
vector<vector<int> > undirectedMatrix;  
vector<vector<int> > directedList;  
vector<vector<int> > undirectedList;

vector<vector<int> > incidenceMatrix;
int vCounter = 0;
int eCounter = 0;

void print_incidence_matrix() {
    cout << "\n ";
    for (int i = 0; i < eCounter; i++) {
        cout << setw(2) << 'E' << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < vCounter; ++i) {
        cout <<  verticesNames[i];
        for (int j = 0; j <	 eCounter; ++j) {
            cout << setw(3) << incidenceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void makeIncidenceMatrix__matrix(vector<vector<int> > adjMatrix) {
    for (int i = 0; i < vCounter; ++i) {
        incidenceMatrix.push_back(vector<int>(eCounter));
        for (int j = 0; j < eCounter; ++j) {
            incidenceMatrix[i][j] = 0;
        }
    }

    int edge = 0;

    for (int i = 0; i < vCounter; ++i) {
        for (int j = 0; j < i; ++j) {
            if (adjMatrix[i][j] == 1 && adjMatrix[j][i] == 0) {
                incidenceMatrix[i][edge] = 1;
                incidenceMatrix[j][edge++] = -1;
            }
            else if (adjMatrix[i][j] == 0 && adjMatrix[j][i] == 1) {
                incidenceMatrix[i][edge] = -1;
                incidenceMatrix[j][edge++] = 1;
            }
        }
    }
}


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

        for(int i = 0; i < line.size(); i++) {
            if (line[i] != 32) {
                directedMatrix.back().push_back((int)line[i] - (int)'0');
                undirectedMatrix.back().push_back(0);
            }            
        }
    }

    vCounter = directedMatrix.size();
    for (int i = 0; i < vCounter; ++i) {
        for (int j = 0; j <	 i; ++j) {
            if (directedMatrix[i][j] || directedMatrix[j][i]) {
                eCounter++;
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

void printGraphMatrix(vector <vector<int> > graph) {
    cout << "\n  ";
    for (int i = 0; i < graph.size(); i++) {
        cout << verticesNames[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << verticesNames[i] << ' ';
        for (int j = 0; j < graph[i].size(); j++)
            cout << graph[i][j] << ' ';
        cout << '\n';
    }
}

void bfs_matrix(vector <vector<int> > graph, int startNode) {
    int n = graph.size();
    queue<int> q;
    vector<bool> visited(n, false);
    q.push(startNode);
    while (!q.empty()) {
        startNode = q.front();
        q.pop();
        if (!visited[startNode]) {
            cout << verticesNames[startNode] << " ";
            visited[startNode] = true;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[startNode][i] != 0) {
                q.push(i);
            }
        }
    }
    cout << endl;   
}

void dfs_matrix(vector <vector<int> > graph, int startNode) {
    int n = graph.size(); 
    stack<int> s;
    vector<bool> visited(n, false);
    s.push(startNode);
    while (!s.empty()) {
        startNode = s.top();
        s.pop();
        if (!visited[startNode]) {
            cout << verticesNames[startNode] << " ";
            visited[startNode] = true;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[startNode][i] != 0) {
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
                cout << "\nAdjacency matrix:";
                printGraphMatrix(directedMatrix);
                cout << "\nIncidence matrix:";
                makeIncidenceMatrix__matrix(directedMatrix);
                print_incidence_matrix();
                cout << "\nBFS:\n";
                for (int i = 0; i < 5; i++)
                    bfs_matrix(directedMatrix, i);
                cout << "\nDFS:\n";
                for (int i = 0; i < 5; i++)
                    dfs_matrix(directedMatrix, i);
            break;
            case '2': 
                printGraphMatrix(undirectedMatrix);
                cout <<"\nBFS:\n";
                for (int i = 0; i < 5; i++)
                    bfs_matrix(undirectedMatrix, i);
                cout << "\nDFS:\n";
                for (int i = 0; i < 5; i++)
                    dfs_matrix(undirectedMatrix, i);
            break;
            case '3': 
                //printGraph(directedList);
                // cout << "BFS:\n";
                // for (int i = 0; i < 5; i++)
                //     bfs_matrix(directedList, i);
                // cout << "DFS:\n";
                // for (int i = 0; i < 5; i++)
                //     dfs_matrix(directedList, i);
            break;
            case '4': 
                //printGraph(undirectedList);
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