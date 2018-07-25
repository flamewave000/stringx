#include <iostream>
#include <limits>
#include "stringx.hpp"

using namespace std;
using namespace strx;

struct name_pair { string first, last; };
format& operator%(format &&fmt, const name_pair &pair) {
	fmt.append(pair.first + ' ' + pair.last);
	return fmt;
}

int main() {
	name_pair name;// = { "Andrew","Fryer" };
	int age = 0;// 27;
	float weight = 0;// 221;
	cout << "Please enter your first name: " << flush;
	cin >> name.first;
	cout << "Please enter your last name: " << flush;
	cin >> name.last;
	cout << "Please enter your age: " << flush;
	cin >> age;
	cout << "Please enter your weight: " << flush;
	cin >> weight;

	cout <<
		"\nHello {0}\n{1}: {2}\n{3}: {4}\n"_f
		% name
		% lpad("age", 6)
		% age
		% "weight"
		% spec("%.0f", weight)
		<< endl;

	cout <<
		"\nHello {#}\n{#}: {#}\n{#}: {#}\n"_f
		% name
		% lpad("age", 6)
		% age
		% "weight"
		% spec("%.0f", weight)
		<< endl;

	cout << "Press any key to continue..." << flush;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	return 0;
}
