#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int kNmax = 1005;

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
  int C[kNmax][kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
      C[x][y] += z;
		}
		fin.close();
	}
	//functie de bfs pentru descoperirea drumului minim intre doua noduri

    int bfs(vector<int>& visited, vector<int>& parinte) {
	    // setez vectorul de vizitat la 0

	    int sursa = 1;
	    int destinatie = n;

        for (int i = 0; i < visited.size(); ++i) {
            visited[i] = 0;
        }

        // nodul sursa (1) e marcat ca vizitat

        visited[sursa] = 1;


        queue<int> Queue;
        Queue.push(sursa);

        while (!Queue.empty()) {
            // se extrage primul nod din coada

            int nod = Queue.front();
            Queue.pop();
            
            for (int neighbour : adj[nod]) {
                // daca neighbourul nu a fost vizitat si avem capacitate  intre nod si neighbour (drum de ameliorare)

                if (!visited[neighbour] && C[nod][neighbour]) {
                    visited[neighbour] = 1;
                    parinte[neighbour] = nod;

                    if (neighbour != destinatie) {
                        Queue.push(neighbour);

                    } else {
                        return 1;
                    }
                }

            }
        }
        // vedem daca nodul destinatie poate fi vizitat

        return visited[destinatie];
    }

	int get_result() {
		/*
		TODO: Calculati fluxul maxim pe graful orientat dat.
		Sursa este nodul 1.
		Destinatia este nodul n.

		In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
		arcelor, iar in C sunt stocate capacitatile arcelor.
		De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
		C[x][y] = z, adj[x] contine y, adj[y] contine x.
		*/
		int maxFlow = 0;
		int sursa = 1;
		int dest = n;

        vector<int> visited(n + 1);
        vector<int> parinte(n + 1);
        // implementarea algoritmului Edmonds - Karp

        while (bfs(visited, parinte)) {
            for (int neighbour : adj[dest])
                // daca neighbourul a fost vizitat si exista capacitate intre neighbour si nodul sursa (n)

                if (visited[neighbour] && C[neighbour][dest]) {
                    int flow = C[parinte[dest]][dest];
                    parinte[dest] = neighbour;
                    // parcurgem drumul invers de la nodul destinatie la nodul sursa, trecand prin fiecare parinte

                    int j = dest;
                    while (j != sursa) {
                        flow = min(flow, C[parinte[j]][j]);
                        j = parinte[j];
                    }
                    // parcurgem drumul invers de la nodul destinatie la nodul sursa, actualizand capacitatea

                    j = dest;
                    while (j != sursa) {
                        // avem grija sa pastram proprietatea de antisimetrie

                        C[parinte[j]][j] -= flow;
                        C[j][parinte[j]] += flow;
                        j = parinte[j];

                    }
                    // adaugam fluxul pentru acest drum la fluxul maxim

                    maxFlow += flow;
                }
        }

		return maxFlow;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
