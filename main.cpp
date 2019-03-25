//
// Created by Hadi Omidi on 3/23/19.
//

#include "functions.h"

int main() {
    vector<string> f = files();
    for (int i = 0; i < f.size(); ++i) {
        cout << f[i] << endl;
    }
    return 0;
}