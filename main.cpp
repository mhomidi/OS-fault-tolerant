//
// Created by Hadi Omidi on 3/23/19.
//

#include "functions.h"

int main() {


    vector<pid_t> pids;
    vector<string> fileDirs = ls("./databases/");
    int numberOfChildren = fileDirs.size();
    int in;
    cin >> in;
    for (int k = 0; k < numberOfChildren; ++k) {
        pids.push_back(0);
    }

    for (int i = 0; i < numberOfChildren; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            int pid = getpid();
            string s = to_string(pid);
            s = "./hadi/" + s;
            const char *name = s.c_str();
            mkfifo(name, 0666);
            int fd = 0;
            if ((fd = open(name, O_NONBLOCK, O_CREAT)) < 0);
            else
                workerDo(fileDirs[i], in, fd, i);
            close(fd);
            cout << fd << endl;
            exit(0);
        }
        wait(NULL);
    }

    int n = numberOfChildren;
    while (n > 0) {
//        wait(NULL);
        --n;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
        map<int, int> data;
        int max = -100000, min = 100000;
        for (int i = 0; i < numberOfChildren; ++i) {
            string s = to_string(pid);
            s = "./hadi/" + s;
            const char *name = s.c_str();
            mkfifo(name, 0666);
            int fd = open(name, O_NONBLOCK);
            int res = getDatumInFinalProcess(fd);
            close(fd);
            if (res > max)
                max = res;
            if (res < min)
                min = res;
            data[res]++;
        }
        int maximum = searchMax(data, min, max);
        cout << maximum << endl;
        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}