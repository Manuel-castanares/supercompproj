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

float Dist(vector<cidade> route, int numCidades){
    float totalDist = 0;
    for(int i = 0; i < numCidades-1; i++){
        double dist = pow(pow(route[i].x - route[i+1].x, 2) + pow(route[i].y - route[i+1].y, 2), 0.5);
        totalDist += dist;
    }
    double dist = pow(pow(route[0].x - route[numCidades-1].x, 2) + pow(route[0].y - route[numCidades-1].y, 2), 0.5);
    totalDist += dist;
    return totalDist;
}

vector<float> menorDist(vector<cidade> route, vector<int> ordem, int numCidades){
    bool check = true;
    vector<cidade> orderedRoute;
    for(int i = 0; i < numCidades; i++){
        orderedRoute.push_back(route[ordem[i]]);
    }
    float minDist = Dist(orderedRoute, numCidades);
    int index = 0;
    float DistTemp = 0;
    vector<cidade> routeCopy;
    while(check){
        if(index < numCidades-1){
            routeCopy = orderedRoute;
            routeCopy[index+1] = orderedRoute[index];
            routeCopy[index] = orderedRoute[index+1];
            DistTemp = Dist(routeCopy, numCidades);
            if(DistTemp < minDist){
                minDist = DistTemp;
                orderedRoute = routeCopy;
            }
        } else {
            check = false;
        }
        index += 1;
    }
    vector<float> final;
    final.push_back(minDist);
    cerr << "local: " << minDist << " ";
    for(int e = 0; e < numCidades; e++){
        cerr << orderedRoute[e].id << " ";
        final.push_back(orderedRoute[e].id);

    }
    cerr << endl;
    return final;
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

    vector<vector<int>> ordens;
    srand(1);
    int counter = 0;
    vector<int> randoms;
    for(int i = 0; i < numCidades*10; i++){
        while(counter < numCidades){
            int index = rand() % numCidades;
            bool found = (find(randoms.begin(), randoms.end(), index) != randoms.end());
            if(found != 1){
                randoms.push_back(index);
                counter += 1;
            }
        }
        ordens.push_back(randoms);
        randoms.clear();
        counter = 0;
    }

    vector<float> resultFinal;
    vector<float> resultTemp;
    for(int i = 0; i < numCidades*10; i++){
        resultTemp = menorDist(cidades, ordens[i], numCidades);
        if(i == 0){
            resultFinal = resultTemp;
        }
        else {
            if(resultTemp[0] < resultFinal[0]){
                resultFinal = resultTemp;
            }
        }
    }

    cout << resultFinal[0] << " " << 0 << endl;
    for(int i = 1; i <= numCidades; i++){
        cout << resultFinal[i] << " ";
    }
    cout << endl;


    return 0;
}