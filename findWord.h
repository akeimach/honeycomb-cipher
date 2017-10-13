#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
// by Alyssa Keimach

#include <cmath>
using namespace std;

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')
#define INDEX_TO_CHAR(i) ((int)'A' + (int)i)


struct coords {
    int r, theta;
    coords() : r(-1), theta(-1) {}
    coords(int r, int theta) : r(r), theta(theta) {}
    coords setCoords(int rUpdate, int thetaUpdate) {
        r = rUpdate;
        theta = thetaUpdate;
        return coords(r, theta);
    }
};


struct TrieNode {
	TrieNode *children[ALPHABET_SIZE];
    coords nodeCoords;
	bool isLeaf; // isLeaf is true if the node is end of a word
    TrieNode() : isLeaf(true) {}
};


TrieNode *newNode(void);


struct findWord {
    int totalLayers;
    vector<char> outputWords;
    vector<vector<char> > letterVector;
    vector<coords> deadEnd;
    vector<coords> validCoords;
    bool runCipher(vector<char> word, int level);
    coords findFirstPosition(char currLetter);
    coords findValidPosition(coords prevCoords, char currLetter);
    coords setValidPosition(char currLetter, int r, int theta);
    bool checkHistory(coords tryCoords);
    void insert(TrieNode *root, vector<char> word);
    int preSearch(TrieNode *root, vector<char> word);
    void lexicographicalPrint(TrieNode *node);
};




