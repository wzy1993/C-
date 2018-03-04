/** @file hw7.cpp
 @author [Zhuoyou Wang]
 @date [11/9/16]
 
 [In this homework we suppose to build a class that mimic the int data type and use the class the calculate addition and multiplication.
 impelementing plus equal and multiplication equal etc.]
 
 */

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/** @class Point2D
 @brief two dimemsional point
 
 The class contains an x, a y coordinates, a magnitude and an angle, it can be printed by using accessor function, print().
 */
class Point2D {
public:Point2D(double x, double y);
    virtual void print() const;
    virtual ~Point2D() { }
    double magnitude();
    double angle();
private:
    double x;
    double y;
};

/** @class ColorPoint2D
 @brief two dimemsional point that comes with a color
 
 The class contains an x, a y coordinates and a color, it can be printed by using its own accessor function, print() that allows us to print its color in front of the x, y coordinates, the user can access its color by public function, getColor().
 */
class ColorPoint2D : public Point2D {
public:
    ColorPoint2D(double init_x, double init_y, std::string init_color);
    virtual void print() const;
    virtual ~ColorPoint2D() { }
    std::string getColor(){
        return color;
    }
private:
    std::string color;
};

/** @class WeightedPoint2D
 @brief two dimemsional point that comes with weight
 
 The class contains an x and a y coordinates and a weight, it can be printed by using its own accessor function, print() that allows us to print its weight in front of the x, y coordinates, the user can access its weight by public function, getWeight().
 */
class WeightedPoint2D: public Point2D{
public:
    WeightedPoint2D(double init_x, double init_y, double weight);
    virtual void print() const;
    virtual ~WeightedPoint2D() { }
    double getWeight(){
        return weight;
    }
    
private:
    double weight;
};

/** @class Points
 @brief stores some vectors of pointer of different subtypes of Point2D, each vector has its unique push_back and sorting function.
 
 By dereferencing, all Point2Ds that are pointed by the elements of Points can by printed. This class is good for preventing memory leak!
 */
class Points {
public:
    // Mutator
    void push_back(Point2D* pt);
    void color_push_back(ColorPoint2D* pt);
    void weighted_push_back(WeightedPoint2D* pt);
    
    void mergePoints();
    
    void sort();
    void colorSort();
    void weightedSort();
    
    // Accessor
    void printPoints() const;
    
    // CRUCIAL ASSUMPTION!  All points must lie on heap!
    // Destructor
    ~Points();
private:
    std::vector<Point2D*> points1;
    std::vector<ColorPoint2D*> points2;
    std::vector<WeightedPoint2D*> points3;
    std::vector<Point2D*> points;
};

/** Main function -
 Repeatedly Ask the users to select a type of points and input corresponding points until the user select 0, then print out all inputed points one by one in an increasing order.
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
                points.color_push_back(new ColorPoint2D(x,y,color));
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
                points.weighted_push_back(new WeightedPoint2D(x,y,weight));
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
    std::cout<< std::endl<<"Your points in sorted order are"<<std::endl<<std::endl;
    
    points.mergePoints();
    points.printPoints();
    
    std::cout<< std::endl;
    
    return 0;
}

/** Constructor of Point2D - calculate the magnitude and the angle of inputed point
 @param x, x coordinate
 @param y, y coordinate
 */
Point2D::Point2D(double x, double y): x(x), y(y) {
    
}

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
Point2D(init_x, init_y), weight(weight) { }

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
    
    for(size_t i=0, n = points.size(); i<n; i++) {
        std::cout << (i+1) << ": ";
        points[i]->print();
        std::cout<< std::endl;
    }
    
}

/** Mutator of class Points
 Add a pointer to Point2D at the end of the vector, points1.
 */
void Points::push_back(Point2D* pt) {
    
    points1.push_back(pt);
}

/** Mutator of class Points
 Add a pointer to Point2D at the end of the vector, points2.
 */
