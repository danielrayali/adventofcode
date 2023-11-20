#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>

using namespace std;

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

struct File {
    string name;
    size_t size;
};

struct Directory {
    Directory(const string& _name, Directory* _parent) : name(_name), parent(_parent) {}

    string name;
    Directory* parent = nullptr;
    vector<File> files;
    vector<Directory> directories;
    size_t total_size = 0;
};

class Shell {
public:
    const string kRootDir{ "/" };
    const string kParentDir{ ".." };

    Shell() : root_(kRootDir, nullptr), current_dir_ptr_(&root_) {}

    ~Shell() = default;

    void ProcessCommandAndOutput(const string& command_and_output) {
        if (command_and_output.substr(2, 2) == "cd") {
            this->ChangeDir(command_and_output.substr(5));
        } else if (command_and_output.substr(2, 2) == "ls") {
            this->List(command_and_output.substr(5));
        }
    }

    void ProcessEachDir(const function<void(Directory*)>& user_function) {
        this->ProcessEachDirHelper(&root_, user_function);
    }

private:
    Directory root_;
    Directory* current_dir_ptr_ = nullptr;

    void ProcessEachDirHelper(Directory* dir, const function<void(Directory*)>& user_function) {
        for (auto& child : dir->directories) {
            this->ProcessEachDirHelper(&child, user_function);
        }

        user_function(dir);
    }

    void ListDir(const string& name) {
        bool in_current_dir = false;
        for (const auto& child_dir : current_dir_ptr_->directories) {
            if (child_dir.name == name) {
                in_current_dir = true;
                break;
            }
        }

        if (!in_current_dir) {
            current_dir_ptr_->directories.emplace_back(name, current_dir_ptr_);
        }
    }

    void AddFile(const string& name, const size_t size) {
        current_dir_ptr_->files.emplace_back(name, size);
        current_dir_ptr_->total_size += size;
        Directory* parent = current_dir_ptr_->parent;
        while (parent != nullptr) {
            parent->total_size += size;
            parent = parent->parent;
        }
    }

    void ListFile(const string& size_and_file) {
        const vector<string> split = SplitString(size_and_file, ' ');
        const int size = atoi(split[0].c_str());
        const string name = split[1];

        bool in_current_dir = false;
        for (const auto& child_file : current_dir_ptr_->files) {
            if (child_file.name == name) {
                in_current_dir = true;
                break;
            }
        }

        if (!in_current_dir) {
            this->AddFile(name, size);
        }
    }

    void List(const string& output) {
        vector<string> files_and_dirs = SplitString(output, '\n');
        for (const auto& iter : files_and_dirs) {
            if (iter.substr(0, 3) == "dir") {
                this->ListDir(iter.substr(4));
            } else {
                this->ListFile(iter);
            }
        }
    }

    void ChangeDir(const string& new_dir) {
        if (new_dir == kRootDir) {
            current_dir_ptr_ = &root_;
            return;
        }

        if (new_dir == kParentDir) {
            if (current_dir_ptr_ != &root_) {
                current_dir_ptr_ = current_dir_ptr_->parent;
            }
            return;
        }

        for (auto& iter : current_dir_ptr_->directories) {
            if (iter.name == new_dir) {
                current_dir_ptr_ = &iter;
                break;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    Shell shell;
    string line;
    while (getline(input, line)) {
        stringstream command_and_output;
        command_and_output << line;
        if (line.starts_with("$")) {
            while (input.peek() != '$' && !input.eof()) {
                getline(input, line);
                command_and_output << "\n" << line;
            }

            // Read command output until we reach a new command
            shell.ProcessCommandAndOutput(command_and_output.str());
        }
    }

    size_t size = 0;
    shell.ProcessEachDir([&size](Directory* dir){
        if (dir->total_size <= 100000) {
            size += dir->total_size;
        }
    });

    cout << "Total size of all directories under 100000 bytes: " << size << endl;

    return 0;
}
