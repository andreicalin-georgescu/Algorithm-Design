#include <fstream>
#include <queue>


int main() {

    std::ifstream fin ("p1.in");
    std::ofstream fout ("p1.out");

    std::priority_queue <int> numbers;
    int N, Tuzgu_sum = 0, Ritza_sum = 0, aux;

    fin >> N;
    for(int i = 0; i < N; i++){
        fin >> aux;
        numbers.push(aux);
    }

    for(int i = 0; i < N; i += 2){
        // adaugare la suma lui Tuzgu

        Tuzgu_sum += numbers.top();
        numbers.pop();

        // daca jocul s-a incheiat

        if(numbers.empty()){
            break;
        }

        // adaugare la suma Ritzei
        Ritza_sum += numbers.top();
        numbers.pop();
    }


    fout << Tuzgu_sum - Ritza_sum<<"\n";

    // cleanup
    fin.close();
    fout.close();
    return 0;
}

