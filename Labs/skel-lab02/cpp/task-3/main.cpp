#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}

private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	static bool cmp(Homework h1, Homework h2) {
		return h1.deadline > h2.deadline;
	}


	static bool comparator(Homework h1, Homework h2) {
		return h1.score < h2.score;
	}

	int get_result() {
		/*
        TODO: Aflati punctajul maxim pe care il puteti obtine planificand
        optim temele.
        */
		sort(hws.begin(), hws.end(), cmp);

		priority_queue<Homework, vector<Homework>, std::function<bool (Homework, Homework)>> hw(comparator);

		int max_score = 0;
		unsigned long it = 0;
		int current_deadline = hws[it].deadline;
		int week = current_deadline;


		while (hws[it].deadline == current_deadline) {
			hw.push(hws[it]);
			it++;
		}

		max_score += hw.top().score;
		hw.pop();
		week--;

		current_deadline = hws[it].deadline;

		while(week != 0) {
			if(current_deadline == week) {
				//adaug temele curente in heap
				while (hws[it].deadline == current_deadline) {
					hw.push(hws[it]);
					it++;
				}
			}
		max_score += hw.top().score;
		hw.pop();
		week --;
		}





		return max_score;
	}

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