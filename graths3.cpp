//Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, 
//если он существует.

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<vector<int>> Gr;   // список смежности
int n;                     // количество вершин
vector<bool> used;         // массив посещённых вершин 

//добавление ребра для неориентированного графа
void addEdge(int u, int v) {
    for (int i = 0; i < Gr[u].size(); i++) {
        if (Gr[u][i] == v) return;
    }
    Gr[u].push_back(v);
    Gr[v].push_back(u);
}

//вывод на экран
void print() {
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        sort(Gr[i].begin(), Gr[i].end());
        for (int j = 0; j < Gr[i].size(); j++) {
            cout << Gr[i][j] << " ";
        }
        cout << endl;
    }
}

//удаление ребра для поиска эйлерового пути/цикла
void removeEdge(int u, int v) {
// удаляем v из списка u
    for (auto it = Gr[u].begin(); it != Gr[u].end(); ++it) {
        if (*it == v) {
            Gr[u].erase(it);
            break;
        }
    }
    // удаляем u из списка v
    for (auto it = Gr[v].begin(); it != Gr[v].end(); ++it) {
        if (*it == u) {
            Gr[v].erase(it);
            break;
        }
    }
}

//обход в ширину
void bfs(int start) {
   
    vector<int> q; //вектор для очереди
    int head = 0;

    used[start] = true;
    q.push_back(start);

    while (head < q.size()) {
        int x = q[head];
        head++;

        for (int i = 0; i < Gr[x].size(); i++) {
            int y = Gr[x][i];
            if (!used[y]) {
                used[y] = true;
                q.push_back(y);
            }
        }
    }
}

void resetUsed() {
    for (int i = 0; i < n; i++) {
        used[i] = false;
    }
}

bool connect() {
    // находим первую вершину, у которой есть рёбра
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (!Gr[i].empty()) {
            start = i;
            break;
        }
    }
    
    if (start == -1) return true;  
    
    // сбрасываем массив used
    fill(used.begin(), used.end(), false);
    
    bfs(start);
    
    // проверяем, все ли вершины с рёбрами посещены
    for (int i = 0; i < n; i++) {
        if (!Gr[i].empty() && !used[i]) {
            return false;   
        }
    }
    return true;
}

//ф-ция поиска эйлерового пути и цикла вместе
vector<int> findeler() {

    vector<int> step(n, 0);   // степень каждой вершины
    vector<int> nch;          // вершины с нечётной степенью
    
    for (int i = 0; i < n; i++) {
        step[i] = Gr[i].size();      // степень это количество соседей
        if (step[i] % 2 == 1) {      // если нечётная, то в нечетное добавляем
            nch.push_back(i);
        }
    }
    
    //проверка на существование эйлерова пути/цикла
    if (nch.size() != 0 && nch.size() != 2) {
        cout << "Нет Эйлерова пути\n";
        return {};
    }
    if (!connect()) {
        cout << "Граф несвязный, Эйлерова пути нет.\n";
        return {};
    }
    
    //определяем тип (путь или цикл) и стартовую вершину
    int start;
    if (nch.empty()) {
        start = 0;
        cout << "\nГраф имеет Эйлеров цикл\n";
    } else {
        start = nch[0];
        cout << "\nГраф имеет Эйлеров путь\n";
    }
    
    vector<int> path;
    stack<int> st;
    st.push(start);
    
    while (!st.empty()) {
        int v = st.top();
        if (!Gr[v].empty()) {
            int u = Gr[v][0];
            removeEdge(v, u);
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    setlocale(LC_ALL, "");
    n = 8;
    Gr.resize(n);
    used.resize(n, false);
    
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(0, 4);
    addEdge(1, 5);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(4, 7);
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(5, 7);
    
    cout << "Граф:\n";
    print();
    
    vector<int> path = findeler();
    
    if (!path.empty()) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}