// thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.tutorialcup.com/cplusplus/multithreading.htm

#include "pch.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include<conio.h>
#include<Windows.h>
#include<mutex>

std::mutex mtx;
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

vector<int> vec;
void push()
{
	for (int i = 0; i != 10; ++i)
	{
		cout << "Push " << i << endl;
		Sleep(500);
		vec.push_back(i);				// Adds a new element at the end of the vector, after its current last element
	}
}
void pop()
{
	for (int i = 0; i != 10; ++i)
	{
		if (vec.size() > 0)
		{
			int val = vec.back();        // Returns a reference to the last element in the vector
			vec.pop_back();				 // Removes the last element in the vector, effectively reducing the container size by one
			cout << "Pop " << val << endl;
		}
		Sleep(500);
	}
}





void push_order() {

	mtx.lock();
		for (int i = 0; i != 10; i++) {
			cout << "Push " << i << endl;
			Sleep(50);
			vec.push_back(i);

		}
	mtx.unlock();

}

void pop_order() {

	mtx.lock();
	for (int i = 0; i != 10; i++) {
		if (vec.size() > 0)
		{
			int val = vec.back();
			vec.pop_back();
			cout << "pop " << val << endl;
			}
		Sleep(50);
		}
	mtx.unlock();
}



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
	// Create three threads 
	myfunctorclass showmessage;
	thread t1(showmessage);
	thread t2(showmessage);
	thread t3(showmessage);

	// Get ID of all threads
	thread::id id1 = t1.get_id();
	thread::id id2 = t2.get_id();
	thread::id id3 = t3.get_id();

	// Join all the threads
	if (t1.joinable()) {
		t1.join();
		cout << endl;
		cout << "Thread with id " << id1 << "is terminated" << endl;

	}

	if (t2.joinable()) {
		t2.join();
		cout << "Thread with id " << id2 << "is terminated" << endl;

	}
	if (t3.joinable()) {
			t3.join();
			cout << "Thread with id " << id3 << "is terminated" << endl;
	}
	

	thread push(push);
	thread pop(pop);
	if (push.joinable())
		push.join();
	if (pop.joinable())
		pop.join();

	// Mutex Lock
	// Synchronization primitive - used to protect shared data from simultaneous access
	// A mutex can be locked and unlocked
	// Once mutex is locked , current thread owns mutex untill its not unlocked
	// No other thread can - execute any instructions from block of code surrounded by mutex - untill thread that owns mutex unlocks it
	// If you like to use mutex , you have to include mutex header into the program
	thread push_orderthread(push_order);
	thread pop_orderthread(pop_order);

	if (push_orderthread.joinable())
		push_orderthread.join();

	if (pop_orderthread.joinable())
		pop_orderthread.joinable();

	getchar();
	
}


