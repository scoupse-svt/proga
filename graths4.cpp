//Дан ориентированный граф. Если это возможно, 
//реализовать топологическую сортировку

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Gr;   // список смежности 
vector<bool> used;        // массив посещённых вершин
vector<int> result;        // массив для топологии
int n;                    // количество вершин

//добавление ребра для ориентированного графа
void addEdge(int u, int v) {
    for (int i = 0; i < Gr[u].size(); i++) {
        if (Gr[u][i] == v) {
            cout << "Ребро " << u << "→" << v << " уже существует!\n";
            return;
        }
    }
    Gr[u].push_back(v);
    sort(Gr[u].begin(), Gr[u].end());
}

//вывод списка смежности
void print() {
    for (int i = 0; i < n; i++) {
        cout << "Вершина " << i << " : ";
        for (int j = 0; j < Gr[i].size(); j++) {
            cout << Gr[i][j] << " ";
        }
        cout << endl;
    }
}

void dfs(int v) {
    used[v] = true;
    
    for (int i = 0; i < Gr[v].size(); i++) {
        int u = Gr[v][i];
        if (!used[u]) {
            dfs(u);
        }
    }
    //записываем вершину после всех потомков
    result.push_back(v);
}

//проверка на наличие цикла
bool cycle(int v, vector<int>& state) {
    // state: 0 - не посещена, 1 - находимся в ней, 2 - обработана
    state[v] = 1;
    
    for (int i = 0; i < Gr[v].size(); i++) {
        int u = Gr[v][i];
        if (state[u] == 1) {
            return true;  // нашли цикл
        }
        if (state[u] == 0 && cycle(u, state)) {
            return true;
        }
    }
    state[v] = 2;
    return false;
}

bool hasCycle() {
    vector<int> state(n, 0);
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (cycle(i, state)) {
                return true;
            }
        }
    }
    return false;
}

//топологическая сортировка
vector<int> topologicalSort() {
    if (hasCycle()) {
        cout << "\nГраф содержит цикл, топологическая сортировка невозможна.\n";
        return {};
    }
    
    result.clear();
    fill(used.begin(), used.end(), false);
    
    // 3. запускаем DFS для всех вершин
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    
    // 4. переворачиваем порядок
    reverse(result.begin(), result.end());
    
    return result;
}

int main() {
    setlocale(LC_ALL, "");
    
    n = 8;
    Gr.resize(n);
    used.resize(n, false);
    
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(1, 4);
    addEdge(2, 4);
    addEdge(3, 4);
    addEdge(5, 6);
    addEdge(5, 7);
    addEdge(7, 0);
    
    cout << "Список смежности:\n";
    print();
    
    vector<int> res = topologicalSort();
    
    if (!res.empty()) {
        cout << "\nТопологическая сортировка: ";
        for (int i = 0; i < res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << endl;
    }
}