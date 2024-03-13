// Michael Walker
// CSC275
// Assignment 4: Multi-threading
// Due: 03/17/2024

// TODO: Demonstrate the creation, execution, and management of multiple threads in a C++ program.
// - Clearly use true multi-threading.
// - Over comment all your code for future you in your own words.
// - Your program should do something in addition to clearly demonstrating multi-threading.
// - You must have a good UX and keep the user over-informed of what is happening.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

// Global variables:
const int numThreads = 5;
mutex mtx;

// Function to determine random distance of incoming asteroid:
int AsteroidDistance() 
{
	// Create a random number generator:
	static random_device rd;

	// Initialize the Mersenne Twister engine with a seed:
	static mt19937 gen(rd());

	// Create a uniform distribution for integers between 1000 and 10000:
	uniform_int_distribution<int> dis(1000, 10000);

	// Return a random number between 1000 and 10000:
	return dis(gen);
}

// Function to be called by each thread:
void ThreadFunction(int tid) {
	// Lock the mutex to prevent other threads from accessing the console:
	mtx.lock();

	// Display the distance of the incoming asteroid:
	cout << "Asteroid " << tid + 1 << " is " << AsteroidDistance() << " miles away." << endl;

	// Unlock the mutex to allow other threads to access the console:
	mtx.unlock();
}

class InterceptionThread
{
public:
	void operator()(int tid)
	{
		cout << "[ALERT]: InterceptionThread " << tid << " initialized." << endl;
		cout << "[ALERT]: InterceptionThread " << tid << " is waiting for the asteroid to get closer." << endl;
		this_thread::sleep_for(chrono::seconds(5));
		cout << "[ALERT]: InterceptionThread " << tid << " is now intercepting the asteroid." << endl;
		this_thread::sleep_for(chrono::seconds(5));
		cout << "[ALERT]: InterceptionThread " << tid << " has successfully intercepted the asteroid." << endl;
	}
};

int main() 
{
	// Display a message to the console to indicate that the program is starting:
	cout << "+----------------------------------------+" << endl;
	cout << "|  Center for Near-Earth Object Studies  |" << endl;
	cout << "|        Asteroid Tracking System        |" << endl;
	cout << "+----------------------------------------+" << endl;
	cout << endl;
	cout << "This application tracks Potentially Hazardous Asteroids (PHAs) as they approach Earth." << endl;
	cout << "The system uses multiple threads to track the distance of each incoming asteroid." << endl;
	cout << "The distance of each asteroid is displayed in miles." << endl;
	cout << endl;

	// Create an array of threads:
	thread threads[numThreads];

	// Populate the array with threads:
	for (int i = 0; i < numThreads; i++)
	{
		threads[i] = thread(ThreadFunction, i);
	}

	// Print a message to the console to indicate that all threads have been initiated:
	cout << "[INFO]: All threat asteroid tracking threads have been initiated." << endl;

	// Join all threads to the main thread of execution:
	for (int i = 0; i < numThreads; i++)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
		else
		{
			cout << "[ERROR]: Tracking thread " << i + 1 << " is not joinable." << endl;
		}
	}

	// Print a message to the console to indicate that all threads have been joined:
	cout << "[INFO]: All asteroid tracking threads have been joined." << endl;

	// Wait for user input:
	cin.get();

	// Clear the console:
	system("cls");

	// Create a new thread using a function object:
	InterceptionThread interceptor;
	thread interceptorThread(interceptor, 1);

	// Wait for the interceptor thread to join the main thread of execution:
	if (interceptorThread.joinable())
	{
		interceptorThread.join();
	}
	else
	{
		cout << "[ERROR]: Interceptor thread is not joinable." << endl;
	}

	// Print a message to the console to indicate that the interceptor thread has been joined:
	cout << "[INFO]: Interceptor thread has been joined." << endl;

	// Print a message to the console to indicate the asteroid interception program is ending:
	cout << "[INFO]: CNEOS PHA interception program is ending." << endl;

	// Return 0 to indicate successful completion:
	return 0;
}