#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void execute_sequentially(const string& command, int count) {
    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            cerr << "Fork failed!" << endl;
            return;
        }

        if (pid == 0) {
            vector<char*> args;
            size_t pos = 0;
            string token;
            string cmd = command;
            while ((pos = cmd.find(" ")) != string::npos) {
                token = cmd.substr(0, pos);
                args.push_back(const_cast<char*>(token.c_str()));
                cmd.erase(0, pos + 1);
            }
            args.push_back(const_cast<char*>(cmd.c_str())); // Add the last argument
            args.push_back(nullptr); // Null-terminate the array

            // Debug: Print the command and arguments
            cout << "Executing: " << args[0] << endl;

            execvp(args[0], args.data());
            cerr << "Error executing command: " << command << endl;
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}

void execute_concurrently(const string& command, int count) {
    vector<pid_t> pids;

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            cerr << "Fork failed!" << endl;
            return;
        }

        if (pid == 0) {
            vector<char*> args;
            size_t pos = 0;
            string token;
            string cmd = command;
            while ((pos = cmd.find(" ")) != string::npos) {
                token = cmd.substr(0, pos);
                args.push_back(const_cast<char*>(token.c_str()));
                cmd.erase(0, pos + 1);
            }
            args.push_back(const_cast<char*>(cmd.c_str())); // Add the last argument
            args.push_back(nullptr); // Null-terminate the array

            // Debug: Print the command and arguments
            cout << "Executing: " << args[0] << endl;

            execvp(args[0], args.data());
            cerr << "Error executing command: " << command << endl;
            exit(1);
        } else {
            pids.push_back(pid);
        }
    }

    for (pid_t pid : pids) {
        waitpid(pid, NULL, 0);
    }
}

int main() {
    string command;
    int count;
    char mode;

    cout << "closh>" << endl;
    cout << "Enter the command to run: ";
    getline(cin, command);

    cout << "count> ";
    cin >> count;

    if (count < 1 || count > 9) {
        cerr << "Invalid count. Please enter a number between 1 and 9." << endl;
        return 1;
    }

    cout << "[p]arallel or [s]equential> ";
    cin >> mode;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (mode != 'p' && mode != 's') {
        cerr << "Invalid mode. Please choose 'p' for parallel or 's' for sequential." << endl;
        return 1;
    }

    if (mode == 's') {
        execute_sequentially(command, count);
    } else if (mode == 'p') {
        execute_concurrently(command, count);
    }

    cout << "closh>" << endl;

    return 0;
}

