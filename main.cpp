#include <limits>
#include "main.h"
using namespace std;

void key::info() {
    cout << "Welcome. This program is designed to determine which scale the notes you input are played in. \n"
            "Currently it can only check the heptatonic (common) major scales in standard notation form.\n"
            "Sharps are denoted with \033[1m#\033[0m and flats are denoted with \033[1mb\033[0m (e.g. F# and Bb).\n"
            "Put a space in between each note and mind capitalization. \n"
            "\nEnter your notes:" << endl;
} // info

void key::readyInput() {
    bool validInput = false;
    while (!validInput) {
        validInput = true;
        // Prompt the user to input userNotes
        string input;
        getline(cin, input);

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
                        "Don't forget the spaces in between each note and use proper capitalization." << endl;
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

void key::showChords(int choice) {
    choice--;
    cout << "Chords in " << get<0>(sortedScales[choice]) << ": ";
    // Search for chord in chords and print out all chords
    for (auto& i : chords) {
        if (i.first == get<0>(sortedScales[choice])) {
            vector<string> onlyChords = chords[i.first];
            for (auto &j : onlyChords) {
                cout << j << " ";
            }//for j
        }//if
    }//for i
    cout << endl << endl;
} // showChords

void key::showMatches() {
    // Check if we have a perfect match
    bool perfect = false;
    for (auto &i: sortedScales) {
        if (i.second == 7) {
            cout << "We have a perfect match. The scale is: " << "\033[1m\033[32m" << i.first << "\033[0m " << endl;
            perfect = true;

            cout << endl << "Would you like to see the chords of this scale? (y/n)" << endl;
            char answer;
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (answer != 'y' && answer != 'Y') {
                break;
            } else {
                showChords(1);
            }//else
        }//if
    }//for i
    if (!perfect) {
        // Otherwise return the closest matches
        cout << "No perfect match found. The three best matches are:" << endl;
        for (int i = 0; i < min(3, (int) sortedScales.size()); i++) {
            // Show scale and how many matches
            cout << sortedScales[i].first << " (" << sortedScales[i].second << "/7)" << endl;

            // Check which notes in the top 3 scales match the user input notes
            vector<string> scaleNotes = scales[sortedScales[i].first];
            for (auto &scaleNote: scaleNotes) {
                bool isMatch = false;
                for (auto &userNote: userNotes) {
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

        cout << endl << "Would you like to see the chords for one of the scales? (y/n)" << endl;
        char answer;
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (answer == 'y' || answer == 'Y') {
            cout << endl << "Choose one of the top three scales. (1/2/3)" << endl;
            int choice;
            cin >> choice;
            showChords(choice);
        }//if
    }//if
} // showMatches

int main() {
    // Enables coloured and stylized text for Windows (uncomment if on Windows)
//    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    DWORD dwMode = 0;
//    GetConsoleMode(hOut, &dwMode);
//    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    key k;
    k.info(); // Info concerning the program

    while(true) {
        k.readyInput(); // Prepare user input
        k.findMatches(); // Find the matches in the scales

        k.showMatches(); // For imperfect matches we show more information

        // Prompt the user to try again or exit
        cout << endl << "Do you want to try inputting new notes? (y/n)" << endl;
        char answer;
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the input stream
        if (answer != 'y' && answer != 'Y') {
            break;
        }//if

        cout << endl << "Enter the notes:" << endl;
        k.userNotes.clear(); // Reset user input
    }//while
    return 0;
} // main
