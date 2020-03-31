import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.Queue;

public class GraphBFS {
    private Graph G;
    private boolean[] visited;
    private ArrayList<Integer> order = new ArrayList<>();

    public GraphBFS(Graph g) {
        this.G = g;
        visited = new boolean[g.getV()];

        for (int i = 0; i < G.getV(); i++) {
            if (!visited[i]) {
                bfs(i);
            }
        }
    }

    private void bfs(int s) {
        Queue<Integer> queue = new LinkedList<>();
        queue.add(s);
        visited[s] = true;
        while (!queue.isEmpty()) {
            int v = queue.remove();
            order.add(v);
            for (int w :
                    G.adj(v)) {
                if (!visited[w]) {
                    queue.add(w);
                    visited[w] = true;
                }
            }
        }
    }

    public Iterable<Integer> order() {
        return order;
    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        GraphBFS G = new GraphBFS(g);
        System.out.println(G.order());
    }

}

