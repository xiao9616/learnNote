import java.util.ArrayList;

public class CycleDetection {
    private Graph G;
    private boolean[] visited;
    private boolean hasCycle;

    public boolean isHasCycle() {
        return hasCycle;
    }

    private ArrayList<Integer> preorder = new ArrayList<>();
    private ArrayList<Integer> postorder = new ArrayList<>();

    public CycleDetection(Graph G) {
        this.G = G;
        visited = new boolean[G.getV()];
        for (int i = 0; i < G.getV(); i++) {
            if (!visited[i]) {
                dfs(i,i);
            }
        }

    }

    public Iterable<Integer> preorder() {
        return preorder;
    }

    public Iterable<Integer> postorder() {
        return postorder;
    }

    private void dfs(int v,int parent) {
        visited[v] = true;
        preorder.add(v);
        for (int w :
                G.adj(v)) {
            if (!visited[w]) {
                dfs(w,v);
            } else {
                if (w != parent) {
                    hasCycle = true;
                }
            }
        }
        postorder.add(v);
    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        CycleDetection G = new CycleDetection(g);
        System.out.println(G.preorder());
        System.out.println(G.postorder());
        System.out.println(G.isHasCycle());
    }
}
