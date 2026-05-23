// rbt_delete_multiple.cpp : Красно-чёрное дерево. Удаление элементов, кратных X
//

#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    int inf;                // значение
    Tree* left;             // левый ребёнок
    Tree* right;            // правый ребёнок
    Tree* parent;           // родитель
    char color;             // 'r' - красный, 'b' - чёрный
};

// создание корня
Tree* root(int x) {
    Tree* n = new Tree;
    n->inf = x;
    n->left = n->right = nullptr;
    n->parent = nullptr;
    n->color = 'b';         // корень всегда чёрный
    return n;
}

// создание узла с родителем
Tree* node(Tree* prev, int x) {
    Tree* n = new Tree;
    n->inf = x;
    n->left = n->right = nullptr;
    n->parent = prev;
    n->color = 'r';         // новый узел всегда красный
    return n;
}

// дедушка узла
Tree* grandFather(Tree* x) {
    if (!x || !x->parent) return nullptr;
    return x->parent->parent;
}

// дядя узла
Tree* uncle(Tree* x) {
    Tree* g = grandFather(x);
    if (!g) return nullptr;
    if (x->parent == g->left) return g->right;
    else return g->left;
}

// брат узла
Tree* brother(Tree* x) {
    if (!x || !x->parent) return nullptr;
    if (x == x->parent->left) return x->parent->right;
    else return x->parent->left;
}

