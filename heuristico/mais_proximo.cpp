#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct cidade {
    int id;
    double x;
    double y;
};

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
    bool fim = 0;
    int index = 0;
    int cacheIndex = 0;
    double totalDist = 0;
    vector<int> cidadesVerificadas;
    cidadesVerificadas.push_back(0);
    while(fim == 0){
        double minDist = 0;
        for(int i = 1; i < numCidades; i++){
            bool found = (find(cidadesVerificadas.begin(), cidadesVerificadas.end(), i) != cidadesVerificadas.end());
            if(i != index){
                double dist = pow(pow(cidades[index].x - cidades[i].x, 2) + pow(cidades[index].y - cidades[i].y, 2), 0.5);
                if(minDist == 0 and found != 1){
                    minDist = dist;
                    cacheIndex = i;
                } else {
                    if(dist < minDist and found != 1) {
                        minDist = dist;
                        cacheIndex = i;
                    }
                }
            }
        }
        if(cidadesVerificadas.size() == cidades.size()){
            fim = 1;
        } else {
            index = cacheIndex;
            cidadesVerificadas.push_back(index);
            totalDist += minDist;
        }
    }
    int ultimaCidade = cidadesVerificadas[cidadesVerificadas.size()-1];
    double dist = pow(pow(cidades[0].x - cidades[ultimaCidade].x, 2) + pow(cidades[0].y - cidades[ultimaCidade].y, 2), 0.5);
    totalDist += dist;
    cout << totalDist << " " << 0 << endl;
    for(int i = 0; i < numCidades; i++){
        cout << cidadesVerificadas[i] << " ";
    }
    cout << endl;
    

    return 0;
}