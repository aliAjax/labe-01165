
#include <iostream>
#include <string>
using namespace std;
int main() {
    string sep = "╠════════════╦═══════════════╬═══════════════╬═══════════════╣";
    cout << sep << endl;
    string top = "╔";
    for (int i = 0; i < 60; i++) top += "═";
    top += "╗";
    cout << top << endl;
    return 0;
}

