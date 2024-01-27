#include<bits/stdc++.h>
#include "Map.h"
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    Map<int,string> redBlackMap;
    int n;
    string str;

    cin >> str;
    while (!cin.eof()){
        if (str == "Clr"){ 
            if (redBlackMap.clear()) cout<<"successful\n";
            else cout<<"unsuccessful\n";
        } else if(str[0] == 'E' && str != "Em"){ 

        } else if(str[0] == 'I'){

        } else if(str == "Em"){
            if (redBlackMap.empty()) cout<<"yes\n";
            else cout<<"no\n";
        } else if(str[0] == 'F'){

        } else if(str[0] == 'S'){
            cout<<redBlackMap.size()<<endl;
        } else if(str == "Itr"){

        }
        cin >> str;
    }
    
    return 0;
}
