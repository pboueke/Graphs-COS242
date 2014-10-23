//GRAPH CPP

#include "graph.h"
#include "nvector.h"
#include "matrix.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//-------------------------------------------------------------------------------------

template <class T, class U>
Tuple<T,U>::Tuple() {}

template <class T, class U>
Tuple<T,U>::Tuple(T t, U u){
    a = t;
    b = u;
}

//-------------------------------------------------------------------------------------

template <class T>
Element<T>::Element(T n_index){
    index = n_index;
    next = NULL; //Can't set beforehand
}

//-------------------------------------------------------------------------------------

template <class T>
DoubleElement<T>::DoubleElement(T n_index){
    index = n_index;
    next = prev = NULL; //Can't set beforehand
}

//-------------------------------------------------------------------------------------

template <class T>
Queue<T>::Queue(){
    empty = true; //Queue starts empty
    first = NULL; //Null first element, there are none
    last = NULL; //Null last element, there are none
}

template <class T>
Queue<T>::~Queue(){
    //Empties queue
    while (!empty){
        Remove();
    }
}

template <class T>
void Queue<T>::Add(T index){
    Element<T>* e = new Element<T>(index); //Allocs memory for new element
    if (empty){
        first = e; //Sets new element as head
        last = e; //Sets new element as tail
        empty = false; //Unempties queue
    }
    else{
        last->next = e; //Links previous last element to new last element
        last = e; //Points queue's tail to new element
    }
}

template <class T>
T Queue<T>::Remove(){
    Element<T>* aux = first; //Auxiliar pointer for memory freeing
    T ind = first->index; //Gets index of removed element for returning such value
    first = first->next; //Sets next in queue as new head
    delete aux; //Memory freeing
    if (!first) empty = true; //If head is a NULL pointer, empties queue
    return ind;
}

//-------------------------------------------------------------------------------------

template <class T>
Stack<T>::Stack(){
    empty = true; //Stack starts empty
    top = NULL; //Null top element
}

template <class T>
Stack<T>::~Stack(){
    //Empties stack
    while (!empty){
        Remove();
    }
}

template <class T>
void Stack<T>::Add(T index){
    Element<T>* e = new Element<T>(index); //Allocs memory for new element
    if (empty){
        //In case stack is empty, sets top pointer to new element
        empty = false;
        top = e;
    }
    else{
        //Else, does above plus sets next element of new element as previous top
        e->next = top;
        top = e;
    }
}

template <class T>
T Stack<T>::Remove(){
    Element<T>* aux = top; //Auxiliar pointer for memory freeing
    T ind = top->index; //What to return
    top = top->next; //Sets top of stack to previous element
    delete aux;
    if (!top) empty = true; //Checks for NULL pointer
    return ind;
}

//-------------------------------------------------------------------------------------

template <class T>
LinkedList<T>::LinkedList(){
    size = 0;
    first = NULL;
}

template <class T>
LinkedList<T>::~LinkedList(){
    while (!size){
        Remove_Head();
    }
}

template <class T>
void LinkedList<T>::Add_Head(T index){
    Element<T>* e = new Element<T>(index);
    if (size) e->next = first;
    first = e;
    size++;
}

template <class T>
T LinkedList<T>::Remove_Head(){
    //Removes first element of list
    Element<T>* aux = first;
    T ind = first->index;
    first = first->next;
    delete aux;
    --size;
    return ind;
}

template <class T>
bool LinkedList<T>::Remove(T index){
    //Removes specific element
    Element<T>* prev = NULL;
    for (Element<T>* it = first; it != NULL; it = it->next){
        if (it->index == index){
            if (prev) prev->next = it->next;
            else first = it->next;
            delete it;
            --size;
            return true;
        }
        prev = it;
    }
    return false;
}

//-------------------------------------------------------------------------------------

template <class T>
Ordered_LinkedList<T>::Ordered_LinkedList(){
    size = 0;
    first = last = NULL;
}

template <class T>
Ordered_LinkedList<T>::~Ordered_LinkedList(){
    //Empties list
    while (!size){
        Remove_Head();
    }
}

template <class T>
void Ordered_LinkedList<T>::Add(T index){
    //Adds new element to list, keeping the order it was in
    Element<T>* e = new Element<T>(index);
    if (!size){
        first = e;
        last = e;
    }
    else if (e->index > first->index){
        e->next = first;
        first = e;
    }
    else{
        Element<T>* it_p = first; //Pointer to previous element
        for (Element<T>* it = first->next; it != NULL; it = it->next){
            //Iterator starts at first, ends at last-1 and next it is next element
            if (e->index > it->index){
                it_p->next = e;
                e->next = it;
                break;
            }
            it_p = it;
        }
        last->next = e;
        last = e;
    }
    ++size;
}

