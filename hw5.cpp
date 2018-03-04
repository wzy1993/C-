/** @file hw5.cpp
	@author [Zhuoyou Wang]
	@date [10/25/2016]
 
 Because of the use of polymorphism, the users are allowed to input as many points as they want. After the users input all points they want, the program will print all points in a specific manner that coincide with their types. In additon, there will be no memory leak after the whole process.
 */

#include <iostream>
#include <string>
#include <vector>

/** @class Point2D
 @brief two dimemsional point
 
 The class contains an x and a y coordinates, it can be printed by using  accessor function, print().
 */
class Point2D {
public:Point2D(double x, double y);
    virtual void print() const;
    virtual ~Point2D() { }
    
private:
    double x;
    double y;
};

/** @class ColorPoint2D
 @brief two dimemsional point that comes with a color
 
 The class contains an x and a y coordinates and a color, it can be printed by using its own accessor function, print() that allows us to print its color in front of the x, y coordinates.
 */
class ColorPoint2D : public Point2D {
public:
    ColorPoint2D(double init_x, double init_y, std::string init_color);
    virtual void print() const;
    virtual ~ColorPoint2D() { }
    
private:
    std::string color;
};

/** @class WeightedPoint2D
 @brief two dimemsional point that comes with weight
 
 The class contains an x and a y coordinates and a weight, it can be printed by using its own accessor function, print() that allows us to print its weight in front of the x, y coordinates.
 */
class WeightedPoint2D: public Point2D{
public:
    WeightedPoint2D(double init_x, double init_y, double weight);
    virtual void print() const;
    virtual ~WeightedPoint2D() { }
    
private:
    double weight;
};

/** @class Points
 @brief stores a vector of pointer of Pont2D
 
 By dereferencing, all Point2Ds that are pointed by the elements of Points can by printed. This class is good for preventing memory leak!
 */
class Points {
public:
    // Mutator
    void push_back(Point2D* pt);
    
    // Accessor
    void printPoints() const;
    
    // CRUCIAL ASSUMPTION!  All points must lie on heap!
    // Destructor
    ~Points();
private:
    std::vector<Point2D*> points;
};

/** Main function -
 Repeatedly Ask the users to select a type of points and input corresponding points until the user select 0, then print out all inputed points one by one.
 */
int main() {
    
    // Declare all variables that will be used
    Points points;
    char selection = '5';
    double x = 0,y =0 ,weight = 0;
    std::string color;
    
    // Print menu of all selection
    std::cout << "Welcome to Point Printer! You can create three different kinds of points:\n"<<std::endl;
    std::cout << "1. Point2D, e.g., (2,6.5)"<<std::endl;
    std::cout << "2. ColorPoint2D, e.g., blue(-4.5,3.5)"<<std::endl;
    std::cout << "3. WeightedPoint2D, e.g., .12(3.6,8.7)\n"<<std::endl;
    std::cout << "Enter 0 when you are finished.\n"<<std::endl;
    
    // Keep asking for selection until the user quit by input 0
    do{
        std::cout << "Selection:  ";
        std::cin >> selection;
        std::cin.ignore();
        
        // Handle different selections
        switch (selection) {
                
                // Select normal Point2D
            case '1':
                std::cout << "x =  ";
                std::cin >> x;
                std::cout << "y =  ";
                std::cin >> y;
                
                //Add a pointer to this Point2D for latter printing purpose
                points.push_back(new Point2D(x,y));
                break;
                // Select ColorPoint2D
            case '2':
                std::cout << "x =  ";
                std::cin >> x;
                std::cout << "y =  ";
                std::cin >> y;
                std::cout << "color =  ";
                std::cin.ignore();
                getline(std::cin, color);
                
                //Add a pointer to this Point2D for latter printing purpose
                points.push_back(new ColorPoint2D(x,y,color));
                break;
                // Select WeightedPoint2D
            case '3':
                std::cout << "x =  ";
                std::cin >> x;
                std::cout << "y =  ";
                std::cin >> y;
                std::cout << "weight =  ";
                std::cin >> weight;
                
                //Add a pointer to this Point2D for latter printing purpose
                points.push_back(new WeightedPoint2D(x,y,weight));
                break;
                // Quit main menu, move to printing step
            case '0':
                break;
                // Handle invalid selection
            default:
                std::cout << "Invalid Input! Try again!\n";
                break;
        }
    }while(selection!= '0');
    
    // Print all Point2Ds that were inputed
    std::cout<< std::endl<<"Your points are"<<std::endl<<std::endl;
    points.printPoints();
    std::cout<< std::endl;
    
    return 0;
}

/** Constructor of Point2D
 @param x, x coordinate
 @param y, y coordinate
 */
Point2D::Point2D(double x, double y): x(x), y(y) {}

/** Constructor of ColorPoint2D
 @param init_x, x coordinate
 @param init_y, y coordinate
 @param inti_color, the color of the Point2D object
 */
ColorPoint2D::ColorPoint2D(double init_x, double init_y, std::string init_color):
Point2D(init_x, init_y), color(init_color) { }

/** Constructor of WeightedPoint2D
 @param init_x, x coordinate
 @param init_y, y coordinate
 @param weight, the weight of the Point2D object
 */
WeightedPoint2D::WeightedPoint2D(double init_x, double init_y, double weight):
Point2D(init_x, init_y), weight(weight) {}

/** Accessor of calss Point2D
 Print the point in the form of (x,y)
 */
void Point2D::print() const{
    std::cout<< "("<<x<< ","<<y<<")";
    return;
}

/** Accessor of calss ColorPoint2D
 Print the point in the form of (x,y), but with the color in front
 */
void ColorPoint2D::print() const{
    std::cout<<color; // How to print using the Point2D::print() function?
    Point2D::print();  // Great idea!
    return;
}

/** Accessor of calss WeightedPoint2D
 Print the point in the form of (x,y), but with the weight in front
 */
void WeightedPoint2D::print() const{
    std::cout << weight;
    Point2D::print();
}

/** Accessor of calss Points
 Print all Point2Ds by dereferencing each elements of the vector, points.
 */
void Points::printPoints() const{
    for(size_t i=0, n=points.size(); i<n; i++) {
        std::cout << (i+1) << ": ";
        points[i]->print();
        std::cout<< std::endl;
    }
}

/** Mutator of class Points
 Add a pointer to Point2D at the end of the vector, points.
 */
void Points::push_back(Point2D* pt) {
    points.push_back(pt);
}

/** Destructor of calss Points
 Not only destruct the object of Points, but also destructor all Point2Ds that were pointed by elements of vector, points.
 */
Points::~Points() {
    for(auto& x : points)
        delete x;
}
