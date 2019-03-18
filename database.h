#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <list>

using namespace std;

struct Node{
    char ch; 
    bool inBlackList;
    bool canAsk;
    vector<string> word;
    list<Node*> children;
    Node(){ word.clear(); inBlackList = false; canAsk = true;}
    Node(char c){ ch = c; word.clear(); inBlackList = false; canAsk = true;}
};

class Database{
public:
    Node* root;
    Database();
    void start();
    void importDatabase();
    void addToTree(string str, string sorted, Node* iter, int letterPos);
    void traverse(Node* iter);
    void pickRandom(Node* iter);
    void calculateLetterValues();
    void simplifyTree(Node* iter);
    void setPossibleLetters(int score, int pos, string newStr);
    void setBlacklist();
    void setExactLetters();
    void printAllStr();
    bool isContain(string str, char ch);
private:
    wchar_t alphabet[23];

    string randomPick;
    string randomPickSorted; 
    vector<int> values;
    vector<string> possibleLetters;
    vector<char> exactLetters;
    vector<char> blackListLetters;
};