// Isha Gupta
// April 24, 2025
// Banker's Algorithm to check if a system is in a safe state

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 

using namespace std;

void getData(const string &filename, vector<vector<int>> &alloc, vector<vector<int>> &maxNeed, vector<int> &available) {
    ifstream in(filename);
    if (!in) {
        cerr << "Failed to open " << filename << endl;
        exit(1);
    }

    string line;
    int section = 0;
    while (getline(in, line)) {
        if (line.find("Allocation:") != string::npos) {
            section = 1;
            continue;
        } else if (line.find("Max:") != string::npos) {
            section = 2;
            continue;
        } else if (line.find("Available:") != string::npos) {
            section = 3;
            continue;
        }

        if (line.empty()) continue;

        vector<int> row;
        size_t pos = line.find(":");
        string nums = (pos != string::npos) ? line.substr(pos + 1) : line;

        stringstream ss(nums);
        int num;
        while (ss >> num) {
            row.push_back(num);
            if (ss.peek() == ',' || ss.peek() == ' ') ss.ignore();
        }

        if (section == 1) {
            alloc.push_back(row);
        } else if (section == 2) {
            maxNeed.push_back(row);
        } else if (section == 3) {
            available = row;
        }
    }
}

bool isSafe(vector<vector<int>> &alloc, vector<vector<int>> &maxNeed, vector<int> available, vector<int> &safeSeq) {
    int n = alloc.size();
    int m = available.size();

    vector<vector<int>> need(n, vector<int>(m));
    vector<bool> finished(n, false);
    safeSeq.clear();

    // Calculating the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - alloc[i][j];
            if (need[i][j] < 0) {
                cerr << "Error: Allocation exceeds maximum need for process P" << i << " and resource R" << j << endl;
                exit(1);
            }
        }
    }

    //Printing the need matrix (for debugging purposes)
    cout << "Need Matrix:\n";
    for (const auto &row : need) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    // Banker's Algorithm
    int finishedCount = 0; // Tracking the number of finished processes
    while (finishedCount < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finished[p]) {
                bool canAllocate = true;
                for (int r = 0; r < m; r++) {
                    if (need[p][r] > available[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    //Printing process execution (for debugging purposes)
                    cout << "Process P" << p << " can be safely executed.\n";

                    for (int r = 0; r < m; r++)
                        available[r] += alloc[p][r];
                    safeSeq.push_back(p);
                    finished[p] = true;
                    finishedCount++;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No safe process found in this iteration.\n";
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> alloc, maxNeed;
    vector<int> available, safeSeq;
    string filename;

    cout << "Enter the input filename: ";
    getline(cin, filename);

    getData(filename, alloc, maxNeed, available);

    //Printing different matrices (for debugging purposes)
    cout << "Allocation Matrix:\n";
    for (const auto &row : alloc) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Max Need Matrix:\n";
    for (const auto &row : maxNeed) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Available Resources:\n";
    for (int val : available) cout << val << " ";
    cout << endl;

    if (isSafe(alloc, maxNeed, available, safeSeq)) {
        cout << "System is in a safe state.\nSafe sequence is:\n";
        for (size_t i = 0; i < safeSeq.size(); i++) {
            cout << "P" << safeSeq[i];
            if (i != safeSeq.size() - 1) cout << " → ";
        }
        cout << endl;
    } else {
        cout << "System is in an unsafe state.\n";
    }

    return 0;
}
