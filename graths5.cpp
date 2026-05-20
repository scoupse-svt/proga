//Дан неориентированный взвешенный граф.
//Найти кратчайшее расстояние от заданной вершины до всех остальных.
//Вывести длину пути и сам путь.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // для INT_MAX
using namespace std;

vector<vector<pair<int, int>>> Gr;  // список смежности
int n;                               

void addEdge(int u, int v, int w) { //новая характеристика w - вес
    Gr[u].push_back({v, w});    
    Gr[v].push_back({u, w});    
}

void print() {
    for (int i = 0; i < n; i++) {
        cout << "Вершина " << i << " : ";
        if (Gr[i].empty()) {
            cout << "(нет соседей)";
        }
        for (int j = 0; j < Gr[i].size(); j++) {
            cout << "(" << Gr[i][j].first << "," << Gr[i][j].second << ") ";
        }
        cout << endl;
    }
}

vector<int> getpath(int finish, vector<int>& prev) {
    vector<int> path;
    int v = finish;
    
    // идём от конечной вершины к начальной по prev
    while (v != -1) {
        path.push_back(v);
        v = prev[v];
    }
    
    reverse(path.begin(), path.end());
    return path;
}

//алгоритм дейкстры (для поиска кратчайших расстояний)
void dikstra(int start) {
    // минимальное расстояние от start до i
    vector<int> dist(n, INT_MAX);
    
    // вершина на кратчайшем пути к i
    vector<int> prev(n, -1);
    
    //обработана ли вершина i
    vector<bool> visited(n, false);
    
    // расстояние до стартовой вершины = 0
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        // находим непосещённую вершину с минимальным расстоянием
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        
        // если нет доступных вершин (остальные недостижимы)
        if (dist[v] == INT_MAX) break;
    
        visited[v] = true;
        
        for (int j = 0; j < Gr[v].size(); j++) {
            int u = Gr[v][j].first;   // соседняя вершина
            int w = Gr[v][j].second;  // вес ребра
            
            // если путь через v короче, чем уже известный
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                prev[u] = v;          // запоминаем, откуда пришли
            }
        }
    }
    

    cout << "Кратчайшие расстояния от вершины " << start << ":\n";
    
    for (int i = 0; i < n; i++) {
        if (i == start) continue;  // пропускаем стартовую вершину
        
        if (dist[i] == INT_MAX) {
            cout << "Вершина " << i << ": недостижима\n";
        } 
        else {
            vector<int> path = getpath(i, prev);
            
            cout << "Вершина " << i << ": расстояние = " << dist[i];
            cout << ", путь: ";
            for (int j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j < path.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    
    n = 6;
    Gr.resize(n);
    
    addEdge(0, 1, 2);   // 0-1 вес 2 и тд
    addEdge(0, 2, 4);   
    addEdge(0, 3, 1);   
    addEdge(1, 3, 3);   
    addEdge(1, 4, 7);   
    addEdge(2, 5, 2);   
    addEdge(3, 5, 5);  
    addEdge(3, 4, 1);   
    addEdge(4, 5, 3);   
    
    print();
    
    int start;
    cout << "\nВведите начальную вершину (0..." << n-1 << "): ";
    cin >> start;
    
    dikstra(start);
}