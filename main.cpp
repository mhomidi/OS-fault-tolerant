//
// Created by Hadi Omidi on 3/23/19.
//

#include "functions.h"

int main() {
    // filesFuncTest();

//    workerDoTest();



    vector<pid_t> pids;
    vector<string> fileDirs = files();
    int numberOfChildren = fileDirs.size();


    for (int k = 0; k < numberOfChildren; ++k) {
        pids.push_back(0);
    }

    for (int i = 0; i < numberOfChildren; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            workerDo(fileDirs[i]);
            exit(0);
        }
    }

    return 0;
}