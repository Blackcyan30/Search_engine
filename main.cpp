// Name : M. Talha Adnan
// UIN: 664908073
// mkhan387@uic.edu
// This is the project 2 of CS 251 fall 2023. This file contains the functions of the search engine created.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <unordered_set>
#include "search.h"
using namespace std;



void printMap(const map<string, set<string> >& index);
void cleanTokenTest();
void gatherTokensTest();
void buildIndexTest();
void queryMatchesTest();


int main() {
    cleanTokenTest();
    gatherTokensTest();
    buildIndexTest();
    queryMatchesTest();
    return 0;
}

// This is a unit test for the cleanToken function.
void cleanTokenTest(){
    string testCase1, testCase2, testCase3, testCase4;
    string ansCase1, ansCase2, ansCase3, ansCase4;

    testCase1 = "Hello"; // Test for all things to be lower case.
    ansCase1 = "hello";

    testCase2 = "!$%#^@^ LSD! lysergic Acid DyethylAmide.@!@#$   "; // Test for punctuation removal and lower case 
    ansCase2 = "lsd! lysergic acid dyethylamide"; 

    testCase3 = "1412355    14!!!&#"; // Tests if returns the empty string if the token does not contain at least one letter 
    ansCase3 = "";

    testCase4 = "  !$   LSD ! is not good for you? &&   ";
    ansCase4 = "lsd ! is not good for you";
    
    bool test1 = (ansCase1 == cleanToken("Hello")) ? true : false;
    bool test2 = (ansCase2 == cleanToken("!$%#^@^ LSD! lysergic Acid DyethylAmide.@!@#$   ")) ? true : false;
    bool test3 = (ansCase3 == cleanToken("1412355    14!!!&#")) ? true : false;
    bool test4 = (ansCase4 == cleanToken("  !$   LSD ! is not good for you? &&   ")) ? true : false;

    if (!(test1 && test2 && test3 && test4)){
        cout << "Your cleanToken function does not function as expected" << endl;
    }else{
        cout << "Your cleanToken function works as expected" << endl;
    }

}

void gatherTokensTest(){

    string testCase1, testCase2, testCase3, testCase4;
    set<string> ansCase1, ansCase2, ansCase3, ansCase4;

    testCase1 = "Hello"; 
    ansCase1 = {"hello"};

    testCase2 = "!$%#^@^ LSD! lysergic Acid DyethylAmide.@!@#$   ";  
    ansCase2 = {"lsd", "lysergic", "acid", "dyethylamide"}; 
    

    testCase3 = "1412355    14!!!&#"; 
    ansCase3 = {};

    testCase4 = "  !$   hello hello hello hello hello? &&   ";
    ansCase4 = {"hello"};
    
    bool test1 = (ansCase1 == gatherTokens(testCase1)) ? true : false;
    bool test2 = (ansCase2 == gatherTokens(testCase2)) ? true : false;
    bool test3 = (ansCase3 == gatherTokens(testCase3)) ? true : false;
    bool test4 = (ansCase4 == gatherTokens(testCase4)) ? true : false;

    if (!(test1 && test2 && test3 && test4)){
        cout << "Your gatherTokens function does not function as expected" << endl;
    }else{
        cout << "Your gatherTokens function works as expected" << endl;
    }

}

void buildIndexTest(){
    map<string, set<string> > test; 
    string testCase1, testCase2, testCase3, testCase4;
    int ansCase1, ansCase2, ansCase3, ansCase4;

    testCase1 = "tiny.txt"; 
    ansCase1 = 4;

    testCase2 = "stackoverflow.txt";  
    ansCase2 = 13; 
    

    testCase3 = "wiki-uni.txt"; 
    ansCase3 = 148;

    testCase4 = "uiccs-news.txt";
    ansCase4 = 85;
    
    bool test1 = (ansCase1 == buildIndex(testCase1, test)) ? true : false;
    bool test2 = (ansCase2 == buildIndex(testCase2, test)) ? true : false;
    bool test3 = (ansCase3 == buildIndex(testCase3, test)) ? true : false;
    bool test4 = (ansCase4 == buildIndex(testCase4, test)) ? true : false;

    if (!(test1 && test2 && test3 && test4)){
        cout << "Your buildIndex function does not function as expected" << endl;
    }else{
        cout << "Your buildIndex function works as expected" << endl;
    }
    
}

void queryMatchesTest(){
    map<string, set<string> > test, test1, test2, test3; 
    string testCase1, testCase2, testCase3, testCase4;
    string testCase1File, testCase2File, testCase3File, testCase4File;
    set<string> ansCase1, ansCase2, ansCase3, ansCase4;

    testCase1 = "tiny.txt";
    buildIndex(testCase1, test);
    set<string> ans1 = findQueryMatches(test,"blue +red -yellow");
    ansCase1 = {"www.dr.seuss.net"};

    testCase2 = "stackoverflow.txt"; 
    buildIndex(testCase2, test1);
    set<string> ans2 = findQueryMatches(test1, "strings time");
    ansCase2 = {"https://stackoverflow.com/questions/477816/what-is-the-correct-json-content-type", "https://stackoverflow.com/questions/8318911/why-does-html-think-chucknorris-is-a-color"}; 
    

    testCase3 = "wiki-uni.txt"; 
    buildIndex(testCase3, test2);
    set<string> ans3 = findQueryMatches(test2, "illinois -college");
    ansCase3 = {"https://en.wikipedia.org/wiki/DeVry_University","https://en.wikipedia.org/wiki/Illinois_State_University", "https://en.wikipedia.org/wiki/Northern_Illinois_University", "https://en.wikipedia.org/wiki/Southern_Illinois_University_Edwardsville", "https://en.wikipedia.org/wiki/University_of_Illinois_at_Chicago", "https://en.wikipedia.org/wiki/University_of_Illinois_at_Springfield", "https://en.wikipedia.org/wiki/University_of_Illinois_at_Urbana", "https://en.wikipedia.org/wiki/Western_Illinois_University"};

    testCase4 = "uiccs-news.txt";
    buildIndex(testCase4, test3);
    set<string> ans4 = findQueryMatches(test3, "award +app");
    ansCase4 = {"https://cs.uic.edu/news-stories/computer-science-student-takes-first-prize-at-uic-2019-impact-and-research-day/"};
    
    bool t1 = (ansCase1 == ans1) ? true : false;
    bool t2 = (ansCase2 == ans2) ? true : false;
    bool t3 = (ansCase3 == ans3) ? true : false;
    bool t4 = (ansCase4 == ans4) ? true : false;

    if (!(t1 && t2 && t3 && t4)){
        cout << "Your findQueryMatches function does not function as expected" << endl;
    }else{
        cout << "Your findQueryMatches function works as expected" << endl;
    }

}

void printMap(const map<string, set<string> >& index) {
    for (const auto& pair : index) {
        cout << "Key: " << pair.first << endl;
        cout << "Values: ";
        for (const string& value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }
}