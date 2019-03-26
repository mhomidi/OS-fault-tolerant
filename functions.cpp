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

void workerDo(string DBFile, int sensor, int fd[]) {
    int key, value;
    ifstream inFile;
    inFile.open(DBFile);
    while (inFile >> key >> value) {
        if (sensor == key) {
            passDatumToFinalProcess(value, fd);
            break;
        }
    }
    inFile.close();
}

void workerDoTest() {
//    workerDo("databases/0/0.txt", 0);
}

void passDatumToFinalProcess(int value, int fd[]) {
    close(fd[0]);
    string val = to_string(value);
    const char* val2 = val.c_str();
    write(fd[1], val2, strlen(val2) + 1);
    close(fd[1]);
}

int getDatumInFinalProcess(int fd[]) {
    close(fd[1]);
    char buff[100];
    read(fd[0], buff, 100);
    int res = atoi(buff);
    return res;
}

int searchMax(map<int, int> data) {

}