#include<bits/stdc++.h>
using namespace std;

#define seed2 045

const long long N = 10000, T = 0.1*N;

bool isPrime(long long n){
    if (n <= 1)
        return false;
    else if(n <= 3)
        return true;
    
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    
    for (size_t i = 5; i*i <= n; i = i+6){
        if (n % i == 0 || n % (i+2) == 0) 
            return false;
    }
    return true;
}

long long nextPrime(long long N){
    if (N <= 1)
        return 2;
    long long prime = N;
    bool found = false;
    while (!found){
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

int generateRandomNumber(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

string generateRandomString(int length){
    static const string charset = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, charset.length() - 1);
    string str;
    for (int i = 0; i < length; ++i) {
        str += charset[dis(gen)];
    }
    return str;
}

vector<string> storeStrings(int len){
    set<string> uniqueStrings;
    vector<string> uniqueStringsArray;
    int i = 0;
    while (i < len){
        int length = generateRandomNumber(5, 10);
        
        string randomString = generateRandomString(length);
        uniqueStrings.insert(randomString);
        i = uniqueStrings.size();
    }
    
    for (const auto& str : uniqueStrings) {
        uniqueStringsArray.push_back(str);
    }
    return uniqueStringsArray;
}

void shuffleStrings(vector<string> &array, long long size) { 
    mt19937 rng; 
    rng.seed(seed2);  

    for (long long i = size - 1; i > 0; i--) {
        long long j = uniform_int_distribution<long long>(0, i)(rng);
        swap(array[i], array[j]);
    }
}

unsigned long long hash1(string key){  //make sure to mod when using
    unsigned long long hashVal = 0;
    for (size_t i = 0; i < key.length(); i++){
        hashVal += key[i];
        hashVal += (hashVal << 10);
        hashVal ^= (hashVal >> 6);
    }

    hashVal += (hashVal << 3);
    hashVal ^= (hashVal >> 11);
    hashVal += (hashVal << 15);

    return hashVal;
}

unsigned long long hash2(string key){   //make sure to mod when using
    unsigned hashVal = 0;
    const unsigned long long fnv_prime = 16777619;

    for (size_t i = 0; i < key.size(); i++){
        hashVal = hashVal * fnv_prime;
        hashVal = hashVal ^ key[i];
    }
    return hashVal;
}

int main(){
    vector<string> uniqueStrings;
    vector<string>testStrings;
    long long size[3] = {5000, 10000, 20000};
    double report [3][3][2][2];
    
    uniqueStrings = storeStrings(N);
    testStrings = uniqueStrings;

    shuffleStrings(testStrings, N);

    long long n = 0;







    ofstream file("report.txt");

    file << " " << setw(68) << setfill('_') << "" << endl;
    file << setfill(' ');
    file << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    file << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    file << "|" << setw(69) << setfill('_') << "|" << endl;
    file << setfill(' ');

    long long i = 0;

    for(long long n : size) {
        file << "| N = " << setw(7) << left << size[i];

        for(long long j = 0; j < 3; j++) {
            if(j == 0) file << "| Separate Chaining | ";
            else if(j == 1) file << "|" << setw(34) << right << "| Double Hashing    | ";
            else file << "|" << setw(34) << right << "| Custom Probing    | ";

            for(long long k = 0; k < 2; k++) {
                for(long long m = 0; m < 2; m++) {
                    if(m == 0) file << defaultfloat << setw(5) << setprecision(5) << right << report[i][j][k][m] << "  ";
                    if(m == 1) file << fixed << setw(2) << setprecision(3) << " " << report[i][j][k][m] << "  ";
                }

                file << "| ";
            }

            file << endl; 
        }

        file << "|" << setw(69) << setfill('_') << "|" << endl;
        file << setfill(' ');
        i++;
    }

    file.close();
    return 0;
}
