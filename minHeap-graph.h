#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> 
using namespace std;

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int* curDist, int* locator, int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int* curDist, int* locator, int i);
  void insert(int* curDist, int* locator,const T& el);
  bool find(const T& key) const;
  int getNum() const; 
  void fixHeap(int* curDist, int* locator, int i);
  void remove(int* curDist, int* locator,int i);
  T getMin(int* curDist, int* locator);

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

template <class T>
minHeap<T>::minHeap(int i){
  this->capacity = i;
  this->num = 0;
  this->ar = new int[this->capacity];
}
//You need to implement all the memeber functions above.
template <class T>
void minHeap<T>::insert(int* curDist, int* locator,const T& el){
      if(this->num >= this->capacity )
    throw "The array is full"; //"The array is full"; 
  else{ 
    this->ar[this->num] = el; //set last element in array equal to new element to be inserted
   // if parent is greater than the the new element, call bubbleUp
     bubbleUp(curDist, locator, this->num-1);
    this->num++;
    }
}

//return the number of elements in the heap.
template <class T>
int minHeap<T>::getNum() const
{
  return num;
}

template <class T>
void minHeap<T>::min_heapify(int* curDist, int* locator, int i){
  int l = (2 * i) + 1; //the index of the left child of i
  int r = (2 * i) + 2; //the index of the right child of i
  int smallest = i; //the index of the smallest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  if(curDist[ar[l]] < curDist[ar[smallest]] && l < this->num){
    smallest = l;
  }
  if(curDist[ar[r]] < curDist[ar[smallest]] && r < this->num){
    smallest = r;
  }
  //The largest is either the right or left child. We need to exchange the parent with it.
  if(smallest != i)
    {
      swap(locator[ar[smallest]], locator[ar[i]]);
      swap(this->ar[smallest], this->ar[i]);
     // mySwap(locator[ar[smallest]], locator[ar[i]]);
      min_heapify(curDist, locator, smallest);
      //exchange the 2 values
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
    }
  
}

template <class T>
void minHeap<T>::bubbleUp(int* curDist, int* locator, int i){
    int p = (i - 1) / 2; //set p equal to parent of i
    while(curDist[ar[i]] < curDist[ar[p]] && i > 0){//while the new element is larger than it's parent
       swap(locator[ar[i]], locator[ar[p]]);
      swap(this->ar[i], this->ar[p]); //swap elements
      
      //mySwap(locator[ar[i]], locator[ar[p]]); 
      i = p; //reset i to its new position
      p = (i - 1) / 2; //set p to i's new parent    
    }
}

template <class T>
bool minHeap<T>::find(const T& key) const
{
  
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return true;
return false;
  //The element doesn't exist 
 // "The element doesn't exist";                                                                                             
}
template <class T>
void minHeap<T>::remove(int* curDist, int* locator, int i){
    if(i >= this->num || i < 0)
    throw "The element doesn't exist"; //"The element doesn't exist";                             
  else{
    swap(locator[ar[i]], locator[ar[num-1]]);
    swap(this->ar[i], this->ar[this->num-1]); // swap last element with element to be removed
    this->num--; //decrement size
  fixHeap(curDist, locator, i);
    } 
  }


template <class T>
T minHeap<T>::getMin(int* curDist, int* locator){
  T temp = this->ar[0]; //set tempm to top element
  this->remove(curDist, locator, 0);
  return temp;
}

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h){
  
  for(int i = 0; i < h.num; i++)
    o << h.ar[i] << " ";
  o << endl;
  return o;
}


//i is the index (within heap) of the vertex whose distance was changed.  
//For example, if vertex 0's distance changed when it is located at 3, i is 3. This is where the heap needs to be fixed by either going up or down.
//curDist is the array that contains the shortest distance from start to every other vertex.                                           
//locator is the array that contains the location of each vertex within the heap. Make sure you understand the homework document posted on Canvas to understand how locator works.     
template <class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{
  //need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. 


  if(i < num){
   if(curDist[ar[i]] < curDist[ar[(i -1) /2]]){
      bubbleUp(curDist, locator, i);
    }else{
      min_heapify(curDist, locator, i);   
  }
                                                                      
     }
  }

#endif
