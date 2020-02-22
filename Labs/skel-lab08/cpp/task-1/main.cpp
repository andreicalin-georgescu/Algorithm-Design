#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
	vector<int> adjt[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	void dfsTarjan(int start, int& index, vector<int>& idx, vector<int>& lowLink, stack<int>& Stack, vector<bool>& inStack,	vector<vector<int>>& sol) {
			idx[start] = index;
			lowLink[start] = index;
			index ++;
			Stack.push(start);
			inStack[start] = true;

			for (auto nod : adj[start]) {
				if(idx[nod] == -1) {
					dfsTarjan(nod, index, idx, lowLink, Stack, inStack, sol);
					lowLink[start] = min(lowLink[start], lowLink[nod]);
				} else if (inStack[nod]) {
						lowLink[start] = min(lowLink[start], idx[nod]);
					}
			}

			if(lowLink[start] == idx[start]) {
				vector<int> solution;
				int aux = 0;
				// radacina unei ctc
				do {
					aux = Stack.top();
					Stack.pop();
					inStack[aux] = false;
					solution.push_back(aux);
				} while (start != aux);
				sol.push_back(solution);
			}
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.

		Atentie: graful transpus este stocat in adjt.
		*/
		vector<vector<int>> sol;
		vector<int>idx(n + 1, -1);
		vector<int> lowLink(n + 1);
		vector<bool> inStack(n + 1, false);
		stack<int> Stack;
		int index = 0;

		for (int i = 1; i <= n; i++) {
			if(idx[i] == -1) {
				dfsTarjan(i, index, idx, lowLink, Stack, inStack, sol);
			}
		}
		return sol;
	}

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
