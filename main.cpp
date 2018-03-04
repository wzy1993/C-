/** @file hw3.cpp
 @author [Zhuoyou Wang]
 @date [10/11/16]
 
 [a program to mimic the int type in C++ to mimic the operation of int]
 
 */

#include <iostream>
#include <vector>
#include <cmath>

/** @class Integer
 @brief Stores an integer value using bits
 
 This class is designed to mimic the operation of int
 and it is able to store both negative and positive numbers
 
 */
class Integer {
public:
    // Constructors
    Integer();
    Integer(int a);
    bool bit_length(const Integer& rhs) const;
    void bit_sub(const Integer& rhs);
    void bit_add(const Integer& rhs);
    //Mutators
    void print_as_int()  const;
    void print_as_bits() const;
    
    //operator overloading
    Integer& operator+=(const Integer& value);
    Integer& operator*=(const Integer& value);
    Integer& operator-=(const Integer& value);
    
    //member function for post fixed and prefixed operation
    //prefixed operators are passed by reference
    //++ increment Intefer by 1
    Integer& operator++();
    Integer operator++(int unused);
    Integer& operator--();
    Integer operator--(int unused);
    
    //plus and minus operator
    Integer& operator+();
    Integer& operator-();
    
    
    //overloding the member comparision function
    bool operator<(const Integer& rhs) const;
    bool operator==(const Integer& rhs) const;
    
    // these are unary member operators
    Integer& operator&=(const Integer& rhs);
    Integer& operator|=(const Integer& rhs);
    Integer& operator^=(const Integer& rhs);
    Integer& operator<<=(const unsigned int);
    Integer& operator>>=(const unsigned int);
    Integer operator~()const;
    
    
private:
    std::vector<bool> bit;//magnitude
    bool sign;
    void clean_up();
};



//add on motified version
Integer operator+(Integer a, const Integer& b);
Integer operator*(Integer a, const Integer& b);
Integer operator-(Integer a, const Integer& b);

//non-member test comparision function
bool operator!= (const Integer& lhs, const Integer& rhs);
bool operator>(const Integer& lhs, const Integer& rhs);
bool operator<=(const Integer& lhs, const Integer& rhs);
bool operator>=(const Integer& lhs, const Integer& rhs);
Integer operator&(Integer a, const Integer& b);
Integer operator^(Integer a, const Integer& b);
Integer operator|(Integer a, const Integer& b);


Integer operator<<(Integer lhs, const unsigned int);
Integer operator>>(Integer lhs, const unsigned int);

