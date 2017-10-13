// by Alyssa Keimach

#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define ALPHABET_SIZE (26)


struct xyCoords {
    char letter;
    double x, y;
    int r, theta;
    xyCoords() : letter(0), x(0), y(0), r(-1), theta(-1) {}
    bool operator < (const xyCoords& inCoord) const {
        if (abs(y - inCoord.y) < 0.005) { return x < inCoord.x; }
        return (y > inCoord.y);
    }
};

struct gridOperations {
    vector<xyCoords> xyVec;
    vector<vector<char> > words;
    vector<vector<char> > letters;
    int size;
    string honeyIn;
    string honeyOut;
    string dictIn;
    void createHoneycombInput();
    void convertPolarToCartesian();
    void printHoneycombStdout();
    void printHoneycombFile();
    void loadDictionary();
    void inventDictionary();
};


