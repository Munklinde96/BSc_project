#include "hoved.h"
#include "graph.h"

#ifndef UTILITY_H
#define UTILITY_H

using namespace std;

// https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/ 
// return: sets af sets for hvert CC call
void DFS(int v, vector<bool> *visited, vector<int> *component, vector<vector<int>> *sample)
{
    // Mark the current node as visited and print it
    (*visited)[v] = true;
    // cout << v << " ";
    (*component).push_back(v);
    // Recur on all adjacent vertices
    for(auto u : (*sample)[v]){
        if(!(*visited)[u]){
            DFS(u, visited, component, sample);
        }
    }
}
// https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/ 
// Method to print connected components in an undirected graph
vector<vector<int>> connectedComponents(vector<vector<vector<int>>> *samples)
{
    vector<vector<int>> vectorOfComponents;
    for (int i = 0; i < (*samples).size(); i++){
        vector<vector<int>> sample = (*samples)[i];
        vector<bool> visited;
        int numNodes = (sample).size();
        // Mark all the vertices as not visited
        visited = vector<bool> (numNodes);
        for (int n = 0; n < numNodes; n++) {
            vector<int> component;
            if (visited[n] == false) {
                // print all reachable vertices from n
                DFS(n, &visited, &component, &sample);
                // cout << "\n";
                vectorOfComponents.push_back(component);
            } 
        }
        visited.clear();
    }
    return vectorOfComponents;
}

vector<vector<vector<int>>> sample(Graph g, int number) {
    default_random_engine eng(static_cast<long unsigned int>(time(0)));
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

set<set<int>> prune(set<set<int>> original) {
	bool foundSuperSet;
    set<set<int>> res = original;
	for (auto it = original.begin(); it != original.end(); it++){
		foundSuperSet = false;
		for (auto resultElem : original){
            if(foundSuperSet){
                break;
            }
			if(*it!=resultElem){
				if(includes(resultElem.begin(), resultElem.end(), it->begin(), it->end())){
					foundSuperSet = true;
                    break;
				}
			}
		}
		if(foundSuperSet){
			res.erase((*it));
		}
	}
	return res;
}

// https://www.geeksforgeeks.org/how-to-convert-a-vector-to-set-in-c/
// Function to convert Vector to Set 
set<int> convertToSet(vector<int> v) 
{ 
    // Declaring the set 
    // using range of vector 
    set<int> s(v.begin(), v.end()); 
  
    // Return the resultant Set 
    return s; 
} 

set<set<int>> convertFrequentToSets (vector<vector<vector<int>>> frequentList){
    set<set<int>> res;
    for (auto elem1:frequentList){
        for (auto elem2:elem1){
            set<int> temp = convertToSet(elem2);
            res.insert(convertToSet(elem2));
        }
    }
    return res;
}

bool DFSWithSubgraphCheck(int v, vector<bool> *visited, vector<vector<int>> *sample, set<int> *subgraph)
{
    // Mark the current node as visited and print it
    (*visited)[v] = true;
    // cout << v << " ";
    // Recur on all adjacent vertices
    for(auto u : (*sample)[v]){
        if((*subgraph).count(u) == 1 && !(*visited)[u]){
            DFSWithSubgraphCheck(u, visited, sample, subgraph);
        }
    }
    for(auto s: *subgraph){
        if(!(*visited)[s]) {
            return false;
        }
    }
    return true;
}

double subgraphReliability( vector<vector<vector<int>>> samples, set<int> subgraph){
    int counter = 0;
    for (auto G: samples){
        bool isInduced = isInducedConnectedComponent(G,subgraph);
        if (isInduced){
            counter++;
        }
    }
    double reliability = counter/samples.size();

}

bool isInducedConnectedComponent(vector<vector<int>> G, set<int> subgraph ){
    // find conneceted comp
    // check if subgraph is connected 

    // make new neighbor table with collumns from suvgraphs vertices
    // create new vector<vector<int>> with collumns from subgraph
    // pushback all G[subgraph] to new vector<vector<int>>
    vector<vector<int>> subG(subgraph.size());
    for (auto s: subgraph){
        subG.push_back(G[s]);
    }
    auto it = subgraph.begin();
    vector<bool> visited(subG.size());
    bool containsSubgraph = DFSWithSubgraphCheck(*it, &visited, &subG, &subgraph);
    return containsSubgraph;
}

#endif