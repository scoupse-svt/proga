#include <iostream>
using namespace std;

struct tree{
    int inf;
    tree* lt; //левый ребёнок
    tree* rt; //правый ребёнок
    tree* pt; // родитель
};

tree* node(int x) { // начальный узел
    tree* n = new tree;
    n->inf = x;
    n->lt = n->rt = NULL;
    n->pt = NULL;
    return n;
}

void insert(tree*& tr, int x) { //вставка
    tree* n = node(x);
    if (!tr) tr = n; //если дерево пустое, то это корень
    else {
        tree* y = tr;
        while (y) {
            if (n->inf > y->inf) { //правая ветка
                if (y->rt) y = y->rt;
                else {
                    n->pt = y; //узел становится правым ребёнком
                    y->rt = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { //левая ветка
                if (y->lt) y = y->lt;
                else {
                    n->pt = y; //узел становится левым ребёнком
                    y->lt = n;
                    break;
                }
            }
        }
    }
}

tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr; //если нашли или дошли до конца
    if (x < tr->inf) {
        return find(tr->lt, x);
    }
    else {
        return find(tr->rt, x);
    }
}

int sumparents(tree* tr, int x) {
    tree* nX = find(tr, x);
    if (!nX) {
        cout << "Такого узла нет в дереве." << endl;
        return 0;
    }
    int summa = 0;
    tree* p = nX->pt;

    while (p) {
        summa += p->inf;
        p = p->pt;
    }

    if (summa == 0) cout << "Предков нет, узел - корень" << endl;

    return summa;
}

void inorder(tree* tr) { //симметричный обход для вывода
    if (tr) {
        inorder(tr->lt);
        cout << tr->inf << " ";
        inorder(tr->rt);
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "");

    tree* root = NULL;

    int n = 0;
    int x = 0;
    cout << "Введите количество элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t = 0;
        cin >> t;
        insert(root, t);
    }

    cout << "Текущее дерево (симметричный обход): ";
    inorder(root);
    cout << endl;

    cout << "Введите узел X: ";
    cin >> x;

    int summa = sumparents(root, x);

    if (summa != 0) {
        cout << "Сумма предков узла " << x << " = " << summa << endl;
    }
    else {
        return 0;
    }
}
