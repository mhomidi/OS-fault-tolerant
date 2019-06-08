//
// Created by Hadi Omidi on 3/23/19.
//

#include "functions.h"

bool fexists(string filename) {
    ifstream ifile(filename);
    return (bool)ifile;
}

vector<string> ls(string path) {
    DIR *mydir;
    vector <string> files;
    struct dirent *myfile;
    mydir = opendir(&path[0]);
    while ((myfile = readdir(mydir)) != NULL) {
        if (myfile->d_name[0] == '.')
            continue;
        else if (myfile->d_type == DT_DIR) {
            vector <string> recursive_files = ls(path + myfile->d_name + "/");
            files.insert(files.end(), recursive_files.begin(), recursive_files.end());
        } else
            files.push_back(path + myfile->d_name);
    }
    closedir(mydir);
    sort(files.begin(), files.end());
    return files;
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

void workerDo(string DBFile, int sensor, int fd, int i) {
    int key, value;
    ifstream inFile;
    inFile.open(DBFile);
    while (inFile >> key >> value) {
        if (sensor == key) {
//            cout << "Salkama" << endl;
//            cout << value << endl;
            passDatumToFinalProcess(value, fd, i);
            break;
        }
    }
    inFile.close();
}

void workerDoTest() {
//    workerDo("databases/0/0.txt", 0);
}

void passDatumToFinalProcess(int value, int fd, int i) {
    string val = to_string(value);
    const char* val2 = val.c_str();
//    cout << write(fd, val2, strlen(val2) + 1) << endl;
    write(fd, val2, strlen(val2) + 1);
}

int getDatumInFinalProcess(int fd) {
//    close(fd[1]);
    char buff[100];
    read(fd, buff, 100);
    int res = atoi(buff);
    return res;
}

int searchMax(map<int, int> data, int min, int max) {
    int m = -100000;
    int index = -1;
    for (int i = min; i < max + 1; ++i) {
        if (data[i] > m) {
            m = data[i];
            index = i;
        }
    }
    return index;
}