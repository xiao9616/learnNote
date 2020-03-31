import java.util.ArrayList;
import java.util.Collections;

public class SingleSourcePath {
    private Graph G;
    private int s;
    private boolean[] visited;
    private ArrayList<Integer> preorder = new ArrayList<>();
    private ArrayList<Integer> postorder = new ArrayList<>();

    private int[] pre;

    public SingleSourcePath(Graph G,int s) {
        this.G = G;
        this.s = s;
        visited = new boolean[G.getV()];
        pre = new int[G.getV()];
        dfs(s,s);
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
        pre[v]=parent;
        for (int w :
                G.adj(v)) {
            if (!visited[w]) {
                dfs(w,v);
            }
        }
        postorder.add(v);
    }

    public boolean isConnected(int i) {
        G.validateVertex(i);
        return visited[i];
    }

    public Iterable<Integer> path(int i) {
        ArrayList<Integer> res = new ArrayList<>();
        if (!isConnected(i)) {
            return res;
        } else {
            int cur = i;
            while (cur != s) {
                res.add(cur);
                cur = pre[cur];
            }
            res.add(s);
        }
        Collections.reverse(res);
        return res;
    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        SingleSourcePath G = new SingleSourcePath(g,0);
        System.out.println(G.preorder());
        System.out.println(G.postorder());
        System.out.println(G.path(2));
    }
}