int main() {
    // Obtain two integer values from the console
    int uint_value;
    std::cout << "Please input an integer a: ";
    std::cin >> uint_value;
    Integer a = uint_value; // Create Integer type with input value
    
    std::cout << "The base-2 representation of a is: "; a.print_as_bits();
    std::cout << std::endl;
    
    std::cout << "Please input an integer b: ";
    std::cin >> uint_value;
    Integer b = uint_value; // Create Integer type with input value
    
    std::cout << "The base-2 representation of b is: "; b.print_as_bits(); std::cout << std::endl;
    
    // Perform basic arithmetic
    Integer plusequals = a; plusequals += b; plusequals.print_as_bits();
    std::cout << std::endl;
    
    Integer minusequals = a; minusequals -= b; minusequals.print_as_bits();
    std::cout << std::endl;
    
    
    Integer timesequals = a; timesequals *= b; timesequals.print_as_bits();
    std::cout << std::endl;
    
    Integer plus = a + b; plus.print_as_bits(); std::cout << std::endl;
    Integer minus = a - b; minus.print_as_bits(); std::cout << std::endl;
    Integer times = a*b; times.print_as_bits(); std::cout << std::endl;
    Integer prefix_increment = ++a; prefix_increment.print_as_bits();
    std::cout << std::endl;
    
    Integer postfix_increment = a++; postfix_increment.print_as_bits();//a is afacted by passing by reference
    std::cout << std::endl;
    
    Integer prefix_decrement = --a; prefix_decrement.print_as_bits();
    std::cout << std::endl;
    
    Integer postfix_decrement = a--; postfix_decrement.print_as_bits();
    std::cout << std::endl;
    
    Integer negative = -a; negative.print_as_bits(); std::cout << std::endl;
    Integer positive = +b; positive.print_as_bits(); std::cout << std::endl;
    
    // Obtain two more integer values from the console
    std::cout << "Please input an integer c: ";
    std::cin >> uint_value;
    Integer c = uint_value; // Create Integer type with input value
    
    std::cout << "The base-2 representation of c is: "; c.print_as_bits(); std::cout << std::endl;
    
    std::cout << "Please input an integer d: "; std::cin >> uint_value;
    Integer d = uint_value; // Create Integer type with input value
    
    std::cout << "The base-2 representation of d is: "; d.print_as_bits();
    std::cout << std::endl;
    
    // Comparison operators
    if (c<d) std::cout << "c<d" << std::endl;
    if (c <= d) std::cout << "c<=d" << std::endl;
    if (c>d) std::cout << "c>d" << std::endl;
    if (c >= d) std::cout << "c>=d" << std::endl;
    if (c == d) std::cout << "c==d" << std::endl;
    if (c != d) std::cout << "c!=d" << std::endl;
    
    // Bitwise operators
    Integer andequals = c; andequals &= d;
    andequals.print_as_bits(); std::cout << std::endl;
    
    Integer orequals = c; orequals |= d;
    orequals.print_as_bits(); std::cout << std::endl;
    
    Integer xorequals = c; xorequals ^= d;
    xorequals.print_as_bits(); std::cout << std::endl;
    
    Integer shiftupequals = c; shiftupequals <<= 2;
    shiftupequals.print_as_bits(); std::cout << std::endl;
    
    Integer shiftdownequals = c; shiftdownequals >>= 1;
    shiftdownequals.print_as_bits(); std::cout << std::endl;
    
    Integer negation = ~c; negation.print_as_bits(); std::cout << std::endl;
    
    Integer the_and = c&d; the_and.print_as_bits(); std::cout << std::endl;
    
    Integer the_or = c | d; the_or.print_as_bits(); std::cout << std::endl;
    
    Integer the_xor = c^d; the_xor.print_as_bits(); std::cout << std::endl;
    
    Integer shift_up = c << 2; shift_up.print_as_bits();
    std::cout << std::endl;
    
    Integer shift_down = d >> 2; shift_down.print_as_bits();
    std::cout << std::endl;
    
    return 0;
    
}

/**the defualt constructor for Integer calss */
Integer::Integer() {
    
    bit.push_back(0);
    
}

/**the constructor is able to take in both positive and negative numbers
 @param rhs [one integer input]
 */
Integer::Integer(int initial) {
    //convert to bit depending on input
    if (initial == 0) {
        bit.clear();
        sign = 0;
    }
    //pos. sign = 0; neg.sign = 1
    else if (initial < 0) sign = 1;
    else sign = 0;
    int value = abs(initial);
    while (value > 0) {
        bit.push_back(value % 2);
        value /= 2;
    }
    
}
/** the member function of Integer print the integer as integer
 */
void Integer::print_as_int()  const {
    //convert the vector back to base 10
    int a = 0;
    // convert binary to int
    for (size_t i = 0, n = bit.size(); i<n; ++i) {
        a += bit[i] * static_cast<int>(pow(2., i));
    }
    if (sign == 1)  std::cout << -a;
    else std::cout << a;
    return;
}


/** the member function of Integer print the integer into binary
 */
void Integer::print_as_bits() const {
    if (sign == true) std::cout << "-";
    else std::cout << " ";
    std::cout << "(";
    //to print vector bits in opposite order
    for (size_t i = 1, n = bit.size(); i <= n; ++i) {
        std::cout << bit[n - i];
    }
    std::cout << ")_2";
    return;
}
/** the member function of Integer is to clean up the redundent zeros in the front of an Integer
 therefore, when we are doing the comparesion will not be misguided
 */
void Integer::clean_up() {
    
    while (bit.size()>1 && bit[bit.size() - 1] == 0) {
        bit.pop_back();
    }
    //make sure 0,0 is the only representation of 0
    if (bit.size() == 0) {
        sign = 0;
        bit.push_back(0);
    }
}

