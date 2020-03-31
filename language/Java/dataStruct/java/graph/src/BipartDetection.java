import java.util.ArrayList;

public class BipartDetection {
    private Graph G;
    private boolean[] visited;
    private int[] colors;
    private boolean isBipartite = true;

    public boolean isBipartite() {
        return isBipartite;
    }

    public BipartDetection(Graph G) {
        this.G=G;
        visited = new boolean[G.getV()];
        colors = new int[G.getV()];

        for (int i = 0; i < G.getV(); i++) {
            colors[i] = -1;
        }
        for (int i = 0; i < G.getV(); i++) {
            if (!visited[i]) {
                if (!dfs(i,0)){
                    isBipartite = false;
                }

            }
        }


    }


    private boolean dfs(int v,int color) {
        visited[v] = true;
        colors[v] = color;
        for (int w :
                G.adj(v)) {
            if (!visited[w]) {
                if(!dfs(w, 1 - color)) return false;
            }else{
                if (colors[v] == colors[w]) {
                    return false;
                }
            }
        }
        return true;

    }

    public static void main(String[] args) {
        Graph g = new Graph("g.txt");
        BipartDetection G = new BipartDetection(g);
        System.out.println(G.isBipartite());
    }
}

