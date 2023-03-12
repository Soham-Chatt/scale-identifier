#ifndef KEYFINDER_MAIN_H
#define KEYFINDER_MAIN_H

#endif //KEYFINDER_MAIN_H


#include <iostream>
#include <vector>
#include <set> // For userNotes to handle duplicate note input from the user
#include <map>
#include <string>
#include <algorithm> // For transform(), find() and sort()
#include <sstream> // For preparing user input
using namespace std;

class key {
public:
    static void info(); // Welcome and instructions
    void readyInput(); // Readies the user input
    void findMatches(); // Finds the matches in the scales
    void showMatches(); // Prints the output with some additional information for imperfect match case

    set<string> userNotes; // Notes inputted by the user
    vector<pair<string,int>> sortedScales; // Scales sorted by the number of matches (descending)
    // Map of all major scales and their respective notes
    map<string, vector<string>> scales = {
            {"C Major",  {"C",  "D",  "E",   "F",  "G",  "A",   "B"}},
            {"G Major",  {"G",  "A",  "B",   "C",  "D",  "E",   "F#"}},
            {"D Major",  {"D",  "E",  "F#",  "G",  "A",  "B",   "C#"}},
            {"A Major",  {"A",  "B",  "C#",  "D",  "E",  "F#",  "G#"}},
            {"E Major",  {"E",  "F#", "G#",  "A",  "B",  "C#",  "D#"}},
            {"B Major",  {"B",  "C#", "D#",  "E",  "F#", "G#",  "A#"}},
            {"F# Major", {"F#", "G#", "A#",  "B",  "C#", "D#",  "E#"}},
            {"C# Major", {"C#", "D#", "E#",  "F#", "G#", "A#",  "B#"}},
            {"F Major",  {"F",  "G",  "A",   "Bb", "C",  "D",   "E"}},
            {"Bb Major", {"Bb", "C",  "D",   "Eb", "F",  "G",   "A"}},
            {"Eb Major", {"Eb", "F",  "G",   "Ab", "Bb", "C",   "D"}},
            {"Ab Major", {"Ab", "Bb", "C",   "Db", "Eb", "F",   "G"}},
            {"Db Major", {"Db", "Eb", "F",   "Gb", "Ab", "Bb",  "C"}},
            {"Gb Major", {"Gb", "Ab", "Bb",  "Cb", "Db", "Eb",  "F"}},
            {"Cb Major", {"Cb", "Db", "Eb",  "Fb", "Gb", "Ab",  "Bb"}}};
};