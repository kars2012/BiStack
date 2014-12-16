#ifndef proj10_class_10_h
#define proj10_class_10_h

#include <stdexcept>
using std::runtime_error;

template <typename T>
class BiStack{
	private:
		long limit;
		long total_size;
		T* left_top;
		T* right_top;
		long left_size;
		long right_size;
		T* data;
		void grow_and_copy();
	public:
		BiStack();
		BiStack(long, long);
		~BiStack();
		long size();
		bool empty1();
		bool empty2();
		void pop1();
		void pop2();
		T top1();
		T top2();
		void push1(T);
		void push2(T);
		bool full();
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

template <typename T>
BiStack<T>::BiStack():limit(32),total_size(4){
	data = new T[total_size]{0};
	left_top = data;
	right_top = data + sizeof(T)*total_size;
	left_size = 0;
	right_size = 0;
}

template <typename T>
BiStack<T>::BiStack(long max, long initial_size): limit(max),total_size(initial_size){
	data = new T[total_size]{0};
	left_top = data;
	right_top = data + sizeof(T)*total_size;
	left_size = 0;
	right_size = 0;
}

template <typename T>
BiStack<T>::~BiStack(){
	delete[] data;
}

template <typename T>
void BiStack<T>::grow_and_copy(){
	
	if (total_size *2 <= limit)
	{
		T* new_array = new T[total_size*2]{0};
		for (int i = 0; i < left_size; i++)
		{
			new_array[i] = data[i];
		}
		for(long i = right_size - 1, j = 0; i<total_size; i++, j++){
            new_data[total_size*2-right_size+j] = data_[i];
        }
        total_size *= 2;
        delete [] data;
        data = new_array;
        delete new_array;
        left_top = data + left_size*sizeof(T);
        right_top = data + (total_size - right_size-1)*sizeof(T);
		
	}
	else if (total_size * 2 > limit && total_size < limit)
	{
		T* new_array = new T[limit]{0};
		for (int i = 0; i < left_size; i++)
		{
			new_array[i] = data[i];
		}
		for(long i = right_size - 1, j = 0; i<total_size; i++, j++){
            new_data[total_size*2-right_size+j] = data_[i];
        }
        total_size = limit;
        delete [] data;
        data = new_array;
        delete new_array;
        left_top = data + left_size*sizeof(T);
        right_top = data + (total_size - right_size-1)*sizeof(T);
	}
	else
	{
		throw runtime_error("data structure met limit");
	}
	
}

template <typename T>
bool BiStack<T>::empty1(){
	return left_size == 0;
}

template <typename T>
bool BiStack<T>::empty2(){
	return right_size == 0;
}

template <typename T>
bool BiStack<T>::full(){
	return (left_size + right_size) == total_size;
}

template <typename T>
void BiStack<T>::pop1(){
	*left_top = 0;
	left_top -= sizeof(T);
	left_size --;
}

template <typename T>
void BiStack<T>::pop2(){
	*right_top = 0;
	right_top += sizeof(T);
	right_size --;
}

template <typename T>
void BiStack<T>::push1(T element){
	if ((left_top + sizeof(T)) == right_top) grow_and_copy();
	
	left_top += sizeof(T);
	*left_top = element;
	left_size ++;	
}

template <typename T>
void BiStack<T>::push2(T element){
	if ((right_top - sizeof(T)) == left_top) grow_and_copy();
	
	right_top -= sizeof(T);
	*right_top = element;
	right_size ++;
}

template <typename T>
T BiStack<T>::top1(){
	return *left_top;
}

template <typename T>
T BiStack<T>::top2(){
	return *right_top;
}

template <typename T>
long BiStack<T>::size(){
	return total_size;
}


#endif