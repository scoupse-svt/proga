#include <iostream>
using namespace std;

struct queue {
    int inf; //хранится элемент, который мы положили в очередь
    queue* next;//указатель на след. элемент
};

void push(queue*& h, queue*& t, int x) { //ф-ция добавления элементов в хвост
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;

    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

int pop(queue*& h, queue*& t) { //ф-ция удаления из головы
    if (!h) return -1; //в случае пустой очереди

    queue* r = h;
    int val = h->inf;
    h = h->next;

    if (!h) t = NULL;
    delete r;
    return val;
}

// поиск минимального числа в очереди
int mini(queue*& h, queue*& t) {
    queue* tmph = NULL;
    queue* tmpt = NULL;
    int m = h->inf;
    while (h) {
        int x = pop(h, t);
        if (x < m) {
            m = x;
        }
        push(tmph, tmpt, x);
    }
    h = tmph;
    t = tmpt;
    return m;
}

//последний четный элемент
int findlast(queue* h, queue* t) {
    queue* tmph = NULL;
    queue* tmpt = NULL;
    int last = 0;
    while (h) {
        int x = pop(h, t);
        if (x % 2 == 0) {
            last = x;
        }
        push(tmph, tmpt, x);
    }
    h = tmph;
    t = tmpt;
    return last;
}

void print(queue* h, queue* t) {
    queue* tmph = NULL;
    queue* tmpt = NULL;
    while (h) {
        int x = pop(h, t);
        cout << x << " ";
        push(tmph, tmpt, x);
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "");

    queue* h = NULL;
    queue* t = NULL;

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cin.ignore(10000, '\n');

    cout << "Введите " << n << " целых чисел через пробел: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push(h, t, x);
    }
}