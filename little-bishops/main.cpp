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

int countDiagonals (int n)
{
	return 2 * n - 1;
}

bool isSolution (int n, int k)
{
	return countDiagonals(n) == k;
}

void processSolution (vector<int> & a)
{
	numSolutions++;
}

int countSquares (int n, int k)
{
	int numD = countDiagonals(n);
	if (k <= numD / 2) {
		return k + 1;
	} else {
		return numD - k;
	}
}

void genCandidates (vector<int> & a, int n, int maxBishops, int k, vector<int> & candidates)
{
	int numBishops = countBishops(a);
	int numSquares = countSquares(n, k);
	bool * emptyRows = new bool[n];
	fill(emptyRows, emptyRows + n, true);
	if (numBishops < maxBishops) {
		// Loop through diagnoals of the same parity as the current one.
		for (int j = (numSquares - 1) % 2; j < k; j += 2) {
			int bishopIndex = a.at(j);
			if (bishopIndex != INT_MAX) {
				emptyRows[bishopIndex] = false;
			}
		}
		for (int i = 0; i < numSquares; i++) {
			// Generate absolute index for bishop. May be negative.
			int candidateIndex = i - numSquares / 2 + n / 2;
			if (emptyRows[candidateIndex]) {
				candidates.push_back(candidateIndex);
			}
		}
	}
	if (maxBishops - numBishops < countDiagonals(n) - k) {
		candidates.push_back(INT_MAX);
	}
}

void genSolutions (vector<int> & a, int n, int maxBishops, int k)
{
	if (isSolution(n, k)) {
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

int main (int argc, char ** argv) 
{
	if (argc == 1) {
		while (true) {
			int n, numBishops;
			cin >> n;
			cin >> numBishops;
			if (n == 0) {
				break;
			}
			vector<int> solutions;
			genSolutions(solutions, n, numBishops, 0);
			cout << numSolutions << "\n";
			numSolutions = 0;
		}
	} else {
		int tmp[] = {10, -2, 3, 5, INT_MAX, 6, 7};
		vector<int> bishops(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));
		cout << countBishops(bishops) << "\n";
		cout << countSquares(3, 2) << " should be 3\n";
		cout << countSquares(3, 4) << " should be 1\n";
		cout << countSquares(4, 4) << " should be 3\n";
	}
	return 0;
}
