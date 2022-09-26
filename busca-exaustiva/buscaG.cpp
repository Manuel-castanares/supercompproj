#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdlib>

using namespace std;

struct cidade {
    int id;
    double x;
    double y;
};

vector<int> final;
float melhor = 0;

vector<int> busca(vector<cidade> cidades, vector<int> used, int numCidades){
    if(used.size() == numCidades){
        float totalDist = 0;
        double dist = 0;
        for(int i = 0; i < numCidades-1; i++){
            dist = pow(pow(cidades[used[i]].x - cidades[used[i+1]].x, 2) + pow(cidades[used[i]].y - cidades[used[i+1]].y, 2), 0.5);
            totalDist += dist;
        }
        dist = pow(pow(cidades[used[0]].x - cidades[used[numCidades-1]].x, 2) + pow(cidades[used[0]].y - cidades[used[numCidades-1]].y, 2), 0.5);
        totalDist += dist;
        if(melhor == 0){
            melhor = totalDist;
            final = used;
        } else {
            if(totalDist < melhor){
                melhor = totalDist;
                final = used;
            }
        }
        return used;
    } 
    vector<int> result;
    for(int i = 0; i < numCidades; i++){
        if(i == 0){
            bool found = (find(used.begin(), used.end(), cidades[i].id) != used.end());
            if(!found){
                used.push_back(cidades[i].id);
            }
        } else {
            bool found = (find(used.begin(), used.end(), cidades[i].id) != used.end());
            if(!found){
                used.push_back(i);
                result = busca(cidades, used, numCidades);
                used.pop_back();
            }
        }
    }
    return used;
}

int main(){
    int numCidades;
    cin >> numCidades;
    vector<cidade> cidades;
    for(int i = 0; i < numCidades; i++){
        cidade novo;
        novo.id = i;
        double texto;
        cin >> texto;
        novo.x = texto;
        cin >> texto;
        novo.y = texto;
        cidades.push_back(novo);
    }
    vector<int> used;
    busca(cidades, used, numCidades);
    cout << melhor << " " << 1 << endl;
    for(int i = 0; i < numCidades-1; i++){
        cout << final[i] << " ";
    }
    cout << final[numCidades-1] << endl;

    return 0;
};