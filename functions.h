//
// Created by Hadi Omidi on 3/23/19.
//
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
#define MAX_DATABASE 10000

vector<string> files();
bool fexists(string filename);
void filesFuncTest();
void workerDo(string DBFile, int sensor, int fd[]);
void workerDoTest();
void passDatumToFinalProcess(int value, int fd[]);