//operation overload modified version
/** the function will put a + sign in front of the Interger, basically it changes nothing
 @returns [the return reference of an integer type for the result of addition]*/
Integer& Integer::operator+() {
    
    return *this;
}
/** the function will flip the sign of the Integer
 @returns [the return reference of an integer type for the result of subtraction]*/
Integer& Integer::operator-() {
    if (sign == 0)sign = 1;
    else sign = 0;
    clean_up();
    return *this;
}

/** the member function for Integer calss is to calculate a+=b for two integers
 @param rhs [one integer input in addition]
 @returns [the return reference of an integer type for the result of addition]
 
 */
Integer& Integer :: operator += (const Integer& rhs)
{
    Integer crhs = rhs;
    if (sign && rhs.sign)//-a-b
    {
        bit_add(rhs);
        sign = 1;
    }
    
    else if (sign && !rhs.sign)//-a+b
    {
        if (bit_length(rhs))//|a| < |b|
        {
            
            crhs.bit_sub(*this);
            *this = crhs;
            sign = 0;
        }
        else//|a| > |b|
        {
            bit_sub(rhs);
            sign = 1;
        }
    }
    else if (!sign && rhs.sign)//a-b
    {
        if (bit_length(rhs))
        {
            crhs.bit_sub(*this);
            *this = crhs;
            sign = 1;
        }
        else
        {
            bit_sub(rhs);
            sign = 0;
        }
        
        
        
    }
    else//a+b
    {
        bit_add(rhs);
    }
    
    return *this;
    
}
/**the member function is to compare the size of two integer
 this is used in the plus operation
 @param rhs is an Integer
 @return is a bool; true is when calling integer < rhs integer; false otherwise.
 */
bool Integer:: bit_length(const Integer& rhs) const
{
    std::vector<bool> v(bit);
    std::vector<bool> w(rhs.bit);
    
    if (bit.size()>rhs.bit.size())
        return false;
    else if (bit.size() < rhs.bit.size())
        return true;
    //if the caller has the same size as rhs
    else {
        size_t j = w.size();
        
        //if v first appears a item smaller than w, then v < w
        bool a = false;
        while (!a && j>0)
        {
            if (v[j - 1]==0 && w[j - 1]==1)
            {
                a = true;
                --j;
            }
            else --j;
        }
        return a;
    }
}



/**the member function is to add two integers' magnitude
 @param rhs is an Integer
 */
void Integer::bit_add(const Integer& rhs)
{
    std::vector<bool>rbit(rhs.bit);//make a copy if rhs
    size_t m = bit.size();
    size_t n = rhs.bit.size();
    
    //make two binary numbers in the same length
    if (m<n)
    {
        for (size_t i = 0; i < n - m; ++i)
        {
            bit.push_back(0);
        }
        
    }
    
    else if (m>n)
    {
        for (size_t i = 0; i< m - n; ++i)
            rbit.push_back(0);
    }
    else {}
    
    bool carry = 0;//carry stores the carrying number when adding bits by bits
    
    for (size_t i = 0; i < bit.size(); ++i)
    {
        bool a = (bit[i] + rbit[i] + carry) % 2;
        if (bit[i] + rbit[i] + carry >= 2)
        {
            carry = 1;
        }
        else
            carry = 0;
        
        bit[i] = a;//copy the value of a to bit[i]
    }
    
    if (carry == 1)
    {
        bit.push_back(1);//if the final carrying is 1, then adding 1 in the front
    }
    
    clean_up();//make sure no 0 in the beginning of the list
};

/**the member function is to minus two integer magnitude ; when the calling object's value is bigger than the other
 @param rhs is an Integer
 */
