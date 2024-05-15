/**********************************************************************************************************/
class BST_Node{
public:
    BST_Node *leftptr;
    BST_Node *rightptr;
    item data;
    BST_Node(item itemdata): data(itemdata), leftptr(nullptr),rightptr(nullptr) {}
};
class BST{
public:
    BST_Node* root;
    BST() {
        root=NULL;
    }
    BST_Node* minValueNode(BST_Node* node) {
        BST_Node* current = node;
        while (current && current->leftptr != NULL)
            current = current->leftptr;
        return current;
    }
    bool IsEmprty(){
        return root==NULL;
    }
    void AddItem(BST_Node*& node ,const item& ItemData) {
        BST_Node* New_node= new BST_Node(ItemData);
        if (node==nullptr) {
            node= New_node;
        }else{
            BST_Node  *c = node;
            BST_Node * prev = NULL;
        while (c != nullptr) {//to get position that insert into to it
            prev = c;
            if (ItemData < c->data) {
                c = c->leftptr;
            } else {
                c = c->rightptr;
            }
        }//check if node insert as a right child or left child
        if (ItemData < prev->data) {
            prev->leftptr = New_node;
        } else {
            prev->rightptr = New_node;
        }
        }

    }
