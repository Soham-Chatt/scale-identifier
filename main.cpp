#include "main.h"
using namespace std;


map<string,vector<string>> key::scaleDefinitions() {
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
    return scales;
}

void key::info() {
    cout << "Welcome. This program is designed to determine which key the userNotes you give are played in. \n"
            "Currently it can only check the heptatonic (common) major scales.\n"
            "Sharps are denoted with # (F#) and flats are denoted with b (Bb). Put a space between each note. \n"
            "Enter the notes:" << endl;
}

void key::readyInput() {
    // Prompt the user to input userNotes
    string input;
    getline(cin, input);
    transform(input.begin(), input.end(),input.begin(), ::toupper);

    // Tokenize input by space
    stringstream ss(input);
    string token;
    while (ss >> token) {
        userNotes.push_back(token);
    }
}

void key::findMatches() {
    // Count the number of matching userNotes for each scale
    map<string, int> scaleMatches;
    map<string, vector<string>> scales = scaleDefinitions();
    for (auto& scale : scales) {
        int matches = 0;
        for (auto& note : userNotes) {
            if (find(scale.second.begin(), scale.second.end(), note) != scale.second.end()) {
                matches++;
            }//if
        }//for note
        scaleMatches[scale.first] = matches;
    }//for scale

    // Sort scales by number of matching userNotes (descending)
    vector<pair<string, int>> temp(scaleMatches.begin(), scaleMatches.end());
    sortedScales = temp;
    sort(sortedScales.begin(), sortedScales.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
}

int main() {
    key k;
    k.info(); // Info concerning the program
    k.readyInput(); // Prepare user input
    k.findMatches(); // Find the matches in the scales

    // Check if we have a perfect match
    for (auto& i : k.sortedScales) {
        if (i.second == 7) {
            cout << "We have a perfect match. The scale is: " << i.first << endl;
            return 0;
        }//if
    }//for i

    // Otherwise return the closest matches
    cout << "We did not find a pefect match. The three best matches are:" << endl;
    for (int i = 0; i < min(3, (int)k.sortedScales.size()); i++) {
        cout << k.sortedScales[i].first << " (" << k.sortedScales[i].second << "/7)" << endl;
    }//for i
    return 1;
}
