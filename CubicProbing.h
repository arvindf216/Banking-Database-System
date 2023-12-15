#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
using namespace std;

class CubicProbing : public BaseClass {
public:
    CubicProbing();
    int primes[8]={1013,2267,4049,8087,16001,32003,64007,128021};
    long long arr[22]={101, 211, 307, 421, 523, 619, 727, 839, 947, 1051, 1153, 1277, 1381, 1483, 1579, 1693, 1787, 1879, 1987, 1999, 1997, 1933};
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Quadratic Probing
    
    int size;
    vector<int> balances;
    int pos;
    int capacity;

    void merge (vector<int> &arr, int left, int mid, int right, vector<int> &aux){
        int i = left, j=mid, d=0;
        while (i < mid && j < right) { 
            if (arr[i] < arr[j]) aux[d++] = arr[i++];
            else aux[d++] = arr[j++];
        }
        if (i == mid) { 
            for (i= left; i < j; i++) arr[i] = aux[i-left]; 
        } 
        else {
            for (int k=mid-1, l=right-1; k >= i; k--, l--) arr[l] = arr[k];
            for (j=left; j<right-(mid-i); j++) arr[j] = aux[j- left];
        }
    }

    void mergeSort(vector<int> &arr, int start, int end, vector<int> &aux){
        if ((end-start)<2) return;
        int mid = start + (end - start) / 2;
        mergeSort(arr,start,mid,aux);
        mergeSort(arr,mid,end,aux);
        merge(arr,start,mid,end,aux);
    }

    int index(vector<int> arr, int elem){
        for (int i=0;i<arr.size();i++){
            if (arr[i]==elem){
                return i;
            }
        }
        return -1;
    }
};

#endif // CUBICPROBING_H
