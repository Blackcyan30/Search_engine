// Name : M.Talha Adnan
// This file contains the functions of the search engine created.

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
    The function cleanToken takes in a string as input. It has terminal statements which return
    an empty string if the string is empty or it has no alphabets.
    It cleans the token by checking if there are any whitespaces or puctuation marks
    (only those flaged by ispunct()) trailing or leading the input string.
    It then returns the cleaned string / token.
*/
string cleanToken(string s) {
    int startInd = 0, endInd = (s.size()) - 1;
    string cleanToken;
    bool alphaChar = false;
    // checks if string is empty

    if(s.empty()){
        return "";
    }
    // trims leading and trailing whitespace as well as punctuation.
    while(( s[startInd] == ' ') || ispunct( s[startInd] )){
        startInd++;
    }
     while(( s[endInd] == ' ' ) || ispunct( s[endInd] )){
        endInd--;
    }

    int cleanSize = (endInd - startInd) + 1 ;

    for (int i = startInd; i <= endInd; i++){
        if (isalpha(s[i])){
            s[i] = tolower(s[i]);
            alphaChar = true;
        }
    }

    // checks if loop encountered at least 1 alphabetical character.
    if(!alphaChar){
        return "";
    }
    string cleanedToken = s.substr(startInd, cleanSize);
    
    return cleanedToken;  // returns the clean portion of the string by slicing it.
}

/*
This function gathers individual words(tokens) from a *cleaned* string of words and outputs them in a set.
The function first divides input string into individual word (tokens), which will be strings separated by spaces.
Each is then cleaned using the cleanToken helper function. This removes any leading and trailing whitespace and punctuation.
After the cleaning is done the function stores them in a set and returns the set as the return of the fuction giving the 
tokens for querying.
*/
set<string> gatherTokens(string text) {
    set<string> tokens;
    size_t currLoc = 0, previousLoc = 0;

    do{
        currLoc = text.find(" ", previousLoc);
        string tempToken = text.substr(previousLoc, currLoc - previousLoc);
        if (cleanToken(tempToken) != ""){
            tokens.emplace(cleanToken(tempToken));
            if (currLoc == string::npos){
                
                tokens.emplace(cleanToken(text.substr(previousLoc)));
                break;
            }
        }

        previousLoc = currLoc + 1;

    }while(currLoc != string::npos);

    return tokens;
}

/*  This function builds the inverted index needed for the search engine to be efficent and quick.
    It takes in the map to populate and the file name of the file to populate it from.
    It returns the number of pages that it has parsed through.
    It reads the file and takes in the first line as the url and the second line always to be the 
    content of the page that is at the url. It stores them in seperate url and content variables.
    It gathers the indiviual words in the content using the gatherTokens function and stores them in a variable.
    The individual tokens are then used as the keys in the map and the urls are inserted in the set that is 
    the value associated with the key that it was found at. After the file content ends the func exits
    and returns the number of pages it went throught to populate the map.
*/
int buildIndex(string filename, map<string, set<string> >& index) {
    string content, url;
    set<string> tokens;
    int ct = 0;
    ifstream input(filename);
    if (!input.is_open()){
        return 0;
    }
    
    while(getline(input, url)){
        getline(input, content);
        tokens = gatherTokens(content);
        for (auto key : tokens){
            index[key].insert(url);
        }
        ct++;
    }
    return ct;
}

//  This function is a helper function. It takes in a set and prints it out using a for each loop
void printSet(const set<string> item){
    for (const auto &token : item){
        cout << token << endl;
    }
}

/*  This function takes in map to be searched and the query according to which will search.
    It returns a set of hits of urls it had upon searching for the user inputed query.
    This func uses the cleanToken function on the input that it takes before putting it 
    inside the buffer of the string stream. It then reads every thing out of the string stream
    till the first white space ensuring that only one word is read at one time. It puts that 
    word into a token. It then takes that token and cleans it using the cleanToken func and cleans
    the token of any unwanted chars and then finally stores it as the query that is to be queried.
    The func then check if the first char in the query is a '+' or a '-' indicating how the query
    should be interpreted either an intersection, a difference or if both are not present the union.
    It then returns the set of url hits in accordance to the query.

*/
set<string> findQueryMatches(map<string, set<string> >& index, string sentence) {
    set<string> result;
    string token;
    stringstream inSS(cleanToken(sentence));
   
    while(inSS >> token){
        
        if (token[0] == '+'){
            string query = cleanToken(token);
            set<string> temp;
            set_intersection(index[query].begin(), index[query].end(), result.begin(), result.end(),inserter(temp, temp.begin()));
            result = temp;
        }
        else if (token[0] == '-'){
            string query = cleanToken(token);
            set<string> temp;
            set_difference(result.begin(), result.end(),index[query].begin(), index[query].end(),inserter(temp, temp.begin()));
            result = temp;
        }
        else{
            string query = cleanToken(token);
            set<string> temp;
            set_union(index[query].begin(), index[query].end(), result.begin(), result.end(),inserter(temp, temp.begin()));
            result = temp;
        }
    }
    
    return result;
}

// This function puts together all of the funcs above to output the query matches.

void searchEngine(string filename) {
    set<string> match;
    map<string, set<string> > searchIndex;
    string query;
    int pages = buildIndex(filename, searchIndex);
    

    cout << "Stand by while building index..." << endl;

    cout << "Indexed " << pages << " pages containing " << searchIndex.size()
    << " unique terms" << endl << endl;

    do{
        
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, query);

        if (query == "") {cout << "Thank you for searching!" << endl; continue;}

        match = findQueryMatches(searchIndex, query);
        cout << "Found " << match.size() << " matching pages" << endl;
        printSet(match);
        cout << endl;
    }
    while(query != "");
}

