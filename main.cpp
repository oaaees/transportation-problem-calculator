#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getVector(int m, string name = "", string name2 = ""){
    vector<int> v(m, 0);

    for(int i = 0; i < m; i++){
        cout << "Enter " << name << " value for " << name2 << i+1 << ": ";
        cin >> v[i];
    }

    return v;
}

vector<vector<int>> getMatrix(int n, int m, string name = ""){
    vector<vector<int>> data(n);

    for(int i = 0; i < n; i++){
        data[i] = getVector(m, name, to_string(i+1)+"-");
    }

    return data;
}

int main (){
    int n = 0, m = 0; 
    cout << "How many origins will the problem have: ";
    cin >> n;
    cout << "How many destinations will the problem have: ";
    cin >> m;

    vector<vector<int>> cost_matrix = getMatrix(n, m, "cost");
    vector<int> supply = getVector(cost_matrix.size(), "supply", "origin ");
    vector<int> demand = getVector(cost_matrix[0].size(), "demand", "destination ");

    return 0;
}