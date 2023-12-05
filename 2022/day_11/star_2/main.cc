#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>

using namespace std;

// AI generated!
vector<string> SplitString(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != string::npos) {
        string token = str.substr(start, end - start);
        if (!token.empty()) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }
    string token = str.substr(start);
    if (!token.empty()) {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}

class Monkey {
public:
    Monkey(vector<Monkey>& monkeys, istream& input) : monkeys_(monkeys) { 
        this->ParseMonkeyConfiguration(input); 
    }

    ~Monkey() = default;

    void InspectItems() {
        while (!items_.empty()) {
            this->InspectFrontItem();
        }
    }

    void AddItem(const long long item) {
        items_.push_back(item);
    }

    list<long long> GetItems() const {
        return items_;
    }

    int GetItemsInspected() const {
        return items_inspected_;
    }

    void SetMaxModule(const int modulo) {
        modulo_ = modulo;
    }

    int GetDivTestParam() const {
        return divisibility_test_parameter_;
    }

private:
    vector<Monkey> &monkeys_;
    list<long long> items_;
    string op_lhs_;
    string op_rhs_;
    string op_op_;
    int divisibility_test_parameter_;
    int pass_monkey_ = -1;
    int fail_monkey_ = -1;
    int items_inspected_ = 0;
    int modulo_ = 0;

    void InspectFrontItem() {
        // Perform operation
        const long long item = items_.front();
        const long long lhs = (op_lhs_ == "old" ? item : atoi(op_lhs_.c_str()));
        const long long rhs = (op_rhs_ == "old" ? item : atoi(op_rhs_.c_str()));
        long long new_worry = 0;
        if (op_op_ == "*") {
            new_worry = lhs * rhs;
        } else {
            new_worry = lhs + rhs;
        }

        // New worry relief
        new_worry %= modulo_;

        const bool test_result = ((new_worry % divisibility_test_parameter_) == 0.0f);
        if (test_result) {
            monkeys_.at(pass_monkey_).AddItem(new_worry);
        } else {
            monkeys_.at(fail_monkey_).AddItem(new_worry);
        }

        items_.erase(items_.begin());
        items_inspected_++;
    }

    void ParseMonkeyConfiguration(istream& input) {
        // Parse starting items
        string line;
        getline(input, line);
        vector<string> tokens = SplitString(line, ' ');
        for (int i = 2; i < tokens.size()-1; ++i) {
            items_.push_back(atoi(tokens[i].substr(0, tokens[i].size()-1).c_str()));
        }
        items_.push_back(atoi(tokens.back().c_str()));

        // Parse operation
        getline(input, line);
        tokens = SplitString(line, ' ');
        op_lhs_ = tokens[3];
        op_rhs_ = tokens[5];
        op_op_ = tokens[4];

        // Parse test
        getline(input, line);
        tokens = SplitString(line, ' ');
        divisibility_test_parameter_ = atoi(tokens[3].c_str());

        // Parse true
        getline(input, line);
        tokens = SplitString(line, ' ');
        pass_monkey_ = atoi(tokens[5].c_str());

        // Parse false
        getline(input, line);
        tokens = SplitString(line, ' ');
        fail_monkey_ = atoi(tokens[5].c_str());
    }
};

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    getline(input, line);

    vector<Monkey> monkeys;
    monkeys.emplace_back(monkeys, input);

    while (getline(input, line)) {
        getline(input, line);
        monkeys.emplace_back(monkeys, input);
    }
    
    int modulo = 1;
    for (auto monkey : monkeys) {
        modulo *= monkey.GetDivTestParam();
    }

    for (auto& monkey : monkeys) {
        monkey.SetMaxModule(modulo);
    }

    const int rounds = 10000;
    for (int i = 0; i < rounds; ++i) {
        for (int j = 0; j < monkeys.size(); ++j) {
            monkeys.at(j).InspectItems();
        }
    }

    int count = 0;
    for (const auto& monkey : monkeys) {
        cout << "Monkey " << count++ << ": ";
        for (const auto& item : monkey.GetItems()) {
            cout << item << ", ";
        }
        cout << endl;
    }

    map<int, int> inspection_counts;
    count = 0;
    for (const auto& monkey : monkeys) {
        cout << "Monkey " << count << " inspected items " << monkey.GetItemsInspected() << " times." << endl;
        inspection_counts[monkey.GetItemsInspected()] = count;
        count++;
    }

    auto iter = inspection_counts.rbegin();
    long long top = iter->first;
    cout << "The top two monkey counts are Monkey " << iter->second;
    cout << " (" << iter->first << " inspections)";
    iter++;
    long long second = iter->first;
    cout << " and Monkey " << iter->second;
    cout << " (" << iter->first << " inspections)" << endl;
    cout << "The monkey business level is " << top * second << endl;

    return 0;
}