template <class T>
T Ordered_LinkedList<T>::Remove_Head(){
    //Removes first element of list
    Element<T>* aux = first;
    T ind = first->index;
    first = first->next;
    delete aux;
    --size;
    return ind;
}

template <class T>
bool Ordered_LinkedList<T>::Remove(T index){
    //Removes specific element
    Element<T>* prev = NULL;
    for (Element<T>* it = first; it != NULL; it = it->next){
        if (it->index == index){
            if (prev) prev->next = it->next;
            else first = it->next;
            delete it;
            --size;
            return true;
        }
        prev = it;
    }
    return false;
}

//-------------------------------------------------------------------------------------

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(){
    size = 0;
    first = last = NULL;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    while (!size){
        Remove_Head();
    }
}

template <class T>
void DoubleLinkedList<T>::Add_Head(T index){
    DoubleElement<T>* e = new DoubleElement<T>(index);
    if (size) {e->next = first; first->prev = e;}
    else last = e;
    first = e;
    size++;
}

template <class T>
void DoubleLinkedList<T>::Add_Tail(T index){
    DoubleElement<T>* e = new DoubleElement<T>(index);
    if (size) {e->prev = last; last->next = e;}
    else first = e;
    last = e;
    size++;
}

template <class T>
T DoubleLinkedList<T>::Remove_Head(){
    DoubleElement<T>* aux = first;
    T ind = first->index;
    first->next->prev = NULL;
    first = first->next;
    delete aux;
    --size;
    return ind;
}

template <class T>
T DoubleLinkedList<T>::Remove_Tail(){
    DoubleElement<T>* aux = last;
    T ind = last->index;
    last->prev->next = NULL;
    last = last->prev;
    delete aux;
    --size;
    return ind;
}