void Integer::bit_sub(const Integer& rhs)//assumption:*this > rhs
{
    Integer arhs = rhs;//make a copy if rhs
    size_t m = bit.size();
    size_t n = rhs.bit.size();
    
    //make two binary numbers in the same length
    if (m<n)
    {
        for (size_t i = 0; i < n - m; ++i)
        {
            bit.push_back(0);//add 0 in the front
        }
        
    }
    
    else if (m>n)
    {
        for (size_t i = 0; i< m - n; ++i)
            arhs.bit.push_back(0);//add 0 in the front
    }
    
    size_t bitS = bit.size();
    
    for (size_t i = 0; i < bit.size(); ++i)
    {
        bool a = !(arhs.bit[i]);
        arhs.bit[i] = a;
    }
    
    Integer z = 1;
    arhs.bit_add(z);
    bit_add(arhs);
    
    if (bit.size() > bitS) bit.pop_back();
    
    clean_up();
    
}


/** the member function for Integer calss is to calculate a-=b for two integers
 @param rhs [one integer input in addition]
 @returns [the return reference of an integer type for the result of subtraction]
 
 */
// this is basically put a negative sign on one of the input and then use the plus operation will give the result
Integer& Integer::operator-=(const Integer& value) {
    //create a mid = lhs integer (sign + vector bit)
    Integer avalue = value;
    //value-
    if (value.sign) avalue.sign = 0;
    //value +
    else if (value.sign == 0) avalue.sign = 1;
    *this += (avalue);
    
    return*this;
}
/** the member function for Integer calss is to calculate a*=b for two integers
 @param value [one integer input in mutiplication]
 @returns [the return reference of an integer type for the result of multiplication (of what)]
 */
Integer& Integer::operator*=(const Integer& value) {
    
    //assign sign value ++/--=>pos(0)  +-/-+ => neg(1)(sign^value.sign)
    if (sign ^ (value.sign)) sign = 1;
    else sign = 0;

    size_t m = bit.size();
    
    size_t n = value.bit.size();
    if (bit.size() == 0 || value.bit.size() == 0 || (value.bit.size() == 1 && value.bit[0] == 1) || (bit.size() == 1 && bit[0] == 1)) {
        std::vector<bool>zero(0);
        this->bit = zero;
    }
    //size_t rowA=n+m-1;//a element number
    //a intedemiate vector
    std::vector<bool> a_0;
    if (value.bit.size()>0 && value.bit[0] == 0) {
        
        a_0.push_back(0);
    }
    else if (value.bit.size()>0 && value.bit[0] == 1) {
        for (size_t p = 0; p<m; ++p) a_0.push_back(bit[p]);
    }
    for (size_t z = 1; z<n; ++z) {
        std::vector<bool> a;
        if (value.bit[z] == 0) {
            a.push_back(0);
        }
        else if (value.bit[z] == 1) {
            for (size_t j = 0; j<z; ++j) {
                a.push_back(0);
            }
            for (size_t j = z; j<z + m; ++j) {
                a.push_back(bit[j - z]);
            }
        }
        //a_0+a calc.
        size_t h = a_0.size();//m  bit
        
        size_t l = a.size();//n   bit2
        if (l>h) {
            for (size_t i = h; i<l; ++i) a_0.push_back(0);
        }
        else for (size_t i = l; i<h; ++i) a.push_back(0);
        bool carry = 0;
        
        
        for (size_t i = 0, w = a_0.size(); i<w; ++i) {
            
            
            if (carry == 0) {
                
                if (a_0[i] & a[i]) {
                    carry = 1;
                    a_0[i] = 0;
                }
                else if (a_0[i] | a[i]) {
                    a_0[i] = 1;
                }
                
            }
            else if (carry == 1) {
                if (a_0[i] & a[i]) {
                    a_0[i] = 1;
                    carry = 1;
                }
                else if (a_0[i] | a[i]) {
                    a_0[i] = 0;
                    carry = 1;
                }
                else if (a_0[i] == 0 && a[i] == 0) {
                    a_0[i] = 1;
                    carry = 0;
                }
            }
        }
        if (carry == 1) {
            a_0.push_back(1);
        }
    }
    bit.clear();
    //final soltion of multi equal
    for (size_t q = 0, max = a_0.size(); q<max; ++q) {
        bit.push_back(a_0[q]);
    }
    
    this->bit = a_0;
    clean_up();
    return *this;
}

