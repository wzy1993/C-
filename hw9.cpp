/** @file hw9.cpp
 @author [Wang Zhuoyou]
 @data [11/25/2016]
 
 This files contains all implementations of classes and related functions.
 */

#include "myTree.h"

/** main function - exactly same as given in the prompt
 */
int main(){
    
    // Create binary search tree, give it values {2,3,5,11,13,17}
    BinarySearchTree bst;
    bst.insert(3);  bst.insert(2); bst.insert(11);
    bst.insert(13); bst.insert(5); bst.insert(17);
    
    // Prints to the console: 2,3,5,11,13,17,
    for (auto x : bst) std::cout << x << ","; // x will assumes every Node in BST
    std::cout << std::endl;
    
    bst.erase(6);  // {2,3,5,11,13,17}, no effect
    bst.erase(11); // {2,3,5,13,17}
    
    auto start = std::begin(bst); // start is of type: TreeIterator*
    auto stop = std::end(bst);    // stop is of type: TreeIterator*
    
    int value = 17;
    bool keep_looking = true;
    
    // Find a 17 in the list
    while (start != stop && keep_looking)
        if (*start++ == value) // same as *(start_++)?
            keep_looking = false;
    --start;
    
    // Prints "17 is in the list."
    if (start != stop) std::cout << *start << " is in the list." << std::endl;
    
    return 0;
}
