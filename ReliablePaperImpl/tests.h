#include "hoved.h"
#include "utility.h"
#include "apriori.h"
#include "peeling.h"
#include "fastPeeling.h"

using namespace std;


void testPrune(){
	vector<vector<int>> vertices = {{1},{1,2}, {1,2,3}, {1,4},{2,3,5},{2,3}};
	vector<vector<int>> pruned = pruneVector(vertices);

	vector<vector<int>> expected = {{1,2,3}, {1,4},{2,3,5}};
	assert(pruned==expected);
}

void testConnectedComponnets(){
		string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file2.inf";
		// string graph_file = ".\\ReliablePaperImpl\\graph_file2.inf";
		//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file2.inf";
		int numEdges = 4;
		int numNodes = 6;
		Graph graph (numNodes,numEdges, graph_file);
		graph.readGraph();
		vector<vector<vector<int>>> samples = sample(graph, 3);
		vector<vector<int>> cC = connectedComponents(&samples);
    }

void testConnectedComponnets2(){
		string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file_certain.inf";
		// string graph_file = ".\\ReliablePaperImpl\\graph_file_certain.inf";
		//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file_certain.inf";
		int numEdges = 11;
		int numNodes = 11;
		Graph graph (numNodes,numEdges, graph_file);
		graph.readGraph();
		vector<vector<vector<int>>> samples = sample(graph, 1);

	    std::cout << "Started testConnectedComponnets: \n";

		vector<vector<int>> cC = connectedComponents(&samples);
		vector<vector<int>> expected = {{0, 1, 4, 3, 2, 5, 6}, {7,8}, {9,10}};

		assert(cC ==  expected);
    }

void testSampler(){
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file.inf";
    // string graph_file = ".\\ReliablePaperImpl\\graph_file.inf";
    //string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file.inf";
	Graph graph (7,10, graph_file);
	graph.readGraph();
	vector<vector<vector<int>>> samples = sample(graph, 5);

	assert(samples.size() == 5);
	for (int i = 0; i < samples.size(); i++){
		vector<vector<int>> world = samples[i];
		assert(world.size()==graph.adjList.size());
		for (int j = 0; j < samples[i].size(); j++){
			vector<int> worldVertex = world[j];
			vector<int> graphVertex = graph.adjList[j];
			assert(worldVertex.size() <= graphVertex.size());
		}
	}
	  std::cout << "Sampling test finished: \n";
}

void testApriori(){
	// string graph_file = ".\\ReliablePaperImpl\\graph_file_certain.inf";
	// //string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file_certain.inf";
	// int numEdges = 11;
	// int numNodes = 11;
	// Graph graph (numNodes,numEdges, graph_file);
	// graph.readGraph();
	// vector<vector<vector<int>>> samples = sample(graph, 1);

	// std::cout << "Started testConnectedComponnets: \n";

	// vector<vector<int>> cC = connectedComponents(&samples);
	vector<vector<int>> transactions = {
		{1,3,4}, {2,3,5}, {1,2,3,5}, {2,5}
	};
	set<set<int>> maximalFI = getMFI(transactions, 0.5, 4);
	set<set<int>> expected = {{2,3,5},{1,3}};
	//assert(maximalFI == expected);
}

void testReliability(){
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file_certain.inf";
	// string graph_file = ".\\ReliablePaperImpl\\graph_file_certain.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file_certain.inf";
	int numEdges = 11;
	int numNodes = 11;
	Graph graph (numNodes,numEdges, graph_file);
	graph.readGraph();
	vector<vector<vector<int>>> samples = sample(graph, 2);
	set<int> subgraph = {0,1};

	double reliability = subgraphReliability(samples, subgraph);
	assert(reliability == 1);
}

//TODO test subgraph DFS
void testSubgraphDFS(){
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file_certain.inf";
	// string graph_file = ".\\ReliablePaperImpl\\graph_file_certain.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file_certain.inf";
	int numEdges = 11;
	int numNodes = 11;
	Graph graph (numNodes,numEdges, graph_file);
	graph.readGraph();
	vector<vector<vector<int>>> samples = sample(graph, 1);
	
}

void testConnectedComponentsSubgraph(){
    // vector<vector<int>> components = connectedComponentsSubgraph(&graphSamples, m);
}


void testPeeling(){
	// string graph_file = ".\\ReliablePaperImpl\\graph_file2.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file2.inf";
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file_certain.inf";
	set<set<int>> res = runPeeling(graph_file, 11, 11, 1, 0.5, 0);
	set<set<int>> expected = {{0, 1, 4, 3, 2, 5, 6}, {7,8}, {9,10}};
	assert(res == expected);
}

void testFastPeeling(){
	// string graph_file = ".\\ReliablePaperImpl\\graph_file2.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file2.inf";
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file_certain.inf";
	set<set<int>> resPeeling = runPeeling(graph_file, 11, 11, 1, 0.5, 0);
	set<set<int>> resFastPeeling = runFastPeeling(graph_file, 11, 11, 1, 0.5);
	set<set<int>> expected = {{0, 1, 4, 3, 2, 5, 6}, {7,8}, {9,10}};
	assert(resPeeling == expected);
	assert(resPeeling == resFastPeeling);
}

void testSetSorting(){
	set<set<int>> unSorted = {{1,2},  {6,7,8},{3,4,5}};
	set<int> tofind = {1,2,3};
	int count = unSorted.count(tofind);
	set<set<int>, customCompareLength> sorted;
	copy(unSorted.begin(), unSorted.end(), inserter(sorted, sorted.begin()));
	assert(sorted == sorted);
}
//TODO FIX result
void testPeelingNonDeterministic(){
	// string graph_file = ".\\ReliablePaperImpl\\graph_file2.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file2.inf";
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file3.inf";
	set<set<int>> res = runPeeling(graph_file, 7, 10, 100, 0.5, 0);
	set<set<int>> expected = {{0, 2, 3, 5}, {1}, {4, 6}};
	assert(res == expected);
}

// How is this test supposed to work? We sample from from an uncertain graph twice - We cannot expect them to be similar
void testFastPeelingNonDeterministic(){
	// string graph_file = ".\\ReliablePaperImpl\\graph_file2.inf";
	//string graph_file = "/Users/sebastianloeschcke/Desktop/6.semester/BSc/BSc_project/ReliablePaperImpl/graph_file2.inf";
	string graph_file = "C:\\Users\\chris\\Documents\\6. Semester\\Bachelor Project\\BSc_project\\ReliablePaperImpl\\graph_file3.inf";
	set<set<int>> res = runPeeling(graph_file, 7, 10, 100, 0.5, 0);
	set<set<int>> resFastPeeling = runFastPeeling(graph_file, 7, 10, 100, 0.5);
	set<set<int>> expected = {{0, 2, 3, 5}, {1}, {4, 6}};
	assert(res == resFastPeeling && res == expected); // How is this test supposed to work? We sample from from an uncertain graph twice - We cannot expect them to be similar 
	std::cout << "finished\n";

}

void testAll(){
    // testPrune();
	// testApriori();
	// testConnectedComponnets();
	// testConnectedComponnets2();
	// testReliability();
	// testSampler();
	// testPeeling();
	testPeelingNonDeterministic();
	// testSetSorting();
	// testFastPeeling();
	testFastPeelingNonDeterministic();
}

