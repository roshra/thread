// thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.tutorialcup.com/cplusplus/multithreading.htm

#include "pch.h"
#include <iostream>
#include <thread>
using namespace std;
void threadFunc();
void keralafunc();

void threadFunc()
{
	cout << "welcome to multithreading" << endl;

}

void keralafunc() {
	cout << "welcome to kerala" << endl;

}

int main() {
	// pass a function to thread
	// main thread does not wait for funcTest1 thread termination
	// main thread finishes execution while funcTest1 still running

	thread funcTest1(threadFunc);

	
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
	
}


