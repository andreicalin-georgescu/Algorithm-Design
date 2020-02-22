#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de subsiruri ale lui v cu suma numerelor para si
		returnati restul impartirii numarului la 10^9 + 7.
		*/


		long dp[n+1][2];
		int i;

		// suma para
		dp[0][0] = 0;
		// suma impara
		dp[0][1] = 0;

		for(i = 1; i <= n; i++) {
		    if(v[i] % 2 == 0) {
		        dp[i][0] = (2 * dp[i-1][0] + 1) % kMod;
		        dp[i][1] = (2 * dp[i-1][1]) % kMod;
		    } else {
		        dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % kMod;
		        dp[i][1] = (dp[i-1][0] + dp[i-1][1] + 1) % kMod;
		    }
		}
        return (int)dp[n][0];
	}

	    // daca vectorul are doar nr pare o sa am 2^(n) - 1
	    // daca vectorul are si numere impare voi avea 2^(n - 1) - 1

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
