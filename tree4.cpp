#include <iostream>
using namespace std;

struct tree {
    int inf;
    int height;
    tree* lt;
    tree* rt;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->height = 1;
    n->lt = n->rt = NULL;
    return n;
}

//функции для балансировки
int height(tree* tr) {
    return tr ? tr->height : 0;
}

void updateHeight(tree* tr) {
    if (tr) {
        int hl = height(tr->lt);
        int hr = height(tr->rt);
        tr->height = (hl > hr ? hl : hr) + 1;
    }
}

int balanceFactor(tree* tr) {
    return tr ? height(tr->lt) - height(tr->rt) : 0;
}

tree* rotateRight(tree* y) {
    tree* x = y->lt;
    tree* T2 = x->rt;
    x->rt = y;
    y->lt = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

tree* rotateLeft(tree* x) {
    tree* y = x->rt;
    tree* T2 = y->lt;
    y->lt = x;
    x->rt = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

tree* balance(tree* tr) {
    if (!tr) return tr;
    updateHeight(tr);
    int bf = balanceFactor(tr);
    // левый перекос
    if (bf > 1) {
        if (balanceFactor(tr->lt) < 0)
            tr->lt = rotateLeft(tr->lt);
        return rotateRight(tr);
    }
    // правый перекос
    if (bf < -1) {
        if (balanceFactor(tr->rt) > 0)
            tr->rt = rotateRight(tr->rt);
        return rotateLeft(tr);
    }
    return tr;
}

//вставка в дерево
tree* insertAVL(tree* tr, int x) {
    if (!tr) return node(x);
    if (x < tr->inf)
        tr->lt = insertAVL(tr->lt, x);
    else if (x > tr->inf)
        tr->rt = insertAVL(tr->rt, x);
    else
        return tr; // дубликаты не вставляем
    return balance(tr);
}

// симметричный обход
void inorder(tree* tr) {
    if (tr) {
        inorder(tr->lt);
        cout << tr->inf << " ";
        inorder(tr->rt);
    }
}

//сумма листьев
int leafsum(tree* tr) {
    if (!tr) return 0;
    if (!tr->lt && !tr->rt) return tr->inf;
    return leafsum(tr->lt) + leafsum(tr->rt);
}

int main() {
    tree* root = NULL;
    int n, x;

    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        root = insertAVL(root, x);
    }

    cout << "\nСимметричный обход AVL-дерева: ";
    inorder(root);
    cout << endl;

    cout << "Сумма листьев: " << leafsum(root) << endl;
}