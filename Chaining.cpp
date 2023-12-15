#include "Chaining.h"

Chaining::Chaining(){
    for (int i=0;i<1000;i++){
        bankStorage2d.push_back(vector<Account> ());
    }
    size=0;
    capacity=1000;
}

void Chaining::createAccount(string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hashVal = hash(id);
    bankStorage2d[hashVal].push_back(Account({id,count}));
    balances.push_back(count);
    size++;
}

vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE

    if (balances.size()==0){
        return vector<int>();
    }
    else{
        int n = balances.size();
        vector<int> temp(n);
        Chaining::mergeSort(balances,0,n,temp);
        int t =k;
        vector<int> ans;
        for (int i=0;i<min(t,n);i++){
            ans.push_back(balances[n-i-1]);
        }
        return ans;
    }
}

int Chaining::getBalance(string id) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        return -1; // Placeholder return value
    }
    else{
        int hashVal = hash(id);
        for (int i=0;i<bankStorage2d[hashVal].size();i++){
            if (bankStorage2d[hashVal][i].id == id){
                return bankStorage2d[hashVal][i].balance;
            }
        }
        return -1;
    }
}

void Chaining::addTransaction(string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (!doesExist(id)){
        createAccount(id,count);
    }
    else{
        int hashVal= hash(id);
        for (int i=0;i<bankStorage2d[hashVal].size();i++){
            if (bankStorage2d[hashVal][i].id == id){
                int found = index(balances,bankStorage2d[hashVal][i].balance);
                balances[found]+=count;
                bankStorage2d[hashVal][i].balance+=count;
                return;
            }
        }
    }
}

bool Chaining::doesExist(string id) {
    // IMPLEMENT YOUR CODE HERE
    if (id.size()<22){
        return false;
    }
    int hashVal = hash(id);
    for (int i=0;i<bankStorage2d[hashVal].size();i++){
        if (bankStorage2d[hashVal][i].id==id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id)){
        int hashVal = hash(id);
        for (int i=0;i<bankStorage2d[hashVal].size();i++){
            if (bankStorage2d[hashVal][i].id==id){
                int found = index(balances,bankStorage2d[hashVal][i].balance);
                balances.erase(balances.begin()+found);
                bankStorage2d[hashVal].erase(bankStorage2d[hashVal].begin()+i);
                size--;
                return true;
            }
        }    
    }
    return false; // Placeholder return value
}

int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(string id) {
    // IMPLEMENT YOUR CODE HERE
    long long ans=0;
    for (int i=0;i<id.size();i++){
        ans += (id[i])*(arr[i])*(arr[i]);
    }
    int res = ans%capacity;
    return res; // Placeholder return value
}


// createAccount CDAD7786825_7990768648 648
// createAccount DCDA7547234_9919615552 552
// createAccount AACB1850545_7974534788 788
// databaseSize
// createAccount CDBD5250777_1124276711 711
// createAccount ABCB8377155_0656808575 575
// getTopK 1
// createAccount CDDC3792028_3313680038 38
// createAccount CBBA9574444_7470182321 321
// createAccount DBCC4334636_8057544188 188
// getTopK 3
// createAccount BABD5741078_5109455304 304
// createAccount BCBA7529510_0817878868 868
// databaseSize
// getTopK 1
// addTransaction BCBA7529510_0817878868 -860
// getBalance BCBA7529510_0817878868
// getTopK 1
// addTransaction DCDA7547234_9919615552 592
// getTopK 5
// deleteAccount DCDA7547234_9919615552
// getTopK 4
// databaseSize

// void printarr(vector<int> &arr){
//     for (int i=0;i<arr.size();i++){
//         cout<<arr[i]<<" ";
//     }
// }

// int main(){
//     Chaining c = Chaining();
//     vector <int> vec;
//     c.createAccount("CDAD7786825_7990768648",648);
//     c.createAccount("DCDA7547234_9919615552",552);
//     c.createAccount("AACB1850545_7974534788",788);
//     cout<<c.databaseSize()<<endl;
//     c.createAccount("CDBD5250777_1124276711",711);
//     c.createAccount("ABCB8377155_0656808575",575);
//     vec = c.getTopK(1); printarr(vec); cout<<endl;
//     c.createAccount("CDDC3792028_3313680038",38);
//     c.createAccount("CBBA9574444_7470182321",321);
//     c.createAccount("DBCC4334636_8057544188",188);
//     vec=c.getTopK(3);
//     printarr(vec); cout<<endl;
//     c.createAccount("BABD5741078_5109455304",304);
//     c.createAccount("BCBA7529510_0817878868",868);
//     cout<<c.databaseSize()<<endl;
//     vec=c.getTopK(1);
//     printarr(vec); cout<<endl;
//     c.addTransaction("BCBA7529510_0817878868",-860);
//     cout<<c.getBalance("BCBA7529510_0817878868")<<endl;
//     vec=c.getTopK(1);
//     printarr(vec); cout<<endl;
//     c.addTransaction("DCDA7547234_9919615552",592);
//     vec=c.getTopK(5);
//     printarr(vec); cout<<endl;
//     c.deleteAccount("DCDA7547234_9919615552");
//     vec=c.getTopK(4);
//     printarr(vec); cout<<endl;
//     cout<<c.databaseSize()<<endl;
// }
