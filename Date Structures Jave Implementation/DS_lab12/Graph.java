package com.company;

public class Graph {
    //  variables
    public static final int DEF_MAX_GRAPH_SIZE = 10;    // Default number of vertices (a constant)
    public static final int INFINITE_EDGE_WT = Integer.MAX_VALUE;   // "Weight" of a missing edge (a constant) — the max int value
    private int dim; // Array size/dimension (n)
    private int size; // Actual number of vertices in the graph
    private Vertex[] vertexList;    // Vertex list
    private int[][] adjMatrix;      // Adjacency matrix (a 2D array)

    //  constructors
    public Graph() {
        this(DEF_MAX_GRAPH_SIZE);
    }
    public Graph (int maxNumber) {
        if (maxNumber <= 0){
            System.out.println("Error: graph size must be greater than zero");
            System.exit(-1);
        }
        this.dim = maxNumber;
        this.vertexList = new Vertex[dim];
        this.adjMatrix = new int[dim][dim];
        this.size = 0;
    }

    //  methods
    public void insertVertex (Vertex newVertex) {
        if (isFull()){  // precondition
            return;
        }
        int insertionIndex = -1;
        for (int i = 0; i< dim; i++){
            if (vertexList[i]!=null && vertexList[i].getLabel().equals(newVertex.getLabel())) // checks if exists
                return;
            if (insertionIndex==-1 && vertexList[i]==null)  // saving first free cell's index
                insertionIndex = i;
        }
        vertexList[insertionIndex] = newVertex;
        this.size++;
    }
    public void insertEdge (String v1, String v2, int wt) {
        int v1_index = index(v1);
        int v2_index = index(v2);
        if (v1_index==-1 || v2_index==-1)   // precondition
            return;
        adjMatrix[v1_index][v2_index] = wt;
        adjMatrix[v2_index][v1_index] = wt;
    }
    public Vertex retrieveVertex (String v) {
        int ret_index = index(v);
        if (ret_index == -1)
            return null;
        return vertexList[ret_index];
    }
    public int edgeWeight (String v1, String v2) {
        int v1_index = index(v1);
        int v2_index = index(v2);
        if (v1_index==-1 || v2_index==-1)   // precondition
            return -1;
        return adjMatrix[v1_index][v2_index];
    }
    public void removeVertex (String v) {
        for (int i = 0; i< dim; i++){
            if (vertexList[i]!=null && vertexList[i].getLabel().equals(v)){
                vertexList[i] = null;           // erase vertex in vertexList
                this.size--;
                for (int j = 0; j< dim; j++){   // erase all edges connected to this vertex
                    adjMatrix[i][j] = 0;
                    adjMatrix[j][i] = 0;
                }
                return;
            }
        }
    }
    public void removeEdge (String v1, String v2) {
        int v1_index = index(v1);
        int v2_index = index(v2);
        if (v1_index==-1 || v2_index==-1)   // precondition
            return;
        adjMatrix[v1_index][v2_index] = 0;
        adjMatrix[v2_index][v1_index] = 0;
    }
    public void clear () {
        int orig_size = vertexList.length;
        this.vertexList = new Vertex[orig_size];
        this.adjMatrix = new int[orig_size][orig_size];
        // new references means that the Garbage Collector will erase the old ones
    }
    public boolean isEmpty () {
        for (int i = 0; i< dim; i++){
            if (vertexList[i]!=null)
                return false;
        }
        return true;
    }
    public boolean isFull () {
        for (int i = 0; i< dim; i++){
            if (vertexList[i]==null)
                return false;
        }
        return true;
    }
    public String toString() {
        if (isEmpty())
            return "Empty Graph";
        String res = "{";
        for (int i=0 ; i<dim ; i++){   // using size which is the actual number of vertices
            if (vertexList[i]==null){
                res += "null, ";
            } else {
                res += vertexList[i].getLabel() + ", ";
            }
        }
        res += "}\n\n";
        for (int i=0 ; i<dim ; i++){
            for (int j=0; j<dim; j++) {
                res += adjMatrix[i][j] + "  ";
            }
            res += "\n";
        }
        return res;
    }

    // helper methods
    private int index (String v) {
        for (int i = 0; i< dim; i++){
            if (vertexList[i]!=null && vertexList[i].getLabel().equals(v))
                return i;
        }
        return -1;
    }
    private int getEdge (int row, int col) {
        return adjMatrix[row][col];
    }
    private void setEdge (int row, int col, int wt) {
        this.adjMatrix[row][col] = wt;
    }
}
