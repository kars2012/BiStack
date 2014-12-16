//
//  class-10.h
//  proj10
//
//  Created by Bryan J Kars on 11/22/14.
//  Copyright (c) 2014 Bryan J Kars. All rights reserved.
//

#ifndef proj10_class_10_h
#define proj10_class_10_h

#include <utility>
#include<iostream>
using std::cout; using std::endl; using std::cin;
using std::ostream;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<iterator>
using std::ostream_iterator;
#include <algorithm>
using std::copy;
using std::swap;
#include <stdexcept>
using std::runtime_error;

template <typename T>
class BiStack{
    
private:
    
    T* top1_;//track of latest entry for 1st stack
    T* top2_;//track of latest entry for 2nd stack
    long max_;
    long initial_;
    long elements1_, elements2_;//counters for elements in each stack
    T *data_;
    void grow_and_copy();
    
public:
    BiStack();
    BiStack(long, long);
    ~BiStack(); //destructor
    //BiStack(BiStack<T>& b);
    void push1(T);
    void push2(T);
    T top1();
    T top2();
    void pop1();
    void pop2();
    bool empty1();
    bool empty2();
    bool full();
    long size();
    BiStack& operator=(BiStack&);
    inline friend ostream& operator<<(ostream& out, const BiStack<T>& b){ //prints contents
        out << "Top 1:" << *b.top1_ << " " << "Top 2:" << *b.top2_ << endl;
        for (int i = 0; i < b.initial_; i++){
            out << b.data_[i] << " , ";
        }
        //copy(b.data_, b.data_+ b.initial_, ostream_iterator<T>(out, ","));
        return out;
    }
};

template<typename T>
BiStack<T>::BiStack(long max, long ini) : max_(max), initial_(ini){
    
    //creates data structure with base values unless otherwise specified
    //initial_ = ini;
    //max_ = max;
    data_ = new T[initial_]{0};
    elements1_ = 0; //sets all data memebers to default
    elements2_ = 0;
    top1_ = data_;
    top2_ = data_+sizeof(T)*ini;
}

template<typename T>
BiStack<T>::BiStack() : max_(32), initial_(4){
    
    //creates data structure with base values unless otherwise specified
    //initial_ = ini;
    //max_ = max;
    data_ = new T[initial_]{0};
    elements1_ = 0; //sets all data memebers to default
    elements2_ = 0;
    top1_ = data_;
    top2_ = data_+sizeof(T)*initial_;
}

template<typename T>
BiStack<T>::~BiStack(){
    
    //deletes the datastructure when needed
    delete [] data_;
}

template<typename T>
BiStack<T>& BiStack<T>::operator=(BiStack<T>& b){
    
    //attempting to find a way to copy one data structure into another data structure
    //swaps each individual element
    swap(top1_, b.top1_);
    swap(top2_, b.top2_);
    swap(elements1_, b.elements1_);
    swap(elements2_, b.elements2_);
    swap(initial_, b.initial_);
    swap(max_, b.initial_);
    swap(data_, b.data_);
    
    return *this;
}

