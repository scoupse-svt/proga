#include <iostream>
using namespace std;

struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

void reverse(stack*& h) {
    stack* head1 = NULL;
    while (h) {
        push(head1, pop(h));
    }
    h = head1;
}

int findmin(stack*& h) { //поиск мин
    int mm = h->inf;
    stack* tmp = NULL;
    while (h) {
        int x = pop(h);
        if (x < mm) {
            mm = x;
        }
        push(tmp, x);
    }
    h = tmp;
    return mm;
}

// поиск макс
int findmax(stack*& h) {
    int mm = h->inf;
    stack* tmp = NULL;
    while (h) {
        int x = pop(h);
        if (x > mm) {
            mm = x;
        }
        push(tmp, x);
    }
    h = tmp;
    return mm;
}

// после каждого минимального числа вставляем максимальное
void insert(stack*& h) {
    if (!h) return;

    int minv = findmin(h);
    int maxv = findmax(h);

    // если минимальное и максимальное совпадают — ничего не делаем
    if (minv == maxv) return;
    reverse(h);

    stack* res = NULL;

    while (h) {
        int x = pop(h);
        push(res, x);
        // если это минимальное число — вставляем максимальное
        if (x == minv) {
            push(res, maxv);
        }
    }
    h = res;
    reverse(h);
}

void print(stack* h) {
    stack* tmp = NULL;
    while (h) {
        int x = pop(h);
        cout << x << " ";
        push(tmp, x);
    }
}


int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    stack* h = NULL;
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Исходный стэк: ";
    for (int i = 0; i < n; ++i) {
        int x = rand() % 10;
        cout << x << " ";
        push(h, x);
    }
    cout << endl;

    insert(h);

    cout << "Результат: ";
    print(h);
}