#include <iostream>  //include cout

using std::cout;

#include <algorithm>  //include the max function
using std::max;

template <typename T> class BSTree;  //class BSTree definition

template <typename T>  //Declaration of the BSNode Template class
class BSNode{
    //Value contained inside the node
    T value;
    //Pointers to a left and a right node, used to create the binary tree structure
    BSNode<T> *left;
    BSNode<T> *right;

    //Class constructor
    explicit BSNode(const T & val);

    //Returns the number of elements inside the tree
    int node_size() const;
    //Insert a value inside the structure, respecting the Bynary Search Tree structure
    int node_insert(const T & data);
    //Print nodes in preorder
    void node_print_pre();
    //Print nodes in Inorder
    void node_print_in();
    //Print nodes in postorder
    void node_print_post();
    //return the heigth of the tree
    int node_height(void) const;
    //clear the memory of the tree
    void node_clear();
    //copy all the nodes in the tree
    BSNode<T>* copy_tree(const BSNode<T> *other);
    //find a node in the tree
    int node_find(T & data);

    // We will make BSTree friend, so it can access directly the methods and
    // values of BSNode
    friend class BSTree<T>;
};

template <typename T>  //Definition of the BSTree template class
class BSTree{
    //pointer to the root of the tree
    BSNode<T> * root;
public:
    //Enumerator used for an easyer understanding of the return values
    //of some of the functions
    enum {BST_OK = 0, BST_DUPLICATE = -1, BST_NOT_FOUND = -2};

    //Class default constructor
    BSTree();
    //Copy constructor
    BSTree(const BSTree<T> &);

    //Clears all of the nodes out of the tree and resets it to be an empty tree.
    void clear(void);
    //Insert additional data in the tree
    int insert(const T & data);
    //calculate and return the height of the tree
    int height(void) const;
    //calculate and returns the number of nodes in the tree
    int size(void) const;
    //Print the tree with preorder traversal
    void print_pre(void) const;
    //print the tree with inorder traversal
    void print_in(void) const;
    //print the tree with portorder traversal
    void print_post(void) const;

    //Find if a value is in the tree
    int find(T & val) const;

    //Assignment operators
    BSTree<T> & operator = (const BSTree<T> &);
    BSTree<T> & operator = (BSTree<T> &&);

    //Destructor
    ~BSTree<T>();
};

/*******************************************************************************
 * Class constructor
 *
 * This constructor is called when a new object is created by passing a T variable
 * as input
 ******************************************************************************/
template <typename T>
BSNode<T>::BSNode(const T & val){
    //assign the input value
    value=val;
    //set the left and right pointer node to NULL
    left=nullptr;
    right=nullptr;
}

/*******************************************************************************
 * Class default constructor
 * This constructor is called when a new object is created without passing any
 * argument as input
 ******************************************************************************/
template <typename T>
BSTree<T>::BSTree(){
    //initialize the tree root node to a null pointer
    root=nullptr;
}

/*******************************************************************************
 * Copy constructor for the BSTree class.
 ******************************************************************************/
template <typename T>
BSTree<T>::BSTree(const BSTree<T> &other){
    // call the copy_tree method over the root of the other tree, which returns
    // the head node of the node structure.
    // we then assign the head of the node structure to the root pointer.
    this->root=other.root->copy_tree(other.root);
}

/*******************************************************************************
 * Copy tree method.
 * This method gets in input a BSNode, and makes an exact copy of it.
 * It then returns the created tree structure to the caller.
 ******************************************************************************/
template <typename T>
BSNode<T>* BSNode<T>::copy_tree(const BSNode<T> *other){
    //if the other node is null, we finished visiting this branch, so we
    //just rerutn null
    if(other==nullptr){
        return nullptr;
    }

    //create a new node, copying the value of the current visited node
    BSNode<T>* new_node = new BSNode(other->value);

    //recursively replicate the scructure of the tree by calling the copy_tree
    // method for both the left and the right branch
    new_node->left=copy_tree(other->left);
    new_node->right=copy_tree(other->right);

    //return a pointer to the newly created node structure
    return new_node;
}

