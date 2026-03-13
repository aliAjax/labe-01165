
#include <iostream>
#include <string>
using namespace std;

int main() {
    string sep = "╠════════════╦═══════════════╬═══════════════╬═══════════════╣";
    string top = "╔════════════════════════════════════════════════════════════╗";
    
    cout << "sep: " << sep << "  length: " << sep.size() << endl;
    cout << "top: " << top << "  length: " << top.size() << endl;
    
    // 计算每个字符的字节数
    cout << "
sep chars (bytes):" << endl;
    for (char c : sep) {
        cout << hex << (0xFF & (unsigned char)c) << " ";
    }
    cout << endl;
    
    return 0;
}

