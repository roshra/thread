// thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.tutorialcup.com/cplusplus/multithreading.htm

#include "pch.h"
#include <iostream>
#include <thread>
#include <string>

using namespace std;
void threadFunc();
void keralafunc();
void funcbangalore();

void threadFunc()
{
	cout << "welcome to multithreading" << endl;

}

void keralafunc() {
	cout << "welcome to kerala" << endl;

}

void funcbangalore() {

	cout << "welcome to bangalore" << endl;
}


class myfunctorclass {
public:

	void operator()() {
		cout << "This is my function object from class myfunctorclass" << endl;
	}

	void publicfunction() {

		cout << "publicfunction of myfunctorclass is called" << endl;
	}

	
	    void printsomevalues() {

		cout << "printsomevalues of myfunctorclass is called" << endl;

	}
};	

void myvalues(int val, char str, double dval)
{
	cout << val << " " << str << " " << dval << endl;

}

class myFunctorParam {

public:
	void operator() (int * arr, int length) {
		cout << "An array of length" << length << "is passed to thread" << endl;
		for (int i = 0; i != length; i++)
			cout << arr[i] << " " << endl;
		cout << endl;
	}

	void changesign (int * arr1, int length2) {
		cout << length2 << endl;
		cout << arr1[0] << endl;
		cout << arr1[1] << endl;
		cout << arr1[2] << endl;
		cout << arr1[3] << endl;
		cout << arr1[4] << endl;
		

	}
};

int main() {

	// Basic thread 
	// pass a function to thread
	// main thread does not wait for funcTest1 thread termination
	// main thread finishes execution while funcTest1 still running and error would pop up if you hide line 41

	thread funcTest1(threadFunc);

	
	// Thread join activity - making all main and child thread synchronized
	// Join function returns only post all threads are terminated
	// main thread will wait untill child thread finish execution
	funcTest1.join();


	
	// afterjoin() returns thread becoms non joinable 
	// thread is not joinable if moved/assigned to another thread 
	// or join() or detach()
	// check if a thread is joinable by using joinable() function
	thread keralathread(keralafunc);

	// check if thread is joinable
	if (keralathread.joinable()) {       // joinable is boolean

		keralathread.join();
	}



	// Thread detach activity , making main and child threads not synchronized
	// detach function detaches a function from parent thread 
	// It allows parent and child threads to be executed independetly from each other 
	// after call of detach function detach, the two threads are not synchronized in any ways
	// post detach You will notice that main thread is not waiting for the termination of its child thread
	thread bangalorethread(funcbangalore);
	cout << "detaching the bangalore thread now" << endl;
	bangalorethread.detach();
	if (bangalorethread.joinable()) {

		cout << "bangalore thead is joinable" << endl;

	}
	else
	{
		cout << "bangalore thread is not joinable as detached in line 60" << endl;
	}


	// Initializing thread with an object
	// you can initialize thread not only with function but also with
	// function object - functor or member function of class
	// publicfunction is another function of myfunctor class and line 117 calls the public function seperately


	myfunctorclass myobject;
	thread threadclass(myobject);				// Initialing thread with object
	if (threadclass.joinable())
		threadclass.join();
	myfunctorclass myobjecta;
	thread threadclassa(&myfunctorclass::publicfunction, myobjecta);   // Initializing thead with function . Scope resolution operator :: to access a global variable when there is a local variable with same name
	if (threadclassa.joinable())
		threadclassa.join();
	

	// Passing arguments to thread
	// We used functions with objects to initialize thread
	// but we did not pass arguments with function to initialize thread
	// Lets do that now
	myfunctorclass myobjectb;
	thread threadclassb(&myfunctorclass::printsomevalues, myobjectb);
	if (threadclassb.joinable())
		threadclassb.join();


	// Passing arguments to thread
	// We used functions with objects to initialize thread
	// but we did not pass arguments with function to initialize thread
	// Lets do that now
	char str = 'h';
	thread parampassthread(myvalues,2,str,3.2);
	if (parampassthread.joinable())
		parampassthread.join();

	// Initialize thread with object and parameters 
	// These params will be passed to the thread
	//these parameters will be passed to thread
	int arr[5] = { 1, 3, 5, 7, 9 };
	myFunctorParam objParamPass;
	thread test(objParamPass, arr,5);
	if (test.joinable())
		test.join();

	// Initialize thread using member function of class
	// Here we using &myFunctorParam::changesign, myFunctorParam is class and changesign is local function of class
	int arr2[5] = { -1,3,5,-7,0 };
	myFunctorParam objParamPass2;
	thread test2(&myFunctorParam::changesign, &objParamPass2, arr2, 5);
	if (test2.joinable())
		test2.join();

	// Thread ID 
}


