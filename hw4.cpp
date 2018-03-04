/** @file hw4.cpp
 @author [Zhuoyou Wang]
 @date [10/18/16]
 
 [In this homework we suppose to write an iterator class WordCrawler which acts like a pointer except it indexes words in a
 std::string. Overload the operators to perform the analogous pointer operations.
 ]
 
 */

#include <iostream>
#include <string>
/** @class WordCrawler
 @brief acts like a pointer except it indexes words in a
 std::string.
 
 This class is designed to mimic the pointer for words in sentence instead of traditional char pointer
 
 */
class WordCrawler{
public:
    WordCrawler(std::string s);
    WordCrawler& operator++();
    WordCrawler& operator--();
    WordCrawler& operator+=(int n);
    WordCrawler& operator-=(int n);
    std::string operator*();
    std::string operator[](int n);
private:
    std::string words;
    char* current_word;
};

int word_count(std::string words);
int the_count(std::string words);
void every_other_in(std::string words);
void print_in_reverse(std::string words);


int main() {
    std::string words;
    std::cout << "Please input some words:\n"; std::getline(std::cin, words);
    std::cout << "The total number of words is : " << word_count(words) << std::endl;
    std::cout << "The total number of times 'the' appears is: " << the_count(words) << std::endl;
    std::cout << "Every other word is: "; every_other_in(words); std::cout << std::endl;
    std::cout << "The words in reverse order are : "; print_in_reverse(words);
    std::cout << std::endl;
    return 0;
}

/**the constructor for class WordCrawler is to construct the class's member
 @param words [string get from user's input]
 create a pointer of char* type pointing to the first letter of the string.
 */
WordCrawler::WordCrawler(std::string a){
    words = a;
    current_word = &words[0];
}

/** operation of uniary addition on the class WordCrawler
 @return [a reference of WordCrawler with the pointer char*  pointing to the word after]
 */
WordCrawler& WordCrawler::operator++(){
    char* a = current_word;
    for(size_t i = 0; i<words.length(); i++){
        if(*a == ' '){
            ++a;
            current_word = a;
            break;
        }
        else if(a == &words[words.length() - 1] ){
            return *this;
            break;
        }
     ++a;
    }
    return *this;
}
/** operation of uniary addition on the class WordCrawler
 @return [a reference of WordCrawler with the pointer char* pointing to the previous word]
 */
WordCrawler& WordCrawler::operator--(){
    //check the operation is valid
    if (current_word == &words[0]){
        std::cout << "Operation is out of range.";
        return *this;
    }
    char* copy_current_word = current_word;
    copy_current_word -= 2;
    //should not be word lenth
    for (size_t i = 1; i<words.length(); i++) {
        if (*(copy_current_word) == ' ') {
            --copy_current_word;
            current_word = copy_current_word;
            break;
        }
        else if (copy_current_word == &words[0]){
            current_word = copy_current_word;
            break;
        }
        --copy_current_word;
    }
    return *this;
}

/** operation of uniary addition
 @param int n [the index of for the WordCrawler]
 @returns [the return reference is WordCrawler with current word points to the nth after word]
 */
WordCrawler& WordCrawler:: operator+=(int n){
    for (size_t i = 0; i<n; ++i) {
        ++*(this);
    }
    return *this;
}
/** operation of uniary minus
 @param int n [the index of for the WordCrawler]
 @returns [the return reference WordCrawler with current word points to the nth previous word ]
 */
WordCrawler& WordCrawler:: operator-=(int n){
    for (size_t i = 0; i<n; ++i) {
        --*(this);
    }
    return *this;
}
/** the member operation of dereference
 @returns [the return string is the word pointed by the currentword pointer]
 */
std::string WordCrawler:: operator*(){
    std::string crawler;
    char* copy_current_word = current_word;
    while (copy_current_word != &words[words.length() - 1]) {
        if (*(copy_current_word) == ' ') break;
        crawler.push_back(*(copy_current_word));
        ++copy_current_word;
    }
    return crawler;
}
/** the member operation of []
 @param int n [the index of for the WordCrawler]
 @returns [the return reference WordCrawler is a string of the word with [n]index]
 */
std::string WordCrawler::operator[](int n){
    char* copy_current_word = current_word;
    current_word = &words[0];
    *(this) += n;
    std::string crawler;
    char* copy_current_word2 = current_word;
    while (copy_current_word2 != &words[words.length() - 1]) {
        if (*(copy_current_word2) == ' ') break;
        crawler.push_back(*(copy_current_word2));
        ++copy_current_word2;
    }
    if (copy_current_word2 == &words[words.length() - 1])crawler.push_back(*(copy_current_word2));
    current_word = copy_current_word;
    return crawler;
}

/** the function  is to count number of words in string input
 @param [string words]
 @returns [ return a value of int for number of words]
 */
int the_count(std::string words){
    WordCrawler input = words;
    size_t n = words.length();
    int coutlenght = 0;
    int i = 0;
    int count = 0;
    while (coutlenght<n) {
        coutlenght += input[i].length() + 1;
        if (input[i] == "the") count++;
        i++;
    }
    
    return count;
}

/** the function  is to count number of "the" in string input
 @param [string words]
 @returns [ return a value of int for number of the]
 */
int word_count(std::string words){
    WordCrawler input = words;
    size_t n = words.length();
    int coutlenght = 0;
    int i = 0;
    while (coutlenght<n) {
        coutlenght += input[i].length() + 1;
        i++;
    }
    return i;
}
/** the function  is to print in reverse
 @param [string words]
 */
void print_in_reverse(std::string words){
    WordCrawler input = words;
    std::string reverse;
    for (int i = word_count(words) - 1; i >= 0; --i) {
        reverse = reverse + input[i] + " ";
    }
    std::cout << reverse;
}
/** the function  is to print out every other word in the input string
 @param [string words]
 */
void every_other_in(std::string words){
    WordCrawler input = words;
    std::string other_words;
    for (int i = 0; i<word_count(words); i += 2){
        other_words = other_words + input[i] + " ";
    }
    std::cout << other_words;
}
