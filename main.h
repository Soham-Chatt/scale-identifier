#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set> // For userNotes to handle duplicate note input from the user
#include <limits> // For numeric limits
// Uncomment the 2 lines below if you are using windows
//#include <windows.h>
//#undef max
#include <algorithm> // For find() and sort()
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

    // Map of all major scales and their respective chords
    map<string, vector<string>> chords = {
            {"C Major",  {"C",  "Dm",  "Em",   "F",  "G",  "Am",   "Bdim"}},
            {"G Major",  {"G",  "Am",  "Bm",   "C",  "D",  "Em",   "F#dim"}},
            {"D Major",  {"D",  "E",  "F#m",  "G",  "A",  "Bm",   "C#dim"}},
            {"A Major",  {"A",  "Bm",  "C#m",  "D",  "E",  "F#m",  "G#dim"}},
            {"E Major",  {"E",  "F#m", "G#m",  "A",  "B",  "C#m",  "D#dim"}},
            {"B Major",  {"B",  "C#m", "D#m",  "E",  "F#", "G#m",  "A#dim"}},
            {"F# Major", {"F#", "G#m", "A##",  "B",  "C#", "D#m",  "E#dim"}},
            {"C# Major", {"C#", "D#m", "E#",  "F#", "G#", "A#",  "B#dim"}},
            {"F Major",  {"F",  "G",  "A",   "Bb", "C",  "Dm",   "Edim"}},
            {"Bb Major", {"Bb", "Cm",  "Dm",   "Eb", "F",  "G",   "Adim"}},
            {"Eb Major", {"Eb", "Fm",  "Gm",   "Ab", "Bb", "Cm",   "Ddim"}},
            {"Ab Major", {"Ab", "Bb", "Cm",   "Db", "Eb", "Fm",   "Gdim"}},
            {"Db Major", {"Db", "Eb", "F",   "Gb", "Ab", "Bbm",  "Cdim"}},
            {"Gb Major", {"Gb", "Abm", "Bbm",  "Cb", "Db", "Ebm",  "Fdim"}},
            {"Cb Major", {"Cb", "Db", "Eb",  "Fb", "Gb", "Ab",  "Bbdim"}}};

    void showChords(int choice);
};