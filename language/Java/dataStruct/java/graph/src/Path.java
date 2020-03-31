import java.util.ArrayList;
import java.util.Collections;

public class Path {
    private Graph G;
    private int s;
    private int t;
    private boolean[] visited;
    private ArrayList<Integer> preorder = new ArrayList<>();
    private ArrayList<Integer> postorder = new ArrayList<>();

    private int[] pre;

    public Path(Graph G,int s,int t) {
        this.G = G;
        this.s = s;
        this.t = t;
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

    private boolean dfs(int v,int parent) {
        visited[v] = true;
        preorder.add(v);
        pre[v]=parent;
        if (v==t) return true;
        for (int w :
                G.adj(v)) {
            if (!visited[w]) {
                if(dfs(w,v)) return true;
            }
        }
        return false;
//        postorder.add(v);
    }

    public boolean isConnected() {
        G.validateVertex(t);
        return visited[t];
    }

    public Iterable<Integer> path() {
        ArrayList<Integer> res = new ArrayList<>();
        if (!isConnected()) {
            return res;
        } else {
            int cur = t;
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
        Path G = new Path(g,0,0);
        System.out.println(G.path());
    }
}

