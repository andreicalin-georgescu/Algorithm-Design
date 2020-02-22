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

	struct Edge {
		int x;
		int y;
	};

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

	void dfsCritica(int start, int parinte, int& timp, vector<int>& idx, vector<int>& low, vector<Edge>& sol) {
		idx[start] = timp;
		low[start] = timp;
		timp ++;

		for (auto nod : adj[start]) {
			if(nod != parinte) {
				if(idx[nod] == -1) {
					dfsCritica(nod, start, timp, idx, low, sol);
					low[start] = min(low[start], low[nod]);
					if(low[nod] > idx[start]) {
						// adaug muchie la solutie
						Edge aux;
						aux.x = start;
						aux.y = nod;
						sol.push_back(aux);
					}
				} else {
					low[start] = min(low[start], idx[nod]);
				}
			}

		}
	}

	vector<Edge> get_result() {
		/*
		TODO: Gasiti muchiile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/

		vector<Edge> sol;
		vector<int>idx(n + 1, -1);
		vector<int> low(n + 1);
		int timp = 0;
		int parinte = 1;

		for (int i = 1; i <= n; i++) {
			if(idx[i] == -1) {
				dfsCritica(i, parinte, timp, idx, low, sol);
			}
		}

		return sol;
	}

	void print_output(vector<Edge> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i].x << ' ' << result[i].y << '\n';
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
