// by Alyssa Keimach

#include "findWord.h"



bool findWord::runCipher(vector<char> word, int level) {
    int i = level;
    while (i < ((int)word.size() - 1)) {
        coords tryCoords;
        if ((i == 0) || validCoords.empty()) {
            tryCoords = findFirstPosition(word[i]);
        }
        else {
            tryCoords = findValidPosition(validCoords.back(), word[i]);
        }
        if (tryCoords.r != -1) {
            validCoords.push_back(tryCoords);
            i++;
        }
        else {
            coords removeCoords;
            while ((removeCoords.r == -1) && (!validCoords.empty())) {
                removeCoords = validCoords.back();
                validCoords.pop_back();
            }
            deadEnd.push_back(removeCoords);
            i--;
            if (i < 0) {
                return false;
            }
        }
    }
    return true;
}



TrieNode *newNode(void) {
	TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
	pNode->isLeaf = false;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		pNode->children[i] = NULL;
	}
	return pNode;
}



void findWord::insert(TrieNode *root, vector<char> word) {
	TrieNode *pCrawl = root;
	for (int level = 0; level < ((int)word.size() - 1); level++) {
		int index = CHAR_TO_INDEX(word[level]);
		if (!pCrawl->children[index]) {
			pCrawl->children[index] = newNode();
        }
        pCrawl->nodeCoords = validCoords.at(level);
		pCrawl = pCrawl->children[index];
	}
	pCrawl->isLeaf = true; // mark last node as leaf
}



int findWord::preSearch(TrieNode *root, vector<char> word) {
	TrieNode *pCrawl = root;
	for (int level = 0; level < ((int)word.size() - 1); level++) {
		int index = CHAR_TO_INDEX(word[level]);
		if (!pCrawl->children[index]) {
			return level;
        }
        validCoords.push_back(pCrawl->nodeCoords);
		pCrawl = pCrawl->children[index];
	}
	return (pCrawl != NULL && pCrawl->isLeaf);
}



coords findWord::findValidPosition(coords prevCoords, char currLetter) {
    coords foundCoords;
    for (int r = (prevCoords.r - 1); (r <= prevCoords.r + 1) && (r < totalLayers); r++) {
        if (prevCoords.r < 1) {
            r = 1;
        }
        int maxTheta = (r * 6) - 1;
        if (r == 0) {
            maxTheta = 0;
        }
        for (int theta = 0; theta <= maxTheta; theta++) {
            if ((prevCoords.r == 0) || (r == 0)) {
                foundCoords = setValidPosition(currLetter, r, theta);
            }
            else if (prevCoords.r == r) { // check if letter exists +- 1 away from previous
                int moveClockwise = prevCoords.theta + 1;
                int moveCounterclock = prevCoords.theta - 1;
                if (prevCoords.theta == 0) {
                    moveCounterclock = maxTheta;
                }
                else if (prevCoords.theta == maxTheta) {
                    moveClockwise = 0;
                }
                if ((theta == moveClockwise) || (theta == moveCounterclock)) {
                    foundCoords = setValidPosition(currLetter, r, theta);
                }
            }
            else { // checking one layer above and below
                int moveA = 0;
                int moveB = 0;
                int edgeValue = 0;
                if (prevCoords.r != 0) {
                    moveA = prevCoords.theta / prevCoords.r;
                    moveB = moveA + 1;
                    edgeValue = prevCoords.theta % prevCoords.r;
                }
                if (prevCoords.r > r) { // moving inwards
                    moveA *= -1;
                    moveB = moveA - 1;
                }
                if (edgeValue > 0) { // non-special case
                    if ((theta == (prevCoords.theta + moveA)) || (theta == (prevCoords.theta + moveB))) {
                        foundCoords = setValidPosition(currLetter, r, theta);
                    }
                }
                else {
                    
                    if (theta == (prevCoords.theta + moveA)) {
                        foundCoords = setValidPosition(currLetter, r, theta);
                    }
                    else if ((prevCoords.theta == 0) && ((theta == maxTheta) || (theta == 1))) {
                        foundCoords = setValidPosition(currLetter, r, theta);
                    }
                    else if (prevCoords.r < r) {
                        if ((theta == (prevCoords.theta + moveB)) || (theta == (prevCoords.theta + moveA - 1))) {
                            foundCoords = setValidPosition(currLetter, r, theta);
                        }
                    }
                }
            }
            if (foundCoords.r != -1) {
                return foundCoords;
            }
        }
    }
    return foundCoords;
}



coords findWord::findFirstPosition(char currLetter) {
    coords firstCoords;
    for (int r = 0; r < totalLayers; r++) {
        int maxTheta = (r * 6) - 1;
        if (r == 0) {
            maxTheta = 0;
        }
        for (int theta = 0; theta <= maxTheta; theta++) {
            if ((currLetter == letterVector[r][theta]) && (checkHistory(coords(r, theta)))) {
                return firstCoords.setCoords(r, theta);
            }
        }
    }
    return firstCoords;
}



coords findWord::setValidPosition(char currLetter, int r, int theta) {
    coords setCoord;
    if ((r < 0) || (theta < 0)) {
        return setCoord;
    }
    if (currLetter == letterVector[r][theta]) {
        if (checkHistory(coords(r, theta))) {
            setCoord.setCoords(r, theta);
        }
    }
    return setCoord;
}



bool findWord::checkHistory(coords tryCoords) {
    for (int i = 0; i < (int)deadEnd.size(); i++) {
        if ((tryCoords.r == deadEnd.at(i).r) && (tryCoords.theta == deadEnd.at(i).theta)) {
            return false;
        }
    }
    for (int i = 0; i < (int)validCoords.size(); i++) {
        if ((tryCoords.r == validCoords.at(i).r) && (tryCoords.theta == validCoords.at(i).theta)) {
            return false;
        }
    }
    return true;
}




void findWord::lexicographicalPrint(TrieNode *node) {
    if (node->isLeaf) {
        std::cout << string(outputWords.begin(), outputWords.end()) << "\n";
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            outputWords.push_back(INDEX_TO_CHAR(i));
            lexicographicalPrint(node->children[i]);
            outputWords.pop_back();
        }
    }
}





