/** @file hw6.cpp
	@author [Wang Zhuoyou]
	@date [11/02/2016]
 
 The program basically just asks the user to input one integer number, then it will create four .txt files, contains corresponding calculations of Partitions, first type Stirling number, second type Stirling number, and factorials.
 */

//strling 1 has some issus need to be resolved

#include <iostream>
#include <string>
#include <fstream>

unsigned int  Partition(int k, int n);
int  Stirling1(int k, int n);
unsigned int  Stirling2(int k, int n);
unsigned int  Factorial(unsigned int n);

/** Main function -
 Asks the user to input one integer number, then it creates four .txt files containing different types of calculations. It also output messages that indicate the file generating processes.
 */
int main() {
    
    // Ask for input integer
    unsigned int m;
    std::cout << "Welcome! Please input a number m: ";
    std::cin >> m;
    std::ofstream fout;
    
    // Create Partition.txt
    fout.open("Partition.txt");
    std::cout << "Creating Partition.txt file ... ";
    
    for (int row =1; row <=m; row++){
        for(int column =1; column <= m; column++){
            fout << Partition(row,column) <<" ";
        }
        fout << std::endl;
    }
    
    fout.close();
    std::cout << "Done." <<std::endl;
    
    // Create Stirling1.txt
    fout.open("Stirling1.txt");
    std::cout << "Creating Stirling1.txt file ... ";
    
    for (int row =1; row <=m; row++){
        for(int column =1; column <= m; column++){
            fout << Stirling1(row,column) <<" ";
        }
        fout << std::endl;
    }
    
    fout.close();
    std::cout << "Done." <<std::endl;
    
    // Create Stirling2.txt
    fout.open("Stirling2.txt");
    std::cout << "Creating Stirling2.txt file ... ";
    
    for (int row =1; row <=m; row++){
        for(int column =1; column <= m; column++){
            fout << Stirling2(row,column) <<" ";
        }
        fout << std::endl;
    }
    
    fout.close();
    std::cout << "Done." <<std::endl;
    
    // Create Factorial.txt
    fout.open("Factorial.txt");
    std::cout << "Creating Factorial.txt file ... ";
    
    for (unsigned int row =1; row <=m; row++){
        fout << Factorial(row) << std::endl;
    }
    
    fout.close();
    std::cout << "Done." <<std::endl;
    
    return 0;
}

/** Partition p(k,n) = p(k,n-k) + p(k-1,n), any negative input is automatically 0; p(0, n) = 0 when n > 0;
 p(k, 0) = 1 when k >= 0; p(k, n) = p(n, n) when k > n.
 @param k is a int
 @param n is alaso int
 @return p(k,n-k) + p(k-1,n).
 */
unsigned int Partition(int k, int n){
    
    //Base case
    if (n < 0 || k<0)
        return 0;
    if (k ==0 && n > 0)
        return 0;
    if (k>=0 && n == 0)
        return 1;
    if (k > n)
        return Partition(n,n);
    
    return Partition(k, n-k)+ Partition(k-1, n);
}

/** First kind of Stirling number: s(k,n) = -(n-1)*s(k, n-1) + s(k-1,n-1), s(k,n)= 0 for k<0 or n<0; s(0,n)=0 for n>0;
 s(k,0)=0 for k >0; s(k,n)=0 for k>n; s(n,n)=1
 @param k is a int
 @param n is alaso an int
 @return -(n-1)*s(k, n-1) + s(k-1,n-1).
 */
int Stirling1(int k, int n){
    
    // Base case
    if (k<0 || n<0)
        return 0;
    if ((n==0 && k >0)|| (k==0 && n >0))
        return 0;
    if (k>n)
        return 0;
    if (k ==n)
        return 1;
    
    return -(n-1)*Stirling1(k,n-1) + Stirling1(k-1, n-1);
}

/** Second kind of Stirling number: S(k,n) = k*S(k, n-1) + S(k-1,n-1), S(k,n)= 0 for k<0 or n<0; S(0,n)=0 for n>0;
 S(k,0)=0 for k >0; S(k,n)=0 for k>n; S(n,n)=1
 @param k is a int
 @param n is alaso an int
 @return k*S(k, n-1) + S(k-1,n-1).
 */
unsigned int Stirling2(int k, int n){
    
    // Base case
    if (k<0 || n<0)
        return 0;
    if ((n==0 && k >0)|| (k==0 && n >0))
        return 0;
    if (k>n)
        return 0;
    if (k ==n)
        return 1;
    
    return k*Stirling2(k,n-1) + Stirling2(k-1, n-1);
}

/** Factorial n! = n*(n-1)*(n-2)... with 0!=1; not defined for negative integers
 @param n is the nonnegative integer
 @return n! the factorial of n.
 */
unsigned int Factorial(unsigned int n) {
    
    // Base cases: 0! = 1 and 1! = 1
    if(n <= 1) return 1;
    
    // n! = (n-1)! * n
    return n*Factorial(n-1);
}
