#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getVector(int m, string name = "", string name2 = ""){
    vector<int> v(m, 0);
    cout << '\n';
    for(int i = 0; i < m; i++){
        cout << "Enter " << name << " value for " << name2 << i+1 << ": ";
        cin >> v[i];
    }

    return v;
}

vector<vector<int>> getMatrix(int n, int m, string name = ""){
    vector<vector<int>> data(n);

    for(int i = 0; i < n; i++){
        data[i] = getVector(m, name, "cell " + to_string(i+1) + "-");
    }

    return data;
}

vector<vector<int>> north_west_method(vector<vector<int>> cost_matrix, vector<int> supply, vector<int> demand){
    int n = cost_matrix.size(), m = cost_matrix[0].size();
    vector<vector<int>> res(n, vector<int>(m, 0));

    int i = 0, j = 0;

    while( supply[n - 1] != 0 && demand[m - 1] != 0 ){
        if(supply[i] < demand[j]){
            res[i][j] = supply[i];
            demand[j] -= supply[i]; 
            supply[i] = 0;
        } else if (supply[i] > demand[j]) {
            res[i][j] = demand[j];
            supply[i] -= demand[j]; 
            demand[j] = 0;
        } else {
            res[i][j] = supply[i];
            supply[i] = 0;
            demand[j] = 0;   
        }

        if(supply[i]==0) i++;
        if(demand[j]==0) j++;
    }

    return res;
}

int main (){
    int n = 0, m = 0; 
    cout << "How many origins will the problem have: ";
    cin >> n;
    cout << "How many destinations will the problem have: ";
    cin >> m;

    vector<vector<int>> cost_matrix = getMatrix(n, m, "COST");
    vector<int> supply = getVector(cost_matrix.size(), "SUPPLY", "origin ");
    vector<int> demand = getVector(cost_matrix[0].size(), "DEMAND", "destination ");

    vector<vector<int>> res_matrix = north_west_method(cost_matrix, supply, demand);

    return 0;
}