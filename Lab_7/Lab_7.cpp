#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

//if element is in the vector, it returns the index of the element. if not, it returns -1.
int FindIndex(string restaurantName, vector<string> &restaurants)
{
	for (int i = 0; i < restaurants.size(); i++)
	{
		if (restaurants[i] == restaurantName)
		{
			return i;
		}
	}

	return -1;
}

bool IsPowerOfTwo(float number)
{
	if ((int)number % 2 == 0)
	{
		while (number >= 1)
		{
			if (number == 1)
				return true;
			else
				number /= 2;
		}

		return false;
	}
	else
		return false;
}

void Battle(vector<string> &restaurants)
{
	if (IsPowerOfTwo(restaurants.size()))
	{
		vector<string> competitors = restaurants;
		vector<string> winners;
		int round = 1;

		while (competitors.size() > 1)
		{
			cout << "Round: " << round << endl;
			cout << endl;

			for (int i = 0; i < competitors.size(); i += 2)
			{
				int choice;
				bool isValid;

				do
				{
					cout << "Type \"1\" if you prefer " << competitors.at(i) << " or " << endl;
					cout << "Type \"2\" if you prefer " << competitors.at(i + 1) << endl;
					cout << "Choice: ";
					cin >> choice;

					if (cin.fail() || choice < 1 || choice > 2)
					{
						cout << "Invalid choice" << endl;
						isValid = false;
						cin.clear();
						cin.ignore(256, '\n');
					}
					else
					{
						cin.ignore(256, '\n');
						isValid = true;
					}

					cout << endl;

				} while (isValid == false);

				switch (choice)
				{
					case 1:
						winners.push_back(competitors.at(i));
						break;
					case 2:
						winners.push_back(competitors.at(i + 1));
						break;
				}
			}

			competitors = winners;
			winners.clear();
			round++;
		}

		cout << "The winning restaurant is " << competitors.at(0) << "." << endl;
		cout << endl;
	}
	else
	{
		cout << "The current tournament size (" << restaurants.size() << ") is not a power of two (2, 4, 8…)." << endl;
		cout << "A battle is not possible. Please add or remove restaurants." << endl;
	}
}

void ShuffleRestaurants(vector<string> &restaurants)
{
	if (IsPowerOfTwo(restaurants.size()))
	{
		vector<string> firstHalf;
		vector <string> secondHalf; 

		for (int i = 0; i < restaurants.size() / 2; i++)
		{
			firstHalf.push_back(restaurants.at(i));
		}

		for (int j = restaurants.size() / 2; j < restaurants.size(); j++)
		{
			secondHalf.push_back(restaurants.at(j));
		}

		vector<string> shuffled;

		for (int k = 0; k < firstHalf.size(); k++) //both firstHalf and secondHalf are the same size 
		{
			shuffled.push_back(secondHalf.at(k));
			shuffled.push_back(firstHalf.at(k));
		}

		restaurants = shuffled;
	}
	else
	{
		cout << "The current tournament size (" << restaurants.size() << ") is not a power of two (2, 4, 8…)." << endl;
		cout << "A shuffle is not possible. Please add or remove restaurants." << endl;
	}
}

void CutRestaurants(vector<string> &restaurants)
{
	int numToCut;
	bool isValid;
	do
	{
		cout << "How many restaurants should be taken from the top and put on the bottom? ";
		cin >> numToCut;

		if (cin.fail())//if input is not an int
		{
			cin.clear();
			cin.ignore(256, '\n');
			isValid = false;
		}
		else if (numToCut > restaurants.size() - 1)
		{
			cout << "The cut number must be between 0 and " << restaurants.size() - 1 << endl;
		}
		else
		{
			cin.ignore(256, '\n'); //fixes input problem with "getline()" in main()
			isValid = true;
		}

		cout << endl;

	}while (isValid == false); 

	vector<string> cutRestaurants;

	for (int i = numToCut; i < restaurants.size(); i++)
	{
		cutRestaurants.push_back(restaurants.at(i));
	}

	for (int j = 0; j < numToCut; j++)
	{
		cutRestaurants.push_back(restaurants.at(j));
	}

	restaurants = cutRestaurants;
}

void RemoveRestaurant(vector<string> &restaurants)
{
	string restaurantName;
	cout << "What is the name of the restaurant you want to remove?" << endl;
	getline(cin, restaurantName);
	cout << endl;

	int restaurantIndex = FindIndex(restaurantName, restaurants);
	if (restaurantIndex >= 0)
	{
		restaurants.erase(restaurants.begin() + restaurantIndex);
	}
}

void AddRestaurant(vector<string> &restaurants)
{
	string restaurantName;
	cout << "What is the name of the restaurant you want to add?" << endl;
	getline(cin, restaurantName);
	cout << endl;

	int restaurantIndex = FindIndex(restaurantName, restaurants);
	if (restaurantIndex < 0) //not in the vector
	{
		restaurants.push_back(restaurantName);
	}
}

void DisplayRestaurants(vector<string> &restaurants)
{
	for (int i = 0; i < restaurants.size(); i++)
	{
		cout << "\t" << restaurants.at(i) << endl;
	}

	cout << endl;
}

void DisplayOptions()
{
	cout << "Menu: Please select one of the following options :" << endl;
	cout << endl;

	cout << "quit - Quit the program" << endl;
	cout << "display - Display all restaurants" << endl;
	cout << "add - Add a restaurant" << endl;
	cout << "remove - Remove a restaurant" << endl;
	cout << "cut - \"Cut\" the list of restaurants" << endl;
	cout << "shuffle - \"Shuffle\" the list of restaurants" << endl;
	cout << "battle - Begin the tournament" << endl;
	cout << "options - Print the options menu" << endl;
	cout << endl;
}

int main()
{
	cout << "Welcome to the restaurant battle!Enter \"options\" to see options." << endl;

	string selection;
	bool isSelectionValid = false;
	
	vector<string> restaurants;

	do
	{
		cout << "Enter your selection : ";
		getline(cin, selection);
		cout << endl;

		if (selection == "options")
		{
			DisplayOptions();
		}
		else if (selection == "quit")
		{
			return 0;
		}
		else if (selection == "display")
		{
			DisplayRestaurants(restaurants);
		}
		else if (selection == "add")
		{
			AddRestaurant(restaurants);
		}
		else if (selection == "remove")
		{
			RemoveRestaurant(restaurants);
		}
		else if (selection == "cut")
		{
			CutRestaurants(restaurants);
		}
		else if (selection == "shuffle")
		{
			ShuffleRestaurants(restaurants);
		}
		else if (selection == "battle")
		{
			Battle(restaurants);
		}

	} while (isSelectionValid == false);

	cout << "Passed" << endl;
	system("pause");

	return 0;
}

