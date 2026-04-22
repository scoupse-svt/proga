#include <iostream>
using namespace std;

struct stack {
    char inf;
    stack* next;
};

void push(stack*& h, char x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop(stack*& h) {
    char i = h->inf;
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

bool check(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// вставка после первой гласной
void insert(stack*& h) {
    if (!h) return;

    stack* res = NULL;
    bool inserted = false;

    while (h) {
        char x = pop(h);
        push(res, x);

        if (!inserted && check(x)) {
            push(res, '?');
            inserted = true;
        }
    }
    h = res;
}

void print(stack* h) {
    stack* tmp = NULL;
    while (h) {
        char x = pop(h);
        cout << x << " ";
        push(tmp, x);
    }
}


int main() {
    setlocale(LC_ALL, "");
    stack* h = NULL;
    int n;
    cout << "Введите количество букв: ";
    cin >> n;
    cout << "Исходный стэк: ";
    stack* temp = NULL;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        push(temp, x);
    }
    // прекладываем в основной стек 
    while (temp) {
        push(h, pop(temp));
    }

    insert(h);
    reverse(h);

    cout << "Результат: ";
    print(h);
}