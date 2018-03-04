/**@file hw10.cpp
 @author [Wang Zhuoyou]
 @date [11/29/2016]
 
 This is the code that will create a template for linked list
 */
//#include _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "LinkedList.h"

using std::cin;
using std::cout;
using std::string;



/** main(), perform exactly same task as the example given in the prompt
 */
int main() {
    List<Point2D> myList;
    
    // Get input integer until the user inputs a negative one
    cout << "Please input a set of nonnegative numbers for a List (Enter the point (-1,-1) when you are finished):\n";
    int a,b ;
    do{
        cin >> a;
        cin >> b;
        if (a == -1 && b == -1)
            break;
        myList.push_back(Point2D(a,b));
        
    }while(1);
    
    cout << "Your list is\n";
    myList.print();cout << std::endl;
    
    cin.ignore(1000,'\n');
    Iterator<Point2D> it (myList);
    int h = 0;
    
    // Keep asking until the user inputs negative one
    do{
        cout << "Select an index for insertion (enter -1 when finished): ";
        cin >> h;
        if (h == -1)
            break;
        it += h;
        
        cout << "x-value: ";
        cin >> a;
        cout << "y-value: ";
        cin >> b;
        myList.insert(it, Point2D(a,b));
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
    List<Point2D> yourList;
    yourList.push_back(Point2D(1,1));
    yourList.push_back(Point2D(2,2));
    yourList.push_back(Point2D(5,5));
    yourList.push_back(Point2D(7,11));
    myList.merge(yourList).print();
    
    return 0;
}
