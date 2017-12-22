
//
//  AlgorithmSorter.cpp
//  AlgorithmProject
//
//  Created by Grant Lanham, Jr on 10/10/17.
//  Copyright © 2017 Grant Lanham, Jr. All rights reserved.
//
//  FLORIDA ATLANTIC UNIVERSITY
//
//


#include "AlgorithmSorter.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

#define randmax 32767


using namespace std;
using namespace chrono;

//Default constructor
AlgorithmSorter::AlgorithmSorter(){
    srand((unsigned)time(0));
    delta = ns = 5000;
    nf = 100000;
    m = 10;
    write = true;
    for (int i = 0; i < nf; i++){
        v.push_back(rand()%randmax);
    }
}

//Explicit value constructor
AlgorithmSorter::AlgorithmSorter(unsigned int ns_i, unsigned int nf_i, unsigned int delta_i, unsigned int m_i ) {
    srand((unsigned)time(0));
    ns = ns_i;
    nf = nf_i;
    delta = delta_i;
    m = m_i;
    write = true;
    for (int i = 0; i < nf; i++) {
        v.push_back(rand()%randmax);
    }

    
}

//Driver for running intended purpose of the assignment
//Calculates run time for each algorithm
//Algorithm ran from ns number of elements to nf
//Algorithm repeated at each number of elements m times and averaged from that value
//Average values pushed into vector for file writing
void AlgorithmSorter::Driver() {
    vector<float> is, ms, qs;
    vector<int> pv, pvr, vect = get_vector();
    int inc = get_delta(), m = get_m();
    auto s = steady_clock::now(), f = steady_clock::now();
    float ia = 0, ma = 0, qa = 0, end = get_nf();
    LoadingBar(0);
    //Loops each function through each
    for (float st = get_ns(); st <= end; st += inc) {
        ia = 0;
        ma = 0;
        qa = 0;
        ParseVector(pv, vect);
        pvr = pv;
        
        for (int z = 0; z < m; z++) {
            
            s = steady_clock::now();
            InsertSort(pv);
            f = steady_clock::now();
            ia +=  nanoseconds(f-s).count();
            
            s = steady_clock::now();
            MergeSort(pv, 0, int(pv.size())-1);
            f = steady_clock::now();
            ma += nanoseconds(f-s).count();
            
            pv = pvr;
            
            s = steady_clock::now();
            QuickSort(pv, 0, int(pv.size())-1);
            f = steady_clock::now();
            qa += nanoseconds(f-s).count();
        }
        ia = floorf( (ia / get_m()) * 0.0001)/1000;
        ma = floorf( (ma / get_m()) * 0.0001)/1000;
        qa = floorf( (qa / get_m()) * 0.0001)/1000;
        is.push_back(ia);
        ms.push_back(ma);
        qs.push_back(qa);
        LoadingBar(st/end);
        cout.flush();
    }
    WriteToFile(is, ms, qs);

   
}
    
void AlgorithmSorter::InsertSort(vector<int> vect) const {
    int key, j, i;
    for(j = 1; j < vect.size(); j++) {
        key = vect[j];
        i = j-1;
        while (i >= 0 && vect[i] >= key){
            vect[i+1] = vect[i];
            i--;
        }
        vect[i+1] = key;
       
    }
}

void AlgorithmSorter::MergeSort(vector<int> &vect, const int p, const int r){
    if (p < r){
        int q = floor((p+r)/2);
        MergeSort(vect, p, q);
        MergeSort(vect, q+1, r);
        Merge(vect, p, q, r);
    }
}

//For MS algorithm
void AlgorithmSorter::Merge(vector<int> &vect, const int p, const int q, int r){
    
      int n1 = q - p + 1;
      int n2 = r - q;
      int i = 0, j = 0, k = 0;
      vector<int> l(n1+1), rt(n2+1);
    
      for (i = 0; i < n1; i++){
        l[i] = vect[p + i];
      }
    
      for (j = 0; j < n2; j++){
        rt[j] = vect[q + j + 1];
      }
    
      l[i] = (randmax + 1);
      rt[j] = (randmax + 1);
    
      i = j = 0;
      for (k = p; k <= r; k++){
        if (l[i] <= rt[j]){
          vect[k] = l[i];
          i++;
        } else {
          vect[k] = rt[j];
          j++;
        }
      }
    l.clear();
    rt.clear();
}

