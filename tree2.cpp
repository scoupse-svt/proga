#include <iostream>
using namespace std;

struct tree {
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

tree* findsibl(tree* tr, int x) {//найти брата
    tree* nX = find(tr, x);
    tree* pt = nX->pt;
    if (!pt) return NULL;  // у корня нет братьев

    if (pt->lt == nX) return pt->rt;  // x слева - брат справа
    else return pt->lt; // x справа - брат слева
}

tree* findlt(tree* tr, int x) { //найти левого племянника
    tree* nX = find(tr, x);
    if (!nX) {
        cout << "Узел не найден!" << endl;
        return 0;
    }

    tree* pt = nX->pt;
    if (!pt) {
        cout << "Узел " << x << " — корень, у него нет братьев" << endl;
        return 0;
    }

    tree* sibl = findsibl(tr, x);
    if (!sibl) {
        cout << "У узла " << x << " нет братьев" << endl;
        return 0;
    }

    if (sibl->lt) {
        return sibl ->lt;
    }
    else {
        cout << "У брата узла " << x << " нет левого ребенка" << endl;
        return 0;
    }
}

bool deletelt(tree*& tr, int x) {//удаление левого племянника
    tree* nephew = findlt(tr, x);

    if (!nephew) {
        return false;
    }

    tree* ptnephew = nephew->pt;

    // обнуляем указатель у родителя
    if (ptnephew->lt == nephew) {
        ptnephew->lt = NULL;
    }
    else {
        ptnephew->rt = NULL;
    }

    delete nephew;
    return true;
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
    cout << "Введите элементы: ";
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

    bool fl = deletelt(root, x);

    if (fl) {
        cout << "Дерево после удаления племенника: ";
        inorder(root);
    }
    else {
        return 0;
    }
}
