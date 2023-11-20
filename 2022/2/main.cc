#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int GetOutcomeScore(const char opponent, const char you) {
    static const map<char,char> kWinMap = {
        {'A', 'Y'},
        {'B', 'Z'},
        {'C', 'X'}
    };

    static const map<char,char> kDrawMap = {
        {'A', 'X'},
        {'B', 'Y'},
        {'C', 'Z'}
    };

    if (opponent != 'A' && opponent != 'B' && opponent != 'C') {
        throw runtime_error("Opponent played " + string(&opponent) + ", which is not valid");
    }

    if (you == kDrawMap.at(opponent)) {
        return 3;
    }

    if (you == kWinMap.at(opponent)) {
        return 6;
    }

    return 0;
}

inline int GetPlayersScore(const char you) {
    switch (you) {
    case 'X': return 1;
    case 'Y': return 2;
    case 'Z': return 3;
    default:
        throw runtime_error("Player cannot play " + string(&you));
    }
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
        score += GetOutcomeScore(line[0], line[2]);
        score += GetPlayersScore(line[2]);
    }

    cout << "Total score: " << score << endl;

    return 0;
}
