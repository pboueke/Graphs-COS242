//GRAPH CPP

#include "graph.h"
#include "nvector.h"
#include "matrix.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INFINITY 10000000

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
HeapElement<T>::HeapElement(T n_index){
    pos = -1; //Error control
    index = n_index;
    parent = left = right = NULL; //Can't set beforehand
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
    //List starts empty
    size = 0;
    first = last = NULL;
}

template <class T>
LinkedList<T>::~LinkedList(){
    //Empties list
    while (size){
        Remove_Head();
    }
}

template <class T>
void LinkedList<T>::Add_Head(T index){
    //Adds a new element to beginning of list
    Element<T>* e = new Element<T>(index);
    if (size) e->next = first; //Prevents crashing when list was empty
    else last = e;
    first = e;
    size++;
}

template <class T>
void LinkedList<T>::Add_Tail(T index){
    //Adds a new element to end of list
    Element<T>* e = new Element<T>(index);
    if (size) last->next = e;
    else first = e;
    last = e;
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
    if (!size) last = NULL;
    return ind;
}

template <class T>
bool LinkedList<T>::Remove(T index){
    //Removes specific element
    Element<T>* prev = NULL;
    for (Element<T>* it = first; it != NULL; it = it->next){
        //Iterates list in search of specific key
        //In case of identical keys, removes first iteration
        if (it->index == index){
            if (prev) prev->next = it->next;
            else first = it->next;
            if (!it->next) last = prev;
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
    //List starts empty
    size = 0;
    first = last = NULL;
}

template <class T>
Ordered_LinkedList<T>::~Ordered_LinkedList(){
    //Empties list
    while (size){
        Remove_Head();
    }
}

template <class T>
void Ordered_LinkedList<T>::Add(T index){
    //Adds new element to list, keeping the order it was in
    Element<T>* e = new Element<T>(index);
    if (!size){
        //List was empty
        first = e;
        last = e;
    }
    else if (e->index > first->index){
        //Element is new first
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
                ++size;
                return;
            }
            it_p = it;
        }
        //Element is new last
        //Will never reach this point otherwise, because of conditional return
        last->next = e;
        last = e;
    }
    //Increments size for cases where there was no conditional return
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
        //Iterates list looking for a specific key
        //If key has a duplicate, removes first iteration
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
    //List starts empty
    size = 0;
    first = last = NULL;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    //Empties list
    while (size){
        Remove_Head();
    }
}

template <class T>
void DoubleLinkedList<T>::Add_Head(T index){
    //Adds element to list's beginning
    DoubleElement<T>* e = new DoubleElement<T>(index);
    //Check to see if list was empty
    if (size) {e->next = first; first->prev = e;}
    else last = e;
    //If it was empty, new = first = last
    first = e;
    size++;
}

template <class T>
void DoubleLinkedList<T>::Add_Tail(T index){
    //Adds element to list's end
    DoubleElement<T>* e = new DoubleElement<T>(index);
    //Check to see if list was empty
    if (size) {e->prev = last; last->next = e;}
    else first = e;
    //If it was empty, new = first = last
    last = e;
    size++;
}

