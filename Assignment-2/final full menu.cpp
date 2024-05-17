#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class item {
private:
    int price;
    string name;
    string category;

public:
    item(int p, string n, string c);
    string getName() const;
    int getPrice() const;
    string getCategory() const;
    void SetName(const string& newName);
    void SetCategory(const string& newCategory);
    void SetPrice(const int& newPrice);
    bool operator<(const item& i) const;
    bool operator>(const item& i) const;
    bool compareByPrice(const item& i) const;
    void print() const;
};

item::item(int p, string n, string c) : price(p), name(n), category(c) {}

string item::getName() const {
    return name;
}
string item::getCategory() const {
    return category;
}
int item::getPrice() const {
    return price;
}
void item::SetName(const string& newName) {
    name = newName;
}
void item::SetCategory(const string& newCategory) {
    category = newCategory;
}
void item::SetPrice(const int& newPrice) {
    price = newPrice;
}
bool item::operator<(const item& i) const {
    return this->name < i.name;
}
bool item::operator>(const item& i) const {
    return this->name > i.name;
}

bool compareByName(const item& i1, const item& i2) {
    return i1.getName() < i2.getName();
}

bool compareByCategory(const item& i1, const item& i2) {
    return i1.getCategory() < i2.getCategory();
}

bool compareByPrice(const item& i1, const item& i2) {
    return i1.getPrice() < i2.getPrice();
}
bool item::compareByPrice(const item& i) const {
    return this->price < i.price;
}
void item::print() const {
    cout << "Item name: " << name << "  Item price: " << price << "  Item category: " << category << endl;
}

void readItems(const string& filename, vector<item>& items) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening the file, please try again." << endl;
        return;
    }
    string line;
    int price;
    string name, category;
    while (file >> price) {
        file.ignore();
        getline(file, name);
        getline(file, category);
        items.emplace_back(price, name, category);
    }
    file.close();
}
void printVectorItems(const vector<item>& items) {
    for (const auto& item : items) {
        item.print();
    }
}


class Heap {
public:
    void Minheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&));
    void Maxheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&));
    void buildHeap(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending);
    void heapSort(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending);
    void insertNodeToHeap(vector<item>& items, int n, const item& newnode, bool (*comp)(const item&, const item&), bool ascending);
    void deleteNodeFromHeap(vector<item>& items, int n, int idx, bool (*comp)(const item&, const item&), bool ascending);
};

void Heap::Minheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&)){
    item tmp=items[i];
    int smallIndex=i*2 + 1;
    while(smallIndex<=n){
        if(smallIndex< n){
            if(comp(items[smallIndex],items[smallIndex + 1])){
                smallIndex += 1;
            }
        }
        if(!comp(tmp, items[smallIndex])){
            break;
        }
        else{
            items[i]= items[smallIndex];
            i= smallIndex;
            smallIndex= 2*i +1;
        }
    }
    items[i]=tmp;
}
void Heap::Maxheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&)){

    item tmp=items[i];
    int largeIndex= i*2 +1;
    while(largeIndex<= n){
        if(largeIndex< n) {
            if(!comp(items[largeIndex],items[largeIndex + 1])){
                largeIndex+= 1;
            }
        }
        if(comp(tmp, items[largeIndex])){
            break;
        }
        else{
            items[i]= items[largeIndex];
            i= largeIndex;
            largeIndex=2*i +1;
        }
    }
    items[i]=tmp;
}

