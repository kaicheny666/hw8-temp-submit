#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include "graph.h"
using namespace std;

int sum_weights(EdgeList const& L) {
    int total = 0;
    for (const auto& edge : L) {
        total += edge.weight;
    }
    return total;
}

void file_to_graph(string filename, Graph & G) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        error("Unable to open file: " + filename);
    }
    infile >> G;
    infile.close();
}

string get_arg(int argc, char *argv[], string def) {
    if (argc > 1) {
        return string(argv[1]);
    }
    return def;
}

void error(string msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

Graph Graph::sort_edges() const {
    Graph sorted_graph = *this;
    std::sort(sorted_graph.begin(), sorted_graph.end(),
              [](const Edge& a, const Edge& b) {
                return a.weight < b.weight;
              });
    return sorted_graph;
}

VertexList Graph::edges_from(Vertex vertex) const {
    VertexList adj_vertices;
    for (const auto& e : *this) {
        if (e.u == vertex) {
            adj_vertices.push_back(e.v);
        } else if (e.v == vertex) {
            adj_vertices.push_back(e.u);
        }
    }
    return adj_vertices;
}

//initialize
DisjointSet::DisjointSet(int numVertices) {
    subsets.resize(numVertices);
}

void DisjointSet::makeSet(Vertex x) {
    subsets[x].parent = x;
}

//find x's root
Vertex DisjointSet::findSet(Vertex x) {
    if (subsets[x].parent != x) {
        subsets[x].parent = findSet(subsets[x].parent);
    }
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
    Vertex rootX = findSet(x);
    Vertex rootY = findSet(y);
    if (rootX != rootY) {
        //parent point to another root
        subsets[rootY].parent = rootX;
    }
}

EdgeList Kruskals(const Graph& G) {
    EdgeList F;
    DisjointSet ds(G.numVertices);
    for (Vertex v = 0; v < G.numVertices; ++v) {
        ds.makeSet(v);
    }
    Graph sortedG = G.sort_edges();
    for (const Edge& e : sortedG) {
        if (ds.findSet(e.u) != ds.findSet(e.v)) {
            F.push_back(e);
            ds.unionSets(e.u, e.v);
        }
    }
    return F;
}

VertexList dfs(const Graph& graph, Vertex startVertex) {
    VertexList result;
    vector<bool> visited(graph.numVertices, false);
    stack<Vertex> s;

    visited[startVertex] = true;
    s.push(startVertex);

    while (!s.empty()) {
        Vertex v = s.top();
        s.pop();
        result.push_back(v);
        VertexList neighbors = graph.edges_from(v);
        for (Vertex w : neighbors) {
            if (!visited[w]) {
                visited[w] = true;
                s.push(w);
            }
        }
    }
    return result;
}

VertexList bfs(const Graph& graph, Vertex startVertex) {
    VertexList result;
    vector<bool> visited(graph.numVertices, false);
    queue<Vertex> q;

    visited[startVertex] = true;
    q.push(startVertex);
    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        result.push_back(v);
        VertexList neighbors = graph.edges_from(v);
        // check all the neighbors
        for (Vertex w : neighbors) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        } 
    }
    return result;
}
