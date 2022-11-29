#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdlib>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

using namespace std;

struct cidade {
    int id;
    double x;
    double y;
};

float Dist(cidade a, cidade b){
    float totalDist = 0;
    totalDist = pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
    return totalDist;
}

struct saxpy
{
    int *a;
    float *b;
    int c;
    saxpy(int *a_, float *b_, int c_) : a(a_), b(b_), c(c_) {};
    __host__ __device__
    float operator()(const int x) {
        int cont = x*c;
        float dist = 0;
        float melhorDist = 0;
        int temp = 0;
        bool check = true;
        for(int i = 0; i < (c-1); i++){
            melhorDist += b[a[cont+i]*c + a[cont+i+1]];
        }
        melhorDist += b[a[cont+(c-1)]*c + a[cont+0]];
        while(check){
            check = false;
            for(int e = 0; e < (c-1); e++){
                temp = a[cont+e+1];
                a[cont+e+1] = a[cont+e];
                a[cont+e] = temp;
                for(int i = 0; i < (c-1); i++){
                    dist += b[a[cont+i]*c + a[cont+i+1]];
                }
                dist += b[a[cont+(c-1)]*c + a[cont+0]];
                if(dist < melhorDist){
                    melhorDist = dist;
                    check = true;
                } else {
                    temp = a[cont+e+1];
                    a[cont+e+1] = a[cont+e];
                    a[cont+e] = temp; 
                }
                dist = 0;
            }
        }
        return melhorDist;
    }
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

    thrust::host_vector<float> Distancias(numCidades*numCidades);

    for(int i = 0; i < numCidades; i++){
        for(int e = 0; e < numCidades; e++){
            Distancias[(cidades[e].id*numCidades) + cidades[i].id] = Dist(cidades[i], cidades[e]);
        }
    }

    thrust::device_vector<float> gpuDist(numCidades*numCidades);

    gpuDist = Distancias;

    thrust::host_vector<int> ordens(numCidades*numCidades*10);
    srand(1);
    int counter = 0;
    int counterGlobal = 0;
    vector<int> randoms;
    for(int i = 0; i < numCidades*10; i++){
        while(counter < numCidades){
            int index = rand() % numCidades;
            bool found = (find(randoms.begin(), randoms.end(), index) != randoms.end());
            if(found != 1){
                randoms.push_back(index);
                ordens[counterGlobal] = index;
                counter += 1;
                counterGlobal += 1;
            }
        }
        randoms.clear();
        counter = 0;
    }

    thrust::device_vector<int> ordensGPU(numCidades*numCidades*10);

    ordensGPU = ordens;
    thrust::device_vector<float> data(numCidades*10);

    auto iter = thrust::make_counting_iterator(0);


    thrust::transform(iter, iter+numCidades*10, data.begin(), saxpy(thrust::raw_pointer_cast(ordensGPU.data()), thrust::raw_pointer_cast(gpuDist.data()), numCidades));

    float resultPrimeiro = data[0];

    float result = thrust::reduce(data.begin(), data.end(), resultPrimeiro, thrust::minimum<float>());

    cout << result << endl;

    return 0;
}