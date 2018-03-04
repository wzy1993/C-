/** @file hw9.cpp
 @author [Wang Zhuoyou]
 @data [11/25/2016]
 
 This files contains all declarations of classes and related functions.
 */

#ifndef hw9_myTree_h
#define hw9_myTree_h
#include <iostream>

/** @class TreeNode
	@brief Node in binary search tree
 
	This custom TreeNode can store int type data, and stores pointers to parent Node, left child and right child.
 */
class TreeNode {
public:
    TreeNode();
    TreeNode(int data);
    void insert_node(TreeNode* new_node);
    int operator*();
    int smallestChild();
    int largestChild();
    bool search(int new_data);
    TreeNode* find(int target);
    friend std::ostream& operator<< (std::ostream& os, const TreeNode& tree_node);
private:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    
    friend class BinarySearchTree;
    friend class TreeIterator;
    
};

class TreeIterator;

/** @class BinarySearchTree
	@brief BinaryTree that stores custom TreeNode
 
	This BinarySearchTree stores a tree of TreeNodes, users can insert or erase TreeNodes in the tree,
	users can find the locations of largest and smallest elements by using member functions.
 */
class BinarySearchTree {
public:
    BinarySearchTree();
    void insert(int data);
    void erase(int data); // so that a node with two children is replaced by the largest child of the left subtree.
    TreeIterator begin(); // points to the node with the smallest value.
    TreeIterator end();   // points to one after the node with the largest value.
    int largest();
    int smallest();
    bool search(int new_data);
    TreeNode* Delete(TreeNode* newRoot, int data);
    ~BinarySearchTree();
    
private:
    TreeNode* root;
    friend class TreeIterator;
    
};

/** @class TreeIterator
	@brief iterator for BinarySearchTree that increments TreeNode by TreeNode
 
	TreeIterator is custom iterator designed specially for BinarySearchTree, increment means points to the next TreeNode that has smallest larger value.
	Decrement means points to the previous TreeNode that has the largest smaller value.
 */
class TreeIterator{
public:
    TreeIterator(BinarySearchTree& BST);
    TreeIterator(TreeNode* tree_ptr);
    TreeIterator& operator++();
    TreeIterator operator++(int unused);
    TreeIterator& operator--();
    int operator*();
    
    friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs);
    friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs);
    
private:
    TreeNode* current_node;
    BinarySearchTree* underlying_tree;
    friend class BinarySearchTree;
};

#endif