void Heap::buildHeap(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending){
    for(int index=n/2 -1;index>=0;index--){
        if(ascending){
            Minheapify(items,index,n - 1,comp);
        }
        else{
            Maxheapify(items,index,n - 1,comp);
        }
    }
}
void Heap::heapSort(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending){
    if(ascending){
        bool minHeap=true;
        buildHeap(items,n,comp,minHeap);
        for(int i=n-1;i>=0;i--){
            item tmp=items[i];
            items[i]=items[0];
            items[0]=tmp;
            if(ascending){
                Minheapify(items,0,i - 1,comp);
            }
            else{
                Maxheapify(items,0,i - 1,comp);
            }
        }
    }
    else {
        bool minHeap=false;
        buildHeap(items,n,comp,minHeap);
        for(int i=n - 1; i>= 0; i--) {
            item tmp=items[0];
            items[0]=items[i];
            items[i]=tmp;
            Maxheapify(items,0,i-1,comp);
        }
    }
}
void Heap::insertNodeToHeap(vector<item>& items, int n, const item& newnode, bool (*comp)(const item&, const item&), bool ascending){
    items.push_back(newnode);
    heapSort(items,items.size(),comp,ascending);
}
void Heap::deleteNodeFromHeap(vector<item>& items, int n, int idx, bool (*comp)(const item&, const item&), bool ascending){
    if(idx>=n){
        cout<<"out of range, please enter another index"<<endl;
        return;
    }
    items[idx]=items.back();
    items.pop_back();
    n=items.size();
    heapSort(items,n,comp,ascending);
}

/*************************************************AVL Tree**************************************************/
class Node {
public:
    item data;
    Node* left;
    Node* right;
    int height;

    Node(item itemData)
        : data(itemData), left(nullptr), right(nullptr), height(1) {}
};
// AVL Tree class
class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        //if node exit return height el
        if (node != NULL)
        {
            return node->height;
        }
        else {
            return 0;
        }
    }

    int getBalanceFactor(Node* node) {
        if (node != NULL)
        {
            return height(node->left) - height(node->right);
        }
        else
        {
            return 0;
        }

    }

    Node* rightRotate(Node* y) { // y is the root
        Node* x = y->left;  // x is left to y
        Node* B = x->right; // beta(B) is the right sub tree of node x
        // gama which is the left subtree to node x will be the same
        // alpha which is the right subtree to node y will be same as it greater than x and y

         /*      y                    x
         *      / \                  /  \
         *      x  alpha    --->    gama  y
         *     /  \                 /      \
         *    gama  B              B       alpha
         */

         // Perform rotation
        x->right = y;
        y->left = B;

        // Update height
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return pointer to the new root
        return x;
    }

    Node* leftRotate(Node* x) { // x is the root
        Node* y = x->right;// y is left to x
        Node* B = y->left;// B (beta) is left to y
        // alpha is subtree left to x and it will be the same as it small than x and x small than y (it is the smallest)
        // gama is subtree right to y and it will be same

        /*     x                     y
        *     /  \                  / \
        *  alpha  y    ---->       x   gama
                 / \              /  \
                B   gama       alpha  B
        */

        // Perform rotation
        y->left = x;
        x->right = B;

        // Update heights
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        // Return pointer to new root
        return y;
    }

    Node* insert(Node* node, item itemData) {
        if (!node) return new Node(itemData);

        if (itemData < node->data)
            node->left = insert(node->left, itemData);
        else if (node->data < itemData)
            node->right = insert(node->right, itemData);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (itemData < node->left->data) {
                return rightRotate(node);
            }
            else if (node->left->data < itemData) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (node->right->data < itemData) {
                return leftRotate(node);
            }
            else if (itemData < node->right->data) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }
    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            node->data.print();
            inorderTraversal(node->right);
        }
    }
    void preorderTraversal(Node* root) {
        if (root) {
            root->data.print();
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
    }
    void printDescending(Node* root) {
        if (root) {
            printDescending(root->right);
            root->data.print();
            printDescending(root->left);
        }
    }
    // Function to delete a node with given data
    Node* deleteNode(Node* root, item data) {
        //  Perform delete as BTS
        if (root == NULL)
            return root;

        // If the data to be deleted is smaller than the root's data,
        // then it lies in left subtree
        if (data < root->data)
            root->left = deleteNode(root->left, data);

        // If the data to be deleted is greater than the root's data,
        // then it lies in right subtree
        else if (data > root->data)
            root->right = deleteNode(root->right, data);

        // If data is same as root's data, then this is the node to be deleted
        else {
            // node with only one child or no child
            if ((root->left == NULL) || (root->right == NULL)) {
                Node* temp;
                if (root->left != NULL) {
                    temp = root->left;
                }
                else {
                    temp = root->right;
                }

                // No child case
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else // One child case
                    *root = *temp; // Copy the contents of the non-empty child
                delete temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                Node* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr)
            return root;

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = getBalanceFactor(root);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    // to find the node with minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(item itemData) {
        root = insert(root, itemData);
    }
    void deleteItem(item key) {
        root = deleteNode(root, key);
    }

    void displayInorder() {
        inorderTraversal(root);
    }

    void displayPreorder() {
        preorderTraversal(root);
    }

    void displayDescending() {
        printDescending(root);
    }
};

void displayAVLMenu() {
    cout << "AVL Tree Operations:\n";
    cout << "1. Add item data\n";
    cout << "2. Remove item data\n";
    cout << "3. Display the item data normally\n";
    cout << "4. Display all the items sorted by their name ascending\n";
    cout << "5. Display all the items sorted by their name descending\n";
    cout << "6. Display all the items sorted by their prices ascending\n";
    cout << "7. Display all the items sorted by their prices descending\n";
    cout << "0. Exit\n";
}
/************************************************************************************************************************************************/

class item2 {
private:
    int price;
    string name;
    string category;

public:
    item2(int p, string n, string c);
    string getName() const;
    int getPrice() const;
    string getCategory() const;
    void SetName(const string& newName);
    void SetCategory(const string& newCategory);
    void SetPrice(const int& newPrice);
    bool operator<(const item2& i) const;
    bool operator>(const item2& i) const;
    void print() const;
};

item2::item2(int p, string n, string c) : price(p), name(n), category(c) {}

string item2::getName() const {
    return name;
}
string item2::getCategory() const {
    return category;
}
int item2::getPrice() const {
    return price;
}
void item2::SetName(const string& newName) {
    name = newName;
}
void item2::SetCategory(const string& newCategory) {
    category = newCategory;
}
void item2::SetPrice(const int& newPrice) {
    price = newPrice;
}
bool item2::operator<(const item2& i) const {
    return this->price < i.price;
}
bool item2::operator>(const item2& i) const {
    return this->price > i.price;
}

bool sortByPriceAscendingly2(const item2& i, const item2& i2) {
    return i.getPrice() < i2.getPrice();
}
bool sortByPriceDescendingly2(const item2& i, const item2& i2) {
    return i.getPrice() > i2.getPrice();
}
bool sortByCategoryAscendingly2(const item2& i, const item2& i2) {
    return i.getCategory() < i2.getCategory();
}
bool sortByCategoryDescendingly2(const item2& i, const item2& i2) {
    return i.getCategory() > i2.getCategory();
}
void item2::print() const {
    cout << "Item name: " << name << "  Item price: " << price << "  Item category: " << category << endl;
}
void readItems2(const string& filename, vector<item2>& items) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening the file, please try again." << endl;
        return;
    }

    string line;
    int price;
    string name, category;

    while (file >> price) {
        file.ignore();
        getline(file, name);
        getline(file, category);
        items.emplace_back(price, name, category);
    }

    file.close();
}

