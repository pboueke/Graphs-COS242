//NVECTOR HEADER

#ifndef NVECTOR_H
#define NVECTOR_H

#include "graph.h"
#include <string>

#define intptr int*

using namespace std;

class NVector{
    /*  NVector is a data structure similar to a boolean matrix of integer indexing of lines and columns
     *  Unlike a matrix, this structure stores for each 'line' an array of columns which would have a TRUE
     *marking for combination lineXcolumn.
     *  Memory usage is, in the wost case scenario of a fully TRUE matrix, k*order*order, where order is
     *how many 'lines' a matrix would have, and k is a constant to differ int and bool memory usage.
     *  Using this data structure to represent graphs, we can check if two vertices are connected by searching
     *its list of neighbors, which can be either O(n) if not ordered, and O(logn) if ordered.
     */
    int size; //Stores how many elements are inside the list
    Tuple<int,double>** neighbors; //Stores each vertex's neighbors

public:
    bool d; //Destroy neighbors signal
    NVector(); //Default constructor
    NVector(string fname, intptr &n_degree, int &n, int &m, int &d_max, bool w); //Graph<Vector> Constructor call
    ~NVector(); //Default destructor
    int* GetNeighbors(const int index, const int degree); //Get Neighbors for vertice 'index'
    Tuple<int,double>* GetSides(int index, int degree);
};

#endif //NVECTOR_H
