
/** @file hw2.cpp
 @author [Zhuoyou Wang]
 @date [10/05/16]
 
 Create a class Integer that mimics the way nonnegative integers are stored in a computer
 */
#include <iostream>
#include <vector>
#include <cmath>


class Integer {
public:
    // Constructors
    Integer();
    Integer(unsigned int a);
    //member function
    void print_as_int()  const;
    void print_as_bits() const;
    
    //operator overload
    Integer& operator+=(const Integer& value);
    Integer& operator*=(const Integer& value);
    
    //comparision function
    bool operator<(const Integer& rhs) const;
    bool operator==(const Integer& rhs) const;
private:
    void clean_up();
    std::vector<bool> bit;
};

//add on motified version
Integer operator+(Integer a, const Integer& b);
Integer operator*(Integer a, const Integer& b);

//

bool operator!= (const Integer& lhs, const Integer& rhs);
bool operator>(const Integer& lhs, const Integer& rhs);
bool operator<=(const Integer& lhs, const Integer& rhs);
bool operator>=(const Integer& lhs, const Integer& rhs);

int main() {
    unsigned int uint_value;
    std::cout << "Please input an integer a: ";
    std::cin >> uint_value;
    Integer a = uint_value; // Create Integer type with input value
    std::cout << "The base-2 representation of a is:"; a.print_as_bits();
    std::cout << std::endl;
    std::cout << "Please input an integer b:";
    std::cin >> uint_value;
    Integer b = uint_value; // Create Integer type with input value
    std::cout << "The base-2 representation of b is: "; b.print_as_bits();
    std::cout << std::endl;
    // Let ' s do some basic arithmetic
    Integer c = a + b;
    Integer d = a*b;
    // Print out values
    std::cout << "a + b = "; c.print_as_int(); std::cout << " = ";
    c.print_as_bits(); std::cout << std::endl;
    std::cout << "a * b = "; d.print_as_int(); std::cout << " = ";
    d.print_as_bits(); std::cout << std::endl;
    //Test comparison functions
    if (a < b) std::cout << "a < b" << std::endl; if (a <= b) std::cout << "a <= b" << std::endl; if (a == b) std::cout << "a == b" << std::endl; if (a != b) std::cout << "a != b" << std::endl; if (a >= b) std::cout << "a >= b" << std::endl;
    if (a > b) std::cout << "a > b" << std::endl;
    
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
    clean_up();
}

/**
 This is where we overload the += operation
 @param value is pass by refferece
 @return return the vlue that is been modified and it does not make a copy
 */

Integer& Integer::operator+=(const Integer& value) {
    
    //get m n vecotr size
    size_t a = bit.size();
    
    size_t b = value.bit.size();
    //create a temperory variable to store and modify the vector
    std::vector<bool> bit2(value.bit);
    
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
    clean_up();
    return *this;
    
}

/** Overload the operator *= and pass the result by refference
 @param value
 @returns return the vlue that is been modified and it does not make a copy
 */
Integer& Integer::operator*=(const Integer& value) {
    
    
    //multi fxn
    size_t m = bit.size();
    size_t n = value.bit.size();
    //a intedemiate vector that store the value to add up to get the final result
    std::vector<bool> intial;
    if (value.bit[0] == 0) {
        
        intial.push_back(0);
    }
    else if (value.bit[0] == 1){
        for (size_t p = 0; p<m; ++p) intial.push_back(bit[p]);
    }
    
    for (size_t z = 1; z<n; ++z) {
        std::vector<bool> a;
        if (value.bit[z] == 0) {
            a.push_back(0);
        }
        else if (value.bit[z] == 1){
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
    clean_up();
    return *this;
}
/** the member function of Integer print the integer as integer
 */
void Integer::print_as_int()  const {
    //convert the vector back to base 10
    
    int base_10 = 0;
    // convert binary to int
    for (size_t i = 0, n = bit.size(); i<n; ++i) {
        base_10 += bit[i] * static_cast<int>(pow(2., i));
    }
    std::cout << base_10;
    return;
}

/** the member function of Integer print the integer as bits
 */
void Integer::print_as_bits() const {
    std::cout << "(";
    //to print vector bits in opposite order
    for (size_t i = 1, n = bit.size(); i <= n; ++i) {
        std::cout << bit[n - i];
    }
    std::cout << ")_2";
    return;
}
//overload operator + and *
Integer operator+(Integer a, const Integer& b) {
    return a += b;
}
/** operation of addition of two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer mutiplication as a vector of bool]
 */
Integer operator*(Integer a, const Integer& b) {
    return a *= b;
}


//define private member function clean up
void Integer::clean_up() {
    while (bit[bit.size() - 1] == 0) {
        bit.pop_back();
    }
}

//overload the comparison operator
/**
 
 */
bool Integer::operator<(const Integer& rhs) const{
    if (bit.size()<rhs.bit.size())
        return true;
    else if (bit.size()>rhs.bit.size())
        return false;
    for (size_t a = bit.size(); a>0; a--) {
        if (bit[a - 1]>rhs.bit[a - 1])
            return false;
        else if (bit[a - 1]<rhs.bit[a - 1])
            return true;
    }
    //when to vectors are equal
        return false;
}

//overload == operator
bool Integer::operator==(const Integer& rhs) const {
    if (bit.size() != rhs.bit.size())
        return false;
    //variable okay to use in one fxn?
    for (size_t i = 0; i<bit.size(); i++) {
        if (bit[i] != rhs.bit[i])
            return false;
    }
    return true;
}


//use those two compairson operator that we got to derive the rest
bool operator!= (const Integer& lhs, const Integer& rhs) { return !(lhs == rhs); }
bool operator>  (const Integer& lhs, const Integer& rhs) { return rhs < lhs; }
bool operator<=(const Integer& lhs, const Integer& rhs) { return !(lhs > rhs); }
bool operator>=(const Integer& lhs, const Integer& rhs) { return !(lhs < rhs); }

