//GRAPH HEADER

#ifndef GRAPH_H
#define GRAPH_H

#include "nvector.h"
#include "matrix.h"
#define intptr int*
#include <string>

template <class T>
struct Element{
    //Element of a linked list, used in queue and stack data structures
    T index; //Index of the element
    Element* next; //Pointer to next element

    Element(T n_index); //Start element given index
};

template <class T>
struct DoubleElement{
    //Element of a double linked list, used in double linked list structure
    T index; //Index of the element
    DoubleElement<T>* prev; //Pointer to previous element
    DoubleElement<T>* next; //Pointer to next element

    DoubleElement(T n_index); //Default constructor
};

template <class T>
struct Queue{
    //Data structure implementing a queue of Elements
    bool empty; //Stores if queue is empty
    Element<T>* first; //Stores pointer to queue's head
    Element<T>* last; //Stores pointer to queue's tail

    Queue(); //Instantiates queue will default elements
    ~Queue(); //Default destructor
    void Add(T index); //Adds Element with index given to the queue
    T Remove(); //Removes Element at the queue's head
};

template <class T>
struct Stack{
    //Data structure implementing a stack of Elements
    bool empty; //Index of element
    Element<T>* top; //Pointer to top of stack

    Stack(); //Instantiates stack will default elements
    ~Stack(); //Default destructor
    void Add(T index); //Adds Element with index given to the stack
    T Remove(); //Removes Element at stack's top
};

template <class T>
struct DoubleLinkedList{
    //Data structure implementing a double linked list
    int size; //List's size
    int max_size; //List's maximum size
    DoubleElement<T>* first; //Pointer to first element
    DoubleElement<T>* last; //Pointer to last element
    DoubleElement<T>** pointers; //Pointer array for each element
    //This allows access to a specific element in O(1)

    DoubleLinkedList(); //Default constructor
    void SetSize(const int n_size); //Fills list with n_size elements
    ~DoubleLinkedList(); //Default destructor
    void Add(T index); //Adds element to list
    void Remove(int index); //Removes element from list
};

struct ConnectedComponent{
    //Data structure for storing a graph's connected component
    int size; //Number of nodes
    int it; //Iterator
    int* nodes; //Array of nodes

    ConnectedComponent(); //Default constructor
    ConnectedComponent(int n_size); //Constructor with preset size
    ~ConnectedComponent(); //Default destructor
    bool operator >(ConnectedComponent &other); //Operator > for sorting
    void Add(int index); //Adds node to connected component
};

template <class T>
class LinkedList{
    //Data structure representing an ordered linked list
public:
    int size; //List's size
    Element<T>* first; //Pointer to first element
    Element<T>* last; //Pointer to last element

    LinkedList(); //Default constructor
    ~LinkedList(); //Default destructor
    void Add(T index); //Adds element to list
    T Remove(); //Removes first element from list
};

template <class T>
class Graph{
    //Represents a generic graph, with auxiliar data structure T, set by the user

    int m; //Number of edges
    int n; //Number of nodes
    double d; //Average node degree
    int d_max; //Max degree
    string fname; //Graph name for file handling
    int* degree_dist; //Degree distribution, degree_dist[0] contains no. of vertices with degree 0
    int* n_degree; //Array for storing each node's degree
    T* t; //Data structure for storing vertices and edges
    ConnectedComponent* FastBFS(const int index, DoubleLinkedList<int>* ll); //Private BFS for ConnectedComponents algorithm
    int VeryFastBFS(const int index); //Private BFS for Diameter algorithm
    void VeryFastDFS(const int index); //Private DFS for reasons

public:
    Graph(); //Default constructor

    ~Graph(); //Default destructor

    bool LoadGraphFromFile(const string path);
    //Loads graph from text file into a Vector or Matrix; Computes n, m and d
    //Fills n_degree with each node's degree
    //Returns 1 if success, 0 otherwise

    void GenerateGraphFile();
    //Generates output file for graph

    int GetNodeDegree(const int index);
    //Returns a node's degree

    int* GetNeighbors(const int index);
    //Returns a list of neighbors for vertex with index 'index'

    ConnectedComponent* BFS(const int index, bool* &mark = NULL, DoubleLinkedList<int>* ll = NULL);
    //Runs a BFS on the graph from starting node with index 'index', given mark vector
    //Writes a file with the spanning tree for the BFS
    //Returns an array with each node's respective parent
    //Root will have parent -1

    void DFS(const int index);
    //Runs a DFS on the graph from starting node with index 'index', given mark vector
    //Writes a file with the spanning tree for the DFS
    //Returns an array with each node's respective parent
    //Root will have parent -1

    void GetConnectedComponents();
    //Runs several BFS until every connected component is found
    //After each iteration, stores component in struct ConnectedComponent

    int GetDiameter();
    //Runs a BFS on every node, returning the deepest level found among all BFS's.
    //Complexity is O(n^2)
};

#endif // GRAPH_H
