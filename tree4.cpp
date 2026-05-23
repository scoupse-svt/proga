#include <iostream>
using namespace std;

struct tree {
    int inf;
    tree* lt;
    tree* rt;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->lt = n->rt = NULL;
    return n;
}

//сбалансированное дерево
void balanced(tree*& tr, int* arr, int start, int end) {
    if (start > end) {
        tr = NULL;
        return;
    }
    int mid = (start + end) / 2;
    tr = node(arr[mid]);
    balanced(tr->lt, arr, start, mid - 1);
    balanced(tr->rt, arr, mid + 1, end);
}

//симметричный обход
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
    setlocale(LC_ALL, "");
    tree* root = NULL;

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Сортируем массив, чтобы дерево было сбалансированным
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    balanced(root, arr, 0, n - 1);
    delete[] arr;

    cout << "\nСимметричный обход: ";
    inorder(root);
    cout << endl;

    int sum = leafsum(root);
    cout << "Сумма листьев: " << sum << endl;
}