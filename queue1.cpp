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

//    if (!h) t = NULL;
    delete r;
    return val;
}

bool check(int n) { //проверка на составное число     
    if (n <= 1) return false;     
    if (n == 2 || n == 3) return false;     
    if (n % 2 == 0) return true;     
    for (int i = 3; i * i <= n; i += 2){         
        if (n % i == 0) return true;     
    }    
    return false; 
}

void circle(queue*& h, queue*& t) {
    queue* t_b = t;
    bool fl = false;

    while (h != t_b) {
        if (!check(h->inf)) {   // если не составное
            int x = pop(h, t);
            push(h, t, x);
        }
        else {                    // если составное
            fl = true;
            break;
        }
    }

    if (!fl && !check(h->inf)) {
        int x = pop(h, t);
        push(h, t, x);
    }
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

    circle(h, t);

    cout << "Результат: ";
    print(h, t);
}