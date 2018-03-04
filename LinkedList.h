
#ifndef __hw10__LinkedList__
#define __hw10__LinkedList__
#define NDEBUG
#include <iostream>
#include <cassert>

//forward decleration makes the complier happy
template<typename T>
class List;

template<typename T>
class Iterator;



/** Overloading of operator !=
 @ param: Iterator on the left
 @ param: Iterator on the right
 @ return: the comparison result, it they po<T> to the same location, return false, otherwise true
 */
/*template<typename T>
bool operator!=(const Iterator<T>& left, const Iterator<T>& right){
    return !(left==right);
}*/


/** Node, store elements of custom List
 Node* po<T>ers po<T> to the elements on either side of the node.
 
 */

template<typename T>
class Node {
public:
    Node (); // create special endNode
    Node(T input_data); // (8)
    T operator*(); // (9)
    const bool specialNode;
private:
    T data;
    Node<T>* previous;
    Node<T>* next;
    
    friend class List<T>;
    friend class Iterator<T>;
};


template<typename T>
bool operator==(const Iterator<T>& left, const Iterator<T>& right);

//template<typename T>
//bool operator!=(const Iterator<T>& left, const Iterator<T>& right);

/** custom Iterator for custom List, acting similarly like wordCrawler, but it is desinged for keeping track of Nodes in List.
 The iterator class contains a Node* po<T>er to the current Node object, AND it must know which list object it is currently part of.
 
 */

template<typename T>
class Iterator{
    friend class List<T>;
    friend bool operator==(const Iterator<T>& left, const Iterator<T>& right){
        return (left.currentNode == right.currentNode);
    }
    friend bool operator!=(const Iterator<T>& left, const Iterator<T>& right){
        return !(left==right);
    }
    
public:
    Iterator<T>(Node<T>* nodeptr);
    Iterator<T>(List<T>& mylist);
    Iterator<T>& operator++();
    Iterator<T> operator++ (int unused);
    Iterator<T>& operator--();
    Iterator<T> operator--(int unused);
    Iterator<T>& operator+=(int pos);
    T operator*();
    
private:
    
    Node<T>* currentNode;    //po<T>er to the current node
    List<T>* underlyingList; //po<T>r to the container of all Nodes that this Iterator can po<T>s to
    
};

template<typename T>
void downsize(List<T>& names);

template<typename T>
T maximum(List<T>& myList);


/** Custom List
 Store address of first and last Nodes. Each node po<T>s to the next and previous nodes, so once we know the first and last elements we can get to any node desired. User can insert, erase, and push back numbers to any position in the List.
 
 */
template<typename T>
class List{
    friend class Iterator<T>;
    
    friend void downsize(List<T>& names){
        
        Iterator<T> namesIter (names);
        size_t size = names.size;
        for (size_t i = 0; i<(size / 2); i++){
            namesIter++;
            namesIter = names.erase(namesIter);
        }
    };
    friend T maximum(List<T>& myList){
        
       // if(myList.firstNode->specialNode==true)
         //   return ;
        Iterator<T> it(myList);
        T max = *it;
        for (++it; it != myList.end(); ++it){
            if (*it > max)
                max = *it;
        }
        return max;
    };
public:
    List(); // (1)
    void push_back(T data);
    Iterator<T> insert(Iterator<T> position, T num); // (3)
    Iterator<T> erase(Iterator<T> position); // (4)
    Iterator<T> begin(); // (5)
    Iterator<T> end(); // (6)
    void reverse();
    void push_front(T newInt);
    void swap(List<T>& other);
    size_t get_size() const;
    ~List(); // (2)
    void print();
    void sort();
    List<T>& merge(List<T>& other);
private:
    Node<T>* firstNode; //po<T>er to first node in the list
    Node<T>* lastNode;  //po<T>er to the last node in the list.
    size_t size;
    
};

/**
 Default constructor of class, Node
 Initial all po<T>er to be nullptr, and data to be 0, this is the special Node
 */

template<typename T>
Node<T>::Node():specialNode(true){
    previous = nullptr;
    next = nullptr;
    return;
}


/**
 Parametized constructor of class, Node
 Initial all po<T>er to be nullptr, and data to be input_data
 @param: input_data
 */
template<typename T>
Node<T>::Node(T input_data):specialNode(false){
    data = input_data;
    previous = nullptr;
    next = nullptr;
}

/**
 Dereference operator *,
 @ return, the actual <T> that the Node stores
 */
