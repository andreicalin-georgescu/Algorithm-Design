#include <fstream>
#include <vector>
#include <algorithm>

int main(){
    std::vector<int> numbers;
    int N, aux, Total_sum = 0;

    std::ifstream fin("p3.in");
    std::ofstream fout("p3.out");

    fin >> N;

    // calculam suma tuturor numerelor din vector pentru a o folosi in aflarea diferentei cerute
    for(int i = 0; i < N; i++) {
        fin >> aux;
        Total_sum += aux;
        numbers.push_back(aux);
    }

    // matrice pentru retinerea mutarilor optime
    long long int MoveValue[N][N];

    for(int interval = 0; interval < N; interval++) {
        for (int i = 0, j = interval; j < N; j++, i++) {
            // analizam posibilitatile pe care Tuzgu le are pentru a selecta un numar

            // mutarea curenta
            long long int x = ((i + 2) <= j) ? MoveValue[i + 2][j] : 0;

            // o mutare in fata
            long long int y = ((i + 1) <= (j - 1)) ? MoveValue[i + 1][j - 1] : 0;

            // doua mutari in fata
            long long int z = (i <= (j - 2)) ? MoveValue[i][j - 2] : 0;

            // cea mai buna mutare curenta a lui Tuzgu
            long long int var1 = numbers[i] + std::min(x, y);
            long long int var2 = numbers[j] + std::min(y, z);

            MoveValue[i][j] = std::max(var1, var2);
        }
    }

    // afisarea diferentei cerute
    fout << 2 * (MoveValue[0][numbers.size() - 1]) - Total_sum << std::endl;

    // cleanup
    fin.close();
    fout.close();
    return 0;
}