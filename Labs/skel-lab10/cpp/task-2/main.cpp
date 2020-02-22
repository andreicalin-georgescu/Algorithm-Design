#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <tuple>
#include <queue>
using namespace std;

const int kNmax = 2e5 + 10;

struct Compara {
    bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
			adj[y].push_back(make_pair(x, w));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Calculati costul minim al unui arbore de acoperire
		folosind algoritmul lui Prim.
		*/
		int muchiiama = 0;
        vector<int> d(n + 1, -1);
        vector<int> P(n + 1, 0);
        vector<bool> selectat(n + 1, false);
        vector<bool> sel(n + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compara> Q;

        Q.push(make_pair(0, 0));
        d[0] = 0;

        while (!Q.empty()) {
            int u = Q.top().first;
            Q.pop();
            selectat[u] = true;
            if (!sel[u]) {
            muchiiama += 
            for (int i = 0; i < adj[u].size(); i++) {
                int vecin = adj[u][i].first;

                if (!selectat[vecin] && (d[vecin] > d[u] || d[vecin] == -1)) {
                    d[vecin] = d[u] + adj[u][i].second;
                    Q.push(make_pair(vecin, d[vecin]));
                }
            }
            sel[u] = true;
            }

        }
		return 0;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
