//
//  main.cpp
//  mp2-lab5-list
//
//  Created by Андрей Лебедев on 21.02.2020.
//  Copyright © 2020 Андрей Лебедев. All rights reserved.
//

#include <iostream>
#include "List.h"
using namespace std;
#define size 2

int main(int argc, const char * argv[]) {
    /*int arr1[size][2];
    int arr2[size][2];
    for (int i = 0; i < size; i++) {
        cout << "Enter coeff" << endl;
        cin >> arr1[i][0];
        cout << "Enter powers" << endl;
        cin >> arr1[i][1];
    }
    for (int i = 0; i < size; i++) {
        cout << "Enter coeff" << endl;
        cin >> arr2[i][0];
        cout << "Enter powers" << endl;
        cin >> arr2[i][1];
    }*/
    TPolynom pol1;
    TPolynom pol2;
    cout << "Enter first polynomial:" << endl;
    cin >> pol1;
    cout << "Pol1: " << pol1 << endl;
    cout << "Enter second polynomial:" << endl;
    cin >> pol2;
    cout << "Pol2: " << pol2 << endl;
    pol1+= pol2;
    cout << "pol1 += pol2: " << pol1 << endl;
    return 0;
}