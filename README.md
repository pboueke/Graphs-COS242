A c++ library intended for use with graph text files developed for the Graph Theory course at UFRJ.
It contains a few usefull graph related methods and many useful data structures.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

1)Data Structures:

* Tuple
* Element
* DoubleElement
* HeapElement
* Queue
* Stack
* Linked List
* Ordered Linked List
* Double Linked List
* Degenerate Double Linked List with Vector
* Degenerate MinHeap
* Degenerate MaxHeap (new)
* ConnectedComponent
* GraphPath (new)

-------------------------------------------------------------------------------------

1.1)Tuple

* Used for containing two pieces of data
* Used mostly for sides and their weight (neighbor,weight)
* Double Template for containers
* No methods but default ones

-------------------------------------------------------------------------------------

1.2)Element

* Used as element of linked lists and data structures
* Template for container, pointer to next
* No methods but default ones

-------------------------------------------------------------------------------------

1.3)DoubleElement

* Same as Element, but for double linked lists

-------------------------------------------------------------------------------------

1.4)HeapElement

* Same as Element, but for heaps
* Keeps pointer to parent and two children

-------------------------------------------------------------------------------------

1.5)Queue

* Data structure for algorithms, template on container
* Methods are: Add, Remove + Default ones
* Keeps pointer to head and tail

1.5.1)Add

* Creates new element, puts it as new tail
* Returns void

1.5.2)Remove

* Removes head, puts it as head's pointer
* Returns removed element

-------------------------------------------------------------------------------------

1.6)Stack

* Data structure for algorithms, template on container
* Methods are: Add, Remove + Default ones
* Keeps pointer to top of stack

1.6.1)Add

* Creates new element, puts it as new top
* Returns void

1.6.2)Remove

* Removes top, puts it as top's pointer
* Returns removed element

-------------------------------------------------------------------------------------

1.7)Linked List

* Simple linked list, stores data dynamically
* Methods are: Add_Head, Add_Tail, Remove_Head, Remove_Tail, Remove(index) + Default ones
* Keeps pointer to head, and keeps count of elements

1.7.1)Add_Head

* Adds new element to beginning of list

1.7.2)Add_Tail

* Adds new element to end of list

1.7.3)Remove_Head

* Removes list's first element
* Returns removed element

1.7.4)Remove(index)

* Searches list for specific element
* Returns false if element not in list, true otherwise

-------------------------------------------------------------------------------------

1.8)Ordered Linked List

* Keeps elements ordered, otherwise same as linked list
* Methods are: Add, Remove_Head, Remove_Tail, Remove(index) + Default ones
* Keeps pointer to head, tail and keeps count of elements

1.8.1)Add

* Parses the list, looking for where to insert new element, and keeps it there.

1.8.2)Remove_Head

* Same as linked list

1.8.3)Remove(index)

* Same as linked list

-------------------------------------------------------------------------------------

1.9)Double Linked List

* Same as linked list, except elements keep pointers to before and after
* Has method remove tail, should be intuitive

-------------------------------------------------------------------------------------

1.10)Degenerate Double Linked List with Vector

* Special type of double linked list used on specific situations
* List is initially filled with a fixed number of elements
* Once filled, it can only be filled again after becoming empty
* There are no options for adding a new element
* An auxiliar vector stores pointers to each element so we can access them in O(1)
* Removing an element grounds the pointer to that element
* Methods are: Fill(size), Remove_First, Remove(index) + Default ones
* Keeps track of first and last elements via special pointers

1.10.1)Fill(size)

* Fills list with size elements
* Requires operator ++ for custom classes

1.10.2)Remove_First

* Removes first element from list
* Returns said element

1.10.3)Remove(index)

* Removes specific element from list
* Reminder that this is O(1) because we can access it via vector

-------------------------------------------------------------------------------------

1.11)Degenerate MinHeap

* Fixed size priority queue for elements with smaller keys
* Requires operator < for custom classes
* All operations are O(log2n)
* Auxiliary vector is used for storing pointers to each element, accessing them in O(1)
* Methods are: Add, Remove, Edit(index) + Special constructor + Default ones

1.11.1)Add

* Inserts new element in heap, maintaining heap order

1.11.2)Remove

* Removes heap root, maintaining heap order

1.11.3)Edit(index)

* Changes value of espcified element, maintaining heap order

1.11.4)Constructor(size)

* Size must be specified at declaration time for array allocation

-------------------------------------------------------------------------------------

1.12)Degenerate MaxHeap

* Same as Degenerate MinHeap, only for elements with bigger keys
* Operator > is required for custom classes

-------------------------------------------------------------------------------------

1.13)Connected Component

* Data structure to represent a graph's connected component
* Contains a vector with each node's index
* Size must be specified beforehand for array allocation
* Methods are: Add, Operator > + Special constructor + Default ones

1.13.1)Add

* Adds a node's index to a connected component.
* Uses an iterator to correctly fill the array.

1.13.2)Operator >

* Returns true if this component has more nodes than other, else returns false

1.13.3)Special Constructor

* Size is specified for array allocation

