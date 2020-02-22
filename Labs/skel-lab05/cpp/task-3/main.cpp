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

	void n_queens(int n, vector<int> &sol) {
		vector<int> queens = vector<int>();
		backtrack(queens,0,n, sol);
	}

	bool is_solution(const vector<int>& queens, int n) {
		return queens.size() == n;
	}

	void save_solution(vector<int> &queens, vector<int> &sol) {
		int k = 0;
		for (int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if (queens[i] == j) {
					// aici am o regina la pozitia i j
					sol[k] = j;
					k++;
				}
			}
		}

	}

	void backtrack(vector<int>& queens, int current_row, int n, vector<int> &sol) {
		// check if the configuration is solved
		if(is_solution(queens, n))
		{
			save_solution(queens, sol);
		}
		else
		{
			// construct a vector of valid candidates
			vector<int> candidates = vector<int>();
			if(construct_candidates(queens,current_row,n,candidates))
			{
				for(int i=0; i < candidates.size(); ++i)
				{
					// Push this in the partial solution and move further
					queens.push_back(candidates[i]);
					backtrack(queens,current_row + 1,n, sol);
					// If no feasible solution was found then we ought to remove this and try the next one
					queens.pop_back();
				}
			}
		}
	}

	bool is_safe_square(const vector<int>& queens, int row, int col, int n) {
		for(int i=0; i<queens.size(); ++i)
		{
			// case when the queens are already placed in the same row or column
			if(i == row || queens[i] == col) return false;
			// case when there is a diagonal threat
			// remember! y = mx + c for a diagonal m = 1 therefore |x2 - x1| = |y2 - y1|
			if(abs(i - row) == abs(queens[i] - col)) return false;
		}
		//Returns true when no unsafe square is found
		//handles the case when there are no queens on the board trivially
		return true;
	}

	bool construct_candidates(const vector<int>& queens, int row, int N, vector<int>& candidates) {
		// Returns false if there are no possible candidates, we must follow a different
		// branch if this so happens
		for(int i=0; i < n; ++i)
		{
			if(is_safe_square(queens,row,i,n))
			{
				// Add a valid candidate, this can be done since we pass candidates by reference
				candidates.push_back(i);
			}
		}
		return candidates.size() > 0;
	}



	vector<int> get_result() {
		vector<int> sol(n + 1, 0);
		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/

		n_queens(n, sol);
		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
