#include <iostream>
#include <vector>

using namespace std;

bool isSolution (vector<int> a)
{
	return true;
}

void processSolution (vector<int> a)
{
}

vector<int> genCandidates (vector<int>a, int n, int k)
{
	return vector<int>();
}

void genSolutions (vector<int> a, int n, int k)
{
	if (isSolution(a)) {
		processSolution(a);
		return;
	}
	vector<int> candidates = genCandidates(a, n, k);
	vector<int>::iterator i;
	for (i = candidates.begin(); i != candidates.end(); i++) {
		int c = *i;
		a.push_back(c);
		genSolutions(a, n, k);
		a.pop_back();
	}
}

int main () 
{
	cout << "Hello, world!\n";
	return 0;
}

