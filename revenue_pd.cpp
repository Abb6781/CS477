#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream infile("revenue_pc_out.txt");
    ofstream outfile("revenue_pd_out.txt");

    if (!infile.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    if (!outfile.is_open()) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    string line;
    vector<string> plan;
    bool readingPlan = false;

    while (getline(infile, line)) {
        if (line.find("Plan") != string::npos) {
            readingPlan = true;
            continue;
        }

        if (readingPlan && !line.empty()) {
            size_t lastComma = line.rfind(',');
            if (lastComma != string::npos && lastComma + 1 < line.length()) {
                string decision = line.substr(lastComma + 1);
                plan.push_back(decision);
            }
        }
    }

    infile.close();

    for (size_t i = 0; i < plan.size(); ++i) {
        outfile << "Day " << i + 1 << ": " << plan[i] << endl;
    }

    outfile.close();
    return 0;
}
