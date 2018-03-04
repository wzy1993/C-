
//#define NDEBUG
#include "LinkedList.h"
#include <cassert>

/**
 Default constructor of class, Node
 Initial all pointer to be nullptr, and data to be 0, this is the special Node
 */
Node::Node():specialNode(true){
    previous = nullptr;
    next = nullptr;
    data = 0;
}

/**
 Parametized constructor of class, Node
 Initial all pointer to be nullptr, and data to be input_data
 @param: input_data
 */
Node::Node(int input_data):specialNode(false){
    data = input_data;
    previous = nullptr;
    next = nullptr;
}

/**
 Dereference operator *,
 @ return, the actual int that the Node stores
 */
int Node::operator*(){
    return data;
}

/** Constructor of class, Iterator
 @param: Node*, inputNode
 @return: an Iterator that is curretly pointing to the input Node
 */
//this is a pass by reference
Iterator::Iterator(List& mylist){
    currentNode = mylist.firstNode;
    underlyingList = &mylist;
}

/** Constructor of class, Iterator
 @param: Node*, inputNode
 @return: an Iterator that is curretly pointing to the input Node
 */
//this input is a pointer
Iterator::Iterator(Node* inputNode){
    currentNode = inputNode;
}

/** Constructor for List that creates the defalt special node(s).
 */
List::List(){
    lastNode = new Node();
    firstNode = lastNode;
    size =0;
}

/** Destructor for List that delete all nodes created by calling new.
 */
List::~List(){
    Iterator it(*this);
    while (it != end()){
        ++it;
        delete it.currentNode->previous;
    }
    delete lastNode;
}

/** Custom push_back function - add an integer to the list in the back
 @param int newInt
 
 */
void List::push_back(int newInt){
    Node* newNode = new Node(newInt);
    if (size == 0){
        firstNode = newNode;
        size++;
        newNode->next = lastNode;
        lastNode->previous = newNode;
    }
    else{
        size++;
        // connect newNode with special end Node, last Node
        newNode->previous = lastNode->previous;
        lastNode->previous->next = newNode;
        
        newNode->next = lastNode;
        lastNode->previous = newNode;
        
    }
}

/** Inserts a node before the position of the first parameter. The node should have
 the value of the second input argument.
 @param: Iterator iter, position to add new element
 @param: int num, integer being added
 @Returns an iterator pointing to the newly inserted node.
 */
Iterator List::insert(Iterator iter, int num){
    if(iter.currentNode == lastNode){
        push_back(num);
        return iter;
    }
    
    Node* newNode = new Node(num);
    if (iter.currentNode == firstNode){
        newNode->previous = nullptr;
        firstNode = newNode;
        newNode->next = iter.currentNode;
        iter.currentNode->previous = newNode;
    }
    else{
        Node* after = iter.currentNode;
        Node* before = after ->previous;
        newNode->previous = before;
        newNode->next = after;
        after->previous = newNode;
        before->next = newNode;
    }
    iter.currentNode = newNode;
    ++size;
    return iter;
}

/** Erases the node from the List pointed to by the input argument.
 @param: Iterator iter, position to add new element
 @Returns an Iterator to the node after the erased node.
 
 */
Iterator List::erase(Iterator iter){
    
    Node* remove = iter.currentNode;
    Node* before = remove->previous;
    Node* after = remove->next;
    if (iter.currentNode == lastNode){//另外加的，感觉这样才对
        lastNode = before;
        return iter;
    }
    if(remove == firstNode)
        firstNode = after;
    else
        before->next = after;
    
    if (after == lastNode){
        lastNode->previous = before;
        before->next = lastNode;
    }
    else
        after->previous = before;
    
    delete remove;
    iter.currentNode = after;
    size--;
    return iter;
}

/**
 Begin()
 @Returns an iterator pointing to the first node
 */
Iterator List::begin(){
    
    Iterator it(firstNode);
    it.underlyingList = this;
    return it;
}

/**
 end()
 @ Returns an iterator pointing to the speical end node after the last node
 */
Iterator List::end(){
    Iterator it(lastNode);
    it.underlyingList = this;
    return it;
}

/** Overloading of operator prefix++
 @ return: modified Iterator that are pointing to the next Node
 */
Iterator& Iterator::operator++(){
    
    if (currentNode != underlyingList->lastNode)
        currentNode = currentNode->next;
    return *this;
}

/** Overloading of operator postfix++, make this Iterator pointing to the next Node
 @ param: int, just for differentiating postfix and prefix
 @ return: copy of original
 */
Iterator Iterator::operator++ (int unused){
    Iterator itCopy(*this);
    ++(*this);
    return itCopy;
}

/** Overloading of operator prefix--
 @ return: modified Iterator that are pointing to the previous Node
 */
Iterator& Iterator::operator--(){
    if(currentNode != underlyingList->firstNode){
        currentNode = currentNode->previous;
    }
    return *this;
}

/** Overloading of operator postfix--, make this Iterator pointing to the previous Node
 @ param: int, just for differentiating postfix and prefix
 @ return: copy of original
 */
Iterator Iterator::operator--(int unused){
    Iterator itCopy(*this);
    --(*this);
    return itCopy;
}

