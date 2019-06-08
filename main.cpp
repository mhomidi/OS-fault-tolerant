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
            int fd = 0;
            int pid = getpid();
            string s = to_string(pid);
            s = "./hadi/" + s;
            const char *name = s.c_str();
            mkfifo(name, 0666);
            fd = open(name, O_WRONLY);
            workerDo(fileDirs[i], in, fd, i);
            close(fd);
//            if ((fd = open(name, O_WRONLY)) < 0);
//            else {
//                workerDo(fileDirs[i], in, fd, i);
//                close(fd);
//            }
//            cout << fd << endl;
            exit(0);
        }
    }

    int n = numberOfChildren;
//    while (n > 0) {
//        cout << "Salam" << endl;
//        --n;
//    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        abort();
    }
    else if (pid == 0) {
        map<int, int> data;
        vector<int> fds;
        int max = -100000, min = 100000;
        for (int i = 0; i < numberOfChildren; ++i) {
            string s = to_string(pids[i]);
            s = "./hadi/" + s;
            const char *name = s.c_str();
            mkfifo(name, 0666);
            int fd = open(name, O_NONBLOCK);
            fds.push_back(fd);
        }
        sleep(1);
        for (int i = 0; i < numberOfChildren; ++i) {
            int res = getDatumInFinalProcess(fds[i]);
            close(fds[i]);
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

    n = numberOfChildren;
    while (n > 0) {
        wait(NULL);
        --n;
    }

    return 0;
}