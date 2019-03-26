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
    int in;
    int pipes[MAX_DATABASE][2];

    for (int i = 0; i < numberOfChildren; ++i) {
        if (pipe(pipes[i]) == -1)
            return 1;
    }

    cin >> in;

    for (int k = 0; k < numberOfChildren; ++k) {
        pids.push_back(0);
    }

    for (int i = 0; i < numberOfChildren; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            workerDo(fileDirs[i], in, pipes[i]);
            exit(0);
        }
    }

    int n = numberOfChildren;
    while (n > 0) {
        wait(NULL);
        --n;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
        map<int, int> data;
        int max = -100000;
        for (int i = 0; i < numberOfChildren; ++i) {
            int res = getDatumInFinalProcess(pipes[i]);
            if (res > max)
                max = res;
            data[res]++;
        }
    } else {
        wait(NULL);
    }

    return 0;
}