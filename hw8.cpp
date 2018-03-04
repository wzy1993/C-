
#include <iostream>
#include "LinkedList.h"

using std::cin;
using std::cout;
using std::string;

/** main(), perform exactly same task as the example given in the prompt
 */
int main() {
    List myList;
    
    // Get input integer until the user inputs a negative one
    cout << "Please input a set of nonnegative numbers for a List (Enter -1 when you are finished):\n";
    int a = -1;
    do{
        cin >> a;
        if (a == -1)
            break;
        myList.push_back(a);
        
    }while(1);
    
    cout << "Your list is\n";
    myList.print();cout << std::endl;
    
    cin.ignore(1000,'\n');
    Iterator it (myList);
    int b = 0;
    a = 0;
    
    // Keep asking until the user inputs negative one
    do{
        cout << "Select an index for insertion (enter -1 when finished): ";
        cin >> a;
        if (a == -1)
            break;
        
        it += a;
        cout << "Select a value for insertion: ";
        cin >> b;
        myList.insert(it, b);
        it = myList.begin();
    }while(1);
    cout << std::endl;
    
    cout << "The augmented List is\n";
    myList.print();cout << std::endl;
    
    cout << "The maximum of the List is: "<< maximum(myList);
    
    cout << "\nThe size of the List is: " << myList.get_size();
    
    cout << "\nWhen we remove every second value from this list we are left with\n";
    downsize(myList);
    myList.print();
    
    cout << "When we sort this downsized list we obtain\n";
    myList.sort();
    myList.print();
    
    cout << "And this sorted list in reverse order is\n";
    myList.reverse();
    myList.print();
    cout << "If we merge this list with the list (2,3,5,7,11) we obtain\n";
    
    // Create the List memtioned in above
    List yourList;
    yourList.push_back(2);
    yourList.push_back(3);
    yourList.push_back(5);
    yourList.push_back(7);
    yourList.push_back(11);
    myList.merge(yourList).print();
    
    return 0;
}