/*******************************************************************************
 * Size method
 *
 * This method calculates the number of nodes instantiated in the tree
 ******************************************************************************/
template <typename T>
int BSTree<T>::size() const{
    //if the root is null, then the tree is an empty tree, so return 0
    if(root==nullptr){
        return 0;
    }
    //if not, run the node_size function, that recursively goes through thre
    // node tree structure, and performs the contu of the nodes
    else{
        return root->node_size();
    }
}

/*******************************************************************************
 * Node_size Function
 *
 * Recursively perform the count of all the nodes in the tree, starting from
 * the current node
 ******************************************************************************/
template <typename T>
int BSNode<T>::node_size() const{
    //initialize a variable to 1, that will be the counted value for the current node
    int i=1;
    //if the left branch if not null, then we have to analyze it and count the
    //number of nodes it contains.
    if(left!=nullptr){
        //we sum the number of nodes counted in the left branch, with the one
        //currently available
        i+=left->node_size();
    }
    //if the right branch if not null, then we have to analyze it and count the
    //number of nodes it contains.
    if(right!=nullptr){
        //we sum the number of nodes counted in the right branch, with the one
        // counted up to now
        i+=right->node_size();
    }
    //return the number of counted nodes
    return i;
}

/*******************************************************************************
 * Insert Function
 *
 * Function used to insert data inside the tree structure
 ******************************************************************************/
template <typename T>
int BSTree<T>::insert(const T & data){
    //if the root of the tree is null, then the tree is empty
    if(root==nullptr){
        //initialize the root of the tree to a new node containing the input data
        root=new BSNode<T>(data);
        //return BST_OK to confirm the correctness of the operation
        return BST_OK;
    }
    //if the tree is not empty, call the function node_insert, to recursively go
    //trough the nodes, and find the correct location where to insert the node
    else{
        //once finished, return the new structure.
        return root->node_insert(data);
    }
}

/*******************************************************************************
 * node_insert Function
 *
 * Function used to insert recursively go trough the nodes, and find the correct
 * location where to insert the node
 ******************************************************************************/
template <typename T>
int BSNode<T>::node_insert(const T & data){
    //We can't have empty nodes, as there's only a constructor that build the node with
    //some data inside. So we can avoid checking for the nullptr case for the current node
    if(data < value){ //our value is less than the value of the current node, go left
        //if left is null, that's where we are going to insert our new node
        if(left==nullptr){
            //create a new node, and attach it to the left of the current node
            left = new BSNode(data);
            //return the code to confirm the correctness of the insert
            return BSTree<T>::BST_OK;
        }
        //if left is not null, then keep descending the tree on the left branch
        return left->node_insert(data);
    }
    else if (data > value){ //our value is greater than the value of the current node, go right
        //if right is null, that's where we are going to insert our new node
        if(right==nullptr){
            //create a new node, and attach it to the right of the current node
            right = new BSNode<T>(data);
            //return the code to confirm the correctness of the insert
            return BSTree<T>::BST_OK;
        }
        //if right is not null, then keep descending the tree on the left branch
        return right->node_insert(data);
    }
    //if it's not bigger or smaller than the current, it means it's equal. so
    //we return a duplicate error message
    return BSTree<T>::BST_DUPLICATE;
}

/*******************************************************************************
 * print_pre Function
 *
 * Print the content of the tree descending the tree with a preorder traversal
 * algorithm
 ******************************************************************************/
template <typename T>
void BSTree<T>::print_pre(void) const{
    //if the root is null, then we don't have nothing to print. if not, call the
    //method node_print_pre to print the values in all the nodes
    if(root!=nullptr){
        return root->node_print_pre();
    }
}

/*******************************************************************************
 * node_print_pre Function
 *
 * Print the content of the tree structure descending the tree with a preorder
 * traversal algorithm
 ******************************************************************************/
