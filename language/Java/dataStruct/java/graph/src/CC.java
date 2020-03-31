import java.util.ArrayList;

public class CC {
    private Graph G;
    private int[] visited;
    private int count;
    private ArrayList<Integer> preorder = new ArrayList<>();
    private ArrayList<Integer> postorder = new ArrayList<>();

    public ArrayList<Integer>[] components() {
        ArrayList<Integer>[] res = new ArrayList[count];
        for (int i = 0; i < count; i++) {
            res[i] = new ArrayList<>();
        }
        for (int i = 0; i < G.getV(); i++) {
            res[visited[i]].add(i);
        }
        return res;
    }

    public int getCount() {
        for (int e :
                visited) {
            System.out.print(e + " ");
        }
        System.out.println();
        return count;
    }

    public CC(Graph G) {
        this.G = G;
        visited = new int[G.getV()];
        for (int i = 0; i < visited.length; i++) {
            visited[i] = -1;
        }
        for (int i = 0; i < G.getV(); i++) {
            if (visited[i]==-1) {
                dfs(i,count++);
            }
        }

    }

    public Iterable<Integer> preorder() {
        return preorder;
    }

    public Iterable<Integer> postorder() {
        return postorder;
    }

    private void dfs(int v,int ccid) {
        visited[v] = ccid;
        preorder.add(v);
        for (int w :
                G.adj(v)) {
            if (visited[w]==-1) {
                dfs(w,ccid);
            }
        }
        postorder.add(v);
    }

    public boolean isConnected(int v, int w) {
        G.validateVertex(v);
        G.validateVertex(w);
        return visited[v] == visited[w];
    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        CC G = new CC(g);
        System.out.println(G.preorder());
        System.out.println(G.postorder());
        System.out.println(G.getCount());
        System.out.println(G.isConnected(1, 5));
        System.out.println(G.components()[0]);
    }
}

