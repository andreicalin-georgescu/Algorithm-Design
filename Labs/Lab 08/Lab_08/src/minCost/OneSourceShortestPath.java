/**
 * Proiectarea Algoritmilor, 2016
 * Lab 8: Drumuri minime
 *
 * @author  adinu
 * @email   mandrei.dinu@gmail.com
 */

package minCost;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

import javax.lang.model.type.ErrorType;

import graph.GraphT;
import graph.NodeT;
import graph.PairT;

public class OneSourceShortestPath {

	private int[] distances;

	private GraphT<String, Integer> g;

	public OneSourceShortestPath(GraphT<String, Integer> g) {
		this.g = g;
		distances = new int[g.size()];
	}

	private class NodeComparator implements Comparator<NodeT<String>> {
		/**
		 * Compares nodes using the current estimation of the distance from the
		 * source node.
		 */
		@Override
		public int compare(NodeT<String> arg0, NodeT<String> arg1) {
			int dist1 = distances[arg0.id()];
			int dist2 = distances[arg1.id()];

			return dist1 > dist2 ? 1 : -1;
		}
	}

	public int[] applyDijkstra(NodeT<String> source) {

		resetDistances();

		PriorityQueue<NodeT<String>> pq = new PriorityQueue<>(g.size(),
				new NodeComparator());

		// TODO
		for (NodeT<String> v : g.nodes()) {
			distances[v.id()] = Integer.MAX_VALUE;
			v.setParent(null);
		}

		distances[source.id()] = 0;

		pq.add(source);

		while (!pq.isEmpty()) {
			NodeT<String> u = pq.remove();
			u.visit();
			for (PairT<NodeT<String>, Integer> node : g.adjList(u)) {
				if (!node.first().isVisited()
						&& distances[node.first().id()] > (distances[u.id()] + node
								.second())) {
					distances[node.first().id()] = distances[u.id()]
							+ node.second();
					node.first().setParent(u);
					pq.add(node.first());
				}
			}
		}
		ArrayList<NodeT<String>> drum = new ArrayList<>();

		return distances;
	}

	public void printminDistance(NodeT<String> des) {

		ArrayList<NodeT<String>> drum = new ArrayList<>();

		NodeT<String> nod = des;

		while (nod != null) {
			drum.add(0, nod);
			nod = nod.parent();
		}
		System.out.println(drum);
	}

	public int[] applyBellmanFord(NodeT<String> source) {

		resetDistances();

		// TODO BONUS

		for (NodeT<String> v : g.nodes()) {
			distances[v.id()] = Integer.MAX_VALUE;
			v.setParent(null);
		}

		source.setParent(null);
		distances[source.id()] = 0;

		for (int i = 0; i < g.nodes().size() - 1; ++i) {
			for (NodeT<String> u : g.nodes()) {
				for (PairT<NodeT<String>, Integer> v : g.adjList(u)) {
					if (distances[v.first().id()] > distances[u.id()]
							+ v.second()) {
						distances[v.first().id()] = distances[u.id()]
								+ v.second();
						v.first().setParent(u);
					}
				}
			}
		}

		for (NodeT<String> u : g.nodes()) {
			for (PairT<NodeT<String>, Integer> v : g.adjList(u)) {
				if (distances[v.first().id()] > distances[u.id()] + v.second()) {
					System.out.println("Fail!!!");
					break;
				}
			}
		}

		return distances;
	}

	public void printInfiniteLoop(NodeT<String> destination) {

		// TODO BONUS
	}

	private void resetDistances() {
		for (int i = 0; i < g.size(); i++) {
			distances[i] = Integer.MAX_VALUE;
		}
	}
}
