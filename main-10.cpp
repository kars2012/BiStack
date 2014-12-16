#include<iostream>
using std::cout; using std::endl;
#include "class-10.h"

int main() {
    BiStack<long> bs_l(32,4);
    cout << bs_l << endl;
    for(int i=1; i<4; i++){
	bs_l.push1(i);
	bs_l.push2(-i);
    }

    BiStack<long> bs_l2;
    bs_l2 = bs_l;
    
    try{
	for(int i=1; i<16; i++){
	    bs_l2.push1(i);
	    bs_l2.push2(-i);
	}
    }
    catch (runtime_error err){
	cout << "stack hit the max. Real error msg follows"<<endl;
	cout << err.what() << endl;
    }

    cout << bs_l << endl;
    cout << "top1 val:"<<bs_l.top1()<<endl;
    cout << "top2 val:"<<bs_l.top2()<<endl;

    for(int i=0; i< 3; i++)
	bs_l.pop2();
    cout << "top1 val:"<<bs_l.top1()<<endl;
    cout << "top2 val:"<<bs_l.top2()<<endl;    
    cout << bs_l << endl;

    try{
	bs_l.pop2();
    }
    catch (runtime_error err){
	cout << "stack empty 2. Real error msg follows"<<endl;
	cout << err.what() << endl;
    }
    
}
