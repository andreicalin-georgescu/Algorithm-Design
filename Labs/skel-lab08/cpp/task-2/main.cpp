#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
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

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void dfsArticulatie(int start, int& timp, vector<int>& idx, vector<int>& low, vector<int>& sol) {
		idx[start] = timp;
		low[start] = timp;
		timp ++;
		vector<int> copii;

		for (auto nod : adj[start]) {
			if(idx[nod] == -1) {
				copii.push_back(nod);
				dfsArticulatie(nod, timp, idx, low, sol);
				low[start] = min(low[start], low[nod]);
			} else {
				low[start] = min(low[start], idx[nod]);
			}
		}

		if(low[start] == idx[start]) {
			// punct de articulatie
			if (copii.size() >= 2) {
				sol.push_back(start);

			}
		} else {
			for (int copil : copii) {
				if (low[copil] >= idx[start]) {
					sol.push_back(start);
					break;
				}
			}
		}
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/
		vector<int> sol;
		vector<int>idx(n + 1, -1);
		vector<int> low(n + 1);
		int timp = 0;

		for (int i = 1; i <= n; i++) {
			if(idx[i] == -1) {
				dfsArticulatie(i, timp, idx, low, sol);
			}
		}
		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