/** Overloading of operator+=, make this Iterator pointing to the pos-th Node after current Node
 @ param: int pos, the number of increments
 @ return: modified Iterator that has been increment for pos times
 */
Iterator& Iterator::operator+=(int pos){
    *this = underlyingList->begin();
    for (int i =0; i< pos; i++){
        ++(*this);
    }
    return (*this);
}

/** Overloading of operator *
 @ return: the actual integer that the Node pointed by this Iterator stores.
 */
int Iterator::operator*(){
    assert(currentNode != nullptr);
    return currentNode->data;
}

/** Overloading of operator ==
 @ param: Iterator on the left
 @ param: Iterator on the right
 @ return: the comparison result, it they point to the same location, return true, otherwise false
 */
bool operator==(const Iterator& left, const Iterator& right){
    return (left.currentNode == right.currentNode);
}

/** Overloading of operator !=
 @ param: Iterator on the left
 @ param: Iterator on the right
 @ return: the comparison result, it they point to the same location, return false, otherwise true
 */
bool operator!=(const Iterator& left, const Iterator& right){
    return !(left==right);
}

/** Custom push_front function, add integer to the beginning of the List
 @ param: integer that is going to be added
 */
void List::push_front(int newInt){
    insert(this->begin(),newInt);
}

/** Swap, swap two List
 @ param: other List by reference
 */
void List::swap(List& other){
    size_t tempSize = this->size;
    this->size = other.size;
    other.size = tempSize;
    
    Node* temp = this->firstNode;
    this->firstNode = other.firstNode;
    other.firstNode = temp;
    
    temp = this->lastNode;
    this->lastNode = other.lastNode;
    other.lastNode = temp;
}
size_t List::get_size() const{
    return size;
}

/** downsize - remove every other elements from the List
 @ param: List that will be modifed
 */
void downsize(List& names){
    
    Iterator namesIter (names);
    size_t size = names.size;
    for (size_t i = 0; i<(size / 2); i++){
        namesIter++;
        namesIter = names.erase(namesIter);
    }
}

/** Maximum - find the largest element in a List
 @ param: List where we will find max
 @ return: the maximum integer in the List
 */
int maximum(List& myList){
    
    if(myList.firstNode->specialNode==true)
        return 0;
    Iterator it(myList);
    
    int max = *it;
    for (++it; it != myList.end(); ++it){
        if (*it > max)
            max = *it;
    }
    return max;
}

/** Sort elements in a List- from small to large
 */
void List::sort(){
    if (size <= 1)
        return;
    Iterator i(*this);
    Iterator j = i;
    for (; i.currentNode->next->next!=nullptr; )
    {
        
        Iterator j = i;
        j = j.currentNode->next;
        for (; j.currentNode->next!=nullptr;)
        {
            if (*i > *j){
                int temp = i.currentNode->data;
                i.currentNode->data = *j;
                j.currentNode->data = temp;
            }
            if (j.currentNode->next != nullptr)
                j = j.currentNode->next;
        }
        if (i.currentNode->next->next != nullptr)
            i = i.currentNode->next;
    }
    
}

/** Reverse elements in a List
 */
void List::reverse(){
    if (size <= 1)
        return;
    Node* NodebeforeLast = firstNode;
    Node* originalSecond = firstNode->next;
    Node* newBegin = lastNode->previous;
    Node* Newsecond = newBegin->previous;
    Iterator it(*this);
    ++it;
    ++it;
    for (; it != lastNode; ++it){
        Node* temp = it.currentNode->previous->previous;
        it.currentNode->previous->previous = it.currentNode->previous->next;
        it.currentNode->previous->next = temp;
    }
    
    newBegin->previous = nullptr;
    newBegin->next = Newsecond;
    
    NodebeforeLast->next = lastNode;
    NodebeforeLast->previous = originalSecond;
    lastNode->previous = NodebeforeLast;
    firstNode = newBegin;
}

/** Member function of List, merge - merge two List in a specific manner
 @ param: second List, rhs
 @ return: the newly modifed List after merging, either return reference to this List, or the passing in parameter.
 */
List& List::merge(List& rhs){
    size_t left = get_size();
    size_t right =rhs.get_size();
    
    if (left > right){
        Iterator itLeft(*this);
        Iterator itRight(rhs);
        ++itLeft;
        
        for (size_t i = 0; i < right; ){
            
            itLeft = insert(itLeft,*itRight); // after this, itLeft points to new Node
            ++i;
            if(i < right){
                ++itLeft;
                ++itLeft;
                ++itRight;
            }
        }
        return *this;
    }
    
    Iterator itLeft(*this);
    Iterator itRight(rhs);
    for (size_t i = 0; i< left; ){
        itRight =rhs.insert(itRight, *itLeft);
        ++i;
        if(i< left){
            ++itRight;
            ++itRight;
            ++itLeft;
        }
    }
    return rhs;
}

/** Print function - print out every elements in a List in a parenthesis, seperated by comma
 */
void List::print(){
    size_t size = get_size();
    size_t indicator = 0;
    std::cout << "(";
    for (Iterator pos(*this);pos!= this->end();++pos){
        indicator++;
        if (indicator != size)
            std::cout<< (*pos)<<",";
        if (indicator == size)
            std::cout<< (*pos);
    }
    std::cout << ")\n";
}
