#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// int GetOutcomeScore(const char opponent, const char you) {
//     static const map<char,char> kWinMap = {
//         {'A', 'Y'},
//         {'B', 'Z'},
//         {'C', 'X'}
//     };

//     static const map<char,char> kDrawMap = {
//         {'A', 'X'},
//         {'B', 'Y'},
//         {'C', 'Z'}
//     };

//     if (opponent != 'A' && opponent != 'B' && opponent != 'C') {
//         throw runtime_error("Opponent played " + string(&opponent) + ", which is not valid");
//     }

//     if (you == kDrawMap.at(opponent)) {
//         return 3;
//     }

//     if (you == kWinMap.at(opponent)) {
//         return 6;
//     }

//     return 0;
// }

// inline int GetPlayersScore(const char you) {
//     switch (you) {
//     case 'X': return 1;
//     case 'Y': return 2;
//     case 'Z': return 3;
//     default:
//         throw runtime_error("Player cannot play " + string(&you));
//     }
// }

int GetOutcomeScore(const char opponent, const char outcome) {
    if (opponent != 'A' && opponent != 'B' && opponent != 'C') {
        throw runtime_error("Opponent cannot choose " + string(&opponent));
    }

    if (outcome != 'X' && outcome != 'Y' && outcome != 'Z') {
        throw runtime_error("Outcome cannot be " + string(&outcome));
    }

    // A -> Opponent chooses Rock
    // B -> Opponent chooses Paper
    // C -> Opponent chooses Scissors
    // Lose X -> 0
    // Draw Y -> 3
    // Win Z -> 6
    // You choosing Rock -> 1
    //   Situations: BX, AY, CZ
    // You choosing Paper -> 2
    //   Situations: CX, BY, AZ
    // You choosing Scissors -> 3
    //   Situations: AX, CY, BZ
    const string input = string(&opponent) + string(&outcome);
    static const map<string, int> kOutcomeScoreMap = {
        { "AX", 3 + 0 },
        { "AY", 1 + 3 },
        { "AZ", 2 + 6 },
        { "BX", 1 + 0 },
        { "BY", 2 + 3 },
        { "BZ", 3 + 6 },
        { "CX", 2 + 0 },
        { "CY", 3 + 3 },
        { "CZ", 1 + 6 }
    };
    return kOutcomeScoreMap.at(input);
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    int score = 0;
    while (getline(input, line)) {
        // score += GetOutcomeScore(line[0], line[2]);
        // score += GetPlayersScore(line[2]);
        score += GetOutcomeScore(line[0], line[2]);
    }

    cout << "Total score: " << score << endl;

    return 0;
}
