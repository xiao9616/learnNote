import java.util.ArrayList;

public class GraphDFS {
    private Graph G;
    private boolean[] visited;
    private ArrayList<Integer> preorder=new ArrayList<>();
    private ArrayList<Integer> postorder=new ArrayList<>();
    public GraphDFS(Graph G) {
        this.G=G;
        visited = new boolean[G.getV()];
        for (int i = 0; i < G.getV(); i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }

    }

    public Iterable<Integer> preorder() {
        return preorder;
    }

    public Iterable<Integer> postorder() {
        return postorder;
    }
    private void dfs(int v) {
        visited[v] = true;
        preorder.add(v);
        for (int w :
                G.adj(v)) {
            if (!visited[w]) {
                dfs(w);
            }
        }
        postorder.add(v);
    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        GraphDFS G = new GraphDFS(g);
        System.out.println(G.preorder());
        System.out.println(G.postorder());
    }
}
