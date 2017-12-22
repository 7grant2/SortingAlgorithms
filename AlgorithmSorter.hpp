//
//  AlgorithmSorter.hpp
//  AlgorithmProject
//
//  Created by Grant Lanham, Jr on 10/10/17.
//  Copyright © 2017 Grant Lanham, Jr. All rights reserved.
//
//  FLORIDA ATLANTIC UNIVERSITY
//
//


#ifndef AlgorithmSorter_hpp
#define AlgorithmSorter_hpp

#include <stdio.h>
#include <vector>

#endif /* AlgorithmSorter_hpp */

using namespace std;

class AlgorithmSorter {
private:
    vector<int> v;
    unsigned int ns;
    unsigned int nf;
    unsigned int delta;
    unsigned int m;
    bool write;
public:
    AlgorithmSorter(); //Default Constructor for assignment
    AlgorithmSorter(unsigned int ns_i, unsigned int nf_i, unsigned int delta_i, unsigned int m_i ); //Explicit Value constructor for specific run
    void Driver(); //Creates base case for algorithm definitions
    void InsertSort(vector<int> v) const; //Perform InsertSort Algorithm
    void MergeSort(vector<int> &v, const int p, const int r); //Perform MergeSort Algorithm
    void Merge(vector<int> &v, int p, const int q, const int r); //Merge function for MergeSort
    void QuickSort(vector<int> &v, const int p, const int r); //Perform QuickSort Algorithm
    int Partition(vector<int> &v, const int p, const int r); //Partition for QuickSort Algorithm
    void WriteToFile(vector<float> avgis, vector<float> avgms, vector<float> avgqs) const; //Write contents of output to file
    vector<int> get_vector() const {return v; } //returns private vector
    unsigned int get_ns() const { return ns; } //returns private ns
    unsigned int get_nf() const{ return nf; } //returns private nf
    unsigned int get_delta() const { return delta; } //returns private nf
    unsigned int get_m() const { return m; } //returns private nf
    int get_vectorsize() const { return int(v.size()); } //returns size of the vector
    void PrintVector() const; //prints the unsorted vector
    void PrintVector(vector<int> v) const; //prints vector input
    void ToggleWrite(); //enables and disables
    void ParseVector(vector<int> &pv, vector<int> &vect); //Parses a vector from to count of f
    void LoadingBar(float x) const; //prints loading bar for driver
};
