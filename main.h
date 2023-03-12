#ifndef KEYFINDER_MAIN_H
#define KEYFINDER_MAIN_H

#endif //KEYFINDER_MAIN_H


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class key {
public:
    map<string,vector<string>> scaleDefinitions(); // All major scales and their userNotes
    vector<string> userNotes; // Notes inputted by the user
    vector<pair<string,int>> sortedScales; // Scales sorted by the number of matches (descending)

    static void info(); // Welcome and instructions
    void readyInput(); // Readies the user input
    void findMatches(); // Finds the matches in the scales
};