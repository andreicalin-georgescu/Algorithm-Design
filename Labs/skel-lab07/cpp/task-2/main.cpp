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
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		vector<int> topsort;
		queue<int> S;
		vector<int> indegree(n + 1, 0);
		// verific daca am in-muchie

		for(int i = 1; i <= n; i++){
			for(auto vecin : adj[i]){
				indegree[vecin]++;
			}
		}

		for (int i = 1; i <= n; i++) {
			if(indegree[i] == 0) {
				S.push(i);
			}
		}

		while(!S.empty()) {
			int u = S.front();
			S.pop();
			topsort.push_back(u);
			for (auto vecin : adj[u]) {
				// decr contor
				indegree[vecin]--;
				if (indegree[vecin] == 0) {
					S.push(vecin);
				}
			}
		}
		return topsort;
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
