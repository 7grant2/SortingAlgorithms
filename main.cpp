//
//  main.cpp
//  AlgorithmProject
//
//  Created by Grant Lanham, Jr on 10/7/17.
//  Copyright © 2017 Grant Lanham, Jr. All rights reserved.
//
//  FLORIDA ATLANTIC UNIVERSITY
//
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include "AlgorithmSorter.hpp"

using namespace std;

void MenuDriver();
void AlgorithmDriver(AlgorithmSorter *A);
char input();

int main(int argc, const char * argv[]) {
    cout <<
    "Welcome to the Algorithm Solver. This program " << endl <<
    "sorts out the following Algorithms:" << endl <<
    " - Insertion-Sort" << endl <<
    " - Merge-Sort" << endl <<
    " - QuickSort" << endl;
    MenuDriver();
    
    cout << "GOODBYE" << endl;
    return (0);
}

//Encapsulates the entire program
void MenuDriver() {
    bool loop = true;
    unsigned int ns, nf, delta, m;
    char x;
    while (loop) {
        cout <<
        "[0] DEFAULT RUN (original purpose)" << endl <<
        "[1] CUSTOM RUN (enter specific values for variables)" << endl <<
        "[2] MINIMAL RUN (1, 1, 10, 3)" << endl <<
        "[3] QUIT PROGRAM" << endl;

        x = input();
        switch(x){
            case '0':
            {
                AlgorithmSorter *A = new AlgorithmSorter();
                AlgorithmDriver(A);
                delete A;
                break;
            }
            case '1':
            {
                cout
                << "Please enter user defined variables" << endl
                << "ns: ";
                cin >> ns;
                cout << "nf: ";
                cin >> nf;
                cout << "delta: ";
                cin >> delta;
                cout << "m: ";
                cin >> m;
                AlgorithmSorter *B = new AlgorithmSorter(ns, nf, delta, m);
                AlgorithmDriver(B);
                delete B;
                break;
            }
            case '2':
            {
                ns = 1;
                delta = 1;
                nf = 10;
                m = 3;
                AlgorithmSorter *C = new AlgorithmSorter(ns, nf, delta, m);
                AlgorithmDriver(C);
                delete C;
                break;
            }
            case '3':
            {
                loop = false;
                break;
            }
            default:
            {
                cout << "Please enter a valid input." << endl;
                break;
            }
        }
    }
}


void AlgorithmDriver(AlgorithmSorter *A){
    bool loop = true;
    char x;
    vector<int> temp;
    while (loop) {
        cout <<
        "[0] RUN ALL THROUGH DRIVER (recommended)" << endl <<
        "[1] PRINT UNSORTED VECTOR" << endl <<
        "[2] RUN INSERTION SORT (full vector)" << endl <<
        "[3] RUN MERGE SORT (full vector)" << endl <<
        "[4] RUN QUICK SORT (full vector)" << endl <<
        "[5] TOGGLE WRITE TO FILE" << endl <<
        "[6] RETURN TO MAIN MENU" << endl;
        x = input();
        
        switch(x){
            case '0':
            {
                cout << "Main Driver Running..." << endl << "-------------" << endl;
                A->Driver();
                break;
            }
            case '1':
            {
                cout << "Printing Vector..." << endl << "-------------" << endl;
                A->PrintVector();
                break;
            }
            case '2':
            {
                cout << "InsertSort Running..." << endl << "-------------" << endl;
                A->InsertSort(A->get_vector());
                break;
            }
            case '3':
            {
	      cout << "MergeSort Running..." << endl  << "-------------" << endl;
                temp = A->get_vector();
                A->MergeSort(temp, 0, (A->get_vectorsize()-1));
                
                break;
            }
            case '4':
            {
	      cout << "QuickSort Running..." << endl << "-------------" << endl;
                temp = A->get_vector();
                A->QuickSort(temp, 0, (A->get_vectorsize())-1);
                break;
            }
            case '5':
            {
                A->ToggleWrite();
                break;
            }
            case '6':
            {
                loop = false;
                break;
            }
            default:
            {
                cout << "Please enter a valid input." << endl;
                break;
            }
        }
        cin.clear();
    }
}

//Read one character from user
char input(){
    bool loop = true;
    string input = "";
    while (loop){
        cin.clear();
        getline(cin, input);
        if(input.length() > 1){
            cout << "Please enter a single character" << endl;
        } else {
            return input[0];
        }
    }
    return input[0];
}

