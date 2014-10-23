//MATRIX HEADER

#ifndef MATRIX_H
#define MATRIX_H

#define intptr int*

#include "graph.h"
#include <string>

using namespace std;

class Matrix{
    /*  Matrix is a data structure that represents a linearized square matrix of a certain order
     *  Memory usage is k*order*order, where order is the matrix's order and k is a constant for data type usage
     *  Using this data structure to represent graphs, we can check if two vertices are connected by searching
     *its lineXcolumn, which can be done in O(1), but returning a list of neighbors is, in the worst case, O(n)
     */
    int order; //Order of Matrix
    double** elements; //Vector for storing each line, each with an array for columns

public:
    bool d; //Destroy neighbors signal
    Matrix(); //Default constructor
    Matrix(const string fname, intptr &n_degree, int &n, int &m, int &d_max, bool w); //Graph<Matrix> Constructor call
    ~Matrix(); //Default destructor
    int* GetNeighbors(const int index, const int degree); //Get Neighbors for vertice 'index'
    Tuple<int,double>* GetSides(int index, int degree); //Get sides incident on node
};

#endif // MATRIX_H