void printVectorItems2(const vector<item2>& items) {
    for (const auto& item2 : items) {
        item2.print();
    }
}


class Node2 {
public:
    item2 data;
    Node2* left;
    Node2* right;
    int height;

    Node2(item2 itemData)
        : data(itemData), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class
class AVLTree2 {
private:
    Node2* root;

    int height(Node2* node) {
        //if node exit return height el
        if (node != NULL)
        {
            return node->height;
        }
        else {
            return 0;
        }
    }

    int getBalanceFactor(Node2* node) {
        if (node != NULL)
        {
            return height(node->left) - height(node->right);
        }
        else
        {
            return 0;
        }

    }

    Node2* rightRotate(Node2* y) { // y is the root
        Node2* x = y->left;  // x is left to y
        Node2* B = x->right; // beta(B) is the rigth sub tree of node x
        // gama which is the left subtree to node x will be the same
        // alpha which is the right subtree to node y will be same as it greater than x and y

         /*      y                    x
         *      / \                  /  \
         *      x  alpha    --->    gama  y
         *     /  \                 /      \
         *    gama  B              B       alpha
         */

         // Perform rotation
        x->right = y;
        y->left = B;

        // Update height
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return pointer to the new root
        return x;
    }

    Node2* leftRotate(Node2* x) { // x is the root
        Node2* y = x->right;// y is left to x
        Node2* B = y->left;// B (beta) is left to y
        // alpha is subtree left to x and it will be the same as it small than x and x small than y (it is the smallest)
        // gama is subtree rigth to y and it will be same

        /*     x                     y
        *     /  \                  / \
        *  alpha  y    ---->       x   gama
                 / \              /  \
                B   gama       alpha  B
        */

        // Perform rotation
        y->left = x;
        x->right = B;

        // Update heights
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        // Return pointer to new root
        return y;
    }

