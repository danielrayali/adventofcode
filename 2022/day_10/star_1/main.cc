#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// AI generated!
vector<string> SplitString(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

class CPU {
public:
    CPU() { this->Reset(); }

    ~CPU() = default;

    void Reset() {
        register_ = 1;
        cycle_count_ = 1;
        current_command_cycle_ = 0;
        current_command_.clear();
    }

    void SetProgram(istream* program) {
        program_ = program;
    }

    int GetRegister() const {
        return register_;
    }

    // This will stop the CPU before the specified cycle has completed.
    //
    //   Cpu cpu;
    //   cpu.SetProgram(program);
    //   cpu.CycleUtil(200);
    //   cout << cpu.GetCycleCount() << endl;
    // 
    // Will print "200" and will stop before the 200th cycle completes.
    void CycleUntil(const int cycle) {
        while (cycle_count_ < cycle) {
            this->CycleOnce();
        }
    }

    // This returns the current cycle number (starting at 1) that is about to be executed
    int GetCycleCount() const {
        return cycle_count_;
    }

private:
    int register_ = 1;
    istream* program_ = nullptr;
    string current_command_;
    int current_command_cycle_ = 0;
    int cycle_count_ = 1;

    void ProcessAddx() {
        if (current_command_cycle_ == 0) {
            current_command_cycle_++;
            return;
        }

        if (current_command_cycle_ == 1) {
            vector<string> split_command = SplitString(current_command_, ' ');
            if (split_command.size() != 2) {
                throw runtime_error("Invalid command detected");
            }

            register_ += atoi(split_command[1].c_str());
            current_command_cycle_ = 0;
            current_command_.clear();
        }
    }

    void CycleOnce() {
        if (current_command_cycle_ == 0) {
            getline(*program_, current_command_);
        }

        if (current_command_ == "noop") {
            current_command_.clear();
            current_command_cycle_ = 0;
        } else if (current_command_.starts_with("addx")) {
            this->ProcessAddx();
        } else {
            throw runtime_error("Invalid instruction detected");
        }

        cycle_count_++;
    }
};


int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    CPU cpu;
    cpu.SetProgram(&input);

    int signal_strength = 0;
    const vector<int> cycle_counts = { 20, 60, 100, 140, 180, 220 };
    for (auto count : cycle_counts) {
        cpu.CycleUntil(count);
        signal_strength += count * cpu.GetRegister();
    }

    cout << "The total signal strength is: " << signal_strength << endl;
    
    return 0;
}