// левый поворот
void left_rotate(Tree*& tr, Tree* x) {
    Tree* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    
    if (!x->parent) tr = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// правый поворот
void right_rotate(Tree*& tr, Tree* x) {
    Tree* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    
    if (!x->parent) tr = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    
    y->right = x;
    x->parent = y;
}

void insert_case_1(Tree*& tr, Tree* x);
void insert_case_2(Tree*& tr, Tree* x);
void insert_case_3(Tree*& tr, Tree* x);
void insert_case_4(Tree*& tr, Tree* x);
void insert_case_5(Tree*& tr, Tree* x);

// X - корень
void insert_case_1(Tree*& tr, Tree* x) {
    if (!x->parent) {
        x->color = 'b';
    } else {
        insert_case_2(tr, x);
    }
}

// родитель чёрный
void insert_case_2(Tree*& tr, Tree* x) {
    if (x->parent->color == 'r') {
        insert_case_3(tr, x);
    }
}

// родитель красный, дядя красный
void insert_case_3(Tree*& tr, Tree* x) {
    Tree* g = grandFather(x);
    Tree* u = uncle(x);
    
    if (u && u->color == 'r' && x->parent->color == 'r') {
        x->parent->color = 'b';
        u->color = 'b';
        g->color = 'r';
        insert_case_1(tr, g);
    } else {
        insert_case_4(tr, x);
    }
}

// родитель красный, дядя чёрный, X - противоположный ребёнок
void insert_case_4(Tree*& tr, Tree* x) {
    Tree* g = grandFather(x);
    Tree* p = x->parent;
    
    if (p->right == x && g->left == p) {
        left_rotate(tr, p);
        x = x->left;
    }
    else if (p->left == x && g->right == p) {
        right_rotate(tr, p);
        x = x->right;
    }
    insert_case_5(tr, x);
}

//родитель красный, дядя чёрный, X - прямой ребёнок
void insert_case_5(Tree*& tr, Tree* x) {
    Tree* g = grandFather(x);
    Tree* p = x->parent;
    
    p->color = 'b';
    g->color = 'r';
    
    if (x == p->left && p == g->left) {
        right_rotate(tr, g);
    }
    else if (x == p->right && p == g->right) {
        left_rotate(tr, g);
    }
}

// вставка значения в дерево
void insert(Tree*& tr, int x) {
    if (!tr) {
        tr = root(x);
        return;
    }
    
    Tree* prev = tr;
    while (prev) {
        if (x < prev->inf) {
            if (!prev->left) {
                prev->left = node(prev, x);
                insert_case_1(tr, prev->left);
                return;
            }
            prev = prev->left;
        }
        else if (x > prev->inf) {
            if (!prev->right) {
                prev->right = node(prev, x);
                insert_case_1(tr, prev->right);
                return;
            }
            prev = prev->right;
        }
        else {
            return; // дубликаты не вставляем
        }
    }
}

void delete_case_1(Tree*& tr, Tree* x);
void delete_case_2(Tree*& tr, Tree* x);
void delete_case_3(Tree*& tr, Tree* x);
void delete_case_4(Tree*& tr, Tree* x);
void delete_case_5(Tree*& tr, Tree* x);
void delete_case_6(Tree*& tr, Tree* x);

//удаление
// X - корень
void delete_case_1(Tree*& tr, Tree* x) {
    if (!x->parent) {
        if (x->left) tr = x->left;
        else tr = x->right;
        if (tr) tr->parent = nullptr;
    } else {
        delete_case_2(tr, x);
    }
}

//родитель- чёрный, брат - красный
void delete_case_2(Tree*& tr, Tree* x) {
    Tree* b = brother(x);
    Tree* p = x->parent;
    
    if (b && b->color == 'r') {
        p->color = 'r';
        b->color = 'b';
        if (p->left == x) left_rotate(tr, p);
        else right_rotate(tr, p);
    }
    delete_case_3(tr, x);
}

// родтель - красный, брат и племянники - чёрные
void delete_case_3(Tree*& tr, Tree* x) {
    Tree* p = x->parent;
    Tree* b = brother(x);
    
    if (p->color == 'r' && b && b->color == 'b' &&
        (!b->left || b->left->color == 'b') &&
        (!b->right || b->right->color == 'b')) {
        b->color = 'r';
        p->color = 'b';
    } else {
        delete_case_4(tr, x);
    }
}

//  брат и его дети - чёрные, родитель - чёрный
void delete_case_4(Tree*& tr, Tree* x) {
    Tree* p = x->parent;
    Tree* b = brother(x);
    
    if (p->color == 'b' && b && b->color == 'b' &&
        (!b->left || b->left->color == 'b') &&
        (!b->right || b->right->color == 'b')) {
        b->color = 'r';
        delete_case_1(tr, p);
    } else {
        delete_case_5(tr, x);
    }
}

// брат - чёрный, один из племянников - красный
void delete_case_5(Tree*& tr, Tree* x) {
    Tree* p = x->parent;
    Tree* b = brother(x);
    
    if (b && b->color == 'b') {
        if (x == p->left && b->right && b->right->color == 'r') {
            b->color = 'r';
            b->right->color = 'b';
            left_rotate(tr, b);
        }
        else if (x == p->right && b->left && b->left->color == 'r') {
            b->color = 'r';
            b->left->color = 'b';
            right_rotate(tr, b);
        }
    }
    delete_case_6(tr, x);
}

// брат - чёрный, племяник - красный
void delete_case_6(Tree*& tr, Tree* x) {
    Tree* p = x->parent;
    Tree* b = brother(x);
    
    if (b) b->color = p->color;
    p->color = 'b';
    
    if (x == p->left) {
        if (b->right) b->right->color = 'b';
        left_rotate(tr, p);
    } else {
        if (b->left) b->left->color = 'b';
        right_rotate(tr, p);
    }
}

// замена узлов при удалении
void replace(Tree*& tr, Tree* u, Tree* v) {
    if (!u->parent) tr = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    
    if (v) v->parent = u->parent;
}

// поиск минимального узла в поддереве
Tree* findMin(Tree* tr) {
    while (tr && tr->left) tr = tr->left;
    return tr;
}

// удаление узла
void erase(Tree*& tr, Tree* x) {
    Tree* y = x;
    Tree* child = nullptr;
    char originalColor = y->color;
    
    //нет левого ребёнка
    if (!x->left) {
        child = x->right;
        replace(tr, x, x->right);
    }
    //нет правого ребёнка
    else if (!x->right) {
        child = x->left;
        replace(tr, x, x->left);
    }
    //есть оба ребёнка
    else {
        y = findMin(x->right);
        originalColor = y->color;
        child = y->right;
        
        if (y->parent == x) {
            if (child) child->parent = y;
        } else {
            replace(tr, y, y->right);
            y->right = x->right;
            y->right->parent = y;
        }
        
        replace(tr, x, y);
        y->left = x->left;
        y->left->parent = y;
        y->color = x->color;
    }
    
    delete x;
    
    // балансировка после удаления
    if (originalColor == 'b' && child) {
        if (child->color == 'r') {
            child->color = 'b';
        } else {
            delete_case_1(tr, child);
        }
    }
}

// поиск узла 
Tree* find(Tree* tr, int x) {
    while (tr) {
        if (x < tr->inf) tr = tr->left;
        else if (x > tr->inf) tr = tr->right;
        else return tr;
    }
    return nullptr;
}

// удаление всех элементов, кратных X
void deleteMultiples(Tree*& tr, int x) {
    if (!tr) return;
    
    //рекурсивно обрабатываем левое и правое поддеревья
    deleteMultiples(tr->left, x);
    deleteMultiples(tr->right, x);
    
    //если кратен X - удаляем его
    if (tr->inf % x == 0) {
        Tree* toDelete = find(tr, tr->inf);
        if (toDelete) erase(tr, toDelete);
    }
}

// симметричный обход 
void inorder(Tree* tr) {
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

void clear(Tree* tr) {
    if (tr) {
        clear(tr->left);
        clear(tr->right);
        delete tr;
    }
}

int main() {
    setlocale(LC_ALL, "");
    
    Tree* root = nullptr;
    int n, x, value;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        insert(root, value);
    }

    cout << "Симметричный обход: ";
    inorder(root);
    cout << endl;
    
    cout << "\nВведите число X: ";
    cin >> x;
    
    deleteMultiples(root, x);
    
    cout << "Симметричный обход после удаления: ";
    inorder(root);
    cout << endl;
    
    clear(root);
}