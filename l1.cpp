#include <iostream>

using namespace std;

//базовый абстрактный класс, от которого наследуются все другие классы
class GameObject {
protected:
    int id;
public:
    GameObject(int id) : id(id) {}
    virtual ~GameObject() {}

    int getId() const { return id; }

    virtual void print() const = 0;
};

//класс, который содержит дополнительное свойство — масса
//наследуется от GameObject и переопределяет метод print, выводя информацию об ID и массе
class PhysicalObject : public virtual GameObject {
protected:
    float mass;
public:
    PhysicalObject(int id, float mass) : GameObject(id), mass(mass) {}

    virtual void print() const override {
        cout << "ID: " << id << ", Mass: " << mass;
    }
};

//класс, который добавляет текстуру как свойство
//наследуется от GameObject и переопределяет метод print
class GraphicObject : public virtual GameObject {
protected:
    string texture;
public:
    GraphicObject(int id, const string& texture) : GameObject(id), texture(texture) {}

    virtual void print() const override {
        cout << "ID: " << id << ", Texture: " << texture;
    }
};

//класс снаряда, наследуется от PhysicalObject
//добавляет свойство caliber и выводит информацию о массе и калибре снаряда
class Shell : public PhysicalObject {
private:
    int caliber;
public:
    Shell(int id, float mass, int caliber)
        : GameObject(id), PhysicalObject(id, mass), caliber(caliber) {}

    void print() const override {
        PhysicalObject::print();
        cout << ", Caliber: " << caliber << endl;
    }
};

//класс, который добавляет мощность двигателя
//выводит информацию о массе и мощности двигателя
class Vehicle : public PhysicalObject {
protected:
    int enginePower;
public:
    Vehicle(int id, float mass, int enginePower)
        : GameObject(id), PhysicalObject(id, mass), enginePower(enginePower) {}

    void print() const override {
        PhysicalObject::print();
        cout << ", Engine Power: " << enginePower;
    }
};

//класс, который наследуется от Vehicle и GraphicObject,объединяет физические и графические свойства объекта
//доп свойство — толщина брони
class Tank : public Vehicle, public GraphicObject {
private:
    int armorThickness;
public:
    Tank(int id, float mass, int enginePower, const string& texture, int armorThickness)
        : GameObject(id), Vehicle(id, mass, enginePower), GraphicObject(id, texture), armorThickness(armorThickness) {}

    void print() const override {
        Vehicle::print();
        cout << ", Texture: " << texture << ", Armor Thickness: " << armorThickness << endl;
    }
};


enum Color { RED, BLACK };

