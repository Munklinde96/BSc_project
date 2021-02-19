#include "hoved.h"
#include "graph.h"
#ifndef SAMPLER_H
#define SAMPLER_H

using namespace std;

vector<vector<vector<int>>> sample(Graph g, int number) {
    default_random_engine eng{static_cast<long unsigned int>(time(0))};
    uniform_real_distribution<> distr(0, 1);
    vector<vector<double>> probs = g.probs;
    vector<vector<int>> adjList = g.adjList;
    vector<vector<vector<int>>> samples (number, vector<vector<int>>(adjList.size()));
    for (int n = 0; n < number; n++){
        for(int i = 0 ; i < adjList.size() ; i++) {
            vector<int> vertex = adjList[i];
            for (int j = 0; j < vertex.size() ; j++){
                if (i <= vertex[j]){
                    double prob = distr(eng);
                    if (prob < probs[i][j]){
                        samples[n][i].push_back(vertex[j]);
                        samples[n][vertex[j]].push_back(i);
                    }
                }
            }
        }
    }
    return samples;
}
#endif
