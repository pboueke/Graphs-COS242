//NVECTOR CPP

#include "nvector.h"
#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

NVector::NVector(){
    //Default values for each variable are set on default constructor
    size = 0; //No elements
    d = false;
    neighbors = NULL; //Null pointer because of above
}

NVector::NVector(string fname, intptr &n_degree, int &n, int &m, int &d_max){
    //Constructor of NVector for conjunct usage with Graph class
    //Receives as const argument the filename to read from, which is enough to start NVector
    //Receives as reference arguments the graph's information, such as n, m, max degree and array of degrees
    //This way, we can initialize both the Graph and the data structure without repeating loops
//TODO: Sort infile
    d = false;
    int tmp,tmpn,count; //Temporary calc variables
    ifstream p;
    p.open(fname.c_str());
    p >> size; //First line is always equal to a graph's n value
    n = size;
    neighbors = new int*[size]; //Allocs memory for NVector's first order array
    n_degree = new int[size](); //Allocs memory for Graph's vertex degree array
    count = 0; //Will count the number of sides in the Graph
    while (true){
        //We limit the loop count to size*size because it will always be bigger than a graph's m value
        //Each for instance is the analysis of a single side
        p >> tmp; //Side's vertex A
        if (p.eof()) break;
        //This breaks out of the loop as there are no more sides to be read
        //It is done after a single read because you must actually read the eof character
        p >> tmpn; //Side's vertex B
        if (tmp == tmpn) continue;
        n_degree[tmp-1]+=1; //Increase vertex A's degree (Remember vertex indexing starts at 1)
        n_degree[tmpn-1]+=1; //Increase vertex B's degree
        count++; //Iterates side count
    }
    m = count;
    p.close();
    p.open(fname.c_str()); //Resets file reading to the beginning of file
    p >> size; //Trash reading
    int* aux = new int[size]; //Array of iterators for inserting things in neighbors[var], as neighbors is not a list, but an array
    d_max = 0; //Stores Graph's highest degree
    for (int i = 0; i < size; ++i){
        //This loop is used to declare every neighbors[i] according to each vertex's degree
        //Also used for initializing aux and computing d_max
        neighbors[i] = new int[n_degree[i]];
        aux[i] = 0;
        if (n_degree[i]>d_max) d_max = n_degree[i];
    }
    for (int i = 0; i < count; ++i){
        //This loop is used to fill NVector with actual data, repeats m times
        p >> tmp; //Side's vertex A
        p >> tmpn; //Side's vertex B
        if (tmp == tmpn) {--i; continue;}
        //Stores data in NVector, using aux[i] as an iterator
        neighbors[tmp-1][aux[tmp-1]] = tmpn;
        neighbors[tmpn-1][aux[tmpn-1]] = tmp;
        aux[tmp-1]++;
        aux[tmpn-1]++;
    }
    p.close();
    delete [] aux;
}

NVector::~NVector(){
    if (!neighbors){
    for (int i = 0; i < size; ++i){
        delete [] neighbors[i];
    }
    delete [] neighbors;
    }
}

int* NVector::GetNeighbors(const int index, const int degree){
    //This function returns in O(1) the list of neighbors for a given index
    //Argument degree is unused, but is present for compatibility with Graph class
    return neighbors[index-1];
}