void Points::color_push_back(ColorPoint2D* pt){
    points2.push_back(pt);
}

/** Mutator of class Points
 Add a pointer to Point2D at the end of the vector, points3.
 */
void Points::weighted_push_back(WeightedPoint2D* pt){
    points3.push_back(pt);
}

/** Destructor of calss Points
 Not only destruct the object of Points, but also destructor all Point2Ds that were pointed by elements of vector, points.
 */
Points::~Points() {
    for(auto& x : points1)
        delete x;
    
    for(auto& x : points2)
        delete x;
    
    for(auto& x : points3)
        delete x;
}

/** Merge points1, points2, and points3 together and store them in vector, points
 
 */
void Points::mergePoints(){
    
    // First, make sure elements are stored in increasing order in points1, points2, and points3.
    sort();
    colorSort();
    weightedSort();
    
    // Copy each element in points1 to points, then points2 to points, lastly, points3 to points
    for(size_t i=0, n1 = points1.size(); i<n1; i++){
        points.push_back(points1[i]);
    }
    for(size_t j=0, n2 = points2.size(); j<n2; j++){
        points.push_back(points2[j]);
    }
    for(size_t k=0, n3 = points3.size(); k<n3; k++){
        points.push_back(points3[k]);
    }
}

/** Sorting elements in vector, points1
 which ever has less magnitude got listed first, if magnitudes are the same, the one with less angle goes first
 
 */
void Points::sort(){
    
    for(size_t i = 0, n = points1.size(); i < n; i++){
        for (size_t j = i+1; j < n; j++){
            if ((points1[i]->magnitude() > points1[j]->magnitude())||((points1[i]->magnitude() == points1[j]->magnitude())&&(points1[i]->angle() > points1[j]->angle()))){
                
                Point2D* temp = points1[i];
                points1[i] = points1[j];
                points1[j] = temp;
            }
        }
    }
}

/** Sorting elements in vector, points2
 which ever has less magnitude got listed first, if magnitudes are the same, the one with less angle goes first,
 then if angles are the same, the one with less color goes first (simply use string comparison)
 */
void Points::colorSort(){
    for(size_t i = 0, n = points2.size(); i < n; i++){
        for (size_t j = i+1; j < n; j++){
            if ((points2[i]->magnitude() > points2[j]->magnitude())||((points2[i]->magnitude() == points2[j]->magnitude())&&(points2[i]->angle() > points2[j]->angle()))||((points2[i]->magnitude() == points2[j]->magnitude())&&(points2[i]->angle() == points2[j]->angle())&&(points2[i]->getColor()> points2[j]->getColor()))){
                
                ColorPoint2D* temp = points2[i];
                points2[i] = points2[j];
                points2[j] = temp;
            }
        }
    }
}

/** Sorting elements in vector, points3
 which ever has less magnitude got listed first, if magnitudes are the same, the one with less angle goes first,
 then if angles are the same, the one with less weight goes first
 */
void Points::weightedSort(){
    for(size_t i = 0, n = points3.size(); i < n; i++){
        for (size_t j = i+1; j < n; j++){
            if ((points3[i]->magnitude() > points3[j]->magnitude())||((points3[i]->magnitude() == points3[j]->magnitude())&&(points3[i]->angle() > points3[j]->angle()))||((points3[i]->magnitude() == points3[j]->magnitude())&&(points3[i]->angle() == points3[j]->angle())&&(points3[i]->getWeight()> points3[j]->getWeight()))){
                
                WeightedPoint2D* temp = points3[i];
                points3[i] = points3[j];
                points3[j] = temp;
            }
        }
    }
}

/** Member function of Point2D
 return the distant from origin to the point
 */
double Point2D::magnitude(){
    return sqrt(x*x+y*y);
}

/** Member function of Point2D
 return the counterclockwise angle defined in the prompt.
 */
double Point2D::angle(){
    
    if(atan2(y,x)> 0)
        return atan2(y,x);
    return atan2(y, x) + 2* M_PI;
}

