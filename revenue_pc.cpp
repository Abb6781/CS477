#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

enum Decision { NONE, REPAIR, CONSTRUCTION };

void computeOptimalRevenueWithPlan(const vector<int>& r, const vector<int>& c, string outputFile) {
    int n = r.size();
    vector<int> OPT(n + 1, 0);
    vector<Decision> choice(n + 1, NONE);

    ofstream out(outputFile);
    out << "Day,OPT Value,Choice\n";

    OPT[0] = 0;
    out << "0," << OPT[0] << ",None\n";

    if (n >= 1) {
        OPT[1] = max({0, r[0], c[0]});
        if (OPT[1] == r[0]) choice[1] = REPAIR;
        else if (OPT[1] == c[0]) choice[1] = CONSTRUCTION;
        out << "1," << OPT[1] << "," << (choice[1] == REPAIR ? "Repair" : choice[1] == CONSTRUCTION ? "Construction" : "None") << "\n";
    }

    for (int i = 2; i <= n; ++i) {
        int doNothing = OPT[i - 1];
        int doRepair = r[i - 1] + OPT[i - 1];
        int doConstruction = c[i - 1] + OPT[i - 2];
        OPT[i] = max({doNothing, doRepair, doConstruction});
        if (OPT[i] == doRepair) choice[i] = REPAIR;
        else if (OPT[i] == doConstruction) choice[i] = CONSTRUCTION;
        else choice[i] = NONE;
        out << i << "," << OPT[i] << "," << (choice[i] == REPAIR ? "Repair" : choice[i] == CONSTRUCTION ? "Construction" : "None") << "\n";
    }

    out << "Final," << OPT[n] << ",\n";
    out << "Plan,,\n";

    vector<string> plan(n + 1, "None");
    for (int i = n; i >= 1;) {
        if (choice[i] == REPAIR) {
            plan[i] = "Repair";
            i -= 1;
        } else if (choice[i] == CONSTRUCTION) {
            plan[i] = "Construction";
            plan[i - 1] = "Prep";
            i -= 2;
        } else {
            i -= 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        out << i << ",," << plan[i] << "\n";
    }

    out.close();
    cout << "Maximum total revenue: " << OPT[n] << endl;
}

int main() {
    vector<int> r = {1000, 100, 1000, 1000};
    vector<int> c = {500, 5000, 500, 100};
    computeOptimalRevenueWithPlan(r, c, "revenue_pc_out.txt");
    return 0;
}
