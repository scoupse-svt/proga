//Дано математическое выражение. Построить на его основе дерево по примеру, 
//приведенному в лекциях. Вывести данное выражение в префиксной и постфиксной формах, 
//используя соответствующие обходы. 

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct tree {
    char inf;           // символ (цифра или знак операции)
    tree* left;         // левый ребёнок
    tree* right;        // правый ребёнок
    tree* parent;       // родитель
};

//создание узла
tree* node(char x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

//построение
tree* create_tree(string str) {
    tree* tr = NULL;
    
    for (int i = 0; i < str.length(); i++) {
        tree* n = node(str[i]);
        
        //если цифра
        if (isdigit(str[i])) {
            if (!tr) {
                tr = n;                     // первая цифра - корень
            }
            else {
                if (!tr->right) {
                    // если нет правого ребёнка, вставляем туда
                    n->parent = tr;
                    tr->right = n;
                }
                else {
                    // ищем операнд без правого сына
                    tree* x = tr->right;
                    while (x->right) {
                        x = x->right;
                    }
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
        //если знак * или /
        else if (str[i] == '*' || str[i] == '/') {
            if (isdigit(tr->inf)) {
                // если корень - цифра, знак становится корнем
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else {
                // добавляем справа от корня
                n->parent = tr;
                n->left = tr->right;
                if (tr->right) tr->right->parent = n;
                tr->right = n;
            }
        }
        // если знак + или - 
        else if (str[i] == '+' || str[i] == '-') {
            if (tr) {
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
        }
    }
    return tr;
}

//префиксная форма, прямой обход
void preorder(tree* tr) {
    if (tr) {
        cout << tr->inf;            
        preorder(tr->left);         
        preorder(tr->right);        
    }
}

//обратный обход, постфиксная форма
void postorder(tree* tr) {
    if (tr) {
        postorder(tr->left);       
        postorder(tr->right);       
        cout << tr->inf;            
    }
}

void clear(tree* tr) {
    if (tr) {
        clear(tr->left);
        clear(tr->right);
        delete tr;
    }
}

int main() {
    setlocale(LC_ALL, "");
    
    string expr;
    cout << "Введите математическое выражение: ";
    getline(cin, expr);
    
    // удаляем пробелы
    string clean = "";
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] != ' ') {
            clean += expr[i];
        }
    }
   
    tree* root = create_tree(clean);
    
    if (!root) {
        cout << "Ошибка при построении дерева!\n";
        return 1;
    }
    
    cout << "Исходное выражение: " << clean << endl;
    
    cout << "Префиксная форма: ";
    preorder(root);
    cout << endl;
    
    cout << "Постфиксная форма: ";
    postorder(root);
    cout << endl;
    
    clear(root);
}