//самобалансирующееся бинарное дерево поиска, где каждый узел окрашен в красный или черный цвет
//оно гарантирует, что дерево всегда остается сбалансированным
template <typename T>
class RedBlackTree {
private:
    struct Node {
        T* data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(T* data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void rotateLeft(Node*& root, Node*& pt);
    void rotateRight(Node*& root, Node*& pt);
    void fixViolation(Node*& root, Node*& pt);
    void fixDeletion(Node*& node);

    Node* insertBST(Node* root, Node* pt);
    Node* removeBST(Node* root, int id);
    Node* minValueNode(Node* node);
    void deleteTree(Node* node);

    void inOrder(Node* node) const;
    void preOrder(Node* node) const;
    void postOrder(Node* node) const;

    T* find(Node* node, int id) const;

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() { deleteTree(root); }

    void insert(T* data);//вставляет новый объект в дерево и исправляет возможные нарушения красно-черного дерева
    void remove(int id);//удаляет объект по ID и выполняет балансировку
    T* find(int id) const;//поиск по ID

    //обходы
    void printInOrder() const;//симметричный обход
    void printPreOrder() const;//прямой
    void printPostOrder() const;//обратный
};

// Вращение влево
template <typename T>
void RedBlackTree<T>::rotateLeft(Node*& root, Node*& pt) {
    Node* pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

// Вращение вправо
template <typename T>
void RedBlackTree<T>::rotateRight(Node*& root, Node*& pt) {
    Node* pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// Исправление нарушений после вставки
template <typename T>
void RedBlackTree<T>::fixViolation(Node*& root, Node*& pt) {
    Node* parent_pt = nullptr;
    Node* grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            Node* uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        else {
            Node* uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

// Вставка в бинарное дерево поиска
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::insertBST(Node* root, Node* pt) {
    if (root == nullptr)
        return pt;

    if (pt->data->getId() < root->data->getId()) {
        root->left = insertBST(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data->getId() > root->data->getId()) {
        root->right = insertBST(root->right, pt);
        root->right->parent = root;
    }
    else {
        cout << "Object with ID " << pt->data->getId() << " already exists.\n";
        pt->data->print();
    }

    return root;
}

// Вставка объекта
template <typename T>
void RedBlackTree<T>::insert(T* data) {
    Node* pt = new Node(data);

    root = insertBST(root, pt);
    fixViolation(root, pt);
}

// Функция удаления узла из бинарного дерева поиска
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::removeBST(Node* root, int id) {
    if (root == nullptr) return root;

    if (id < root->data->getId()) {
        root->left = removeBST(root->left, id);
    }
    else if (id > root->data->getId()) {
        root->right = removeBST(root->right, id);
    }
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeBST(root->right, temp->data->getId());
        }
    }

    if (root == nullptr) return root;

    fixDeletion(root);

    return root;
}

// Удаление объекта
template <typename T>
void RedBlackTree<T>::remove(int id) {
    root = removeBST(root, id);
}

// Исправление нарушений после удаления
template <typename T>
void RedBlackTree<T>::fixDeletion(Node*& node) {
    Node* s;
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            s = node->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                node->parent->color = RED;
                rotateLeft(root, node->parent);
                s = node->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                node = node->parent;
            }
            else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotateRight(root, s);
                    s = node->parent->right;
                }

                s->color = node->parent->color;
                node->parent->color = BLACK;
                s->right->color = BLACK;
                rotateLeft(root, node->parent);
                node = root;
            }
        }
        else {
            s = node->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                node->parent->color = RED;
                rotateRight(root, node->parent);
                s = node->parent->left;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                node = node->parent;
            }
            else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotateLeft(root, s);
                    s = node->parent->left;
                }

                s->color = node->parent->color;
                node->parent->color = BLACK;
                s->left->color = BLACK;
                rotateRight(root, node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

// Нахождение минимального значения в правом поддереве
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::minValueNode(Node* node) {
    Node* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Поиск объекта
template <typename T>
T* RedBlackTree<T>::find(int id) const {
    return find(root, id);
}

template <typename T>
T* RedBlackTree<T>::find(Node* node, int id) const {
    if (node == nullptr) return nullptr;

    if (id < node->data->getId()) {
        return find(node->left, id);
    }
    else if (id > node->data->getId()) {
        return find(node->right, id);
    }
    else {
        return node->data;
    }
}

// Удаление дерева
template <typename T>
void RedBlackTree<T>::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node->data;
    delete node;
}

// Печать дерева в порядке возрастания (симметричный обход)
template <typename T>
void RedBlackTree<T>::printInOrder() const {
    inOrder(root);
    cout << endl;
}

template <typename T>
void RedBlackTree<T>::inOrder(Node* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    node->data->print();
    inOrder(node->right);
}

// Печать дерева в порядке посещения (прямой обход)
template <typename T>
void RedBlackTree<T>::printPreOrder() const {
    preOrder(root);
    cout << endl;
}

template <typename T>
void RedBlackTree<T>::preOrder(Node* node) const {
    if (node == nullptr) return;
    node->data->print();
    preOrder(node->left);
    preOrder(node->right);
}

// Печать дерева в обратном порядке (обратный обход)
template <typename T>
void RedBlackTree<T>::printPostOrder() const {
    postOrder(root);
    cout << endl;
}

template <typename T>
void RedBlackTree<T>::postOrder(Node* node) const {
    if (node == nullptr) return;
    postOrder(node->left);
    postOrder(node->right);
    node->data->print();
}


int main() {
    RedBlackTree<GameObject> tree;

    tree.insert(new Tank(1, 50.0f, 500, "Forest DDPAT", 100));
    tree.insert(new Shell(2, 10.0f, 120));
    tree.insert(new Tank(3, 45.0f, 600, "Desert", 120));

    cout << "Симметричный обход:\n";
    tree.printInOrder();

    cout << "\nПрямой обход:\n";
    tree.printPreOrder();

    cout << "\nОбратный обход:\n";
    tree.printPostOrder();

    cout << "\nУдаление ID = 2\n";
    tree.remove(2);

    cout << "\nСимметричный обход после удаления:\n";
    tree.printInOrder();

    return 0;
}
