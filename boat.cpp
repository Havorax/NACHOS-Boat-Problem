#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

void adult_itinerary();
void child_itinerary();

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cerr << "Usage: ./boat [num_adults] [num_children]\nExample: ./boat 1 2" << endl;
		return 1;
	}
	const int adults = atoi(argv[1]);
	const int children = atoi(argv[2]);
	cout << "Spawning " << adults << " adults and " << children << " children..." << endl;
	thread threads[adults + children];

	for (int i = 0; i < adults; ++i)
	{
		threads[i] = thread(adult_itinerary);
	}
	for (int i = 0; i < children; ++i)
	{
		threads[adults + i] = thread(child_itinerary);
	}

	for (int i = 0; i < adults + children; ++i)
	{
		threads[i].join();
	}

	return 0;
}

const int adult = 2;
const int child = 1;

bool finished = false;

mutex Oahu_pop;
unsigned int num_adults_at_Oahu = 0;
unsigned int num_children_at_Oahu = 0;

mutex boat_permit;
bool boat_at_Oahu = true;
unsigned int boat_capacity = 0;
bool allow_adult = false;

void adult_itinerary()
{
	bool at_Oahu = true;

	Oahu_pop.lock();
	cout << "Adult thread has spawned. " << endl;
	num_adults_at_Oahu++;
	Oahu_pop.unlock();

	this_thread::sleep_for(chrono::milliseconds(100));
	this_thread::yield();

	while (!finished)
	{
		boat_permit.lock();
		cout << "(A) Status: \tboat_at_Oahu: " << boat_at_Oahu 
			<< " \tat_Oahu: " << at_Oahu 
			<< " \tboat_capacity: " << boat_capacity 
			<< " \tallow_adult: " << allow_adult 
			<< " \tC_Oahu: " << num_children_at_Oahu
			<< " \tA_Oahu: " << num_adults_at_Oahu
			<< endl; 
		if (boat_at_Oahu && at_Oahu && boat_capacity == 0 && (allow_adult || num_children_at_Oahu == 0) && !finished && num_children_at_Oahu < 2)
		{
			cout << "Adult rows to Molokai" << endl;
			Oahu_pop.lock();
			num_adults_at_Oahu--;
			Oahu_pop.unlock();
			if ((num_adults_at_Oahu + num_children_at_Oahu) == 0)
			{
				finished = true;
			}
			at_Oahu = false;
			boat_at_Oahu = false;
			allow_adult = false;
		}
		boat_permit.unlock();
		else this_thread::yield();
	}

	return;
}

void child_itinerary()
{
	bool at_Oahu = true;

	Oahu_pop.lock();
	num_children_at_Oahu++;
	cout << "Child thread has spawned. " << endl;
	Oahu_pop.unlock();

	this_thread::sleep_for(chrono::milliseconds(100));

	while (!finished)
	{
		boat_permit.lock();
		cout << "(C) Status: \tboat_at_Oahu: " << boat_at_Oahu 
			<< " \tat_Oahu: " << at_Oahu 
			<< " \tboat_capacity: " << boat_capacity 
			<< " \tallow_adult: " << allow_adult 
			<< " \tC_Oahu: " << num_children_at_Oahu
			<< " \tA_Oahu: " << num_adults_at_Oahu
			<< endl; 
		if (boat_at_Oahu && at_Oahu && boat_capacity < 2 && !finished && (!allow_adult || num_children_at_Oahu > 0))
		{
			boat_capacity++;
			Oahu_pop.lock();
			num_children_at_Oahu--;
			Oahu_pop.unlock();
			at_Oahu = false;
			if ((num_adults_at_Oahu + num_children_at_Oahu) == 0)
			{
				finished = true;
				cout << "Child rows to Molokai" << endl;
				if (boat_capacity == 2)
				{
					cout << "Child rides to Molokai" << endl;
				}
				boat_capacity = 0;
				boat_at_Oahu = false;
			}
			else if (boat_capacity == 2)
			{
				cout << "Child rows to Molokai" << endl;
				cout << "Child rides to Molokai" << endl;
				boat_capacity = 0;
				boat_at_Oahu = false;
			}
			else if (num_children_at_Oahu == 0)
			{
				boat_capacity--;
				Oahu_pop.lock();
				num_children_at_Oahu++;
				Oahu_pop.unlock();
				at_Oahu = true;
			}
		}
		else if (!boat_at_Oahu && !at_Oahu && boat_capacity < 2 && !finished)
		{
			cout << "Child rows to Oahu" << endl;
			at_Oahu = true;
			Oahu_pop.lock();
			num_children_at_Oahu++;
			Oahu_pop.unlock();
			boat_at_Oahu = true;
			allow_adult = true;
		}
		boat_permit.unlock();
		else this_thread::yield();
	}

	return;
}