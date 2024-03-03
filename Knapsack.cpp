#include<bits/stdc++.h>
using namespace std;

// double knapsack(int wt[], double val[], int w, int n, vector<vector<int> > &dp){
//     for(int i = 1; i <= n; i++){
//         for(int j = 1; j <= w; j++){
//             int notTake = dp[i-1][j];
//             int take = -1;
            
//             if (wt[i-1] <= j){
//                 take = val[i-1] + dp[i-1] [j-wt[i-1]];
//             }
//             dp[i][j] = max(take, notTake);
//         }
//     }
//     return dp[n][w];
// }

double knapsack2(int wt[], double val[], int w, int n, vector<vector<int> > &dp, double maxVal){
    for (size_t i = 1; i <= maxVal; i++)
       dp[0][i] = 1e9;
   
    for (size_t i = 1; i <= n; i++){
        for (size_t j = 1; j <= maxVal; j++){
            dp[i][j] = min(dp[i-1][j], (j > val[i-1] ? dp[i-1][j-val[i-1]] : 0) + wt[i-1]);
        }
    }    
    return dp[n][maxVal];
}

pair<int,vector<int>> traverse(vector<vector<int> > &dp, int wt[], double val[]){
    vector<int>chosenItems;

    int i = dp.size()-1;
    int j = dp[0].size()-1;

    while(i > 0 && j > 0){
        if (dp[i][j] == dp[i-1][j]){
            i--;
        }
        else{
            chosenItems.push_back(i);
            j = j - val[i-1];
            i--;
        }
    }

    int usedWeight = 0;

    for (size_t i = 0; i < chosenItems.size(); i++){
        usedWeight += wt[chosenItems[i]-1];
    }

    return {usedWeight,chosenItems};
}

int main(){
    int n,w;
    double vmax = 0;
    cin>>n>>w;
    int wt[n];
    double val[n];
    for(int i=0;i<n;i++){
        cin>>val[i]>>wt[i];
        vmax = max(vmax,val[i]);
    }
    vector<vector<int> >dp(n+1,vector<int>(1,0)); 
    double maxVal = 0;

    //edit started here  
    vector<vector<int> >dp2(n+1,vector<int>(2,0));

    int prevWeight = 0, newWeight = 0;
    
    double inVal = 1;
    while (newWeight = knapsack2(wt,val,w,n,dp2,inVal) < w){
        prevWeight = newWeight;
        inVal++;

        dp.clear();
        dp.resize(n+1,vector<int>(inVal,0));
        dp = dp2;

        dp2.clear();
        dp2.resize(n+1,vector<int>(inVal+1,0));
    }
    maxVal = inVal-1;
    cout<<"Original Instance: \n";
    cout<<"Answer: "<<maxVal<<"\n";

    //int minWeight = knapsack2(wt,val,w,n,dp2,maxVal);
    //cout<<"Answer: "<<minWeight<<"\n";

    // pair<int,vector<int>> result = traverse(dp,wt,val);
    pair<int,vector<int>> result = traverse(dp,wt,val);
    
    cout<<"Used Weight: "<<result.first<<endl;

    cout<<"Indices: ";

    for (size_t i = 0; i < result.second.size(); i++){
        cout<<result.second[i]<<" ";
    }

    cout<<endl;

    double epsilon = 0.5;
    double theta = (epsilon * vmax) / (2*n);
    cout<<"\nTheta: "<<theta<<endl;

    double roundedVal[n];

    for (size_t i = 0; i < n; i++){
        roundedVal[i] = ceil(val[i] / theta) ;
    }
    
    // dp.clear();
    // dp.resize(n+1,vector<int>(w+1,0));

    // double reducedMaxVal = knapsack(wt,roundedVal,w,n,dp);
    // cout<<"Answer of Reduced Instance: "<<reducedMaxVal<<endl;
    // double reducedByTheta = reducedMaxVal* 1.0 * theta;
    // cout<<"Answer of Reduced Instance multiplied by theta: "<<reducedByTheta<<endl;
    // dp2.clear();
    // dp2.resize(n+1,vector<int>(reducedMaxVal+1,0));
    // int reducedMinWeight = knapsack2(wt,roundedVal,w,n,dp2,reducedMaxVal);
    // result = traverse(dp2,wt,roundedVal);
    // cout<<"Indices: ";
    // for (size_t i = 0; i < result.second.size(); i++){
    //     cout<<result.second[i]<<" ";
    // }
    // cout<<endl;
    // double roundedUpValue = 0;
    // for (size_t i = 0; i < result.second.size(); i++){
    //     roundedUpValue += val[result.second[i]-1];
    // }
    // cout<<"Answer of Original Instance(Rounded Up): "<<roundedUpValue<<endl;
    // cout<<"Used Weight: "<<result.first<<endl;
    return 0;
}


