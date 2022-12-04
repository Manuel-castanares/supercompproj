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
        totalDist += pow(pow(route[i].x - route[i+1].x, 2) + pow(route[i].y - route[i+1].y, 2), 0.5);
    }
    totalDist += pow(pow(route[0].x - route[numCidades-1].x, 2) + pow(route[0].y - route[numCidades-1].y, 2), 0.5);
    return totalDist;
}

float menorDist(vector<cidade> route, vector<int> ordem, int numCidades){
    bool check = true;
    vector<cidade> orderedRoute;
    for(int i = 0; i < numCidades; i++){
        orderedRoute.push_back(route[ordem[i]]);
    }
    float minDist = Dist(orderedRoute, numCidades);
    int index = 0;
    float DistTemp = 0;
    vector<cidade> routeCopy;
    int temp = 0;
    while(check){
        if(index < numCidades-1){
            routeCopy = orderedRoute;
            routeCopy[index+1] = orderedRoute[index];
            routeCopy[index] = orderedRoute[index+1];
            temp = ordem[index+1];
            ordem[index+1] = ordem[index];
            ordem[index] = temp;
            DistTemp = Dist(routeCopy, numCidades);
            if(DistTemp < minDist){
                minDist = DistTemp;
                orderedRoute = routeCopy;
            } else {
                temp = ordem[index+1];
                ordem[index+1] = ordem[index];
                ordem[index] = temp;
            }
        } else {
            check = false;
        }
        index += 1;
    }
    return minDist;
}

vector<int> menorRoute(vector<cidade> route, vector<int> ordem, int numCidades){
    bool check = true;
    vector<cidade> orderedRoute;
    for(int i = 0; i < numCidades; i++){
        orderedRoute.push_back(route[ordem[i]]);
    }
    float minDist = Dist(orderedRoute, numCidades);
    int index = 0;
    float DistTemp = 0;
    vector<cidade> routeCopy;
    int temp = 0;
    while(check){
        if(index < numCidades-1){
            routeCopy = orderedRoute;
            routeCopy[index+1] = orderedRoute[index];
            routeCopy[index] = orderedRoute[index+1];
            temp = ordem[index+1];
            ordem[index+1] = ordem[index];
            ordem[index] = temp;
            DistTemp = Dist(routeCopy, numCidades);
            if(DistTemp < minDist){
                minDist = DistTemp;
                orderedRoute = routeCopy;
            } else {
                temp = ordem[index+1];
                ordem[index+1] = ordem[index];
                ordem[index] = temp;
            }
        } else {
            check = false;
        }
        index += 1;
    }
    vector<int> final;
    //cerr << "local: " << minDist << " ";
    for(int e = 0; e < numCidades; e++){
        //cerr << orderedRoute[e].id << " ";
        final.push_back(orderedRoute[e].id);

    }
    //cerr << endl;
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
    float resultFinal;
    float resultTemp;
    int indexOrdem;
    #pragma omp parallel
    {
        #pragma omp for private(resultTemp)
        for(int i = 0; i < numCidades*10; i++){
            if(i == 0){
                resultFinal = menorDist(cidades, ordens[i], numCidades);
                indexOrdem = i;
            }
            else {
              resultTemp = menorDist(cidades, ordens[i], numCidades);
              if(resultTemp < resultFinal){
                #pragma omp critical
                {
                  if(resultTemp < resultFinal){
                    resultFinal = resultTemp;
                    indexOrdem = i;
                  }
                }
              }
            }
        }
    }
    vector<int> route = menorRoute(cidades, ordens[indexOrdem], numCidades);
    cout << resultFinal << " " << 0 << endl;
    for(int i = 0; i < numCidades; i++){
        cout << route[i] << " ";
    }
    cout << endl;


    return 0;
}
