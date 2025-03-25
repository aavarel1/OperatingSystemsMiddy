#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void executeSequential(int count) {
    for (int i = 0; i < count; ++i) {
        cout << "hello world" << endl;
    }
}

void executeParallel(int count) {
    vector<pid_t> pids;
    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            cout << "hello world" << endl;
            exit(0); // Child process exits after printing
        } else if (pid > 0) {
            pids.push_back(pid); // Store child PID for waiting
        } else {
            cerr << "Fork failed!" << endl;
            exit(1);
        }
    }

    for (pid_t pid : pids) {
        waitpid(pid, nullptr, 0); // Parent waits for all child processes
    }
}

int main() {
    int count;
    char mode;
    
    cout << "Enter the command to run: ./q6fork" << endl;
    cout << "count> ";
    cin >> count;

    if (count < 1 || count > 9) {
        cerr << "Invalid count. Please enter a number between 1 and 9." << endl;
        return 1;
    }

    cout << "[p]arallel or [s]equential> ";
    cin >> mode;

    if (mode == 'p') {
        executeParallel(count);
    } else if (mode == 's') {
        executeSequential(count);
    } else {
        cerr << "Invalid option. Please choose 'p' for parallel or 's' for sequential." << endl;
        return 1;
    }

    cout << "closh>" << endl;
    return 0;
}

