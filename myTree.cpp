/** @file hw9.cpp
 @author [Wang Zhuoyou]
 @data [11/25/2016]
 
 This files contains all implementations of classes and related functions.
 */

#include "myTree.h"

/** Default Constructor of class, TreeNode - construct a TreeNode with value 0, and all pointers being nullptr
 */
TreeNode::TreeNode(){
    data = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

/** Overloaded Constructor of class, TreeNode - construct a TreeNode with input_data, and all pointers being nullptr
 */
TreeNode::TreeNode(int input_data){
    data = input_data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

/** Dereference operator of class, TreeNode -
	@ return the value of data stored in the TreeNode
 */
int TreeNode::operator*(){
    return data;
}

/** Default Constructor of class, BinarySearchTree - set root to be a nullptr
 */
BinarySearchTree::BinarySearchTree(){
    root = nullptr;
}

/** Member function of BinarySearchTree - insert
	@param: int data, the value of the new TreeNode
 */
void BinarySearchTree::insert(int data){
    
    TreeNode* new_node = new TreeNode(data);
    if (root == nullptr)
        root = new_node;
    else root->insert_node(new_node);
}

/** Member function of TreeNode - search
	@param: int new_data, target integer
	@return: true if this TreeNode contain new_data, false if not
 */
bool TreeNode::search(int new_data){
    if (data == new_data)
        return true;
    if (data > new_data){
        if (right == nullptr)
            return false;
        else
            return right->search(new_data);
    }
    // data <= new_data
    if (left == nullptr)
        return false;
    // right!= nullptr
    return left->search(new_data);
}

/** Member function of BinarySearchTree - search
	@param: int new_data, target integer
	@return: true if new_data is in the tree, false if not
 */
bool BinarySearchTree::search(int new_data){
    return root->search(new_data);
}

/** Member function of TreeNode - insert a new TreeNode to the bottom of this TreeNode
	@param: TreeNode* new_node, new TreeNode to be inserted
 */
void TreeNode::insert_node(TreeNode* new_node){
    if (new_node->data < data){
        if (left == nullptr){
            left = new_node;
            new_node->parent = this;
        }
        else
            left->insert_node(new_node);
    }
    else if (new_node->data >= data){ //(new_node ->data >= data)
        if (right == nullptr){
            right = new_node;
            new_node->parent = this;
        }
        else
            right->insert_node(new_node);
    }
}

/** Member function of TreeNode - find TreeNode that stores the target integer
	@param: int target
	@return: an TreeIterator to that TreeNode
 */
TreeNode* TreeNode::find(int target){
    if (data == target)
        return this;
    if (data < target){
        if (right == nullptr)
            return nullptr;
        else
            return right->find(target);
    }
    if (left == nullptr)
        return nullptr;
    return left->find(target);
}

/** smallestChild(), Member function of TreeNode
	@return: the smaller integer store in Children TreeNodes
 */
int TreeNode::smallestChild(){
    TreeNode* current = this;
    while (current->left != nullptr){
        current = current->left;
    }
    return current->data;
}

/** largestChild(), Member function of TreeNode
	@return: the larger integer store in Children TreeNodes
 */
int TreeNode::largestChild(){
    TreeNode* current = this;
    while (current->right != nullptr){
        current = current->right;
    }
    return current->data;
}

/** largest(), Member function of BinarySearchTree
	@return: the largestr integer store in this BinarySearchTree
 */
int BinarySearchTree::largest(){
    return root->largestChild();
}

/** smallest(), Member function of BinarySearchTree
	@return: the smallest integer store in this BinarySearchTree
 */
int BinarySearchTree::smallest(){
    return root->smallestChild();
}

/** Delete, Member function of BinarySearchTree
	@param: TreeNode* newRoot, the starting TreeNode for finding the location to delete
	@param: int data
	@return: pointer to TreeNode for recursion
 */
TreeNode* BinarySearchTree::Delete(TreeNode* newRoot, int data){
    
    if (newRoot == nullptr)
        return newRoot;
    else if (data < newRoot->data){
        newRoot = Delete(newRoot->left, data);
        return newRoot;
    }
    else if (data > newRoot->data){
        newRoot= Delete(newRoot->right, data);
        return newRoot;
    }
    else{
        // case 1: no child
        if (newRoot->left == nullptr && newRoot->right == nullptr){
            if (newRoot->parent->right == newRoot)
                newRoot->parent->right = nullptr;
            else if (newRoot->parent->left == newRoot)
                newRoot->parent->left = nullptr;
            delete newRoot;
            return nullptr;
        }
        // case 2: one child
        else if (newRoot->left == nullptr){
            TreeNode* temp = newRoot;
            newRoot = newRoot->right;
            newRoot->parent = temp->parent;
            temp->parent->right = newRoot;
            delete temp;
            return nullptr;
        }
        else if (newRoot->right == nullptr){
            TreeNode* temp = newRoot;
            newRoot = newRoot->left;
            newRoot->parent = temp->parent;
            temp->parent->left = newRoot;
            delete temp;
            return nullptr;
        }
        // case 3: two child
        else{
            TreeNode* temp = newRoot->find(newRoot->left->largestChild());
            newRoot->data = temp->data;
            Delete(temp, temp->data);
            return newRoot;
        }
    }
}

/** Erase, Member function of BinarySearchTree - erase targeted TreeNode
	@param: int data
 */
void BinarySearchTree::erase(int data){
    
    Delete(root, data);
}

/** Operator overload for std::cout so that we can cout TreeNode directly
	@param: std::ostream& os
	@param: const TreeNode& tree_node
	@return: an ostream by reference that store the actual data in a TreeNode
	*/
std::ostream& operator<< (std::ostream& os, const TreeNode& tree_node){
    os << tree_node.data;
    return os;
}

/** BinarySearchTree member function, begin() - such that range-based loop can be used
	@return: a TreeIterator that points to the TreeNode with smallest int
 */
TreeIterator BinarySearchTree::begin(){
    TreeIterator iter(root->find(smallest()));
    iter.underlying_tree = this;
    return iter;
}

/** BinarySearchTree member function, end() - such that range-based loop can be used
	@return: a TreeIterator that points to the special TreeNode with value INT_MAX, it will always serve as the special end TreeNode
 */
TreeIterator BinarySearchTree::end(){
    this->insert(INT_MAX);
    TreeIterator iter(root->find(largest()));
    iter.underlying_tree = this;
    
    return iter;
}

/** Constructor for TreeIterator - current_node points to the root of BST and underlying_tree becomes BST
	@param: BinarySearchTree& BST
 */
TreeIterator::TreeIterator(BinarySearchTree& BST){
    current_node = BST.root;
    underlying_tree = &BST;
}

/** Constructor for TreeIterator - current_node points to tree_ptr and underlying_tree becomes nullptr
	@param: TreeNode* tree_ptr
 */
TreeIterator::TreeIterator(TreeNode* tree_ptr){
    current_node = tree_ptr;
    underlying_tree = nullptr;
}

/** Dereference operator overloading
	@return the value of int that stored in the TreeNode pointed by this Treeiterator
 */
int TreeIterator::operator*(){
    return this->current_node->data;
}

/** "==", Comparison operator for Iterator
	@param: const TreeIterator& lhs
	@param: const TreeIterator& rhs
	@return: ture if they have same data, false otherwise
 */
bool operator==(const TreeIterator& lhs, const TreeIterator& rhs){
    return **(lhs.current_node) == **(rhs.current_node);
}

/** "!=", Comparison operator for Iterator
	@param: const TreeIterator& lhs
	@param: const TreeIterator& rhs
	@return: false if they have same data, true otherwise
 */
bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs){
    return **(lhs.current_node) != **(rhs.current_node);
}

/** prefix++ for TreeIterator
	@return by reference a TreeIterator after increment
 */
TreeIterator& TreeIterator::operator++(){
    
    
    TreeIterator iter = *this;
    
    // if we have right child, we can find larger int in right subtree
    if (iter.current_node->right != nullptr)
    {
        // start checking from the top of right subtree
        iter.current_node = iter.current_node->right;
        
        // if we have left child, we need to find the smallest larger element
        while (iter.current_node->left != nullptr)
            iter.current_node = iter.current_node->left;
        
        // now, we are pointing to the smallest larger element
        *this = iter;
        return *this;
    }
    
    // now, we don't have anymore right child, let's check if we have parent
    while (iter.current_node->parent != nullptr)
    {
        // if we are on the left of parent, parent is greater than us
        if (iter.current_node->parent->left == iter.current_node)
        {
            // let's move to our parent
            iter.current_node = iter.current_node->parent;
            *this = iter;
            return *this;
        }
        // if we are on the right of parent, try to get back to the top Node we haven't reached
        iter.current_node = iter.current_node->parent;
        
    }
    return *this;
}

/** postfix++ for TreeIterator
	@param: unused int, just for differentiating postfix and prefix
	@return a copy of original TreeIterator before increment
 */
TreeIterator TreeIterator::operator++(int unused){
    TreeIterator iter = *this;
    ++(*this);
    return iter;
}

/** prefix-- for TreeIterator
	@return by reference a TreeIterator after decrement
 */
TreeIterator& TreeIterator::operator--(){
    
    TreeIterator iter = *this;
    
    // if we have left child
    if (iter.current_node->left != nullptr)
    {
        //start checking from the top of left subtree
        iter.current_node = iter.current_node->left;
        
        // if left subtree still have right child, we can find largest smaller element
        while (iter.current_node->right != nullptr)
            iter.current_node = iter.current_node->right;
        
        *this = iter;
        return *this;
    }
    
    // if we have parent and no child any more
    while (iter.current_node->parent != nullptr)
    {
        // if we are the right child of parent
        if (iter.current_node->parent->right == iter.current_node)
        {
            // let's become parents
            iter.current_node = iter.current_node->parent;
            *this = iter;
            return *this;
        }
        
        // if we are on the left, keep moving to the highest parent that we haven't reached yet
        iter.current_node = iter.current_node->parent;
        
    }
    return *this;
}
/**
 Destructor - prevent memory leak!
 */
BinarySearchTree::~BinarySearchTree(){
    TreeIterator iter(*this);
    TreeIterator end = iter.underlying_tree->end();
    while (iter.current_node!= end){
        TreeIterator temp = iter;
        iter++;
        delete temp.current_node;
    }
    delete iter.current_node;
}


