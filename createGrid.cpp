// by Alyssa Keimach

#include "createGrid.h"



void gridOperations::createHoneycombInput() {
    ofstream honeycomb;
    honeycomb.open(honeyIn.c_str());
    honeycomb << char('A' + rand() % ALPHABET_SIZE) << "\n";
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < (i * 6); j++) {
            honeycomb << char('A' + rand() % ALPHABET_SIZE);
        }
        honeycomb << "\n";
    }
    honeycomb.close();
    return;
}



void gridOperations::convertPolarToCartesian() {
    
    ifstream honeycomb;
    string str;
    vector<vector<double> > transforms(6);
    int r = 0;
    
    double a = sqrt(3) / 2.0;
    double b = 1.0 / 2.0;
    double c = 0.0;
    double d = 1.0;

    transforms[0].push_back(a);
    transforms[0].push_back(-b);
    transforms[1].push_back(c);
    transforms[1].push_back(-d);
    transforms[2].push_back(-a);
    transforms[2].push_back(-b);
    transforms[3].push_back(-a);
    transforms[3].push_back(b);
    transforms[4].push_back(c);
    transforms[4].push_back(d);
    transforms[5].push_back(a);
    transforms[5].push_back(b);
    
    honeycomb.open(honeyIn.c_str());
    if(!(honeycomb)) {
        std::cout << "Error opening input files!\n";
    }
    while (getline(honeycomb, str)) {
        str.erase(str.find_last_not_of(" \n\r\t") + 1);
        vector<char> line(str.begin(), str.end());
        letters.push_back(line);
        xyCoords setCoords;
        setCoords.letter = line[0];
        setCoords.theta = 0;
        setCoords.r = r;
        setCoords.x = 0;
        setCoords.y = r;
        xyVec.push_back(setCoords);
        for (int i = 1; i < (int)line.size(); i++) {
            xyCoords transformCoords;
            transformCoords.letter = line[i];
            transformCoords.theta = i;
            transformCoords.r = r;
            if (r == 0) {
                transformCoords.x = setCoords.x + transforms[(i - 1)][0];
                transformCoords.y = setCoords.y + transforms[(i - 1)][1];
            }
            else {
                transformCoords.x = setCoords.x + transforms[(i - 1) / r][0];
                transformCoords.y = setCoords.y + transforms[(i - 1) / r][1];
            }
            xyVec.push_back(transformCoords);
            setCoords = transformCoords;
        }
        r++;
    }
    honeycomb.close();
    
    if (size == 0) { size = r; }
    std::sort(xyVec.begin(), xyVec.end());
    
    return;
}

void gridOperations::printHoneycombStdout() {

    double currMax = 0;
    int row = 0;
    int count = 2;
    
    for (int i = 0; i < (int)xyVec.size(); i++) {
        
        if ((xyVec[i].y < currMax) || (i == 0)) {
            std::cout << "\n";
            row++;
            
            if (row < size) {
                for (int t = 0; t <= size - row; t++) {
                    std::cout << "\t";
                }
            }
            else if ((row >= size) && (row < (size * 3.0) - 1)) {
                if ((size % 2) == 0) {
                    if ((row % 2) == 0) { std::cout << "\t"; }
                    else { std::cout << "\t\t"; }
                }
                else {
                    if ((row % 2) == 0) { std::cout << "\t\t"; }
                    else { std::cout << "\t"; }
                }
            }
            else if (row >= (size * 3.0) - 1 ) {
                for (int t = 0; t < count; t++) {
                    std::cout << "\t";
                }
                count++;
            }
        }
        std::cout << xyVec[i].letter << "\t\t";
        currMax = xyVec[i].y;
        
    }
    std::cout << "\n";
    return;
}


void gridOperations::printHoneycombFile() {
    
    ofstream honeycomb;
    honeycomb.open(honeyOut.c_str());

    double currMax = 0;
    int row = 0;
    int count = 2;
    
    for (int i = 0; i < (int)xyVec.size(); i++) {
        
        if ((xyVec[i].y < currMax) || (i == 0)) {
            honeycomb << "\n";
            row++;
            
            if (row < size) {
                for (int t = 0; t <= size - row; t++) {
                    honeycomb << "\t";
                }
            }
            else if ((row >= size) && (row < (size * 3.0) - 1)) {
                if ((size % 2) == 0) {
                    if ((row % 2) == 0) { honeycomb << "\t"; }
                    else { honeycomb << "\t\t"; }
                }
                else {
                    if ((row % 2) == 0) { honeycomb << "\t\t"; }
                    else { honeycomb << "\t"; }
                }
            }
            else if (row >= (size * 3.0) - 1 ) {
                for (int t = 0; t < count; t++) {
                    honeycomb << "\t";
                }
                count++;
            }
        }
        honeycomb << xyVec[i].letter << "\t\t";
        currMax = xyVec[i].y;
        
    }
    honeycomb << "\n";
    
    honeycomb.close();
    return;

}


void gridOperations::loadDictionary() {

    ifstream dictionary;
    dictionary.open(dictIn.c_str());
    if(!(dictionary)) {
        std::cout << "Error opening input files!\n";
    }
    string str;
    while (getline(dictionary, str)) {
        str.erase(str.find_last_not_of(" \n\r\t") + 1);
        vector<char> line(str.begin(), str.end());
        for (int i = 0; i < (int)line.size(); i++) {
            line[i] = toupper(line[i]);
        }
        line.push_back('\r');
        words.push_back(line);
    }
    dictionary.close();
    
    std::sort( words.begin(), words.end() );
}


void gridOperations::inventDictionary() {
    
    int stop = 0;
    string str;
    
    while (!stop) {
        std::cin >> str;
        if (isdigit(*str.c_str())) {
            stop = 1;
        }
        else {
            vector<char> line(str.begin(), str.end());
            for (int i = 0; i < (int)line.size(); i++) {
                line[i] = toupper(line[i]);
            }
            line.push_back('\r');
            words.push_back(line);
        }
    }

    std::sort( words.begin(), words.end() );
}

