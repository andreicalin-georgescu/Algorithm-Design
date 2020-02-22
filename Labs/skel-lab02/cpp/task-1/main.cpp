#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

struct Object {
    int weight;
    int price;
    
    Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }
    
private:
    int n, w;
    vector<Object> objs;
    
    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }
    
    static bool cmp(struct Object a, struct Object b)
    {
        double r1 = (double)a.price / a.weight;
        double r2 = (double)b.price / b.weight;
        return r1 > r2;
    }
    
    double get_result() {
        
        //TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
        // sorting Item on basis of ratio
        sort(objs.begin(), objs.end(), cmp);
        
        //    Uncomment to see new order of Items with their ratio
        /*
         for (int i = 0; i < n; i++)
         {
         cout << arr[i].value << "  " << arr[i].weight << " : "
         << ((double)arr[i].value / arr[i].weight) << endl;
         }
         */
        
        int curWeight = 0;  // Current weight in knapsack
        double finalvalue = 0.0; // Result (value in Knapsack)
        
        // Looping through all Items
        for (int i = 0; i < n; i++)
        {
            // If adding Item won't overflow, add it completely
            if (curWeight + objs[i].weight <= w)
            {
                curWeight += objs[i].weight;
                finalvalue += objs[i].price;
            }
            
            // If we can't add current Item, add fractional part of it
            else
            {
                int remain = w - curWeight;
                finalvalue += objs[i].price * ((double) remain / objs[i].weight);
                break;
            }
        }
        
        // Returning final value
        return finalvalue;
    }
    
    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
        fout.close();
    }
};

int main() {
    Task task;
    task.solve();
    return 0;
}
