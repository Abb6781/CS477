#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void computeOptimalRevenue(const vector<int>& r, const vector<int>& c, string outputFile) {
    int n = r.size();
    vector<int> OPT(n + 1, 0);

    ofstream out(outputFile);
    out << "Day,OPT Value\n";

    OPT[0] = 0;
    out << "0," << OPT[0] << "\n";

    if (n >= 1) {
        OPT[1] = max({0, r[0], c[0]});
        out << "1," << OPT[1] << "\n";
    }

    for (int i = 2; i <= n; ++i) {
        int doNothing = OPT[i - 1];
        int doRepair = r[i - 1] + OPT[i - 1];
        int doConstruction = c[i - 1] + OPT[i - 2];

        OPT[i] = max({doNothing, doRepair, doConstruction});
        out << i << "," << OPT[i] << "\n";
    }

    cout << "Maximum total revenue: " << OPT[n] << endl;
    out << "Final, " << OPT[n] << "\n";

    out.close();
}

int main() {
    vector<int> r = {1000,100,1000,1000};
    vector<int> c = {500,5000,500,100};   

    computeOptimalRevenue(r, c, "revenue_pb_out.txt");

    return 0;
}

