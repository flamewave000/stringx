#include <iostream>
#include "../include/stringx.h"

using namespace std;
using namespace strx;


int main() {

	string firstName, lastName;
	int age = 0;
	float weight = 0;
	cout << "Please enter your first name: " << flush;
	cin >> firstName;
	cout << "Please enter your last name: " << flush;
	cin >> lastName;
	cout << "Please enter your age: " << flush;
	cin >> age;
	cout << "Please enter your weight: " << flush;
	cin >> weight;

	cout <<
		"\nHello {0} {1}\n{2}: {3}\n{4}: {5}\n"_f
		% firstName
		% lastName
		% lpad("age", 6)
		% age
		% "weight"
		% spec("%.0f", weight)
		<< endl;

	string dev_null;
	cout << "Enter anything to exit: " << flush;
	cin >> dev_null;

	return 0;
}