-------------------------------------------------------------------------------------

1.14)Graph Path

* Data structure to represent path between two nodes in a graph
* Contains an integer to store distance, starts as infinity
* Contains a linked list of nodes that make the path
* Methods are: Add, Operator X + default ones

1.14.1)Add

* Adds a node to the path, appends node to head of list
* Increments path on side's weight

1.14.2)Operator X

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

2)Classes:

-NVector
-Matrix
-Graph (updated)

-------------------------------------------------------------------------------------

2.1)NVector

* Adjacency Vector, allocs memory in a fixed fashion for speed purposes
* Similar to an adjacency list, only it uses memory contiguously

* Methods are:
>GetNeighbors
>GetSides
>Special Constructor used by Graph
>Default ones

2.1.1)GetNeighbors

* Returns a pointer to a node's neighbors list, which MUST NOT BE DELETED
* If there are weights, will return an array of neighbors only

2.1.2)GetSides

* Returns a tuple with neighbors and weights

2.1.3)Special Constructor

* Reads a file and loads it as a graph
* A boolean switch indicates the presence of weights
* This same boolean switch is present under class Graph

-------------------------------------------------------------------------------------

2.2)Matrix

* Adjacency Matrix, allocs memory in two dimensions, it's a matrix after all
* Not exactly good in terms of performance due to memory constraints

* Methods are:
>GetNeighbors
>GetSides
>Special Constructor used by Graph
>Default ones

2.2.1)GetNeighbors

* Returns an array of a node's neighbors, which MUST BE DELETED after parsing
* If there are weights, will return an array of tuples

2.2.2)GetSides

* Returns an array of tuples containing neighbors and weights for sides

2.2.3)Special Constructor

* Reads a file and loads it as a graph
* A boolean switch indicates the presence of weights
* This same boolean switch is present under class Graph
* Matrix is always numerical, should weights be off then all weights are 1

-------------------------------------------------------------------------------------

2.3)Graph

* Represents a graph, and has a plethora of methods for algorithms
* A boolean switch indicates the presence of weights for sides

* Members are:
>Number of nodes
>Number of sides
>Average node degree
>Highest degree
>Filename [File handling - load and save]
>Array of degree distributions
>Array of node degrees
>Instance of data structure (in this case, NVector or Matrix)

* Methods are:
>Default constructor and destructor
>LoadGraphFromFile
>GenerateGraphFile
>GetNeighbors
>GetSides
>BFS
>FastBFS (private)
>VeryFastBFS (private)
>DFS
>VeryFastDFS (private)
>GetConnectedComponents
>GetDiameter
>Dijkstra (new)
>Dijkstra(dst) (new)
>VeryFastDijkstra (private) (new)
>MST (new)
>GetAverageDistance (new)

2.3.1)LoadGraphFromFile

* Reads a specific file and generates an instance of graph from it
* Most members are calculated inside the data structure's constructor
* Transparent to presence of weights

2.3.2)GenerateGraphFromFile

* Generates a file containing graph statistics
* Transparent to presence of weights

2.3.3)GetNeighbors

* Returns an array containing a node's neighbors
* Array type is always int

2.3.4)GetSides

* Returns an array containing a node's sides, including neighbors and weights
* Array type is a tuple of int, double

2.3.5)BFS

* Runs a BFS from a specfied node
* Prints spanning tree on file
* Returns the connected component

2.3.6)FastBFS (private)

* Runs a BFS from a specified node
* Does not print spanning tree
* Returns the connected component
* Used only inside GetConnectedComponents, which is why it's private

2.3.7)VeryFastBFS (private)

* Runs a BFS from a specified node
* Does not print the spanning tree
* Returns the highest distance found
* Used only inside GetDiameter, which is why it's private

2.3.8)DFS

* Runs a DFS from a specified node
* Prints spanning tree on file
* Returns void

2.3.9)VeryFastDFS (private)

* Runs a DFS from a specfied node
* Does not print spanning tree
* Not used within class code, used only for performance testing

2.3.10)GetConnectedComponents

* Runs several FastBFS until all vertices have been visited
* Uses an ordered linked list to store components
* Prints components in decreasing order to file

2.3.11)GetDiameter

* Runs a VeryFastBFS for each node
* Compares return to current max value
* Returns max value

2.3.12)Dijkstra

* Runs Dijkstra's algorithm from a specified node
* Prints spanning tree and shorter paths to files
* Returns array with shorter paths to each node

2.3.13)Dijkstra(dst)

* Runs Djikstra's algorithm from a specified node
* Stops when distance to destination is found
* Returns shortest path from source to destination

2.3.14)VeryFastDijkstra (private)

* Runs Dijkstra's algorithm from a specified node
* Does not write anything to file
* Returns array with shorter distances to each node

2.3.15)MST

* Runs Prim's algorithm to find a MST
* Prints the MST to file
* Returns void

2.3.16)GetAverageDistance

* If graph is weightless, calls GetDiameter
* Else, runs VeryFastDijkstra for every node
* Returns GetDiameter if weightless
* Returns sum of all VFastDij. divided by n* (n-1)

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
