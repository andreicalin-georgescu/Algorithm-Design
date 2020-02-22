#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
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
	string expr;

	void read_input() {
		ifstream fin("1.in");
		fin >> n >> expr;
		expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de parantezari ale expresiei date astfel incat
		rezultatul sa dea true si returnati restul impartirii numarului
		la 10^9 + 7.
		*/

		// 2 matrici pentru valorile de adevar

		int F[n][n], T[n][n];


		// completam diagonala principala cu valorile literanzilor (operatorii nu ne intereseaza)
        for(int i = 0; i < n; i++)
        {
            F[i][i] = (expr[i] == 'F')? 1: 0;
            T[i][i] = (expr[i] == 'T')? 1: 0;
        }

        //pornesc de la a 2-a col ()
        for (int l = 1; l < n; l++){
            // parcurg diagonala secundara
            for (int i = 0, j = l; i < n; i+=2, j+=2) {
                // parcurg subsecventa
                for (int k = i + 1; k < j; k+=2) {
                    if (expr[k] == '&') {
                        T[i][j] += (T[i][k - 1] * T[k + 1][j])%kMod;
                        F[i][j] += (F[i][k - 1] * F[k + 1][j])%kMod;
                    }

                    if (expr[k] == '^') {
                        T[i][j] += (T[i][k - 1] * F[k + 1][j])%kMod +
                                (F[i][k - 1] * T[k + 1][j])%kMod;
                        F[i][j] += (F[i][k - 1] * F[k + 1][j])%kMod +
                                (T[i][k - 1] * T[k + 1][j]) % kMod;
                    }

                    if (expr[k] == '|') {
                        T[i][j] += (T[i][k - 1] * T[k + 1][j])%kMod + (T[i][k - 1] * F[k + 1][j]) % kMod
                                + (F[i][k - 1] * T[k + 1][j])%kMod;
                        F[i][j] += (F[i][k - 1] * F[k + 1][j])%kMod;
                    }
                }
            }
        }

        return T[0][n];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
