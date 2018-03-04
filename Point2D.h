//
//  Point2D.h
//  hw10
//
//  Created by zhuoyou wang on 12/2/16.
//  Copyright © 2016 zhuoyou wang. All rights reserved.
//
#define _USE_MATH_DEFINES
#ifndef Point2D_h
#define Point2D_h
#include <cmath>
/** @class Point2D
 @brief two dimemsional point
 
 The class contains an x, a y coordinates, a magnitude and an angle, it can be printed by using accessor function, print().
 */
class Point2D {
public:Point2D();
    Point2D(double x, double y);
    virtual void print() const;
    virtual ~Point2D() { };
    double magnitude();
    double angle();
    //need to overload a cout operator
    friend std::ostream& operator<< (std::ostream& stream, const Point2D& point2d);
    bool operator >(const Point2D& rhs)const;
private:
    double x;
    double y;
};

Point2D::Point2D(){
    x = 0;
    y = 0;
}

/** Constructor of Point2D - calculate the magnitude and the angle of inputed point
 @param x, x coordinate
 @param y, y coordinate
 */
Point2D::Point2D(double x, double y): x(x), y(y) {
    
}

/** Accessor of calss Point2D
 Print the point in the form of (x,y)
 */
void Point2D::print() const{
    std::cout<< "("<<x<< ","<<y<<")";
    return;
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

/**overload the > operator
 for Point2D class
 */
bool Point2D::operator >(const Point2D& rhs)const{
    Point2D temp1 = *this;
    Point2D temp2 = rhs;
    double a = temp1.magnitude();
    double b = temp2.magnitude();
    double c = temp1.angle();
    double d = temp2.angle();
    if(a>b)
        return true;
    else if (b<a)
        return false;
    else if (a == b){
        if(c>d)
            return true;
        else if(d<c)
            return false;
    }
    return false;
}

/**overload the cout operator
 */
std::ostream& operator<<(std::ostream& stream, const Point2D& point2d) {
    stream<<"("<<point2d.x<<","<<point2d.y<<")";
    return stream;
}
#endif /* Point2D_h */
