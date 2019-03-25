//
// Created by Hadi Omidi on 3/23/19.
//

#include "functions.h"

bool fexists(string filename) {
    ifstream ifile(filename);
    return (bool)ifile;
}

vector<string> files() {
    vector<string> f;
    int number = 0;
    int folderName = 0;
    int fileName = 0;
    string fileNameStr, folderNameStr, dir;
    while (true){
        while(true) {
            fileNameStr = to_string(fileName);
            folderNameStr = to_string(folderName);
            dir = "databases/" + folderNameStr + "/" + fileNameStr + ".txt";
            if (fexists(dir))
                f.push_back(dir);
            else
                break;
            fileName++;
        }
        folderName++;
        fileName = 0;
        fileNameStr = "0";
        folderNameStr = folderNameStr = to_string(folderName);
        dir = "databases/" + folderNameStr + "/" + fileNameStr + ".txt";
        if (!fexists(dir))
            break;
    }
    return f;
}

void filesFuncTest() {
    vector<string> f = files();
    for (int i = 0; i < f.size(); ++i) {
        cout << f[i] << endl;
    }
}

void workerDo(string DBFile, int sensor) {
    int key, value;
    ifstream inFile;
    inFile.open(DBFile);
    while (inFile >> key >> value) {
        if (sensor == key)
            passDatumToFinalProcess(value);
    }
    inFile.close();
}

void workerDoTest() {
    workerDo("databases/0/0.txt");
}

void passDatumToFinalProcess(int value) {

}