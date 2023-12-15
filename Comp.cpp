#include "Comp.h"

Comp::Comp(){
    size=0;
    pos=0;
    capacity=primes[pos];
    for (int i=0;i<capacity;i++){
        bankStorage1d.push_back(Account({"empty",0}));
    }
}

void Comp::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (size >= capacity/2 && pos!=7){
        vector<Account> fauz;
        capacity = primes[++pos];
        for (int i=0;i<capacity;i++)  fauz.push_back(Account({"empty",0}));
        int old_cap = primes[pos-1];
        for (int i=0;i<old_cap;i++){
            if ((bankStorage1d[i].id!="empty")&&(bankStorage1d[i].id!="X")){
                long long hashVal =hash(bankStorage1d[i].id);
                long long temp =hashVal;
                long long j=1;
                while (fauz[hashVal].id!="empty"){
                    hashVal = (temp+(j*((j*j)%capacity)))%capacity;
                    j++;
                }
                fauz[hashVal].id=bankStorage1d[i].id;
                fauz[hashVal].balance=bankStorage1d[i].balance;
            }
        }
        bankStorage1d.clear();
        bankStorage1d=fauz;
    }

    long long hashVal  = hash(id);
    long long temp = hashVal;
    long long i=1;
    while (bankStorage1d[hashVal].id!="empty"){
        if (bankStorage1d[hashVal].id!="X"){
            hashVal =(temp+(i*((i*i)%capacity)))%capacity;
            i++;
        }
        else{
            break;
        }
    }
    bankStorage1d[hashVal].id=id;
    bankStorage1d[hashVal].balance=count;
    balances.push_back(count);
    size++;
}

std::vector<int> Comp::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    if (balances.size()==0) return vector<int>(); // Placeholder return value 
    else{
        int n = balances.size();
        vector<int> temp(n);
        Comp::mergeSort(balances,0,n,temp);
        int t =k;
        vector<int> ans;
        for (int i=0;i<min(t,n);i++){
            ans.push_back(balances[n-i-1]);
        }
        return ans;
    }
}

int Comp::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        return -1; // Placeholder return value
    }
    else{
        long long i=1;
        long long hashVal = hash(id);
        long long temp = hashVal;
        while (bankStorage1d[hashVal].id!=id){
            hashVal =(temp+(i*((i*i)%capacity)))%capacity; 
            i++;
        }
        return bankStorage1d[hashVal].balance;
    }
}

void Comp::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        createAccount(id,count);
    }
    else{
        long long i=1;
        long long hashVal = hash(id);
        long long temp = hashVal;
        while (bankStorage1d[hashVal].id!=id){
            hashVal =(temp+(i*((i*i)%capacity)))%capacity; 
            i++;
        }
        int found = index(balances,bankStorage1d[hashVal].balance);
        balances[found]+=count;
        bankStorage1d[hashVal].balance+=count;
    }
}

bool Comp::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (id.size()<22){
        return false;
    }
    long long i=1;
    long long hashVal  = hash(id);
    long long temp = hashVal;
    while (bankStorage1d[hashVal].id!=id){
        if (bankStorage1d[hashVal].id=="empty"){
            return false;
        }
        hashVal = (temp+(i*((i*i)%capacity)))%capacity;
        i++;   
        if (temp==hashVal)  return false;
    }
    if (bankStorage1d[hashVal].id==id){
        return true;
    }
    else{
        return false; // Placeholder return value
    }
}

bool Comp::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if ((size<=capacity/4)&&(pos!=0)){
        capacity=primes[--pos];
        vector<Account> fauz;
        for (int i=0;i<capacity;i++)  fauz.push_back(Account({"empty",0}));
        int old_cap = primes[pos+1];
        for (int i=0;i<old_cap;i++){
            if ((bankStorage1d[i].id!="empty")&&(bankStorage1d[i].id!="X")){
                long long j=1;
                long long hashVal =hash(bankStorage1d[i].id);
                long long temp =hashVal;
                while (fauz[hashVal].id!="empty"){
                    hashVal = (temp+(j*((j*j)%capacity)))%capacity;
                    j++;
                }
                fauz[hashVal].id=bankStorage1d[i].id;
                fauz[hashVal].balance=bankStorage1d[i].balance;
            }
        }
        bankStorage1d.clear();
        bankStorage1d=fauz;      
    }

    if (!doesExist(id)){
        return false; // Placeholder return value  
    }   
    else{
        long long i=1;
        long long hashVal = hash(id);
        long long temp = hashVal;
        while (bankStorage1d[hashVal].id!=id){
            hashVal =(temp+(i*((i*i)%capacity)))%capacity; 
            i++;
        }
        int found = index(balances,bankStorage1d[hashVal].balance);
        balances.erase(balances.begin()+found);
        bankStorage1d[hashVal].id="X";
        bankStorage1d[hashVal].balance=0;
        size--; 
        return true;
    }
}

int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Comp::hash(std::string id) {
    long long ans=0;
    for (int i=0;i<id.size();i++){
        ans += (id[i])*(arr[i])*(arr[i]);
    }
    int res = ans%capacity;
    return res; // Placeholder return value
}

// Feel free to add any other helper functions you need
// Good Luck!