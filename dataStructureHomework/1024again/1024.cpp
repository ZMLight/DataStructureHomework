#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
 
using namespace std;
 
void printError() {
    cout << "Error!" << endl;
}
 
void list(int i, int j, const vector<string> &text) {
    if (i <= j && i >= 1 && j <= text.size()) {
        for (int k = i - 1; k <= j - 1; ++k) {
            cout << text[k] << endl;
        }
    } else {
        printError();
    }
}
 
void ins(int i, int j, string str, vector<string> &text) {
    if (i >= 1 && i <= text.size() && j >= 1 && j <= text[i - 1].size() + 1) {
        text[i - 1].insert(j - 1, str);
    } else {
        printError();
    }
}
 
void del(int i, int j, int num, vector<string> &text) {
    if (i >= 1 && i <= text.size() && j >= 1 && j <= text[i - 1].size() && num >= 0 && j + num - 1 <= text[i - 1].size()) {
        text[i - 1].erase(j - 1, num);
    } else {
        printError();
    }
}
 
int main()
{
    vector <string> text;
    string input, str;
    int i, j, num;
    while (getline(cin, input)) {
        if (input == "******") {
            break;
        } else {
            text.push_back(input);
        }
    }
    while (cin >> input) {
        if (input == "list") {
            cin >> i >> j;
            list(i, j, text);
        } else if (input == "ins") {
            cin >> i >> j;
            getchar();
            getline(cin, str);
            ins(i, j, str, text);
        } else if (input == "del") {
            cin >> i >> j >> num;
            del(i, j, num, text);
        } else {
            list(1, text.size(), text);
            break;
        }
    }
    return 0;
}