template<typename T>
void BiStack<T>::grow_and_copy(){
    
    //in the event the data structure runs out of room, we create a new one 2x as big
    //and place the old into the new. Will not expand larger than designated max.
    if(initial_*2 <= max_){

        
        T *new_data;
        new_data = new T[initial_*2]{0};
        //create new data structure 2x the size
        //loop through data and new_data item by item and assign
        //do this for the amount of elements in data_ first stack
        
        for(long i = 0; i<elements1_; i++){
            new_data[i] = data_[i];
        }
        //loop through data and new_data item by item and assign
        //for the amount of elements in second stack.
        //use the idea that 2xinitial_ is a full new_data
        //subtract one from that and you have the last item in the stack
        //subract the current i from that and you have the desired position in the stack
        
        for(long i = elements2_, j = 0; i<initial_; i++, j++){
            new_data[initial_*2-elements2_+j] = data_[i];
        }
        //set all other values the same
        //flip the data structures positions in memory
        //copy(new_data, new_data+initial_*2, data_);
        //get rid of new_data now that we are done
        
        delete [] data_;
        data_ = new_data;
        initial_ = initial_ * 2;
    }
    else if (initial_ == max_){
        throw runtime_error("data structure met limit");
    }
    else{
        //same as above
        T *new_data;
        new_data = new T[max_];
        
        /*for(long i = 0; i<elements1_; i++){
            new_data[i] = data_[i];
        }
        for(long i = 0; i<elements2_; i++){
            new_data[max_-1-i] = data_[initial_-1-i];
        }*/
        
        for(long i = 0; i<elements1_; i++){
            new_data[i] = data_[i];
        }
        //loop through data and new_data item by item and assign
        //for the amount of elements in second stack.
        //use the idea that 2xinitial_ is a full new_data
        //subtract one from that and you have the last item in the stack
        //subract the current i from that and you have the desired position in the stack
        
        for(long i = elements2_, j = 0; i<initial_; i++, j++){
            new_data[initial_*2-elements2_+j] = data_[i];
        }
        
        //copy(new_data, new_data+initial_*2, data_);
        delete [] data_;
        data_ = new_data;
        //set initial_ to max_ instead of x2
        initial_ = max_;
    }
}

template<typename T>
void BiStack<T>::push1(T top){
    
    //method of adding a value to the first stack
    //checks to see if data structure is full
    if(!full()){
        //if not add to elements
        //place top in the next position of data_
        //set top1_ pointer to new element
        
        data_[elements1_] = top;
        top1_ = data_+sizeof(T) * elements1_;
        elements1_++;;
    }
    else{
        //if data structure is full
        //make room or throw error
        //same as above
        grow_and_copy();
        
        data_[elements1_] = top;
        //top1_ = data_[elements1_];
        top1_ = data_+sizeof(T) * elements1_;
        elements1_++;
    }
}

template<typename T>
void BiStack<T>::push2(T top){
    
    //method of adding a value to the second stack
    //checks to see if data structure is full
    if(!full()){
        //if not add to elements
        //place top in the next position of data_
        //set top2_ pointer to new element
        
        data_[initial_-elements2_] = top;
        top1_ = data_+sizeof(T)*(initial_-elements2_);
        elements2_++;
    }
    else{
        //if data structure is full
        //make room or throw error
        //same as above
        
        grow_and_copy();
        
        data_[initial_-elements2_] = top;
        top1_ = data_+sizeof(T)*(initial_-elements2_);
        //top1_ = data_[initial_-elements2_];
        elements2_++;
    }
}

template<typename T>
bool BiStack<T>::full(){
    
    //checks to see if data structure is full
    //compares sum of two element counters to current size
    if(elements1_ + elements2_ == initial_){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
void BiStack<T>::pop1(){
    
    if(empty1()){
        throw runtime_error("empty stack");
    }
    else{
        //throw runtime_error("empty stack");
        data_[elements1_ -1] = T();
        elements1_--;
        top1_ = data_-sizeof(T);
    }
}

template<typename T>
void BiStack<T>::pop2(){
    
    if(empty2()){
        throw runtime_error("empty stack");
    }
    else{
        //throw runtime_error("empty stack");
        data_[initial_ - elements2_ - 1] = T();
        elements2_--;
        top1_ = data_-sizeof(T);
    }
}

template<typename T>
bool BiStack<T>::empty1(){
    
    if(elements1_ == 0){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
bool BiStack<T>::empty2(){
    
    if(elements2_ == 0){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
T BiStack<T>::top1(){
    
    if(empty1()){
        return T();
    }
    return *top1_;
}

template<typename T>
T BiStack<T>::top2(){
    
    if(empty2()){
        return T();
    }
    return *top2_;
}

template <typename T>
long BiStack<T>::size() {
    return initial_;
};
#endif