    Node2* insert(Node2* node, item2 itemData) {
        if (!node) return new Node2(itemData);

        if (itemData < node->data)
            node->left = insert(node->left, itemData);
        else if (node->data < itemData)
            node->right = insert(node->right, itemData);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (itemData < node->left->data) {
                return rightRotate(node);
            }
            else if (node->left->data < itemData) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (node->right->data < itemData) {
                return leftRotate(node);
            }
            else if (itemData < node->right->data) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }



    void inorderTraversal(Node2* node) {
        if (node) {
            inorderTraversal(node->left);
            node->data.print();
            inorderTraversal(node->right);
        }
    }
    void preorderTraversal(Node2* root) {
        if (root) {
            root->data.print();
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
    }
    void printDescending(Node2* root) {
        if (root) {
            printDescending(root->right);
            root->data.print();
            printDescending(root->left);
        }
    }

    // Function to delete a node with given data
    Node2* deleteNode(Node2* root, item2 data) {
        //  Perform delete as BTS
        if (root == NULL)
            return root;

        // If the data to be deleted is smaller than the root's data,
        // then it lies in left subtree
        if (data < root->data)
            root->left = deleteNode(root->left, data);

        // If the data to be deleted is greater than the root's data,
        // then it lies in right subtree
        else if (data > root->data)
            root->right = deleteNode(root->right, data);

        // If data is same as root's data, then this is the node to be deleted
        else {
            // node with only one child or no child
            if ((root->left == NULL) || (root->right == NULL)) {
                Node2* temp;
                if (root->left != NULL) {
                    temp = root->left;
                }
                else {
                    temp = root->right;
                }

                // No child case
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else // One child case
                    *root = *temp; // Copy the contents of the non-empty child
                delete temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                Node2* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr)
            return root;

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = getBalanceFactor(root);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    // to find the node with minimum value
    Node2* minValueNode(Node2* node) {
        Node2* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }




public:
    AVLTree2() : root(nullptr) {}

    void insert(item2 itemData) {
        root = insert(root, itemData);
    }

    void deleteItem(item2 key) {
        root = deleteNode(root, key);
    }
    void displayInorder() {
        inorderTraversal(root);
    }

    void displayPreorder() {
        preorderTraversal(root);
    }

    void displayDescending() {
        printDescending(root);
    }


};

bool ascendingORdescending(int &input){
    if (input == 1) {
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************************************************/
class BST_Node {
public:
    BST_Node* leftptr;
    BST_Node* rightptr;
    item data;
    BST_Node(item itemdata) : data(itemdata), leftptr(nullptr), rightptr(nullptr) {}
};
class BST {
public:
    BST_Node* root;
    BST() {
        root = NULL;
    }
    BST_Node* minValueNode(BST_Node* node) {
        BST_Node* current = node;
        while (current && current->leftptr != NULL)
            current = current->leftptr;
        return current;
    }
    bool IsEmpty() {
        return root == NULL;
    }
    void AddItemByName(BST_Node*& node, const item& ItemData) {
    BST_Node* newNode = new BST_Node(ItemData);
    if (node == nullptr) {
        node = newNode;
        return;
    }
    BST_Node* current = node;
    while (true) {
        if (ItemData < current->data) {
            if (current->leftptr == nullptr) {
                current->leftptr = newNode;
                break;
            } else {
                current = current->leftptr;
            }
        } else {
            if (current->rightptr == nullptr) {
                current->rightptr = newNode;
                break;
            } else {
                current = current->rightptr;
            }
        }
    }
}

    void AddItemByPrice(BST_Node*& node, const item& ItemData) {
    BST_Node* newNode = new BST_Node(ItemData);
    if (node == nullptr) {
        node = newNode;
        return;
    }

    BST_Node* current = node;
    while (true) {
        if (ItemData.compareByPrice(current->data)) {
            if (current->leftptr == nullptr) {
                current->leftptr = newNode;
                break;
            } else {
                current = current->leftptr;
            }
        } else {
            if (current->rightptr == nullptr) {
                current->rightptr = newNode;
                break;
            } else {
                current = current->rightptr;
            }
        }
    }
}
    void AddItemByName(const item& ItemData) {
        AddItemByName(root, ItemData);
    }
    void AddItemByPrice(const item& ItemData) {
        AddItemByPrice(root, ItemData);
    }
    void DisplayInOrder(BST_Node* node) {
        if (node != nullptr) {
            DisplayInOrder(node->leftptr);
            node->data.print();
            DisplayInOrder(node->rightptr);
        }
    }
    void DisplayReverseOrder(BST_Node* node) {
        if (node != nullptr) {
            DisplayReverseOrder(node->rightptr);
            node->data.print();
            DisplayReverseOrder(node->leftptr);
        }
    }
    void DisplayNameAsc() {
        DisplayInOrder(root);
    }
    void DisplayNameDesc() {
        DisplayReverseOrder(root);
    }
    void DisplayPriceAsc() {
        DisplayInOrder(root);
    }
    void DisplayPriceDesc() {
        DisplayReverseOrder(root);
    }
    // Remove item from BST by name
    BST_Node* RemoveItemByName(BST_Node* node, const item& ItemData) {
        if (node == nullptr) return node;
    //HAS 2 CHILD
        if (ItemData < node->data) {
            node->leftptr = RemoveItemByName(node->leftptr, ItemData);
        } else if (ItemData > node->data) {
            node->rightptr = RemoveItemByName(node->rightptr, ItemData);
        } else {
            // Node with only one child or no child
            if (node->leftptr == nullptr) {
                BST_Node* temp = node->rightptr;
                delete node;
                return temp;
            } else if (node->rightptr == nullptr) {
                BST_Node* temp = node->leftptr;
                delete node;
                return temp;
            }

            //MINVALUE GET SUCCESSOR
            BST_Node* temp = minValueNode(node->rightptr);
            node->data = temp->data;
            node->rightptr = RemoveItemByName(node->rightptr, temp->data);
        }
        return node;
    }
    void RemoveItemByName(const item& ItemData) {
        root = RemoveItemByName(root, ItemData);
    }
    // Remove item from BST by price
    BST_Node* RemoveItemByPrice(BST_Node* node, const item& ItemData) {
        if (node == nullptr) return node;
        if (ItemData.compareByPrice(node->data)) {
            node->leftptr = RemoveItemByPrice(node->leftptr, ItemData);
        } else if (node->data.compareByPrice(ItemData)) {
            node->rightptr = RemoveItemByPrice(node->rightptr, ItemData);
        } else {
            // Node with only one child or no child
            if (node->leftptr == nullptr) {
                BST_Node* temp = node->rightptr;
                delete node;
                return temp;
            } else if (node->rightptr == nullptr) {
                BST_Node* temp = node->leftptr;
                delete node;
                return temp;
            }
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            BST_Node* temp = minValueNode(node->rightptr);
            node->data = temp->data;
            node->rightptr = RemoveItemByPrice(node->rightptr, temp->data);
        }
        return node;
    }
    void RemoveItemByPrice(const item& ItemData) {
        root = RemoveItemByPrice(root, ItemData);
    }
};
int main() {
    vector<item> items;
    readItems("try.txt", items);

    vector<item> AVL1items;
    readItems("try.txt", AVL1items);
    AVLTree avlTree;
    for (const auto& it : AVL1items) {
        avlTree.insert(it);
    }
    vector<item2> AVL2items2;
    readItems2("try.txt", AVL2items2);
    AVLTree2 avlTree2;
    for (const auto& it : AVL2items2) {
        avlTree2.insert(it);
    }
    BST bstByName;
    BST bstByPrice;
    for (const auto& item : items) {
        bstByName.AddItemByName(item);
        bstByPrice.AddItemByPrice(item);
    }
    int treeType,choice=-1,input;
    int outerchoice=-1;
    do{
        cout << "Welcome to our online Supermarket Ordering System\n";
        cout << "Please choose the data structure you want to use:\n";
        cout << "1. Binary Search Tree (BST)\n";
        cout << "2. Heaps\n";
        cout << "3. AVL Trees\n";
        cin >> treeType;
        if (treeType == 1){
         do{
            cout << "Please enter what you would like to choose:\n"
                << "1 - Print items before sorting\n"
                << "2 - Sort items by name\n"
                << "3 - Sort items by price\n"
                << "4 - Insert a new item\n"
                << "5 - Delete an item\n"
                << "0 - Exit\n";

            cin >> choice;
            if(choice==1){
                cout << "Before sorting:\n";
                printVectorItems(items);
                cout << endl;
            }
            else if(choice==2){
                cout << "please enter if you want sorting ascending(1) or descending(2)\n";
                cin >> input;
                if(ascendingORdescending(input)){
                    cout << "Items sorted by name (ascending):" << endl;
                    bstByName.DisplayNameAsc();
                }else{
                    cout << "\nItems sorted by name (descending):" << endl;
                    bstByName.DisplayNameDesc();
                }
            }
            else if(choice==3){
                cout << "please enter if you want sorting ascending(1) or descending(2)\n";
                cin >> input;
                if(ascendingORdescending(input)){
                    cout << "\nItems sorted by price (ascending):" << endl;
                    bstByPrice.DisplayPriceAsc();
                }else{
                    cout << "\nItems sorted by price (descending):" << endl;
                    bstByPrice.DisplayPriceDesc();
                }
            }
            else if(choice==4){
                cout << "please enter the item contents you want to insert in order of price, name, category: \n";
                int price;
                string category, name;
                cin >> price >> name >> category;
                item i = { price,name,category };
                bstByName.AddItemByName(i);
                bstByPrice.AddItemByPrice(i);
                cout << "please enter if you want sorting ascending(1) or descending(2)\n";
                cin >> input;
                if(ascendingORdescending(input)){
                    cout << "\nItems sorted by name (ascending) after insertion:" << endl;
                    bstByName.DisplayNameAsc();
                    cout << "\nItems sorted by price (ascending) after insertion:" << endl;
                    bstByPrice.DisplayPriceAsc();
                }else{
                    cout << "\nItems sorted by name (descending) after insertion:" << endl;
                    bstByName.DisplayNameDesc();
                    cout << "\nItems sorted by price (descending) after insertion:" << endl;
                    bstByPrice.DisplayPriceDesc();
                }
            }
            else if(choice==5){
                cout<<"please enter the item contents you want to delete in order of price, name, category: \n";
                int price;
                string category, name;
                cin >> price >> name >> category;
                item itemToRemove = { price,name,category };
                bstByName.RemoveItemByName(itemToRemove);
                bstByPrice.RemoveItemByPrice(itemToRemove);
                cout << "please enter if you want sorting ascending(1) or descending(2)\n";
                cin >> input;
                if(ascendingORdescending(input)){
                    cout << "\nItems sorted by name (ascending) after insertion:" << endl;
                    bstByName.DisplayNameAsc();
                    cout << "\nItems sorted by price (ascending) after insertion:" << endl;
                    bstByPrice.DisplayPriceAsc();
                }else{
                    cout << "\nItems sorted by name (descending) after insertion:" << endl;
                    bstByName.DisplayNameDesc();
                    cout << "\nItems sorted by price (descending) after insertion:" << endl;
                    bstByPrice.DisplayPriceDesc();
                }
            }
            else if(choice==0){
                cout << "Exit...\n";

            }
        }while(choice!=0);
    }

    else if (treeType == 2) {
        Heap heap;
        do{
            cout << "Please enter what you would like to choose:\n"
                << "1 - Print items before sorting\n"
                << "2 - Sort items by name\n"
                << "3 - Sort items by price\n"
                << "4 - Insert a new item\n"
                << "5 - Delete an item\n"
                << "0 - Exit\n";

            cin >> choice;
            if(choice==1){
                cout<<"Before sorting:\n";
                printVectorItems(items);
                cout<<endl;
            }
            else if(choice==2){
                cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
                cin>>input;
                heap.heapSort(items, items.size(), compareByName, ascendingORdescending(input));
                cout<<"Sorted by name:\n";
                printVectorItems(items);
                cout<<endl;
            }
            else if(choice==3){
                cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
                cin>>input;
                heap.heapSort(items, items.size(), compareByPrice, ascendingORdescending(input));
                cout<<"Sorted by price:\n";
                printVectorItems(items);
                cout<<endl;
            }
            else if(choice==4){
                cout<<"please enter the item contents you want to insert in order of price, name, category: \n";
                int price;
                string category, name;
                cin>>price>>name>>category;
                item i={price,name,category};
                cout<<"please enter whether to sort by price or name\n"
                <<"if by price type: 1\n"
                <<"if by name type: 2\n";
                bool (*comp)(const item&, const item&);
                cin>>input;
                if(input==1){
                    comp=compareByPrice;
                }else if(input==2){
                    comp=compareByName;
                }else{
                    cout<<"invalid input\n";
                }
                cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
                cin>>input;
                heap.insertNodeToHeap(items, items.size(), i, comp, ascendingORdescending(input));
                cout<<"Sorted by price after inserting a new node:\n";
                printVectorItems(items);
                cout<<"items size after insertion:" << items.size() << endl;
            }
            else if(choice==6){
                int index,input2;
                cout<<"please enter the index of the item you want to delete: \n";
                cin>>index;
                cout<<"please enter whether to sort by price or name\n"
                <<"if by price type: 1\n"
                <<"if by name type: 2\n";
                bool (*comp)(const item&, const item&);
                cin>>input2;
                if(input2==1){
                    comp=compareByPrice;
                }else if(input2==2){
                    comp=compareByName;
                }else{
                    cout<<"invalid input\n";
                }
                cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
                cin>>input;
                heap.deleteNodeFromHeap(items, items.size(), index, comp, ascendingORdescending(input));
                printVectorItems(items);
                cout<<"items size after deletion:" << items.size() << endl;
            }
            else if(choice==0){
                cout<<"Exit...\n";
            }
        }while(choice!=0);
    }

    else if (treeType == 3){
        int n = -1;
        do {
            displayAVLMenu();
            cin >> n;

            if (n == 1) {
                string name, category;
                int price;
                cout << "Enter the data about the item you want to insert in order of price, name, category: \n";
                cin >> price >> name >> category;
                item i = { price,name,category };
                item2 i2 = { price,name,category };
                avlTree.insert(i);
                avlTree2.insert(i2);

            }
            else if (n == 2)
            {
                string name, category;
                int price;
                cout << "Enter the data about the item you want to delete in order of price, name, category: \n";
                cin >> price >> name >> category;
                item i = { price,name,category };
                avlTree.deleteItem(i);
                item2 i2 = { price,name,category };
                avlTree2.deleteItem(i2);
            }
            else if (n == 3)
            {
                cout << "Before sorting:\n";
                avlTree.displayPreorder();
                cout << endl;
            }
            else if (n == 4)
            {

                avlTree.displayInorder();
            }
            else if (n == 5)
            {

                avlTree.displayDescending();
            }
            else if (n == 6)
            {
                avlTree2.displayInorder();

            }
            else if (n == 7)
            {
                avlTree2.displayDescending();

            }
            else if (n == 0)
            {
                cout << "Exit...\n";
            }
        } while (n != 0);
    }
    cout<<"If you want to continue press 1 and if you want to exit the program press 0\n";
    cin>>outerchoice;
    }while(outerchoice!=0);

    return 0;
}
