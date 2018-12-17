#ifndef ARRAY_H_INCLUDED_
#define ARRAY_H_INCLUDED_
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <exception>
using namespace std;

class OutOfBoundsException: public exception
{
  virtual const char* what() const throw()
  {
    return "Out of Bounds happened!";
  }
} OutofBound;


template<class myType>
class Array{
public:
  // Default constructor
  Array();

  // Array(int length,myType* value)
  Array(int length, myType* value);
  
  // copy constructor
  Array(const Array& y);

  // Destructor
  ~Array();

  // Initialize an array with size =s and assign all elements as v
  Array(int s, myType v);

  // get size
  int size() const;

  // append x to the end of the array
  void append(myType x);

  // append array y to the end of the array
  void append(const Array& y);

  // overload of =
  Array& operator=(const Array& y);
 
  // overload of []
  myType& operator[](int index)const;

  // overload of <<
  template<class Y>
  friend ostream& operator<<(ostream& os, const Array<Y>& y);  

  // get count
  int count()const;

  // overload of +
  Array& operator+(const Array& y);

  // update Count
  void updateCount(){
    Count++;
  }
  
private:
    // array stores all elements
    myType* array;

    // size is the capacity of the array
    int Size;

    // count records the number of elements in the current array 
    int Count;

    // double the arraysize when the array is full
    void expand();
};

// Constructor
// array is NULL pointer, size and count = 0
template <class myType>
Array<myType>::Array(){
    array = NULL;
    Size = 0;
    Count = 0;
}

// copy constructor
template <class myType>
Array<myType>::Array(const Array<myType>& y){

  // allocate int array 
  Size = y.size();
  try{
      array = new myType[Size];
  }
  catch(std::exception &e){
    cout << "New Exception Error" << e.what() << endl;
  }
  // copy elements in Array y
  for (int i = 0;i < Size;i++)
    array[i] = y[i];
  
  Count = y.count();
}

// Array(int length,myType* values)
template <class myType>
Array<myType>::Array(int length, myType* values){
  // allocate int array 
  Size = length;
  try{
      array = new myType[Size];
  }
  catch(std::exception &e){
    cout << "New Exception Error" << e.what() << endl;
  }
  if (values != NULL){

    // copy elements in Array y
    for (int i = 0;i < Size;i++)
      array[i] = values[i];
  }
  Count = length; 
}

// destructor
template <class myType>
Array<myType>::~Array(){
  try{
      delete array;
  }
  catch(std::exception &e){
    cout << "Delete Exception Error" << e.what() << endl;
  }
}

// Initialize an array with size = s and assign all elements as v
template <class myType>
Array<myType>::Array(int s,myType v){
  Size = s;
  
  // allocate memeory for the array
  try{
      array = new myType[Size];
  }
  catch(std::exception &e){
    cout << "New Exception Error" << e.what() << endl;
  }
  
  Count = 0;

  // initialize all elements as v
  for (int i = 0;i < Size;i++)
    array[i] = v;
  
}

// get size
template <class myType>
int Array<myType>::size() const{
  return Size;
}

// append x to the end of the array
template <class myType>
void Array<myType>::append(myType x){
  // if the array is full, expand the capacity
   if (Count == Size)
      this->expand();
   
  // append x to the end and update count
  array[Count++] = x;
}

// append array y to the end of the array
template <class myType>
void Array<myType>::append(const Array<myType>& y){

  // copy all elements in y 
  for (int i = 0;i < y.size();i++){
    // When array is full, expand the capacity
    if (Count == Size)
      this->expand();
    
    array[Count++] = y[i];
  }
}

// overload of =
template <class myType>
Array<myType>& Array<myType>::operator=(const Array& y){
  if(this != &y){
    
    // clear the current array
    try{
        delete array;
    }
    catch(std::exception &e){
    cout << "Delete Exception Error" << e.what() << endl;
    }
    
    // same as the copy constructor
    Size = y.size();
    try{
        array = new myType[Size];
    }
    catch(std::exception &e){
        cout << "New Exception Error" << e.what() << endl;
    }
    for (int i = 0;i < Size;i++)
      array[i] = y[i];
    

    Count = y.count();
  }
  return *this;
}

// overload of []
template <class myType>
myType& Array<myType>::operator[](int index)const{

  // if the index is illegal, throw exception
  if (index < 0 or index >= Size)
    throw OutofBound;
    
  return array[index];
}

// get count
template <class myType>
int Array<myType>::count()const{
  return Count;
}

// double the arraysize when the array is full
template <class myType>
void Array<myType>::expand(){

  // allocate a array with double size
  myType *newArray = new myType[2 * Size];
  int newSize = 2 * Size;
  int newCount = Count;

  // copy all elements
  for (int i = 0;i < Size;i++)
    newArray[i] = array[i];

  // clear up the current array
  try{
      delete array;
  }
  catch(std::exception &e){
    cout << "Delete Exception Error" << e.what() << endl;
  }
  array = newArray;
  Size = newSize;
  Count = newCount;
}

// overload of +
template <class myType>
Array<myType>& Array<myType>::operator+(const Array<myType>& y){
  
  // copy all elements in y 
  for (int i = 0;i < y.size();i++){

    // When array is full, expand the capacity
    if (Count == Size)
      this->expand();
    
    array[Count++] = y[i];
  }

  return *this;
}

//printf function for Array (overload of <<)
template <class myType>
ostream& operator<<(ostream& os, const Array<myType>& y)  
{  
  os << "[";
  int i;
  for (i = 0;i < y.count() - 1;i++){
    os << y[i] << ", "; 
  }
  os << y[i] << "]" << endl;
  return os;
}
#endif
