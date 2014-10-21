#include "matrix.h"
#include "nvector.h"
#include "graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INDEX 1
#define FNAME "graphA.txt"
#define SIZE 32385

using namespace std;

int main(){
    /*(Un)comment the lines you (don't) wish to test!! (Vector)*/
    //Graph<NVector> gv; //Instantiates a graph with a vector
    //gv.LoadGraphFromFile(FNAME); //Loads graph from path
    //gv.GenerateGraphFile(); //Generates output file
    //int degree_v = gv.GetNodeDegree(INDEX); //Gets degree of specific node
    //int* neighbors_v = gv.GetNeighbors(INDEX); //Gets list of neighbors for a node
    //Runs a BFS on a specific node: [Begin]
    //bool* mark_v = new bool[SIZE];
    //for (int i = 0; i < SIZE; ++i){
    //    mark_v[i] = false;
    //}
    //gv.BFS(INDEX,mark_v);
    //delete [] mark_v;
    //Runs a BFS on a specific node: [End]
    //gv.DFS(INDEX); //Runs a DFS on a specific node
    //gv.GetConnectedComponents(); //Prints all connected components to a file
    //int diameter_v = gv.GetDiameter(); //Gets diameter
    //cout << "DONE" << endl;

    /*(Un)comment the lines you (don't) wish to test!! (Matrix)*/
    //Graph<Matrix> gm; //Instantiates a graph with a vector
    //gm.LoadGraphFromFile(FNAME); //Loads graph from path
    //gm.GenerateGraphFile(); //Generates output file
    //int degree_m = gm.GetNodeDegree(INDEX); //Gets degree of specific node
    //int* neighbors_m = gm.GetNeighbors(INDEX); //Gets list of neighbors for a node
    //Runs a BFS on a specific node: [Begin]
    //bool* mark_m = new bool[SIZE];
    //for (int i = 0; i < SIZE; ++i){
    //    mark_m[i] = false;
    //}
    //gm.BFS(INDEX,mark_m);
    //delete [] mark_m;
    //Runs a BFS on a specific node: [End]
    //gm.DFS(INDEX); //Runs a DFS on a specific node
    //gm.GetConnectedComponents(); //Prints all connected components to a file
    //int diameter_m = gm.GetDiameter(); //Gets diameter
    //cout << "DONE" << endl;

    return 0;

}
