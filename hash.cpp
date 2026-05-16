// Метод деления по зарплате

#include <iostream>
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
    int salary;         // зарплата (это ключ)
};

struct list {
    sotr inf;           // данные сотрудника
    list* next;         // указатель на следующий элемент
    list* prev;         // указатель на предыдущий элемент
};

void push(list*& h, list*& t, const sotr& x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;

    if (!h && !t) {
        r->prev = NULL;
        h = t = r;
    }
    else {
        t->next = r;
        r->prev = t;
        t = r;
    }
}

void pop(list*& h, list*& t, list*& r) {
    if (h == r && t == r) {
        h = t = NULL;
    }
    else if (r == h) {
        h = h->next;
        if (h) h->prev = NULL;
    }
    else if (r == t) {
        t = t->prev;
        if (t) t->next = NULL;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
    r = NULL;
}

list** table;       // массив указателей на головы списков
list** tail;        // массив указателей на хвосты списков
int M;

int hashf(int salary) {
    return salary % M;
}

//создание таблицы
void hashtable(int size) {
    M = size;
    table = new list * [M];
    tail = new list * [M];
    for (int i = 0; i < M; i++) {
        table[i] = NULL;
        tail[i] = NULL;
    }
}

//удаление таблицы, очистака памяти
void deletehash() {
    for (int i = 0; i < M; i++) {
        list* p = table[i];
        while (p) {
            list* temp = p;
            p = p->next;
            delete temp;
        }
    }
    delete[] table;
    delete[] tail;
}

//вставка
void insert(const sotr& s) {
    int index = hashf(s.salary);
    push(table[index], tail[index], s);
}

//поиск
sotr* find(int salary) {
    int index = hashf(salary);
    list* p = table[index];

    while (p) {
        if (p->inf.salary == salary) {
            return &(p->inf);
        }
        p = p->next;
    }
    return NULL;
}

//удаление одного сотрудника
bool remove(int salary) {
    int index = hashf(salary);
    list* p = table[index];

    while (p) {
        if (p->inf.salary == salary) {
            pop(table[index], tail[index], p);
            return true;
        }
        p = p->next;
    }
    return false;
}

// удаление всех сотрудников
int removeall(int salary) {
    int index = hashf(salary);
    int count = 0;
    list* p = table[index];

    while (p) {
        list* node = p->next;
        if (p->inf.salary == salary) {
            pop(table[index], tail[index], p);
            count++;
        }
        p = node;
    }
    return count;
}

//поиск всех сотрудников с данной зарплатой
vector<sotr> findall(int salary) {
    int index = hashf(salary);
    vector<sotr> result;
    list* p = table[index];

    while (p) {
        if (p->inf.salary == salary) {
            result.push_back(p->inf);
        }
        p = p->next;
    }
    return result;
}

// вывод в файл
void printfile(ofstream& out) {
    for (int i = 0; i < M; i++) {
        out << i << ": ";
        list* p = table[i];
        if (!p) {
            out << "(пусто)";
        }
        while (p) {
            out << p->inf.sotrud << "(" << p->inf.salary << ")";
            if (p->next) out << " , ";
            p = p->next;
        }
        out << endl;
    }
}

void print() {
    for (int i = 0; i < M; i++) {
        cout << i << ": ";
        list* p = table[i];
        if (!p) {
            cout << "(пусто)";
        }
        while (p) {
            cout << p->inf.sotrud << "(" << p->inf.salary << ")";
            if (p->next) cout << " , ";
            p = p->next;
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

    M = 13;
    hashtable(M);           

    for (int i = 0; i < workers.size(); i++) {
        insert(workers[i]);
    }

    print();
    printfile(out);

    int searchsalary;
    cout << "\nВведите зарплату для поиска: ";
    cin >> searchsalary;

    vector<sotr> found = findall(searchsalary);
    if (found.empty()) {
        cout << "Сотрудников с зарплатой " << searchsalary << " не найдено.\n";
    }
    else {
        cout << "\nНайдено " << found.size() << " сотрудников:\n";
        for (const auto& s : found) {
            print(s);
        }
    }

    int deletesalary;
    cout << "\nВведите зарплату для удаления всех сотрудников: ";
    cin >> deletesalary;

    int removed = removeall(deletesalary);
    if (removed > 0) {
        cout << "Удалено " << removed << " сотрудников с зарплатой " << deletesalary << "\n";

        // Выводим обновлённую таблицу
        cout << "Обновлённая таблица\n";
        print();
        printfile(out);
    }
    else {
        cout << "Сотрудников с зарплатой " << deletesalary << " не найдено.\n";
    }

    out.close();
    in.close();
}


