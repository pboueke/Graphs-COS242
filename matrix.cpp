//MATRIX CPP

#include "matrix.h"
#include <fstream>
#include <iostream>

#define intptr int*

using namespace std;

Matrix::Matrix(){
    //Default values for each variable, null matrix
    order = 0; //Order zero, no matrix at all
    d = true; //Destroys return of get neighbors
    elements = NULL; //Null pointer because of above
}

Matrix::Matrix(const string fname, intptr &n_degree, int &n, int &m, int &d_max){
    //Constructor of Matrix for conjunct usage with Graph class
    //Receives as const argument the filename to read from, which is enough to start Matrix
    //Receives as reference arguments the graph's information, such as n, m, max degree and array of degrees
    //This way, we can initialize both the Graph and the data structure without repeating loops
    d = true;
    int tmp,tmpn,count; //Temporary calc variables
    ifstream q;
    q.open(fname.c_str());
    q >> order; //First line is always equal to a graph's n value
    n = order;
    n_degree = new int[order](); //Allocs memory for Graph's vertex degree array
    elements = new bool[order*order](); //Allocs memory for Matrix's array
    count = 0;
    while (true){
        //We limit the loop count to size*size because it will always be bigger than a graph's m value
        //Each for instance is the analysis of a single side
        q >> tmp; //Side's vertex A
        if (q.eof()) break;
        //This breaks out of the loop as there are no more sides to be read
        //It is done after a single read because you must actually read the eof character
        q >> tmpn; //Side's vertex B
        //cout << tmp << " " << tmpn << endl;
        if (tmp == tmpn) continue;
        if (elements[(tmp-1)*order + (tmpn-1)]) continue;
        n_degree[tmp-1]+=1; //Increase vertex A's degree (Remember vertex indexing starts at 1)
        n_degree[tmpn-1]+=1; //Increase vertex B's degree        
        elements[(tmp-1)*order + (tmpn-1)] = true; //Sets data for side AB in matrix
        elements[(tmpn-1)*order + (tmp-1)] = true; //Sets data for side BA in matrix
        count++; //Iterates side count

    }
    q.close();
    //Computes max degree
    int max = 0;
    for (int i = 0; i < order; ++i){
        if (n_degree[i] > max) max = n_degree[i];
    }
    d_max = max;
    m = count;
}

Matrix::~Matrix(){
    if (!elements) delete [] elements;
}

int* Matrix::GetNeighbors(const int index, const int degree){
    //This function returns in O(n) the list of neighbors for a given index
    int* aux = new int[degree]; //Return
    int count = 0; //Neighbors found ; Iterator
    int it = 0;
    while (count < degree){
        //Stops when all enighbors are found, worst case is O(n)
        if (elements[(order*(index-1)) + it]){
            aux[count] = it+1; //Adds side to list of neighbors, remember indexing starts at 1
            count++;
        }
        it++;
    }
    return aux;
}