//test comparision function
/** the member function of Integer is to compare two integers in binary
 @param const rhs [the right integer input]
 @returns [the return value is an bool, if the ... is smaller than rhs the function retruns true; false otherwise.]
 */
bool Integer::operator < (const Integer& rhs) const {
    if (sign != rhs.sign) {
        if (sign) return true;
        else return false;
    }
    
    else if (sign&rhs.sign) {
        if (bit.size()<rhs.bit.size())
            return false;
        else if (bit.size()>rhs.bit.size())
            return true;
        //alternative way? size_t i=bit.size()-1;i>=0; i--
        for (size_t i = bit.size(); i>0; i--) {
            if (bit[i - 1]>rhs.bit[i - 1])
                return true;
            else if (bit[i - 1]<rhs.bit[i - 1])
                return false;
        }
        return false;
    }
    
    else {//when positive
        if (bit.size()<rhs.bit.size())
            return true;
        else if (bit.size()>rhs.bit.size())
            return false;
        //alternative way? size_t i=bit.size()-1;i>=0; i--
        for (size_t i = bit.size(); i>0; i--) {
            if (bit[i - 1]>rhs.bit[i - 1])
                return false;
            else if (bit[i - 1]<rhs.bit[i - 1])
                return true;
        }
        return false;
        
    }
}

/** the member function of Integer is to test if the two integers in binary is equal
 @param const rhs [the right integer input]
 @returns [the return value is an bool, if the ... is the same as rhs, the function retruns true; false otherwise.]*/
bool Integer::operator==(const Integer& rhs) const {
    //when to use = !=...?
    if (sign != rhs.sign) return false;
    if (bit.size() != rhs.bit.size())
        return false;
    //variable okay to use in one fxn?
    for (size_t i = 0; i<bit.size(); i++) {
        if (bit[i] != rhs.bit[i])
            return false;
    }
    return true;
}

//adds on motified version
/** operation of addition of two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer addition as a vector of bool]
 */
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
/** operation of subtraction of two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer mutiplication as a vector of bool]
 */
Integer operator-(Integer a, const Integer& b) {
    return a -= b;
}
/**
 operation of prefixed++ for two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer a+1 as a vector of bool]
 */
Integer& Integer::operator++() {
    
    *this = *this + 1;
    
    return*this;
}
/**
 operation of postfixed++ for two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer a+1 as a vector of bool]
 */
Integer Integer::operator++(int unused) {
    Integer clone(*this); // make a copy
    ++ *this;                  // increment the object
    return clone;            // return the clone
}
/**
 operation of prefixed-- for two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer a-1 as a vector of bool]
 */
Integer& Integer::operator--() {
    *this = *this - 1;
    return*this;
}
/**
 operation of postfixed -- for two integers in binary
 @param lhs [the left integer input] @param rhs [the right integer input]
 @returns [the return value is an integer a-1 as a vector of bool]
 */
Integer Integer::operator--(int unused) {
    Integer clone(*this); // make a copy
    -- *this;                  // increment the object
    return clone;
}




/** the function  is to test if the two integers in binary is not equal
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return value is an bool, if the lhs is not the same as rhs, the function retruns true; false otherwise.]
 */
bool operator!= (const Integer& lhs, const Integer& rhs) { return !(lhs == rhs); }
/** the function  is to test if the lhs integer is bigger than rhs one
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return value is an bool, if the lhs is larger than rhs, the function retruns true; false otherwise.]
 */
bool operator>(const Integer& lhs, const Integer& rhs) { return (rhs < lhs); }
/** the function  is to test if the lhs integer is smaller and equal to  rhs one
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return value is an bool, if the lhs <= rhs, the function retruns true; false otherwise.]
 */
bool operator<=(const Integer& lhs, const Integer& rhs) { return !(lhs > rhs); }
/** the function  is to test if the lhs integer >= rhs one
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return value is an bool, if the lhs >= rhs, the function retruns true; false otherwise.]
 */
bool operator>=(const Integer& lhs, const Integer& rhs) { return !(lhs < rhs); }

