//Основная — линейное хеширование, вспомогательная — метод умножения по стажу

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;

ifstream in("sotrudniki.txt");
ofstream out("result.txt");


struct date {
    int day, mth, year;
};

struct sotr {
    string sotrud;      // фамилия
    string sotrjob;     // должность
    date birth;         // дата рождения
    int exp;            // стаж
    int salary;         // зарплата 
};

vector<sotr> table;
vector<bool> visited;
vector<bool> deleted;
int M;

// золотое сечение для метода умножения
const double A = 0.6180339887498949;

//метод умножения по стажу
int hash_aux(int exp) {
    double p = exp * A;
    double f = p - floor(p);
    double result = M * f;
    return (int)floor(result);
}

//линейное хэширование
int hashm(int exp, int attempt) {
    return (hash_aux(exp) + attempt) % M;
}

// создание таблицы
void hashtable(int size) {
    M = size;
    table.resize(M);
    visited.resize(M, false);
    deleted.resize(M, false);
}

// вставка
void insert(const sotr& s) {
    int k = 0;

    while (k < M) {
        int p = hashm(s.exp, k);   

        if (!visited[p] || deleted[p]) {
            table[p] = s;
            visited[p] = true;
            deleted[p] = false;
            return;
        }
        k++;
    }
    cout << "Ошибка: таблица переполнена\n";
}

// поиск всех сотрудников с заданным стажем
vector<sotr> findall(int exp) {
    vector<sotr> result;
    int attempt = 0;

    while (attempt < M) {
        int p = hashm(exp, attempt);     

        if (!visited[p]) break;
        if (!deleted[p] && table[p].exp == exp) {
            result.push_back(table[p]);
        }
        attempt++;
    }
    return result;
}

// вывод в файл
void printfile(ofstream& out) {
    for (int i = 0; i < M; i++) {
        out << i << ": ";
        if (!visited[i]) {
            out << "(пусто)";
        }
        else if (deleted[i]) {
            out << "(удалён)";
        }
        else {
            out << table[i].sotrud << "(" << table[i].exp << ")";
        }
        out << endl;
    }
}

void print() {
    for (int i = 0; i < M; i++) {
        out << i << ": ";
        if (!visited[i]) {
            cout << "(пусто)";
        }
        else if (deleted[i]) {
            cout << "(удалён)";
        }
        else {
            cout << table[i].sotrud << "(" << table[i].exp << ")";
        }
        cout << endl;
    }
}

// преобразование строки в дату
date str_int(string str) {
    date x;
    string temp = str.substr(0, 2);
    x.day = atoi(temp.c_str());
    temp = str.substr(3, 2);
    x.mth = atoi(temp.c_str());
    temp = str.substr(6, 4);
    x.year = atoi(temp.c_str());
    return x;
}

// чтение из файла 
vector<sotr> inFile() {
    vector<sotr> x;
    sotr temp;
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string razd;
        getline(ss, razd, ' ');
        temp.sotrud = razd;
        getline(ss, razd, ' ');
        temp.sotrjob = razd;
        getline(ss, razd, ' ');
        temp.birth = str_int(razd);
        getline(ss, razd, ' ');
        temp.exp = atoi(razd.c_str());
        getline(ss, razd, ' ');
        temp.salary = atoi(razd.c_str());
        x.push_back(temp);
    }
    return x;
}
void print(const sotr& x) {
    cout << "  " << setw(10) << left << x.sotrud;
    cout << setw(15) << left << x.sotrjob;
    if (x.birth.day < 10) cout << '0';
    cout << x.birth.day << ".";
    if (x.birth.mth < 10) cout << '0';
    cout << x.birth.mth << ".";
    cout << x.birth.year;
    cout << setw(6) << right << x.exp;
    cout << setw(10) << right << x.salary << endl;
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<sotr> workers = inFile();

    M = 31;
    hashtable(M);

    for (int i = 0; i < workers.size(); i++) {
        insert(workers[i]);
    }

    print();
    printfile(out);

    int searchexp;
    cout << "\nВведите стаж для поиска: ";
    cin >> searchexp;

    vector<sotr> found = findall(searchexp);
    if (found.empty()) {
        cout << "Сотрудников со стажем " << searchexp << " не найдено.\n";
    }
    else {
        cout << "\nНайдено " << found.size() << " сотрудников:\n";
        for (const auto& s : found) {
            print(s);
        }
    }

    out.close();
    in.close();
}


