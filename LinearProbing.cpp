#include "LinearProbing.h"

LinearProbing::LinearProbing(){
    size=0;
    pos=0;
    capacity=primes[pos];
    for (int i=0;i<capacity;i++){
        bankStorage1d.push_back(Account({"empty",0}));
    }
}

void LinearProbing::createAccount(string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (size >= capacity/2 && pos!=7){
        vector<Account> fauz;
        capacity = primes[++pos];
        for (int i=0;i<capacity;i++)  fauz.push_back(Account({"empty",0}));
        int old_cap = primes[pos-1];
        for (int i=0;i<old_cap;i++){
            if ((bankStorage1d[i].id!="empty")&&(bankStorage1d[i].id!="X")){
                int hashVal=hash(bankStorage1d[i].id);
                while (fauz[hashVal].id!="empty"){
                    hashVal = (hashVal+1)%capacity;
                }
                fauz[hashVal].id=bankStorage1d[i].id;
                fauz[hashVal].balance=bankStorage1d[i].balance;
            }
        }
        bankStorage1d.clear();
        bankStorage1d=fauz;
    }

    int hashVal = hash(id);
    while (bankStorage1d[hashVal].id!="empty"){
        if (bankStorage1d[hashVal].id!="X"){
            hashVal = (hashVal+1)%capacity;
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

vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE

    if (balances.size()==0) return vector<int>(); // Placeholder return value 
    else{
        int n = balances.size();
        vector<int> temp(n);
        LinearProbing::mergeSort(balances,0,n,temp);
        int t =k;
        vector<int> ans;
        for (int i=0;i<min(t,n);i++){
            ans.push_back(balances[n-i-1]);
        }
        return ans;
    }
}

int LinearProbing::getBalance(string id) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        return -1; // Placeholder return value
    }
    else{
        int hashVal = hash(id);
        while (bankStorage1d[hashVal].id!=id){
            hashVal = (hashVal+1)%capacity;
        }
        return bankStorage1d[hashVal].balance;
    }
}

void LinearProbing::addTransaction(string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        createAccount(id,count);
    }
    else{
        int hashVal= hash(id);
        while (bankStorage1d[hashVal].id!=id){
            hashVal = (hashVal+1)%capacity; 
        }
        int found = index(balances,bankStorage1d[hashVal].balance);
        balances[found]+=count;
        bankStorage1d[hashVal].balance+=count;
    }
}

bool LinearProbing::doesExist(string id) {
    // IMPLEMENT YOUR CODE HERE
    if (id.size()<22){
        return false;
    }
    int hashVal = hash(id);
    int temp = hashVal;
    while (bankStorage1d[hashVal].id!=id){
        if (bankStorage1d[hashVal].id=="empty"){
            return false;
        }
        hashVal = (hashVal+1)%capacity;   
        if (temp==hashVal)  return false;
    }
    if (bankStorage1d[hashVal].id==id){
        return true;
    }
    else{
        return false; // Placeholder return value
    }
}

bool LinearProbing::deleteAccount(string id) {
    // IMPLEMENT YOUR CODE HERE
    if ((size<=capacity/4)&&(pos!=0)){
        capacity=primes[--pos];
        vector<Account> fauz;
        for (int i=0;i<capacity;i++)  fauz.push_back(Account({"empty",0}));
        int old_cap = primes[pos+1];
        for (int i=0;i<old_cap;i++){
            if ((bankStorage1d[i].id!="empty")&&(bankStorage1d[i].id!="X")){
                int hashVal=hash(bankStorage1d[i].id);
                while (fauz[hashVal].id!="empty"){
                    hashVal = (hashVal+1)%capacity;
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
        int hashVal= hash(id);
        while (bankStorage1d[hashVal].id!=id){
            hashVal = (hashVal+1)%capacity; 
        }
        int found = index(balances,bankStorage1d[hashVal].balance);
        balances.erase(balances.begin()+found);
        bankStorage1d[hashVal].id="X";
        bankStorage1d[hashVal].balance=0;
        size--; 
        return true;
    }
}

int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(string id) {
    // IMPLEMENT YOUR CODE HERE
    long long ans=0;
    for (int i=0;i<id.size();i++){
        ans += (id[i])*(arr[i])*(arr[i]);
    }
    int res = ans%capacity;
    return res; // Placeholder return value
}


// int main(){
//     LinearProbing l = LinearProbing();
//     cout<<l.hash("DBCA1230004_0000567890")<<endl;
// }


