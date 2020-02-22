#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}

private:
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	void backtrack(int n, std::vector<int> & submultime, std::vector<std::vector<int>> & all, int pas = 0){
		int i;

		if (pas == 0) {
			i = 1;
		}

		else {
			i = submultime[pas - 1] + 1;
		}

		for (; i <= n; i++)
		{
			submultime.resize(pas + 1);
			submultime[pas] = i;
			all.push_back(submultime);
			backtrack(n, submultime, all, pas + 1);
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;
		all.push_back(std::vector<int>());
		std::vector<int> submultime;
		/*
        TODO: Construiti toate submultimile multimii {1, ..., N}.

        Pentru a adauga o noua submultime:
            vector<int> submultime;
            all.push_back(submultime);
        */

		backtrack(n, submultime, all);



		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					 (j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