template <typename T>
void BSNode<T>::node_print_pre(){
    //print the current node value
    cout << value << " ";
    //descend the tree on the left if the left branch is not null
    if(left!=nullptr){
        left->node_print_pre();
    }
    //descend the tree on the right if the right branch is not null
    if(right!=nullptr){
        right->node_print_pre();
    }
}

/*******************************************************************************
 * print_in Function
 *
 * Print the content of the tree descending the tree with a inorder traversal
 * algorithm
 ******************************************************************************/
template <typename T>
void BSTree<T>::print_in(void) const{
    //if the root is null, then we don't have nothing to print. if not, call the
    //method node_print_pre to print the values in all the nodes
    if(root!=nullptr){
        return root->node_print_in();
    }
}

/*******************************************************************************
 * print_in Function
 *
 * Print the content of the treestructure descending the tree with a inorder
 * traversal algorithm
 ******************************************************************************/
template <typename T>
void BSNode<T>::node_print_in(){
    //descend the tree on the left if the left branch is not null
    if(left!=nullptr){
        left->node_print_in();
    }

    //print the current value
    cout << value << " ";

    //descend the tree on the right if the right branch is not null
    if(right!=nullptr){
        right->node_print_in();
    }
}

/*******************************************************************************
 * print_post Function
 *
 * Print the content of the tree descending the tree with a postorder traversal
 * algorithm
 ******************************************************************************/
template <typename T>
void BSTree<T>::print_post(void) const{
    //if the root is null, then we don't have nothing to print. if not, call the
    //method node_print_pre to print the values in all the nodes
    if(root!=nullptr){
        return root->node_print_post();
    }
}

/*******************************************************************************
 * print_post Function
 *
 * Print the content of the tree structure descending the tree with a postorder
 * traversal algorithm
 ******************************************************************************/
template <typename T>
void BSNode<T>::node_print_post(){
    //descend the tree on the left if the left branch is not null
    if(left!=nullptr){
        left->node_print_post();
    }
    //descend the tree on the right if the right branch is not null
    if(right!=nullptr){
        right->node_print_post();
    }

    //print the current value
    cout << value << " ";
}

/*******************************************************************************
 * height Function
 *
 * calculate the height of the tree
 ******************************************************************************/
template <typename T>
int BSTree<T>::height(void) const{
    //if the tree is empty, then it's heigth is zero
    if(root==nullptr){
        return 0;
    }
    //if it/s not empty, then traverse the tree to calculate the height, by
    // using the function node_heigth
    else{
        //return the calculated node height
        return root->node_height();
    }
}

/*******************************************************************************
 * height Function
 *
 * calculate the height of the tree structure, by recursively calculating at each
 * visited node the hight of the left and right branch, and then returning 1 +
 * the maximum number of nodes between the left and the right branch.
 ******************************************************************************/
template <typename T>
int BSNode<T>::node_height(void) const{
    //initialize the number of nodes on the left and right branch to be zero
    int left_n = 0;
    int right_n = 0;

    //if the left branch in not null, then calculate it's height
    if(left!=nullptr){
        left_n=left->node_height();
    }
    //if the right branch is not null, then calculate it's height
    if(right!=nullptr){
        right_n=right->node_height();
    }
    //return the height of the current tree, as the maximum height between the
    //height of the left and the right branch, plus 1 (the current node)
    return 1+max(left_n,right_n);
}

/*******************************************************************************
 * clear Function
 *
 * the current function takes care of clearing the momery allocated by the tree
 ******************************************************************************/
template <typename T>
void BSTree<T>::clear(void){
    //if the root of the tree is null, then do nothing
    if(root!=nullptr){
        //if the root is not null, call the nodeclear function, that will perform
        // a deep clean of all the nodes of the tree
        root->node_clear();
        //reset the root pointer to be a null pointer
        root=nullptr;
    }
}

