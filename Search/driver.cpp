//Name: Shane Soderstrom
//Project: Search
//Class: CS 2420
//Date: 7/27/17


/**
* Add your code to this skeleton file to complete the search comparison
* project for the three specified sorts.
* It is expected that you will add additional methods to structure the simulation
* as discussed in class and for convenience.  This code is just a starting point.
*/

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <tuple>
#include <functional>
#include <time.h>
#include <chrono>
#include <fstream>

using std::vector;
using std::stringstream;
using std::cout;
using std::cin;
using std::string;
using std::ostream_iterator;
using std::endl;
using std::tuple;
using std::make_tuple;
using std::function;
using std::get;
const int TWO = 2;
const int THREE = 3;
/**
* Convenience function returns a comma-separated string version of the specified vector.
*/
string toString(const vector<int>& v)
{
	stringstream ss;
	copy(v.begin(), v.end(), ostream_iterator<int>(ss, ", "));
	return ss.str();
};

//iterative search requires a number to search for and a vector. Returns a tuple.
tuple<double, int> iterativeBinarySearch(int target, vector<int>& v) {
	//start the clock
	auto start = std::chrono::high_resolution_clock::now();
	int i = 0;
	int low = 0;
	int high = v.size() - 1;

	//if the vector is empty
	if (v.size() == 0)
	{
		i++;
		auto end = std::chrono::high_resolution_clock::now();
		double difference = (end - start).count() / 1e6;
		return make_tuple(difference, i);
	}
	i += TWO;

	//Find the number by dividing the size in half and searching based on size
	while (low <= high)
	{
		int mid = low + ((high - low) / TWO);

		//if number is smaller
		if (target < v[mid])
		{
			i++;
			high = mid - 1;
		}
		//if number is larger
		else if (target > v[mid])
		{
			i += TWO;
			low = mid + 1;
		}
		//if the target is found
		else if (target == v[mid])
		{
			i += THREE;
			auto end = std::chrono::high_resolution_clock::now();
			double difference = (end - start).count() / 1e6;
			return make_tuple(difference, i);
		}
		//if none of these are true
		else
		{
			i += THREE;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	double difference = (end - start).count() / 1e6;
	return make_tuple(difference, i);
}

//Recursive binary function requires a vector, starting value called first, vector size, target number to find, and a count called i.
//This returns a tuple.
tuple<double, int> recursiveBinarySearch(const vector<int>& v, size_t first, size_t size, int target, int& i) {
	//Start clock
	auto start = std::chrono::high_resolution_clock::now();
	size_t middle;

	//if it's empty
	if (size == 0) 
	{
		i++;
		auto end = std::chrono::high_resolution_clock::now();
		double difference = (end - start).count() / 1e6;
		return make_tuple(difference, i);
	}
	else {
		middle = first + size / 2;
		i++;

		//If number is found
		if (target == v[middle]) {
			auto end = std::chrono::high_resolution_clock::now();
			double difference = (end - start).count() / 1e6;
			return make_tuple(difference, i);
		}
		//if number is smaller
		else if (target < v[middle]) {
			recursiveBinarySearch(v, first, size / 2, target, i);
		}
		//if number is larger
		else {
			recursiveBinarySearch(v, middle + 1, (size - 1) / 2, target, i);
		}
	}
}


//Linear Search function. Needs to have a vector and a number to search for.
//Returns a tuple.
tuple<double, int> linearSearch(int target, vector<int>& v) {
	//Start the clock and start counting comparisons.
	auto start = std::chrono::high_resolution_clock::now();
	int j = 0;
	int size = v.size();

	//For loop to search for the target.
	for (int i = 0; i < size; i++)
	{
		j += TWO;
		//If target is found.
		if (v[i] == target)
		{
			j++;
			auto end = std::chrono::high_resolution_clock::now();
			double difference = (end - start).count() / 1e6;
			return make_tuple(difference, j);
		}
	}
	//If the loop is never entered or the if condition inside is never hit.
	auto end = std::chrono::high_resolution_clock::now();
	double difference = (end - start).count() / 1e6;
	return make_tuple(difference, j);
}

/**
* A convenience method to create a vector of size VectorSize of random integers where
* each value is between 0 and (M-1).
*/
vector<int> makeRandomVector(unsigned int vectorSize, unsigned int M)
{
	vector<int> v(vectorSize);
	std::generate(v.begin(), v.end(), [&M] { return rand() % M; });
	return v;
}


/**
* @TODO Add your application code here.
*/
int main()
{
	unsigned int size = 100;
	unsigned int numRange = 100;
	//Create a csv file
	std::ofstream numbers;
	string file = "calculations.csv";
	numbers.open(file);
	//Check to see if the csv worked
	if (numbers.fail())
	{
		cout << "Could not open file. Please make sure that the excel file is closed and that the file path is correct.";
		system("PAUSE");
		exit(0);
	}
	//Print column titles in file.
	numbers << "Search Method" << "," << "Wall Time" << "," << "Number of Comparisons" << "," << "Vector Size" << endl;

	numbers.close();

	tuple<double, int> value;
	tuple<double, int> valueTwo;
	tuple<double, int> valueThree;
	int target;
	vector<int> v;
	size_t first = 0;
	size_t sizes = 0;
	int count = 0;
	for (int i = 0; i <= THREE; i++)
	{
		//Create a vector and a number to find.
		size *= 10;
		numRange *= 10;
		target = rand() % numRange;
		v = makeRandomVector(size, numRange);

		//sort the function so it works.
		cout << "Sorting the vector of size " << size << "." << endl;
		sort(begin(v), end(v));
		sizes = v.size();

		//Call the three search functions
		cout << "Conducting recursive binary search. ";
		value = recursiveBinarySearch(v, first, sizes, target, count);
		cout << "Time taken: " << get<0>(value) << endl;

		cout << "Conducting iterative binary search. ";
		valueTwo = iterativeBinarySearch(target, v);
		cout << "Time taken: " << get<0>(valueTwo) << endl;

		cout << "Conducting linear search. ";
		valueThree = linearSearch(target, v);
		cout << "Time taken: " << get<0>(valueThree) << endl << endl;

		//Open file
		numbers.open(file, std::ios_base::app);

		//Check to see if the csv worked
		if (numbers.fail())
		{
			cout << "Could not open file. Please make sure that the excel file is closed and that the file path is correct.";
			system("PAUSE");
			exit(0);
		}

		//Print the tuple data to the csv file.
		numbers << "Recursive" << "," << get<0>(value) << "," << get<1>(value) << "," << size << endl;
		numbers << "Iterative" << "," << get<0>(valueTwo) << "," << get<1>(valueTwo) << "," << size << endl;
		numbers << "Linear" << "," << get<0>(valueThree) << "," << get<1>(valueThree) << "," << size << endl;
		v.erase(v.begin(), v.end());
		numbers.close();
	}

	//hold the console open
	system("PAUSE");
	return 0;
};