//bitwise
/** the function  is to negate bitwise */
Integer Integer:: operator~()const {
    Integer mid5 = *this;
    if (sign) mid5.sign = 0;
    else mid5.sign = 1;
    for (size_t i = 0; i<bit.size(); ++i) {
        //mid5.bit[i]=~bit[i];
        if (mid5.bit[i] == true) mid5.bit[i] = false;
        else mid5.bit[i] = true;
    }
    mid5.clean_up();
    return mid5;
}
/** the member function  is to & bitwise */
Integer& Integer::operator&=(const Integer& rhs) {
    //same size
    size_t m = bit.size();
    
    size_t n = rhs.bit.size();
    //copy of value bit
    std::vector<bool> bit2(rhs.bit);
    
    if (bit.size()<rhs.bit.size()) {
        for (size_t i = m; i<n; ++i) bit.push_back(0);
    }
    else for (size_t e = n; e<m; ++e) bit2.push_back(0);
    
    sign = (sign&(rhs.sign));
    for (size_t i = 0; i<bit.size(); ++i) {
        bit[i] = (bit[i] & bit2[i]);
    }
    clean_up();
    return *this;
}
/** the member function  is to or bitwise */
Integer& Integer::operator|=(const Integer& rhs) {
    //same size
    size_t m = bit.size();
    
    size_t n = rhs.bit.size();
    //copy of value bit
    std::vector<bool> bit2(rhs.bit);
    
    if (bit.size()<rhs.bit.size()) {
        for (size_t i = m; i<n; ++i) bit.push_back(0);
    }
    else for (size_t e = n; e<m; ++e) bit2.push_back(0);
    
    
    sign = (sign | rhs.sign);
    for (size_t i = 0; i<bit.size(); ++i) {
        bit[i] = (bit[i] | bit2[i]);
    }
    return *this;
}
/** the member function  is to ^ bitwise */
Integer& Integer::operator^=(const Integer& rhs) {
    //same size
    size_t m = bit.size();
    
    size_t n = rhs.bit.size();
    //copy of value bit
    std::vector<bool> bit2(rhs.bit);
    
    if (bit.size()<rhs.bit.size()) {
        for (size_t i = m; i<n; ++i) bit.push_back(0);
    }
    else for (size_t e = n; e<m; ++e) bit2.push_back(0);
    
    
    sign = (sign ^ (rhs.sign));
    for (size_t i = 0; i<bit.size(); ++i) {
        bit[i] = (bit[i] ^ (bit2[i]));
    }
    return *this;
}

/** the function  is to operate & for two integers
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return integer value ]
 */
Integer operator&(Integer a, const Integer& b) {
    
    Integer value = a; value &= b;
    return value;
}
/** the function  is to operate | for two integers
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return integer value ]
 */
Integer operator|(Integer a, const Integer& b) {
    return a |= b;
}
/** the function  is to operate ^ for two integers
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return integer value ]
 */
Integer operator^(Integer a, const Integer& b) {
    return a ^= b;
}

//shift
/** the member function  is to shift up by a value bitwise */
Integer& Integer::operator<<=(const unsigned int a) {
    
    for (size_t j = a; j < bit.size(); j--) bit.push_back(bit[bit.size() - 1]);
    
    for (size_t jc = bit.size(); jc> a; jc--)    bit[jc - 1] = bit[jc - a - 1];
    for (int i = a - 1; i >= 0; i--) {
        bit[i] = 0;
    }
    clean_up();
    return *this;
    
}
/** the member function  is to shift down by a value bitwise */
Integer& Integer:: operator>>=(const unsigned int a) {
    
    
    for (size_t j = 0; j < bit.size() - a; j++) bit[j] = bit[j + a];
    
    for (size_t jc = a; jc> 0; jc--)    bit.pop_back();
    
    clean_up();
    return *this;
}
/** the function  is to is to shift up by a value bitwise
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return integer value ]
 */
Integer operator<<(Integer lhs, const unsigned int a) {
    
    return lhs <<= a;
}
/** the function  is to is to shift down by a value bitwise
 @param const rhs [the right integer input] @param const lhs [the left integer input]
 @returns [the return integer value ]
 */
Integer operator>>(Integer lhs, const unsigned int a) {
    return lhs >>= a;
}
