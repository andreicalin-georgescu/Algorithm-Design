#include <fstream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream fin("p2.in");
    std::ofstream fout("p2.out");

    int N, K, x;


    fin >> N >> K;

    // vector pentru a retine numerele din sir, indexat de la 1
    long long int *numbers = new long long int[N + 1];

    // vector pentru a retine scorurile maxime pe care le putem obtine
    long long int *diff = new long long int[N - K + 1];

    // vector pentru a retine scorul curent, pentru a verifica daca este favorabila
    // eliminarea numarului din numbers
    long long int *copy = new long long int[N - K + 1];


    // primul scor
    diff[0] = 0;
    copy[0] = -123456789;

    for (int i = 1; i <= N; i++) {
        fin >> x;
        numbers[i] = x;
    }

    // initializarea vectorilor de ajutor
    for (int i = 1; i <= (N - K); i++) {
        diff[i] = -123456789;
        copy[i] = -123456789;
    }

    // sortam vectorul in ordine descrescatoare
    std::sort(numbers + 1, numbers + N + 1, std::greater<long long int>());


    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i && j <= (N - K); j++) {
            // Randul lui Tuzgu

            if (j % 2 == 1) {

                // daca este benefica eliminarea numarului, diferenta de scor va creste
                if (numbers[i] + diff[j - 1] >= diff[j]) {
                    copy[j] = diff[j - 1] + numbers[i];
                }
            } else {
                // Randul Ritzei

                // fiind randul Ritzei, diferenta se va micsora
                if (diff[j - 1] - numbers[i] >= diff[j]) {
                    copy[j] = diff[j - 1] - numbers[i];
                }
            }
        }


        for(int k = 1; k <= (N - K); k++) {
            diff[k] = copy[k];
        }
    }

    fout << diff[N - K] << std::endl;

    // cleanup
    delete[] numbers;
    delete[] copy;
    delete[] diff;
    fin.close();
    fout.close();

    return 0;
}