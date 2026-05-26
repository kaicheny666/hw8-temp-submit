#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include "graph.h"
using namespace std;

int sum_weights(EdgeList const& L); {
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
Disjointset::DisjointSet(int numVertices) {
    subsets.resize(numVertices);
}

void Disjointset::makeSet(Vertex x) {
    subsets[x].parents = x;
}

//find x's root
Vertex Disjointset::findSet(Vertex x) {
    if (subsets[x].parent != x) {
        subsets[x].parent = findSet(subsets[x].parents);
    }
    return subsets[x].parents;
}

void Disjointset::unionSets(Vertex x, Vertex y) {
    Vertex rootX = findSet(x);
    Vertex rootY = findSet(y);
    if (rootX != rootY) {
        //parent point to another root
        subsets[rootY].parent = rootX;
    }
}

EdgeList Kruskals(const Graph& G);

VertexList dfs(const Graph& graph, Vertex startVertex);

VertexList bfs(const Graph& graph, Vertex startVertex);
