#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include "minHeap-graph.h"
using namespace std;

class edge
{
  friend class graph;  //You want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) { this->neighbor = u, this->wt = w;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                     
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void DijkstraShortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  this->num_ver = num;
  this->ver_ar = new list<edge*>[num];
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object 
}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  
  for(list<edge*>::iterator u =ver_ar[0].begin(); u != ver_ar[0].end(); u++){
    delete (*u);
  }

  //destroy the ver_ar dynamic array
  delete[] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  this->ver_ar[v].push_back(new edge(u, w));
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void diplayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  int *num = new int[num_ver];
  //I created a queue object of string data type from the library's queue class to save all the paths.
  queue<string> edges;
  for(int v = 0; v < this->num_ver; v++){
    num[v] = 0;
  }

  int i = 1;
  int tempVer = start;
  do{
    DFT_helper(tempVer, i, num, edges);
    tempVer = nextUnvisitedNodes(num, start, start);
    
  } while(tempVer != -1);
  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.
  //You could call displayQueue() implemented above to display all the paths. 
  diplayQueue(edges);
  //Don't forget to destroy the dynamic array
  delete[] num;
}

//I made the following function to see if there are still unvisited nodes. Start checking at s, which is the one after the vertext we started last time                       
//num points to an array containing visit numbers. 0 indicates, the vertex hasn't been visited yet.                                           
//s is the vertext right after the vertex we started last time                         
int graph::nextUnvisitedNodes(int* num, int start, int s) 
{ 
  int index = -1;

  //go through the num array to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.

  for(int i =s; i != start; i=(i+1) % this->num_ver){
    if(num[i] == 0){
      index = i;
      return index;
    }
  }
  return index;
}


void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  num[v] = i++;
  cout << v << " ";
  
  for (list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
      if(num[(*u)->neighbor] == 0){ // if u's neighbor(adjacent vertice) is 0 then connect it
        q.push(to_string(v) + "->" + to_string((*u)->neighbor));
        DFT_helper((*u)->neighbor, i, num, q);
      }
    }

}

//start is the index for the start vertex
void graph::BFT(int start)
{
  int *num = new int[num_ver];
  //The algorithm is in my lecture notes
  for(int i = 0; i < num_ver; i++){
    num[i] = 0;
  }
  //Use the queue class from the library
  queue<int> q;
  //I used another queue of strings to save all the paths. 
  queue<string> edges;
  int v = start;
  int i = 1;
  do{
    num[v] = i++;
    q.push(v);
     while(!q.empty()){
      v = q.front();
      q.pop();
      cout << v << " ";
      for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++){  //
      
        if(num[(*u)->neighbor] == 0){
          num[(*u)->neighbor] = i++;
          q.push((*u)->neighbor);
          edges.push(to_string(v) + "->" + to_string((*u)->neighbor)); //
        }
    }  
  } 
      v = nextUnvisitedNodes(num, start, start);
    }while(v != -1);
  //I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited verteces.

diplayQueue(edges);

  //You could call show all paths by calling displayQueue()                                                                     

  //Don't forget to destroy the dynamic array if you used one
  delete[] num;
}

void showShortestDistance(int* curDist, int* predecessor, int start) // change to include end vert
{
  int dest; //destination                                                                                         //trace the shortest path from dest back to start  
  cout << "Enter the destination: ";                                                                          
  cin >> dest;
  int i = dest;
  stack<int> s;

  while(i != start){
    s.push(i);
    i = predecessor[i];
  }
  s.push(i);

                                          
  cout << "The shortest path from " << start << " to " << dest << " is ";
  while(!s.empty()){
    cout << s.top() << " ";
    s.pop();
  }
 
  cout << "\nThe distance is " << curDist[dest] << endl;   
                                   
}


void printHeapArrays(const minHeap<int>& h, int* curDist, int* locator, int* predecessor, int num_ver)
{
  cout << "heap ------" << endl;
  cout << h << endl; 

  cout << "locator ------" << endl;
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << locator[i] << " ";                                                                                               
  cout << endl;

  cout << "curDist ------- " << endl;                                                                                           
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << curDist[i] << " ";                                                                                               
  cout << endl << endl;

  cout << "Predecessor ------- " << endl;                                                                                      
  for(int i = 0; i < num_ver; i++)                                                                                         
    cout << predecessor[i] << " ";                                                                                             
  cout << endl << endl;
}

void graph::DijkstraShortestPath(int start) // include end vert
{
  minHeap<int> toBeChecked(num_ver); //the top of this heap has the vertex with the shortest distance
//  declare a dynamic array called curDist //contains the current shortest distance from start to every other vertex
  int *curDist = new int[num_ver];
  int *predecessor = new int[num_ver];
  int *locator = new int[num_ver];
  //declare a dynamic array called predecessor //contains the predecessor of each vertex
  //declare a dynamic array called locator //tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertext 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap

  for(int i = 0; i < num_ver; i++){
    curDist[i] = 999;
  }
  //initialize each array
  //curDist should be 999 for all vertices to start with 
  
  //populate toBeChecked heap 
  //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers
  //to start with, locator [0, 1, 2, 3, 4, ...] 
  for(int i =0; i < num_ver; i++){
    locator[i] = i;
  }
  //Initialize predecessor for each vertex to -1
  for(int i = 0; i < num_ver; i++){
    predecessor[i] = -1;
  }
  for(int i = 0; i < num_ver; i++){
    toBeChecked.insert(curDist, locator, i);
  }
  curDist[start] = 0; //curDist(first) = 0;
  int v = start;
  while(toBeChecked.getNum() != 0){ 
    //while toBeChecked is not empty
    toBeChecked.fixHeap(curDist, locator, locator[v]);
    v = toBeChecked.getMin(curDist, locator);
   
    for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++){//for all vertices u adjacent to v 
    
      if(toBeChecked.find((*u)->neighbor) != false ){
            if(curDist[(*u)->neighbor] > curDist[v] + (*u)->wt){ 
          curDist[(*u)->neighbor] = curDist[v] + (*u)->wt; 
          predecessor[(*u)->neighbor]  = v; 
          toBeChecked.fixHeap(curDist, locator, locator[(*u)->neighbor]);
          }
      }
 
  }
    }
  showShortestDistance(curDist, predecessor, start);
  delete[] curDist;
  delete[] predecessor;
  delete[] locator;

  }
#endif
