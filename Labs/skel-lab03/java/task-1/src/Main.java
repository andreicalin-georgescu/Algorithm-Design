import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	static class Task {
		public final static String INPUT_FILE = "in";
		public final static String OUTPUT_FILE = "out";

		int n, S;
		int[] v;

		private void readInput() {
			try {
				Scanner sc = new Scanner(new File(INPUT_FILE));
				n = sc.nextInt();
				S = sc.nextInt();
				v = new int[n + 1];
				for (int i = 1; i <= n; i++) {
					v[i] = sc.nextInt();
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(int result) {
			try {
				PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
				pw.printf("%d\n", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {
			// TODO: Aflati numarul minim de monede ce poate fi folosit pentru a
			// obtine suma S. Tipurile monedelor sunt stocate in vectorul v, de
			// dimensiune n.
			int coinChange(int[] v, int S) {
					if (S < 1) return 0;
					return coinChange(v, S, new int[S]);
			}

			int coinChange(int[] v, int rem, int[] count) {
				if (rem < 0) return -1;
				if (rem == 0) return 0;
				if (count[rem - 1] != 0) return count[rem - 1];
				int min = Integer.MAX_VALUE;
				for (int coin : v) {
					int res = coinChange(v, rem - coin, count);
					if (res >= 0 && res < min)
						min = 1 + res;
				}
				count[rem - 1] = (min == Integer.MAX_VALUE) ? -1 : min;
				return count[rem - 1];
			}
			return 0;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
