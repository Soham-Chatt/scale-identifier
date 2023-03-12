#include "main.h"
using namespace std;

void key::info() {
    cout << "Welcome. This program is designed to determine which scale the notes you input are played in. \n"
            "Currently it can only check the heptatonic (common) major scales in standard notation form.\n"
            "Sharps are denoted with \033[1m#\033[0m and flats are denoted with \033[1mb\033[0m (e.g. F# and Bb).\n"
            "Put a space in between each note. \n"
            "\nEnter your notes:" << endl;
} // info

void key::readyInput() {
    bool validInput = false;
    while (!validInput) {
        validInput = true;
        // Prompt the user to input userNotes
        string input;
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize input by space
        stringstream ss(input);
        string token;
        while (ss >> token) {
            char note = token[0];
            char modifier = token[1];
            // Check if the token (note) is valid
            if (token.length() == 2 && (note >= 'A' && note <= 'G' && (modifier == '#' || modifier == 'b'))) {
                validInput = true;
            } else if (token.length() == 1 && (note >= 'A' && note <= 'G')) {
                validInput = true;
            } else {
                validInput = false;
                cout << "You have inputted one or more non-existent note(s). Please try again. "
                        "Don't forget the spaces in between each note." << endl;
                break;
            }//else

            // All checks passed
            userNotes.insert(token);
        }//while
    }//while
} // readyInput

void key::findMatches() {
    // Count the number of matching userNotes for each scale
    map<string, int> scaleMatches;
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
} // findMatches

void key::showMatches() {
    // Otherwise return the closest matches
    cout << "No perfect match found. The three best matches are:" << endl;
    for (int i = 0; i < min(3, (int)sortedScales.size()); i++) {
        // Show scale and how many matches
        cout << sortedScales[i].first << " (" << sortedScales[i].second << "/7)" << endl;

        // Check which notes in the top 3 scales match the user input notes
        vector<string> scaleNotes = scales[sortedScales[i].first];
        for (auto & scaleNote : scaleNotes) {
            bool isMatch = false;
            for (auto& userNote : userNotes) {
                if (scaleNote == userNote) {
                    isMatch = true;
                    break;
                }//if
            }//for userNote
            if (isMatch) {
                cout << "\033[1m\033[32m" << scaleNote << "\033[0m ";
            } else {
                cout << scaleNote << " ";
            }//else
        }//for scaleNote
        cout << endl << endl;
    }//for i
} // showMatches

int main() {
    key k;
    k.info(); // Info concerning the program

    while(true) {
        k.readyInput(); // Prepare user input
        k.findMatches(); // Find the matches in the scales

        // Check if we have a perfect match
        for (auto &i: k.sortedScales) {
            if (i.second == 7) {
                cout << "We have a perfect match. The scale is: " << "\033[1m\033[32m" << i.first << "\033[0m " << endl;
                return 0;
            }//if
        }//for i

        k.showMatches(); // For imperfect matches we show more information

        // Prompt the user to try again or exit
        cout << "Do you want to try again? (y/n)" << endl;
        char answer;
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the input stream
        if (answer != 'y' && answer != 'Y') {
            break;
        }//if

        cout << "Enter the notes:" << endl;
        k.userNotes.clear(); // Reset user input
    }//while
    return 0;
} // main