template <class T>
bool DoubleLinkedList<T>::Remove(T index){
    if (first->index == index) {Remove_Head(); return true;}
    else if (last->index == index) {Remove_Tail(); return true;}
    else {
        for (DoubleElement<T>* it = first->next; it != last; it = it->next){
            if (it->index == index){
                it->prev->next = it->next;
                it->next->prev = it->prev;
                delete it;
                --size;
                return true;
            }
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------

template <class T>
Degen_DoubleLinkedList<T>::Degen_DoubleLinkedList(){
    size = max_size = 0;
    first = last = NULL;
    pointers = NULL;
}

template <class T>
Degen_DoubleLinkedList<T>::~Degen_DoubleLinkedList(){
    //Empties list and frees memory
    while (size){
        Remove(first->index);
    }
    for (int i = 0; i < max_size; ++i){
        delete pointers[i];
    }
    delete [] pointers;
}

template <class T>
void Degen_DoubleLinkedList<T>::Fill(const int n_size){
    //Fills list with n_size elements, not exactly generic enough
    max_size = n_size;
    pointers = new DoubleElement<T>*[n_size];
    for (int i = 0; i < n_size; ++i){
        Add(i+1);
    }
}

template <class T>
void Degen_DoubleLinkedList<T>::Add(T index){
    //Adds new element to list, updates pointers
    DoubleElement<T>* e = new DoubleElement<T>(index);
    pointers[index-1] = e;
    if (!size){
        first = e;
        last = e;
    }
    else{
        last->next = e;
        e->prev = last;
        last = e;
    }
    ++size;
}

template <class T>
void Degen_DoubleLinkedList<T>::Remove(int index){
    //Removes element from list, updates pointers
    if (pointers[index-1]!=last) pointers[index-1]->next->prev = pointers[index-1]->prev;
    else last = pointers[index-1]->prev;
    if (pointers[index-1]!=first) pointers[index-1]->prev->next = pointers[index-1]->next;
    else first = pointers[index-1]->next;
    pointers[index-1] = NULL;
    --size;
}

//-------------------------------------------------------------------------------------

ConnectedComponent::ConnectedComponent(){
    size = it = 0;
    nodes = NULL;
}

ConnectedComponent::ConnectedComponent(int n_size){
    //Sets connected component to a fixed size
    size = n_size;
    it = 0;
    nodes = new int[n_size];
}

ConnectedComponent::~ConnectedComponent(){
    //delete [] nodes;
}

bool ConnectedComponent::operator >(ConnectedComponent &other){
    return size > other.size;
}

void ConnectedComponent::Add(int index){
    //Fills nodes array
    nodes[it] = index;
    ++it;
}

//-------------------------------------------------------------------------------------

template<class T>
Graph<T>::Graph(){
    //Default constructor sets every variable to default values
    n = m = d = d_max = 0;
    fname = "";
    n_degree = NULL;
    degree_dist = NULL;
    t = NULL;
}

template<class T>
Graph<T>::~Graph(){
    if (!n_degree) delete [] n_degree;
    if (!degree_dist) delete [] degree_dist;
    delete t;
}

template<class T>
bool Graph<T>::LoadGraphFromFile(const string path, bool weight){
    //Loads Graph from specified path, must call graph constructor from class T
    //If either class T isn't compatible or file is inxistent, returns false
    int sum = 0; //Used for computing average node degree
    w = weight; //Stores whether graph has weights or not
    fname = path; //Saves path used for this graph
    t = new T(path,n_degree,n,m,d_max,w);
    degree_dist = new int[d_max+1](); //Allocs d_max+1 because a node can have degree zero
    for (int i = 0; i < n; ++i){
        //Fills degree_dist and readies sum for d computing
        sum += n_degree[i];
        degree_dist[n_degree[i]]++;
    }
    d = (double)sum/n;
    cout << "n=" << n << endl;
    cout << "m=" << m << endl;
    return true;
}

template<class T>
void Graph<T>::GenerateGraphFile(){
    //Generates file containing graph information
    ofstream o;
    stringstream ss;
    string tmp;
    string path = "out-"+fname; //E.g.: "out-graph.txt"
    o.open(path.c_str());
    o << "n = " << n << "\n"; //No. of nodes
    o << "m = " << m << "\n"; //No. of sides
    o << "d_medio = " << d << "\n"; //Average degree
    for (int i = 0; i < d_max+1; ++i){
        ss << "Degree=" << i << ": ";
        ss << (double)degree_dist[i]/n;
        ss >> tmp;
        o << tmp << (double)degree_dist[i]/n << "\n"; //Degree distribution
        ss.str("");
    }
    o << endl;
    o.close();
}

template<class T>
int Graph<T>::GetNodeDegree(const int index){
    //Returns a node's degree in O(1)
    return n_degree[index-1];
}

template<class T>
int* Graph<T>::GetNeighbors(const int index){
    //Returns a node's neighbor list, complexity varies between data types
    return t->GetNeighbors(index,n_degree[index-1]);
}

template<class T>
ConnectedComponent* Graph<T>::BFS(const int index, bool* &mark, Degen_DoubleLinkedList<int>* ll){
    bool m = false;
    if (!mark) {mark = new bool[n]; m = true;}
    int* parent = new int[n];
    int* level = new int[n]; //Stores each node's levels
    for (int i = 0; i < n; ++i){
        parent[i] = 0;
        level[i] = -1;
    }
    int aux,tmp,count; //Auxiliary variables
    int* neighbors; //Return
    stringstream ss;
    string path;
    Queue<int> q; //Define empty queue;
    parent[index-1] = -1; //Root has parent -1 and level 0
    level[index-1] = 0; //Remember indexing starts at 1
    if (m) mark[index-1] = true;
    q.Add(index);
    if (ll) {ll->Remove(index);}
    count = 1;
    while (!q.empty){
        aux = q.Remove();
        neighbors = GetNeighbors(aux);
        for (int i = 0; i < n_degree[aux-1]; ++i){
            //aux and tmp store nodes' indexes, which start at 1, so we have to subtract 1 from both
            tmp = neighbors[i]-1;
            if (!parent[tmp]){
                //Node is considered not marked if its value is 0 in mark
                parent[tmp] = aux;
                if (ll) {ll->Remove(tmp+1);}
                level[tmp] = level[aux-1]+1; //Level of a child is one more than its parent's
                q.Add(tmp+1);
                ++count;
                if (m) mark[tmp] = true;
            }
        }
        if (t->d) delete [] neighbors;
    }
    ConnectedComponent* cc = new ConnectedComponent(count);
    ss << "bfs/bfs-" << index << "-" << fname;
    ss >> path;
    ofstream o;
    o.open(path.c_str());
    o << "Data_Organized_as:_Index_Parent_Level" << "\n";
    for (int i = 0; i < n; ++i){
        o << i+1 << " " << parent[i] << " " << level[i] << "\n"; //E.g.: "281 22 4"
        if (m && mark[i]) cc->Add(i+1);
        else if (parent[i]) cc->Add(i+1);
    }
    o << endl;
    o.close();
    delete [] parent;
    delete [] level;
    return cc;
}

template <class T>
ConnectedComponent* Graph<T>::FastBFS(const int index, Degen_DoubleLinkedList<int>* ll){
    bool* mark = new bool[n];
    for (int i = 0; i < n; ++i){
        mark[i] = false;
    }
    int tmp,aux,count;
    int* neighbors;
    Queue<int> q;
    mark[index-1] = true;
    q.Add(index);
    ll->Remove(index);
    count = 1;
    while (!q.empty){
        aux = q.Remove();
        neighbors = GetNeighbors(aux);
        for (int i = 0; i < n_degree[aux-1]; ++i){
            tmp = neighbors[i]-1;
            if (!mark[tmp]){
                mark[tmp] = true;
                ll->Remove(tmp+1);
                q.Add(tmp+1);
                count++;
            }
        }
        if (t->d) delete [] neighbors;
    }
    ConnectedComponent* cc = new ConnectedComponent(count);
    for (int i = 0; i < n; ++i){
        if (mark[i]) cc->Add(i+1);
    }
    delete [] mark;
    return cc;
}

template <class T>
int Graph<T>::VeryFastBFS(const int index){
    bool* mark = new bool[n];
    int* level = new int[n];
    int tmp,aux;
    int* neighbors;
    for (int i = 0; i < n; ++i){
        mark[i] = false;
        level[i] = -1;
    }
    Queue<int> q;
    mark[index-1] = true;
    level[index-1] = 0;
    q.Add(index);
    while (!q.empty){
        aux = q.Remove();
        neighbors = GetNeighbors(aux);
        for (int i = 0; i < n_degree[aux-1]; ++i){
            tmp = neighbors[i]-1;
            if (!mark[tmp]){
                mark[tmp] = true;
                level[tmp] = level[aux-1]+1;
                q.Add(tmp+1);
            }
        }
        if (t->d) delete [] neighbors;
    }
    tmp = 0;
    for (int i = 0; i < n; ++i){
        if (level[i]>tmp) tmp = level[i];
    }
    delete [] mark;
    delete [] level;
    return tmp;
}

template<class T>
void Graph<T>::DFS(const int index){
    int* mark = new int[n];
    int* level = new int[n];
    for (int i = 0; i < n; ++i){
        mark[i] = 0;
        level[i] = -1;
    }
    int aux,tmp;
    int* neighbors;
    stringstream ss;
    string path;
    Stack<int> s;
    s.Add(index);
    mark[index-1] = -1;
    level[index-1] = 0;
    while (!s.empty){
        aux = s.Remove();
        neighbors = GetNeighbors(aux);
        for (int i = 0; i < n_degree[aux-1]; ++i){
            tmp = neighbors[i]-1;
            if (!mark[tmp]){
                mark[tmp] = aux;
                level[tmp] = level[aux-1]+1;
                s.Add(tmp+1);
            }
        }
        if (t->d) delete [] neighbors;
    }
    ss << "dfs/dfs-" << index << "-" << fname;
    ss >> path;
    ofstream o;
    o.open(path.c_str());
    o << "Data_Organized_as:_Index_Parent_Level" << "\n";
    for (int i = 0; i < n; ++i){
        o << i+1 << " " << mark[i] << " " << level[i] << "\n"; //E.g.: "281 22 4"
    }
    o << endl;
    o.close();
    delete [] mark;
    delete [] level;
}

template <class T>
void Graph<T>::VeryFastDFS(const int index){
    bool mark[n];
    for (int i = 0; i < n; ++i){
        mark[i] = false;
    }
    int aux,tmp;
    int* neighbors;
    Stack<int> s;
    s.Add(index);
    mark[index-1] = true;
    while (!s.empty){
        aux = s.Remove();
        neighbors = GetNeighbors(aux);
        for (int i = 0; i < n_degree[aux-1]; ++i){
            tmp = neighbors[i]-1;
            if (!mark[tmp]){
                mark[tmp] = true;
                s.Add(tmp+1);
            }
        }
        if (t->d) delete [] neighbors;
    }
}

template<class T>
void Graph<T>::GetConnectedComponents(){
    Ordered_LinkedList<ConnectedComponent>* ll = new Ordered_LinkedList<ConnectedComponent>;
    Degen_DoubleLinkedList<int>* dll = new Degen_DoubleLinkedList<int>;
    dll->Fill(n);
    int aux = n;
    ConnectedComponent* ccptr;
    while (aux > 0){
        //Runs BFS until dll is empty
        ccptr = FastBFS(dll->first->index,dll);
        ll->Add(*ccptr);
        aux = dll->size;
    }
    delete dll;
    ofstream o;
    string path = "components-"+fname;
    o.open(path.c_str());
    ConnectedComponent cc;
    while (ll->size){
        cc = ll->Remove_Head();
        o << "CONNECTED COMPONENT OF SIZE " << cc.size << "\n";
        for (int i = 0; i < cc.size; ++i){
            o << cc.nodes[i] << "\n";
        }
    }
    o << endl;
    o.close();
}

template <class T>
int Graph<T>::GetDiameter(){
    int tmp;
    int diameter = 0;
    for (int i = 0; i < n; ++i){
        //Runs BFS for every node
        tmp = VeryFastBFS(i+1);
        if (tmp > diameter) diameter = tmp;
    }
    return diameter;
}


template class Graph<NVector>;
//template class Graph<Matrix>;
template class Ordered_LinkedList<int>;
template class Degen_DoubleLinkedList<int>;
template class Tuple<int,double>;
//http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