void AlgorithmSorter::QuickSort(vector<int> &vect, const int p, const int r) {
  if (p < r) {
    int q = Partition (vect, p, r);
    QuickSort(vect, p, q-1);
    QuickSort(vect, q+1, r);
  }
}

//Partition function for QS
//Items less or equal than vect[r] move to left pivot
//items greater than vect[r] move to right of pivot
//returns pivot
int AlgorithmSorter::Partition(vector<int> &vect, const int p, const int r) {
    int x = vect[r];
    int i = p-1;
    int temp = 0;
    for (int j = p; j < r; j++){
        if (vect[j] <= x){
          i++;
          temp = vect[i];
          vect[i] = vect[j];
          vect[j] = temp;
        }
    }
    temp = vect[i+1];
    vect[i+1] = vect[r];
    vect[r] = temp;
    return i+1;
}

//writes to .csv file
//arguments contain average values for each algorithm
//Computes theoretical run times for each algorithm
//Computes hidden notation from theoretical and actual values
void AlgorithmSorter::WriteToFile(vector<float> avgis, vector<float> avgms, vector<float> avgqs) const {
    if(!write) return;
    cout << "Writing to file..." << endl << "------------" << endl;
    string filename = "reports.csv";
    fstream file;
    int inc = get_delta(), i;
    long double thrt;
    vector<float>::iterator iteri = avgis.begin(), iterm = avgms.begin(), iterq = avgqs.begin();
    file.open(filename, ios::out);
    if (file.is_open()){
        file << "ALGORITHM ANALYSIS,,,,,,,,,\n";
        i = get_ns();
        file << "Elements, "
        << "Insert Sort (Th), "
        << "Insert Sort (Exp), "
        << "Insert Sort Hidden Constant, "
        << "Merge Sort (Th), "
        << "Merge Sort (Exp), "
        << "Merge Sort Hidden Constant, "
        << "Quick Sort (Th), " 
        << "Quick Sort (Exp), "
	     << "Quick Sort Hidden Constant\n";
        while(iteri != avgis.end() && iterm != avgms.end() && iterq != avgms.end()){
            thrt = (i * i);
            file
            << i << ", "
            << thrt << ", "
            << *iteri << ", "
            << (float(*iteri) / float(thrt)) << ", ";
            
            
            thrt = (i * log2(i));
            file << thrt << ", "
            << *iterm << ", "
            << (float(*iterm) / float(thrt)) << ", ";
            
            thrt = (i * i);
            file << thrt << ", "
            << *iterq << ", "
            << (float(*iterq) / float(thrt)) << "\n";
            
            iterm++;
            iteri++;
            iterq++;
            i += inc;
        }
        file.close();
    }
    else cout << "ERROR: Unable to open file";
}

//Prints private vector
void AlgorithmSorter::PrintVector() const {
    vector<int> a = v;
    while (!a.empty()){
        cout << a.back() << endl;
        a.pop_back();
    }
}

//Prints Vector based on argument
void AlgorithmSorter::PrintVector(vector<int> v) const {
    vector<int> a = v;
    while (!a.empty()){
        cout << a.back() << endl;
        a.pop_back();
    }
}


//enables and disables write;
void AlgorithmSorter::ToggleWrite() {
    write = !write;
    string x;
    x = write ? "ON" : "OFF";
    cout << "Write to file: " << x << endl;
}

//Parses "vect" into the vector pv.
void AlgorithmSorter::ParseVector(vector<int> &pv, vector<int> &vect){
    for(int i = 0; i < get_delta(); i++){
        pv.push_back(vect.back());
        vect.pop_back();
    }
}

//Displays loading bar based on float x input.
void AlgorithmSorter::LoadingBar(float x) const {
    float progress = x;
        int barWidth = 70;
        
        cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << int(progress * 100.0) << " %\r";
        cout.flush();
}


