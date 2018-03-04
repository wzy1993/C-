/**
 @file hw1.cpp
 @author Zhuoyou Wang
 @date 09/29/2016
 
 description
 */
#include <iostream>
#include <vector>
#include <cmath>

/** @class integer
 @brief store integer value and convert them into binary code, and
 define two operations, one is plus and the other one is multiplcation
 
 */
class Integer{
public:
    Integer();
    Integer(unsigned int a);
    
    void plus_equals(const Integer& rhs); // adds current value to rhs
    void times_equals(const Integer& rhs);// multiplies current value to rhs
    void print_as_int () const ;
    void print_as_bits () const ;
    
    private :
    std::vector<bool> bit;
};

Integer plus(Integer lhs, const Integer& rhs);
Integer multiply(Integer lhs, const Integer& rhs);

int main() {
    
    unsigned int uint_value ;
    
    std::cout << "Please input an integer a: ";
    std:: cin >> uint_value ;
    Integer a = uint_value; // Create Integer type with input value
    
    std::cout << "The base−2 representation of a is: "; a.print_as_bits();
    std::cout << std::endl;
    
    std::cout << "Please input an integer b: ";
    std::cin >> uint_value ;
    Integer b = uint_value; // Create Integer type with input value
    
    std::cout << "The base−2 representation of b is: "; b.print_as_bits();
    std::cout << std::endl;
    
    Integer c = plus(a,b); // a + b
    Integer d = multiply(a,b); // a * b
    
    std::cout << "a + b = "; c.print_as_int(); std::cout <<" = "; c.print_as_bits () ; std::cout <<std::endl;
    std::cout << "a * b = "; d.print_as_int(); std::cout <<" = "; d.print_as_bits () ; std::cout << std::endl;
    
    a . plus_equals ( b ) ;
    std::cout << "After a += b, a = "; a.print_as_int(); std::cout << std::endl ;
    
    Integer two = 2;
    b . times_equals ( two ) ;
    std::cout << "After b *= 2, b = "; b.print_as_int(); std::cout << std::endl ;
    
    return 0;
}

/**the defualt constructor for Integer calss */
Integer::Integer(){
    bit.push_back(0);
}

/**the constructor for Integer calss to convert an integer into binary code
 @param initial the input for class integer
 */
Integer::Integer(unsigned int initial){
    //convert to bit depending on input
    if (initial == 0)bit.push_back(0);
    while (initial > 0){
        bit.push_back(initial % 2);
        initial /= 2;
    }
}

/** the member function for Integer calss to do the plus operation
 @param rhs the variable use to addition
 */
void Integer::plus_equals(const Integer& rhs){
    //get m n vecotr size
    size_t a = bit.size();
    
    size_t b = rhs.bit.size();
    //create a temperory variable to store and modify the vector
    std::vector<bool> bit2(rhs.bit);
    
    if (b>a) {
        for (size_t i = a; i<b; ++i) bit.push_back(0);
    }
    else{
        for (size_t e = b; e<a; ++e) bit2.push_back(0);
    }
    
    bool carry = 0;
    
    for (size_t f = 0, l = bit.size(); f<l; ++f) {
        if (carry == 0) {
            
            if (bit[f] & bit2[f]) {
                carry = 1;
                bit[f] = 0;
            }
            else if (bit[f] | bit2[f]) {
                bit[f] = 1;
            }
            
        }
        else if (carry == 1) {
            if (bit[f] & bit2[f]) {
                bit[f] = 1;
                carry = 1;
            }
            else if (bit[f] | bit2[f]) {
                bit[f] = 0;
                carry = 1;
            }
            else if (bit[f] == 0 && bit2[f] == 0) {
                bit[f] = 1;
                carry = 0;
            }
        }
    }
    //form addition solution
    if (carry == 1) {
        bit.push_back(1);
    }
    return;
}

/** the member function for Integer calss to do multiplication
 @param rhs the input for multiplication and this is a pass by reference
 */
void Integer::times_equals(const Integer& rhs){
    //multi fxn
    size_t m = bit.size();
    size_t n = rhs.bit.size();
    //a intedemiate vector that store the value to add up to get the final result
    std::vector<bool> intial;
    if (rhs.bit[0] == 0) {
        
        intial.push_back(0);
    }
    else if (rhs.bit[0] == 1){
        for (size_t p = 0; p<m; ++p) intial.push_back(bit[p]);
    }
    
    for (size_t z = 1; z<n; ++z) {
        std::vector<bool> a;
        if (rhs.bit[z] == 0) {
            a.push_back(0);
        }
        else if (rhs.bit[z] == 1){
            for (size_t j = 0; j<z; ++j) {
                a.push_back(0);
            }
            for (size_t j = z; j<z + m; ++j) {
                a.push_back(bit[j - z]);
            }
        }
        //intial+a calc.
        size_t h = intial.size();//m  bit
        
        size_t l = a.size();//n   bit2
        if (l>h) {
            for (size_t i = h; i<l; ++i) intial.push_back(0);
        }
        else for (size_t i = l; i<h; ++i) a.push_back(0);
        bool carry = 0;
        
        
        for (size_t i = 0, w = intial.size(); i<w; ++i) {
            
            
            if (carry == 0) {
                
                if (intial[i] & a[i]) {
                    carry = 1;
                    intial[i] = 0;
                }
                else if (intial[i] | a[i]) {
                    intial[i] = 1;
                }
                
            }
            else if (carry == 1) {
                if (intial[i] & a[i]) {
                    intial[i] = 1;
                    carry = 1;
                }
                else if (intial[i] | a[i]) {
                    intial[i] = 0;
                    carry = 1;
                }
                else if (intial[i] == 0 && a[i] == 0) {
                    intial[i] = 1;
                    carry = 0;
                }
            }
        }
        if (carry == 1) {
            intial.push_back(1);
        }
    }
    bit.clear();
    //final soltion of multi equal
    for (size_t q = 0, max = intial.size(); q<max; ++q) {
        bit.push_back(intial[q]);
    }
    
    return;
    
}

/** the member function of Integer print the integer as integer
 */
void Integer::print_as_int()  const{
    //convert the vector back to base 10
    
    int base_10 = 0;
    // convert binary to int
    for (size_t i = 0, n = bit.size(); i<n; ++i){
        base_10 += bit[i] * static_cast<int>(pow(2., i));
    }
    std::cout << base_10;
    return;
}

/** the member function of Integer print the integer as a binary code
 */
void Integer::print_as_bits() const{
    std::cout << "(";
    //to print vector bits in opposite order
    for (size_t i = 1, n = bit.size(); i <= n; ++i){
        std::cout << bit[n - i];
    }
    std::cout << ")_2";
    return;
}

/** operation of addition of two integers in binary
 doing addition
 @param lhs the input for addition
 @param rhs the input for addition
 @returns lhs in binary code
 */
Integer plus(Integer lhs, const Integer& rhs){
    lhs.plus_equals(rhs);
    return lhs;
}


/** operation of multipilcation of two integers in binary
 @param lhs the input for multiplication
 @param rhs the input for multiplication
 @returns lhs return in binary code
 */

Integer multiply(Integer lhs, const Integer& rhs){
    lhs.times_equals(rhs);
    return lhs;
}

