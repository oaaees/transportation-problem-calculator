#include <iostream>
#include <fstream>
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

void balance_cost_matrix(vector<vector<int>> &cost_matrix, vector<int> &supply, vector<int> &demand){
    int sum_supply = 0, sum_demand = 0;

    for(int x : supply){
        sum_supply += x;
    }

    for(int x : demand){
        sum_demand += x;
    }

    if(sum_supply == sum_demand) return;

    if(sum_supply > sum_demand){
        for (int i = 0; i < cost_matrix.size(); i++){
            cost_matrix[i].push_back(0);
        }
        demand.push_back(sum_supply - sum_demand);
    } else {
        cost_matrix.push_back(vector<int>(cost_matrix[0].size(), 0));
        supply.push_back(sum_demand - sum_supply);
    }

    return;
}

vector<vector<int>> north_west_method(vector<vector<int>> &cost_matrix, vector<int> supply, vector<int> demand){
    int n = cost_matrix.size(), m = cost_matrix[0].size();
    vector<vector<int>> res(n, vector<int>(m, 0));

    int i = 0, j = 0;

    while( supply[n - 1] != 0 && demand[m - 1] != 0 ){
        if(supply[i] < demand[j]){
            res[i][j] = supply[i];
            demand[j] -= supply[i]; 
            supply[i] = 0;
        } else {
            res[i][j] = demand[j];
            supply[i] -= demand[j]; 
            demand[j] = 0;
        }

        if(supply[i]==0) i++;
        if(demand[j]==0) j++;
    }

    return res;
}

void printMatrix(vector<vector<int>> m){
    for(vector<int> x : m){
        for (int y : x){
            cout << y << " ";
        }
        cout << '\n';
    }
}

int calculate_cost(vector<vector<int>> &cost, vector<vector<int>> &res){
    int total_cost = 0;

    for(int i = 0; i < cost.size(); i++){
        for(int j = 0; j < cost[i].size(); j++){
            total_cost += cost[i][j] * res[i][j];
        }
    }

    return total_cost;
}

void getDataManual(vector<vector<int>> &cost_matrix, vector<int> &supply, vector<int> &demand);
void getDataFromFile(string filename,vector<vector<int>> &cost_matrix, vector<int> &supply, vector<int> &demand);

int main (int argc, char* argv[]){
    int n, m;
    vector<vector<int>> cost_matrix;
    vector<int> supply;
    vector<int> demand;

    if(argc == 2){
        getDataFromFile(argv[1],cost_matrix, supply, demand);
    } else {
        getDataManual(cost_matrix, supply, demand);
    }

    balance_cost_matrix(cost_matrix, supply, demand);
    vector<vector<int>> res_matrix = north_west_method(cost_matrix, supply, demand);

    printMatrix(res_matrix);
    int total_cost = calculate_cost(cost_matrix, res_matrix);

    cout << "with total cost: " << total_cost;

    return 0;
}

void getDataManual(vector<vector<int>> &cost_matrix, vector<int> &supply, vector<int> &demand){
    int n, m;
    cout << "How many origins will the problem have: ";
    cin >> n;
    cout << "How many destinations will the problem have: ";
    cin >> m;

    cost_matrix = getMatrix(n, m, "COST");
    supply = getVector(cost_matrix.size(), "SUPPLY", "origin ");
    demand = getVector(cost_matrix[0].size(), "DEMAND", "destination ");
}

void getDataFromFile(string filename,vector<vector<int>> &cost_matrix, vector<int> &supply, vector<int> &demand){
    int n, m;
    ifstream f;
    f.open(filename);
    f >> n >> m;
    cost_matrix = vector<vector<int>>(n, vector<int>(m, 0));
    supply = vector<int>(n, 0);
    demand = vector<int>(m, 0);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            f >> cost_matrix[i][j]; 
        }
    }

    for(int i = 0; i < n; i++){
        f >> supply[i];
    }

    for(int j = 0; j < m; j++){
        f >> demand[j];
    }

    f.close();
}