template<typename T>
T Node<T>::operator*(){
    return data;
}

/** Constructor of class, Iterator
 @param: Node*, inputNode
 @return: an Iterator that is curretly po<T>ing to the input Node
 */
//this is a pass by reference
template<typename T>
Iterator<T>::Iterator(List<T>& mylist){
    currentNode = mylist.firstNode;
    underlyingList = &mylist;
}

/** Constructor of class, Iterator
 @param: Node*, inputNode
 @return: an Iterator that is curretly po<T>ing to the input Node
 */
//this input is a po<T>er
template<typename T>
Iterator<T>::Iterator(Node<T>* inputNode){
    currentNode = inputNode;
}

/** Constructor for List that creates the defalt special node(s).
 */
template<typename T>
List<T>::List(){
    lastNode = new Node<T>();
    firstNode = lastNode;
    size =0;
}

/** Destructor for List that delete all nodes created by calling new.
 */
template<typename T>
List<T>::~List(){
    Iterator<T> it(*this);
    while (it != end()){
        ++it;
        delete it.currentNode->previous;
    }
    delete lastNode;
}

/** Custom push_back function - add an <T>eger to the list in the back
 @param <T> new<T>
 
 */
template<typename T>
void List<T>::push_back(T newInt){
    Node<T>* newNode = new Node<T>(newInt);
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
 @param: <T> num, <T>eger being added
 @Returns an iterator po<T>ing to the newly inserted node.
 */
template<typename T>
Iterator<T> List<T>::insert(Iterator<T> iter, T num){
    if(iter.currentNode == lastNode){
        push_back(num);
        return iter;
    }
    
    Node<T>* newNode = new Node<T>(num);
    if (iter.currentNode == firstNode){
        newNode->previous = nullptr;
        firstNode = newNode;
        newNode->next = iter.currentNode;
        iter.currentNode->previous = newNode;
    }
    else{
        Node<T>* after = iter.currentNode;
        Node<T>* before = after ->previous;
        newNode->previous = before;
        newNode->next = after;
        after->previous = newNode;
        before->next = newNode;
    }
    iter.currentNode = newNode;
    ++size;
    return iter;
}

/** Erases the node from the List po<T>ed to by the input argument.
 @param: Iterator iter, position to add new element
 @Returns an Iterator to the node after the erased node.
 
 */
template<typename T>
Iterator<T> List<T>::erase(Iterator<T> iter){
    
    Node<T>* remove = iter.currentNode;
    Node<T>* before = remove->previous;
    Node<T>* after = remove->next;
    if (iter.currentNode == lastNode){//另外加的
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
 @Returns an iterator po<T>ing to the first node
 */
template<typename T>
Iterator<T> List<T>::begin(){
    
    Iterator<T> it(firstNode);
    it.underlyingList = this;
    return it;
}

/**
 end()
 @ Returns an iterator po<T>ing to the speical end node after the last node
 */
template<typename T>
Iterator<T> List<T>::end(){
    Iterator<T> it(lastNode);
    it.underlyingList = this;
    return it;
}

/** Overloading of operator prefix++
 @ return: modified Iterator that are po<T>ing to the next Node
 */
template<typename T>
Iterator<T>& Iterator<T>::operator++(){
    
    if (currentNode != underlyingList->lastNode)
        currentNode = currentNode->next;
    return *this;
}

/** Overloading of operator postfix++, make this Iterator po<T>ing to the next Node
 @ param: <T>, just for differentiating postfix and prefix
 @ return: copy of original
 */
template<typename T>
Iterator<T> Iterator<T>::operator++ (int unused){
    Iterator<T> itCopy(*this);
    ++(*this);
    return itCopy;
}

/** Overloading of operator prefix--
 @ return: modified Iterator that are po<T>ing to the previous Node
 */
template<typename T>
Iterator<T>& Iterator<T>::operator--(){
    if(currentNode != underlyingList->firstNode){
        currentNode = currentNode->previous;
    }
    return *this;
}

/** Overloading of operator postfix--, make this Iterator po<T>ing to the previous Node
 @ param: <T>, just for differentiating postfix and prefix
 @ return: copy of original
 */
template<typename T>
Iterator<T> Iterator<T>::operator--(int unused){
    Iterator<T> itCopy(*this);
    --(*this);
    return itCopy;
}

/** Overloading of operator+=, make this Iterator po<T>ing to the pos-th Node after current Node
 @ param: <T> pos, the number of increments
 @ return: modified Iterator that has been increment for pos times
 */
template<typename T>
Iterator<T>& Iterator<T>::operator+=(int pos){
    *this = underlyingList->begin();
    for (int i =0; i< pos; i++){
        ++(*this);
    }
    return (*this);
}

/** Overloading of operator *
 @ return: the actual <T>eger that the Node po<T>ed by this Iterator stores.
 */
template<typename T>
T Iterator<T>::operator*(){
    assert(currentNode != nullptr);
    return currentNode->data;
}

/** Overloading of operator ==
 @ param: Iterator on the left
 @ param: Iterator on the right
 @ return: the comparison result, it they po<T> to the same location, return true, otherwise false
 */
template<typename T>
bool operator==(const Iterator<T>& left, const Iterator<T>& right){
    return (left.currentNode == right.currentNode);
}


/** Custom push_front function, add <T>eger to the beginning of the List
 @ param: <T>eger that is going to be added
 */
template<typename T>
void List<T>::push_front(T newInt){
    insert(this->begin(),newInt);
}

/** Swap, swap two List
 @ param: other List by reference
 */
template<typename T>
void List<T>::swap(List<T>& other){
    size_t tempSize = this->size;
    this->size = other.size;
    other.size = tempSize;
    
    Node<T>* temp = this->firstNode;
    this->firstNode = other.firstNode;
    other.firstNode = temp;
    
    temp = this->lastNode;
    this->lastNode = other.lastNode;
    other.lastNode = temp;
}

template<typename T>
size_t List<T>::get_size() const{
    return size;
}

/** downsize - remove every other elements from the List
 @ param: List that will be modifed
 */
/**
template<typename T>
void downsize(List<T>& names){
    
    Iterator<T> namesIter (names);
    size_t size = names.size;
    for (size_t i = 0; i<(size / 2); i++){
        namesIter++;
        namesIter = names.erase(namesIter);
    }
}
 */

/** Maximum - find the largest element in a List
 @ param: List where we will find max
 @ return: the maximum <T>eger in the List
 */
/**
template<typename T>
T maximum(List<T>& myList) {
    
    if(myList.firstNode->specialNode==true)
        return 0;
    Iterator<T> it(myList);
    T max = *it;
    for (++it; it != myList.end(); ++it){
        if (*it > max)
            max = *it;
    }
    return max;
}
 */


/** Sort elements in a List- from small to large
 */
template<typename T>
void List<T>::sort(){
    if (size <= 1)
        return;
    Iterator<T> i(*this);
    Iterator<T> j = i;
    for (; i.currentNode->next->next!=nullptr; )
    {
        
        Iterator<T> j = i;
        j = j.currentNode->next;
        for (; j.currentNode->next!=nullptr;)
        {
            if (*i > *j){
                T temp = i.currentNode->data;
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
template<typename T>
void List<T>::reverse(){
    if (size <= 1)
        return;
    Node<T>* NodebeforeLast = firstNode;
    Node<T>* originalSecond = firstNode->next;
    Node<T>* newBegin = lastNode->previous;
    Node<T>* Newsecond = newBegin->previous;
    Iterator<T> it(*this);
    ++it;
    ++it;
    for (; it != lastNode; ++it){
        Node<T>* temp = it.currentNode->previous->previous;
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
template<typename T>
List<T>& List<T>::merge(List<T>& rhs){
    size_t left = get_size();
    size_t right =rhs.get_size();
    
    if (left > right){
        Iterator<T> itLeft(*this);
        Iterator<T> itRight(rhs);
        ++itLeft;
        
        for (size_t i = 0; i < right; ){
            
            itLeft = insert(itLeft,*itRight); // after this, itLeft po<T>s to new Node
            ++i;
            if(i < right){
                ++itLeft;
                ++itLeft;
                ++itRight;
            }
        }
        return *this;
    }
    
    Iterator<T> itLeft(*this);
    Iterator<T> itRight(rhs);
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

/** Pr<T> function - pr<T> out every elements in a List in a parenthesis, seperated by comma
 */
template<typename T>
void List<T>::print(){
    size_t size = get_size();
    size_t indicator = 0;
    std::cout << "(";
    for (Iterator<T> pos(*this);pos!= this->end();++pos){
        indicator++;
        if (indicator != size)
            std::cout<<(*pos)<<",";
        if (indicator == size)
            std::cout<< (*pos);
    }
    std::cout << ")\n";
}


#endif /* defined(__hw10__MyList__) */
