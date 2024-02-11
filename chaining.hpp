#include<bits/stdc++.h>
using namespace std;

bool isPrime(long long num){
     if (num <= 1)
        return false;
    else if(num <= 3)
        return true;
    
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    
    for (size_t i = 5; i*i <= num; i = i+6){
        if (num % i == 0 || num % (i+2) == 0) 
            return false;
    }
    return true;
}

long long nextPrime(long long num){
    if (num <= 1)
        return 2;
    long long prime = num;
    bool found = false;
    while (!found){
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

long long previousPrime(long long num){
    if (num <= 1)
        return 2;
    long long prime = num;
    bool found = false;
    while (!found){
        prime--;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

class chainingHash{
   long long N, currentMaxLen, size, collisions, probes, chainLength;

   class Node{
    string key;
    long long value;
    Node* next;

  public:
    void setKey(string key) {this->key = key;}
    string getKey() {return key;}
    void setValue(long long value) {this->value = value;}
    long long getValue() {return value;}
    void setNext(Node* next) {this->next = next;}
    Node* getNext() {return next;}

    Node(string key = "", long long value = -1, Node* next = nullptr) {
        this->key = key;
        this->value = value;
        this->next = next;
    }  
   };

   Node** hashTable;

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
   
 public:
   chainingHash(long long N, long long chainLength ){
        this -> N = N;  //make sure this comes as a prime number
        this -> currentMaxLen = N;
        this -> size = 0;
        this -> chainLength = chainLength;
        this -> collisions = 0;
        this -> probes = 1;

        hashTable = new Node* [N];
        for (long long i = 0; i < N; i++)    
            hashTable[i] = nullptr;
   }

   chainingHash(const chainingHash& other){
        this -> N = other.N;
        this -> currentMaxLen = other.currentMaxLen;
        this -> size = other.size;
        this -> collisions = other.collisions;
        this -> probes = other.probes;
        this -> chainLength = other.chainLength;

        hashTable = new Node* [currentMaxLen];
        for (long long i = 0; i < currentMaxLen; i++) {
            if (other.hashTable[i] != nullptr)
                hashTable[i] = new Node(*(other.hashTable[i]));
            else hashTable[i] = nullptr;       
        }
   }

    ~chainingHash(){
        for (long long i = 0; i < N; i++) {
            Node *temp = hashTable[i];
            while (temp != nullptr) {
            Node *temp2 = temp;
            temp = temp->getNext();
            delete temp2;
            }
        }
        delete[] hashTable;
    }

   void resetCollisions() {
        collisions = 0;
   }

   long long getCollisions() {
        return collisions;
   }

   void resetProbes() {
        probes = 1;
   }

   long long getProbes() {
        return probes;
   }

   long long getSize() {
        return size;
   }

   void insert(string key, long long value){
        
        size++;
   }

   bool find(){

   }

   void reHash(long long n){
        //be sure that n here comes as a prime number
        long long oldMaxLen = currentMaxLen;
        Node **oldHashTable = hashTable;
        hashTable = new Node* [n];

        for (long long i = 0; i < n; i++)    
          hashTable[i] = nullptr;
        
        for(long long i = 0; i < oldMaxLen; i++){
            Node *temp = oldHashTable[i];
            while (temp != nullptr) {
                insert(temp->getKey(), temp->getValue());
                temp = temp->getNext();
            }
        }

        for (long long i = 0; i < oldMaxLen; i++){
          Node *temp = oldHashTable[i];
          while (temp != nullptr) {
               Node *temp2 = temp;
               temp = temp->getNext();
               delete temp2;
          }
        }
        delete[] oldHashTable;
   }

   void deleteNode(string key){
    
   }

};