/*******************************************************************************
 * node_clear Function
 *
 * the current function  function, that will perform a deep clean of all the
 * nodes of the tree structure, starting froma defined node
 ******************************************************************************/
template <typename T>
void BSNode<T>::node_clear(){
    //we will delete first the leafs and then the nodes, as if we deleted first
    // the nodes and then tle leafs we would lose access to the memory location
    // creating a memory leak. for this reason we will perform the clear using
    // a port_order traversal

    //if the left branch is not null, then descend on the left branch
    if(left!=nullptr){
        left->node_clear();
    }
    //if the right branch is not null, then descend on the right branch
    if(right!=nullptr){
        right->node_clear();
    }
    //reset the left and right branch to point to null
    left=nullptr;
    right=nullptr;
    //delete the current object
    //https://isocpp.org/wiki/faq/freestore-mgmt#delete-this
    delete this;
}

/*******************************************************************************
 * Assignment operator
 ******************************************************************************/
template <typename T>
BSTree<T> & BSTree<T>::operator = (const BSTree<T> & other){
    //check for assignment to self
    if(this!=&other){
        //clear the memory of the current tree
        this->clear();
        //reassign the current tree, to be a copy of the other tree
        this->root=other.root->copy_tree(other.root);
    }
    //return a reference to the newly copied tree
    return *this;
}

/*******************************************************************************
 * Move constructor operator
 ******************************************************************************/
template <typename T>
BSTree<T> & BSTree<T>::operator = (BSTree<T> && other){
    //point the current root to the other tree root
    this->root=other.root;
    //point the other tree root to null, so when the descructor will get called
    //on that structure, it won't deallocate the memoty that we are now letting
    //this object to point at
    other.root=nullptr;
    //return a reference to this object
    return *this;
}

/*******************************************************************************
 * find Function
 *
 * the current function will return an integer representing the exit codes
 * available in the enum declared in the class. if the element with value val
 * is found in the tree, the method will return BS_OK, if not the method will
 * return BST_NOT_FOUND
 ******************************************************************************/
template <typename T>
int BSTree<T>::find(T & val) const{
    //if the root is null, the tree is empty. so it's impossible that any value
    //can be found in the tree. so return BST_NOT_FOUND
    if(root==nullptr){
        return BST_NOT_FOUND;
    }
    //if the tree is not null, then call the node_find function to perform
    // a traverse between all the node of the tree
    else{
        return root->node_find(val);
    }
}

/*******************************************************************************
 * node_find Function
 *
 * the current function will performa traverse between all the node of the tree,
 * to see it it can find the input value, between all the linked nodes
 ******************************************************************************/
template <typename T>
int BSNode<T>::node_find(T & data){
    //if the value we are searching is the current one, then we are done and we
    //can return the value BST_OK
    if(data == value){
        return BSTree<T>::BST_OK;
    }

    //if not, then we have to go through the tree. beinb this tree a BST, then we
    //know that the value on the left are smaller than the current one, while
    //the alue on the right are bigger than the current one. Using this, we can
    //search the value in this way

    if(data < value){ //our value is less than the value of the current node, go left
        //if the left branch is not null, then keep searching on the left branch
        if(left!=nullptr){
            return left->node_find(data);
        }
    }
    else if (data > value){ //our value is greater than the value of the current node, go right
        //if the right branch is not null, then keep searching on the right branch
        if(right!=nullptr){
            return right->node_find(data);
        }
    }
    //if the current value is not equal to what we were searching, and if we
    //weren't able to search in the left and right branch because they were both
    //null, it means that we reached a leaf, that is not equal to the value we were
    //searching. so the value is not inside the tree
    return BSTree<T>::BST_NOT_FOUND;
}

/*******************************************************************************
 * destructor method
 ******************************************************************************/
template <typename T>
BSTree<T>::~BSTree<T>(){
    //if the root is not null, we have to deallocate all the nodes
    if(root!=nullptr){
        root->node_clear();
        //then we have to reset the pointer to the root
        root=nullptr;
    }
}
