import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.TreeSet;

public class Graph {
    private int V;
    private int E;
    private TreeSet<Integer>[] adj;

    public Graph(String filename) {
        File file = new File(filename);
        try (Scanner scanner = new Scanner(file)) {
            V = scanner.nextInt();
            if (V < 0) throw new IllegalArgumentException("V must be non-negetive");
            adj = new TreeSet[V];
            for (int i = 0; i < V; i++) {
                adj[i] = new TreeSet<>();
            }
            E = scanner.nextInt();
            if (E < 0) throw new IllegalArgumentException("E must be non-negetive");
            for (int i = 0; i < E; ++i) {
                int a = scanner.nextInt();
                int b = scanner.nextInt();
                validateVertex(a);
                validateVertex(b);
                if (a == b) throw new IllegalArgumentException("self loop");
                if (adj[a].contains(b)) throw new IllegalArgumentException("parallel ");
                adj[a].add(b);
                adj[b].add(a);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void validateVertex(int v) {
        if (v < 0 || v >= V) {
            throw new IllegalArgumentException("vertex" + v + "is valid");
        }
    }

    public int getV() {
        return V;
    }

    public int getE() {
        return E;
    }

    public boolean hasEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return adj[v].contains(w);
    }

    public Iterable<Integer> adj(int v) {
        validateVertex(v);
        return adj[v];
    }

    public int degree(int v) {
        return adj[v].size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append((String.format("V=%d,E=%d\n", V, E)));
        for (int i = 0; i < V; i++) {
            sb.append(String.format("%d :", i));
            for (int w :
                    adj[i]) {
                sb.append(String.format("%d ", w));
            }
            sb.append('\n');
        }
        return sb.toString();
    }



    public static void main(String[] args) {
        Graph Graph = new Graph("g.txt");
        System.out.println(Graph);
    }
}
