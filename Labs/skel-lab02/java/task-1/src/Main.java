import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Comparator;

public class Main {
	static class Obj {
		public int weight;
		public int price;

		public Obj() {
			weight = 0;
			price = 0;
		}
	};

	static class Task {
		public final static String INPUT_FILE = "in";
		public final static String OUTPUT_FILE = "_out";

		int n, w;
		Obj[] objs;

		private void readInput() {
			try {
				Scanner sc = new Scanner(new File(INPUT_FILE));
				n = sc.nextInt();
				w = sc.nextInt();
				objs = new Obj[n];
				for (int i = 0; i < n; i++) {
					objs[i] = new Obj();
					objs[i].weight = sc.nextInt();
					objs[i].price = sc.nextInt();
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(double result) {
			try {
				PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
				pw.printf("%.4f\n", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private double getResult() {
			// TODO: Aflati profitul maxim care se poate obtine cu
			// obiectele date.

			ItemValue[] iVal = new ItemValue[objs.length];

			for(int i = 0; i < objs.length; i++){
				iVal[i] = new ItemValue(objs[i].weight, objs[i].price, i);
			}

			Arrays.sort(iVal, new Comparator<ItemValue>() {
				@Override
				public int compare(ItemValue o1, ItemValue o2) {
					return o2.cost.compareTo(o1.cost) ;
				}
			});

			double totalValue = 0d;

			for(ItemValue i: iVal){

				int curWt = (int) i.wt;
				int curVal = (int) i.val;

				if (w - curWt >= 0){//this weight can be picked while
					w = w-curWt;
					totalValue += curVal;

				}else{//item cant be picked whole

					double fraction = ((double)w/(double)curWt);
					totalValue += (curVal*fraction);
					w = (int)(w - (curWt*fraction));
					break;
				}


			}

			return totalValue;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}

		static class ItemValue {
			Double cost;
			double wt, val, ind;

			// item value function
			public ItemValue(int wt, int val, int ind){
				this.wt = wt;
				this.val = val;
				this.ind = ind;
				cost = new Double(val/wt );
			}

		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
