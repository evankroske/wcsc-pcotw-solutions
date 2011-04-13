#include <iostream>
#include <set>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;

int main () {
	while (cin) {
		set<int> foundNums;
		int numNums;
		cin >> numNums;

		if (!cin.good()) break;

		int min = 1;
		int max = numNums - 1;
		bool jolly = true;
		int lastNum;
		cin >> lastNum;

		for (int i = 0; i < numNums-1; i++) {
			int num;
			cin >> num;
			int diff = abs(num - lastNum);
			int inRange = diff >= min && diff <= max;
			int unique = foundNums.insert(diff).second;
			if (!inRange || !unique) {
				jolly = false;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				break;
			}
			lastNum = num;
		}
		string result = (jolly) ? "Jolly" : "Not jolly";
		cout << result << endl;
	}
	return 0;
}
