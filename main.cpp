// by Alyssa Keimach

#include <ctime>
#include "findWord.h"
#include "createGrid.h"

int main(int argc, const char * argv[]) {

    gridOperations initiateGrid;
    std::cout << "\nEnter '1' to enter your honeycomb filename, or '2' to autogenerate: ";
    int input;
    std::cin >> input;
    if (input == 1) {
        std::cout << "\nEnter your honeycomb filename: ";
        std::cin >> initiateGrid.honeyIn;
        initiateGrid.honeyOut = "grid_" + initiateGrid.honeyIn;
        initiateGrid.size = 0;
    }
    else if (input == 2) {
        std::cout << "\nEnter the size of the honeycomb: ";
        std::cin >> initiateGrid.size;
        std::cout << "\nEnter a filename to save it: ";
        std::cin >> initiateGrid.honeyIn;
        initiateGrid.honeyOut = "grid_" + initiateGrid.honeyIn;
        std::cout << "\nCreating a " << initiateGrid.size << " layer honeycomb at " << initiateGrid.honeyIn << "...\n";
        initiateGrid.createHoneycombInput();
    }
    else {
        std::cout << "\nSorry, couldn't process your request";
        return 0;
    }

    initiateGrid.convertPolarToCartesian();
    initiateGrid.printHoneycombStdout();
    initiateGrid.printHoneycombFile();

    std::cout << "\nEnter '1' to enter a dictionary file, or '2' to type in your own words: ";
    std::cin >> input;
    if (input == 1) {
        std::cout << "\nEnter your dictionary filename: ";
        std::cin >> initiateGrid.dictIn;
        initiateGrid.loadDictionary();
    }
    else if (input == 2) {
        std::cout << "\nHit 'enter' after each word, or type 1 then 'enter' to quit entry mode\n";
        initiateGrid.inventDictionary();
    }
    else {
        std::cout << "\nSorry, couldn't process your request";
        return 0;
    }


    clock_t start = clock();
    TrieNode *root = newNode();
    findWord search;
    search.letterVector = initiateGrid.letters;
    search.totalLayers = initiateGrid.size;

    
    std::cout << "\nLooking for words...\nFound:\n";

    for (int i = 0; i < (int)initiateGrid.words.size(); i++) {

        search.validCoords.clear();
        search.deadEnd.clear();

        int level = search.preSearch(root, initiateGrid.words[i]);

        if (search.runCipher(initiateGrid.words[i], level)) {
            search.insert(root, initiateGrid.words[i]);
        }
    }

    search.lexicographicalPrint(root);
    std::cout << "Time: " << (clock() - start) / (CLOCKS_PER_SEC / 1000.0) << " milliseconds\n";
    return 0;
}