template <class T>
T DoubleLinkedList<T>::Remove_Head(){
    //Removes list's first element
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
    //Removes list's last element
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
    //Removes a specific element from list, returns false if not in list
    if (first->index == index) {Remove_Head(); return true;}
    else if (last->index == index) {Remove_Tail(); return true;}
    else {
        for (DoubleElement<T>* it = first->next; it != last; it = it->next){
            //Iterates list looking for key
            //In case of duplicate keys, removes first iteration
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
    //List starts empty
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

template <class T>
Degen_MinHeap<T>::Degen_MinHeap(int n_size){
    //Heap starts empty, gets filled with infinity
    size = 0;
    elements = new HeapElement<T>*[n_size];
    heap_elements = new HeapElement<T>*[n_size];
    for (int i = 0; i < n_size; ++i){
        Add(INFINITY);
    }
}

template <class T>
Degen_MinHeap<T>::~Degen_MinHeap(){
    //Empties heap and frees memory
    while (size){
        Remove();
    }
    delete [] elements;
    delete [] heap_elements;
}

template <class T>
void Degen_MinHeap<T>::Add(T index){
    //Creates new element
    HeapElement<T>* e = new HeapElement<T>(index);
    if (!size){
        //Heap was empty
        top = e;
        elements[0] = e;
        heap_elements[0] = e;
        e->pos = 0;
        e->node = 0;
        size++;
    }
    else{
        int parent = ((size-1)/2); //Parent of a new node: (size-1)/2
        //Add element to heap
        e->parent = heap_elements[parent];
        elements[size] = e;
        heap_elements[size] = e;
        e->pos = size;
        e->node = size;
        //Adjust parent-child pointers
        //If left is NULL, so is right, and if left is not NULL, right is
        if (heap_elements[parent]->left) heap_elements[parent]->right = e;
        else heap_elements[parent]->left = e;
        HeapElement<T>* aux; //Auxiliar for transfering pointers
        HeapElement<T>* dad; //Auxiliar for pointer operations
        int npos; //Auxiliar for transfering positions
        while (e->parent && index < e->parent->index){
            //While heap order is not achieved, switch e with its parent
            dad = e->parent;
            if (dad == top) top = e;
            //Change parent and grandparent relations
            //If parent is root, dad->parent is NULL, so the following should be skipped over
            if (dad->parent && dad->parent->left == dad) dad->parent->left = e;
            else if (dad->parent) dad->parent->right = e;
            e->parent = dad->parent;
            dad->parent = e;
            //Switch positions
            heap_elements[e->pos] = dad;
            heap_elements[dad->pos] = e;
            npos = e->pos;
            e->pos = dad->pos;
            dad->pos = npos;
            //Change child relations
            if (e->right) e->right->parent = dad;
            if (e->left) e->left->parent = dad;
            if (dad->left == e){
                //e is to the left of parent
                dad->right->parent = e;
                aux = e->right;
                e->right = dad->right;
                dad->right = aux;
                dad->left = e->left;
                e->left = dad;
            }
            else {
                //e is to the right of parent
                dad->left->parent = e;
                aux = e->left;
                e->left = dad->left;
                dad->left = aux;
                dad->right = e->right;
                e->right = dad;
            }
        }
        size++;
    }
}

template <class T>
int Degen_MinHeap<T>::Remove(){
    --size;
    //Store what should be returned before deleting element
    int ret = heap_elements[0]->node;
    if (!size){
        //Heap is now empty, delete and return
        delete top;
        return ret;
    }
    //Shift last element to top of heap
    HeapElement<T>* old_top = top;
    heap_elements[0] = heap_elements[size];
    heap_elements[size] = NULL;
    HeapElement<T>* new_top = heap_elements[0];
    new_top->pos = 0;
    top = new_top;
    //valgrind bug???
    //Update child relations
    if (new_top->parent->left == new_top) new_top->parent->left = NULL;
    else new_top->parent->right = NULL;
    new_top->parent = NULL;
    new_top->left = old_top->left;
    new_top->right = old_top->right;
    if (old_top->left) old_top->left->parent = new_top;
    if (old_top->right) old_top->right->parent = new_top;
    delete old_top;
    T index = new_top->index;
    HeapElement<T>* child; //Auxiliar for pointer operations
    HeapElement<T>* aux; //Auxiliar for pointer transfers
    int npos; //Auxiliar for position transfers
    while (new_top->left){
        //All operations shift new top downwards only
        //If left is NULL, so is right
        //If left is NULL, you can't shift down anymore
        if (index > new_top->left->index && (!new_top->right || new_top->left->index < new_top->right->index)){
            //switch to the left
            //mandatory condition (I): key for left is smaller than parent
            //if there is no pointer to the right of parent (II): do it
            //else, check if left is smaller than right (III), if true, do it
            // I && (II || III), since II and III are mutually exclusive
            //All operations are similar to those of Add, refer to that for details
            child = new_top->left;
            if (top == new_top) top = child;
            if (new_top->parent && new_top->parent->left == new_top) new_top->parent->left = child;
            else if (new_top->parent) new_top->parent->right = child;
            child->parent = new_top->parent;
            new_top->parent = child;
            heap_elements[child->pos] = new_top;
            heap_elements[new_top->pos] = child;
            npos = child->pos;
            child->pos = new_top->pos;
            new_top->pos = npos;
            if (new_top->right) new_top->right->parent = child;
            if (child->right) child->right->parent = new_top;
            if (child->left) child->left->parent = new_top;
            aux = child->right;
            child->right = new_top->right;
            new_top->right = aux;
            new_top->left = child->left;
            child->left = new_top;
        }
        else if (new_top->right && new_top->right->index < index){
            //if pointer exists and index is smaller than parent, switch
            //if above is met, right < left was verified above, because if right exists, left must also exist
            //also, if parent < left and right < parent, it follows that right < left
            //switch to the right
            //All operations are similar to those of Add, refer to that for details
            child = new_top->right;
            if (top == new_top) top = child;
            if (new_top->parent && new_top->parent->left == new_top) new_top->parent->left = child;
            else if (new_top->parent) new_top->parent->right = child;
            child->parent = new_top->parent;
            new_top->parent = child;
            heap_elements[child->pos] = new_top;
            heap_elements[new_top->pos] = child;
            npos = child->pos;
            child->pos = new_top->pos;
            new_top->pos = npos;
            new_top->left->parent = child;
            if (child->left) child->left->parent = new_top;
            if (child->right) child->right->parent = new_top;
            aux = child->left;
            child->left = new_top->left;
            new_top->left = aux;
            new_top->right = child->right;
            child->right = new_top;
        }
        else {
            //heap order achieved
            break;
        }
    }
    return ret;
}

template <class T>
void Degen_MinHeap<T>::Edit(int index, T value){
    int n_index = index-1; //Adjust since indexing in graphs start with 1
    int pos = elements[n_index]->pos;
    elements[n_index]->index = value;
    HeapElement<T>* e = heap_elements[pos];
    //Identical to heapify of Add, refer to that for details
    HeapElement<T>* aux;
    HeapElement<T>* dad;
    int npos;
    while (e->parent && value < e->parent->index){
        dad = e->parent;
        if (dad == top) top = e;
        if (dad->parent && dad->parent->left == dad) dad->parent->left = e;
        else if (dad->parent) dad->parent->right = e;
        e->parent = dad->parent;
        dad->parent = e;
        heap_elements[e->pos] = dad;
        heap_elements[dad->pos] = e;
        npos = e->pos;
        e->pos = dad->pos;
        dad->pos = npos;
        if (e->right) e->right->parent = dad;
        if (e->left) e->left->parent = dad;
        if (dad->left == e){
            //e is to the left of parent
            if (dad->right){
                dad->right->parent = e;
                aux = e->right;
                e->right = dad->right;
                dad->right = aux;
            }
            dad->left = e->left;
            e->left = dad;
        }
        else {
            //e is to the right of parent
            dad->left->parent = e;
            aux = e->left;
            e->left = dad->left;
            dad->left = aux;
            dad->right = e->right;
            e->right = dad;
        }
    }
}

//-------------------------------------------------------------------------------------

template <class T>
Degen_MaxHeap<T>::Degen_MaxHeap(int n_size){
    //Heap starts empty, gets filled with infinity
    size = 0;
    elements = new HeapElement<T>*[n_size];
    heap_elements = new HeapElement<T>*[n_size];
    for (int i = 0; i < n_size; ++i){
        Add(INFINITY);
    }
}

template <class T>
Degen_MaxHeap<T>::~Degen_MaxHeap(){
    //Empties heap and frees memory
    while (size){
        Remove();
    }
    delete [] elements;
    delete [] heap_elements;
}

template <class T>
void Degen_MaxHeap<T>::Add(T index){
    //Refer to minheap for comments
    HeapElement<T>* e = new HeapElement<T>(index);
    if (!size){
        top = e;
        elements[0] = e;
        heap_elements[0] = e;
        e->pos = 0;
        e->node = 0;
        size++;
    }
    else{
        int parent = ((size-1)/2); //Parent of a new node: (size-1)/2
        e->parent = heap_elements[parent];
        elements[size] = e;
        heap_elements[size] = e;
        e->pos = size;
        e->node = size;
        if (heap_elements[parent]->left) heap_elements[parent]->right = e;
        else heap_elements[parent]->left = e;
        HeapElement<T>* aux;
        HeapElement<T>* dad;
        int npos;
        while (e->parent && index > e->parent->index){
            dad = e->parent;
            if (dad == top) top = e;
            if (dad->parent && dad->parent->left == dad) dad->parent->left = e;
            else if (dad->parent) dad->parent->right = e;
            e->parent = dad->parent;
            dad->parent = e;
            heap_elements[e->pos] = dad;
            heap_elements[dad->pos] = e;
            npos = e->pos;
            e->pos = dad->pos;
            dad->pos = npos;
            if (e->right) e->right->parent = dad;
            if (e->left) e->left->parent = dad;
            if (dad->left == e){
                //e is to the left of parent
                dad->right->parent = e;
                aux = e->right;
                e->right = dad->right;
                dad->right = aux;
                dad->left = e->left;
                e->left = dad;
            }
            else {
                //e is to the right of parent
                dad->left->parent = e;
                aux = e->left;
                e->left = dad->left;
                dad->left = aux;
                dad->right = e->right;
                e->right = dad;
            }
        }
        size++;
    }
}

template <class T>
int Degen_MaxHeap<T>::Remove(){
    //Refer to minheap for comments
    --size;
    int ret = heap_elements[0]->node;
    if (!size){
        delete top;
        return ret;
    }
    HeapElement<T>* old_top = heap_elements[0];
    heap_elements[0] = heap_elements[size];
    heap_elements[size] = NULL;
    HeapElement<T>* new_top = heap_elements[0];
    new_top->pos = 0;
    top = new_top;
    //valgrind bug???
    if (new_top->parent->left == new_top) new_top->parent->left = NULL;
    else new_top->parent->right = NULL;
    new_top->parent = NULL;
    new_top->left = old_top->left;
    new_top->right = old_top->right;
    delete old_top;
    T index = new_top->index;
    HeapElement<T>* child;
    HeapElement<T>* aux;
    int npos;
    while (new_top->left){
        if (index < new_top->left->index && (!new_top->right || new_top->left->index > new_top->right->index)){
            //switch to the left
            //mandatory condition (I): key for left is smaller than parent
            //if there is no pointer to the right of parent (II): do it
            //else, check if left is smaller than right (III), if true, do it
            // I && (II || III), since II and III are mutually exclusive
            child = new_top->left;
            if (top == new_top) top = child;
            if (new_top->parent && new_top->parent->left == new_top) new_top->parent->left = child;
            else if (new_top->parent) new_top->parent->right = child;
            child->parent = new_top->parent;
            new_top->parent = child;
            heap_elements[child->pos] = new_top;
            heap_elements[new_top->pos] = child;
            npos = child->pos;
            child->pos = new_top->pos;
            new_top->pos = npos;
            if (new_top->right) new_top->right->parent = child;
            if (child->right) child->right->parent = new_top;
            if (child->left) child->left->parent = new_top;
            aux = child->right;
            child->right = new_top->right;
            new_top->right = aux;
            new_top->left = child->left;
            child->left = new_top;
        }
        else if (new_top->right && new_top->right->index > index){
            //if pointer exists and index is smaller than parent, switch
            //if above is met, right < left was verified above, because if right exists, left must also exist
            //also, if parent < left and right < parent, it follows that right < left
            //switch to the right
            child = new_top->right;
            if (top == new_top) top = child;
            if (new_top->parent && new_top->parent->left == new_top) new_top->parent->left = child;
            else if (new_top->parent) new_top->parent->right = child;
            child->parent = new_top->parent;
            new_top->parent = child;
            heap_elements[child->pos] = new_top;
            heap_elements[new_top->pos] = child;
            npos = child->pos;
            child->pos = new_top->pos;
            new_top->pos = npos;
            new_top->left->parent = child;
            if (child->left) child->left->parent = new_top;
            if (child->right) child->right->parent = new_top;
            aux = child->left;
            child->left = new_top->left;
            new_top->left = aux;
            new_top->right = child->right;
            child->right = new_top;
        }
        else {
            //heap order achieved
            break;
        }
    }
    return ret;
}

template <class T>
void Degen_MaxHeap<T>::Edit(int index, T value){
    //Refer to minheap for comments
    int n_index = index-1;
    int pos = elements[n_index]->pos;
    elements[n_index]->index = value;
    HeapElement<T>* e = heap_elements[pos];
    HeapElement<T>* aux;
    HeapElement<T>* dad;
    int npos;
    while (e->parent && value > e->parent->index){
        dad = e->parent;
        if (dad == top) top = e;
        if (dad->parent && dad->parent->left == dad) dad->parent->left = e;
        else if (dad->parent) dad->parent->right = e;
        e->parent = dad->parent;
        dad->parent = e;
        heap_elements[e->pos] = dad;
        heap_elements[dad->pos] = e;
        npos = e->pos;
        e->pos = dad->pos;
        dad->pos = npos;
        if (e->right) e->right->parent = dad;
        if (e->left) e->left->parent = dad;
        if (dad->left == e){
            //e is to the left of parent
            dad->right->parent = e;
            aux = e->right;
            e->right = dad->right;
            dad->right = aux;
            dad->left = e->left;
            e->left = dad;
        }
        else {
            //e is to the right of parent
            dad->left->parent = e;
            aux = e->left;
            e->left = dad->left;
            dad->left = aux;
            dad->right = e->right;
            e->right = dad;
        }
    }
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

GraphPath::GraphPath(){
    path = new LinkedList<int>;
}

GraphPath::~GraphPath(){
    delete [] path;
}

void GraphPath::Add(int node){
    path->Add_Head(node);
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

template <class T>
int Graph<T>::GetNodeDegree(const int index){
    //Returns a node's degree in O(1)
    return n_degree[index-1];
}

template <class T>
int* Graph<T>::GetNeighbors(const int index){
    //Returns a node's neighbor list, complexity varies between data types
    return t->GetNeighbors(index,n_degree[index-1]);
}

template <class T>
Tuple<int,double>* Graph<T>::GetSides(int index){
    //Returns a node's sides list, complexity varies between data types
    return t->GetSides(index,n_degree[index-1]);
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
        delete [] neighbors;
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
        delete [] neighbors;
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
        delete [] neighbors;
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
        delete [] neighbors;
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
        delete [] neighbors;
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

template <class T>
GraphPath* Graph<T>::Dijkstra(int node){
    double* dist = new double[n];
    int* parents = new int[n];
    Degen_MinHeap<double>* heap = new Degen_MinHeap<double>(n);
    for (int i = 0; i < n; i++){
        dist[i] = INFINITY;
        parents[i] = 0;
    }
    int n_node = node-1;
    dist[n_node] = 0;
    parents[n_node] = -1;
    heap->Edit(node,0);
    int tmp_a, top;
    double tmp_b;
    Tuple<int,double>* sides;
    while (heap->size){
        top = heap->Remove();
        if (dist[top] == INFINITY) break;
        sides = GetSides(top+1);
        for (int i = 0; i < n_degree[top]; i++){
            tmp_a = sides[i].a-1;
            tmp_b = dist[top] + sides[i].b;
            if (dist[tmp_a] > tmp_b){
                dist[tmp_a] = tmp_b;
                heap->Edit(tmp_a+1,tmp_b);
                parents[tmp_a] = top;
            }
        }
        if (t->d) delete [] sides;
    }
    GraphPath* paths = new GraphPath[n];
    paths[n_node].Add(node);
    paths[n_node].distance = 0;
    for (int i = 0; i < n_node; i++){
        paths[i].distance = dist[i];
        int it = i;
        while (it != n_node){
            paths[i].Add(it+1);
            it = parents[it];
        }
        paths[i].Add(node);
    }
    for (int i = n_node+1; i < n; i++){
        paths[i].distance = dist[i];
        int it = i;
        while (it != n_node){
            paths[i].Add(it+1);
            it = parents[it];
        }
        paths[i].Add(node);
    }
    delete [] dist;
    delete [] parents;
    return paths;
}

template <class T>
GraphPath* Graph<T>::Dijkstra(int src, int dst){
    double* dist = new double[n];
    int* parents = new int[n];
    Degen_MinHeap<double>* heap = new Degen_MinHeap<double>(n);
    for (int i = 0; i < n; i++){
        dist[i] = INFINITY;
        parents[i] = 0;
    }
    int n_src = src-1;
    int n_dst = dst-1;
    dist[n_src] = 0;
    parents[n_src] = -1;
    heap->Edit(src,0);
    int tmp_a, top;
    double tmp_b;
    while (heap->size){
        top = heap->Remove();
        if (top == n_dst) break;
        if (dist[top] == INFINITY) break;
        Tuple<int,double>* sides = GetSides(top+1);
        for (int i = 0; i < n_degree[top]; i++){
            tmp_a = sides[i].a-1;
            tmp_b = dist[top] + sides[i].b;
            if (dist[tmp_a] > tmp_b){
                dist[tmp_a] = tmp_b;
                heap->Edit(tmp_a+1,tmp_b);
                parents[tmp_a] = top;
            }
        }
        if (t->d) delete [] sides;
    }
    GraphPath* path = new GraphPath;
    double d = dist[n_dst];
    path->distance = d;
    if (d == INFINITY) path->Add(dst);
    else {
        int it = n_dst;
        while (it != n_src){
            path->Add(it+1);
            it = parents[it];
        }
        path->Add(src);
    }
    delete [] dist;
    delete [] parents;
    return path;
}

template <class T>
void Graph<T>::VeryFastDijkstra(int node, double* dist){
    Degen_MinHeap<double>* heap = new Degen_MinHeap<double>(n);
    for (int i = 0; i < n; i++){
        dist[i] = INFINITY;
    }
    int n_node = node-1;
    dist[n_node] = 0;
    heap->Edit(node,0);
    int tmp_a, top;
    double tmp_b;
    while (heap->size){
        top = heap->Remove();
        if (dist[top] == INFINITY) break;
        Tuple<int,double>* sides = GetSides(top+1);
        for (int i = 0; i < n_degree[top]; i++){
            tmp_a = sides[i].a-1;
            tmp_b = dist[top] + sides[i].b;
            if (dist[tmp_a] > tmp_b){
                dist[tmp_a] = tmp_b;
                heap->Edit(tmp_a+1,tmp_b);
            }
        }
        if (t->d) delete [] sides;
    }
}

template <class T>
void Graph<T>::MST(){
    double* cost = new double[n];
    bool* mark = new bool[n];
    Tuple<int,double>* mst_sides = new Tuple<int,double>[n];
    Degen_MinHeap<double>* heap = new Degen_MinHeap<double>(n);
    for (int i = 0; i < n; i++){
        cost[i] = INFINITY;
        mark[i] = false;
    }
    cost[0] = 0;
    mark[0] = true;
    mst_sides[0] = Tuple<int,double>(0,0);
    heap->Edit(1,0);
    int tmp_a, top;
    double tmp_b;
    bool connected = true;
    while (heap->size){
        top = heap->Remove();
        if (cost[top] == INFINITY) {connected = false; break;}
        mark[top] = true;
        Tuple<int,double>* sides = GetSides(top+1);
        for (int i = 0; i < n_degree[top]; i++){
            tmp_a = sides[i].a-1;
            if (mark[tmp_a]) continue;
            tmp_b = sides[i].b;
            if (cost[tmp_a] > tmp_b){
                cost[tmp_a] = tmp_b;
                mst_sides[tmp_a] = Tuple<int,double>(top+1,tmp_b);
                heap->Edit(tmp_a+1,tmp_b);
            }
        }
        if (t->d) delete [] sides;
    }
    ofstream o;
    string path = "mst-"+fname; //E.g.: "mst-graph.txt"
    o.open(path.c_str());
    if (!connected) o << "WARNING - Graph is not connected and this result may be wrong" << "\n";
    o << n << "\n";
    double sum = 0;
    for (int i = 1; i < n; i++){
        o << i+1 << " " << mst_sides[i].a << " " << mst_sides[i].b << "\n";
        sum += mst_sides[i].b;
    }
    o << "CUSTO TOTAL: " << sum << endl;
    o.close();
    delete [] cost;
    delete [] mark;
    delete [] mst_sides;
}

template <class T>
double Graph<T>::AverageDistance(){
    double sum = 0;
    int count = 0;
    double n_n = n;
    double* dist = new double[n];
    for (int i = 0; i < n; i++){
        VeryFastDijkstra(i+1,dist);
        for (int j = 0; j < n; j++){
            if (dist[j] != INFINITY) sum += dist[j];
            else count++;
        }
    }
    sum /= ((n_n*(n_n-1))-count);
    return sum;
}

template class Graph<NVector>;
template class Graph<Matrix>;
template class Ordered_LinkedList<int>;
template class Degen_DoubleLinkedList<int>;
template class Tuple<int,double>;
//http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
