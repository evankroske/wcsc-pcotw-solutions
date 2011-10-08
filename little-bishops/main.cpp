#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int numSolutions = 0;

int countBishops (vector<int> & a)
{
	int numBishops = 0;
	vector<int>::iterator i;
	for (i = a.begin(); i != a.end(); i++) {
		numBishops += (*i != INT_MAX) ? 1 : 0;
	}
	return numBishops;
}

bool isSolution (vector<int> a)
{
	return countBishops(a) == 3;
}

void processSolution (vector<int> a)
{
	numSolutions++;
}

int countSquares (int n, int k)
{
	if (k <= n / 2 - 1 + n % 2) {
		return k + 1;
	} else {
		return n - k;
	}
}

void genCandidates (vector<int> a, int n, int maxBishops, int k, vector<int> & candidates)
{
	int numBishops = countBishops(a);
	int numSquares = countSquares(n, k);
	if (numBishops < maxBishops) {
		for (int i = 0; i < numSquares; i++) {
			int candidateIndex = i - numSquares / 2;
			for (int j = (numSquares - 1) % 2; j < k; j += 2) {
				int bishopIndex = a.at(j);
				if (bishopIndex == INT_MAX) {
					candidates.push_back(candidateIndex);
				} else if (bishopIndex != candidateIndex) {
					candidates.push_back(candidateIndex);
				}
			}
		}
	}
	candidates.push_back(INT_MAX);
}

void genSolutions (vector<int> & a, int n, int maxBishops, int k)
{
	if (isSolution(a)) {
		processSolution(a);
		return;
	}
	vector<int> candidates;
	genCandidates(a, n, maxBishops, k, candidates);
	vector<int>::iterator i;
	for (i = candidates.begin(); i != candidates.end(); i++) {
		int c = *i;
		a.push_back(c);
		genSolutions(a, n, maxBishops, k+1);
		a.pop_back();
	}
}

int main () 
{
	while (true) {
		int n, numBishops;
		cin >> n >> numBishops;
		if (n == 0) {
			break;
		}
		vector<int> solutions;
		genSolutions(solutions, n, numBishops, 0);
		cout << numSolutions << "\n";
		numSolutions = 0;
	}
	return 0;
}
