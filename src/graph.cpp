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



template
    <typename T>
inline ostream& operator <<(ostream& out, const vector<T> & V)
{
    for (auto && e : V)
        out << e << ' ';
    return out;
}

using Vertex = int;

class DisjointSet {
    struct Set {
        Vertex parent;
    };
    vector<Set> subsets;
public:
    DisjointSet(int numVertices);
    void makeSet(Vertex x);
    Vertex findSet(Vertex x);
    void unionSets(Vertex x, Vertex y);
};

struct Edge {
    Vertex u, v;
    int weight;

    inline friend istream& operator >>(istream& in, Edge & e)
    {
        return in >> e.u >> e.v >> e.weight;
    }

    inline friend ostream& operator <<(ostream& out, const Edge & e)
    {
       return out << "(" << e.u << ","  << e.v << ","  << e.weight << ")" ;
    }
};

using EdgeList = vector<Edge>;
using VertexList = vector<Vertex>;

struct Graph : public EdgeList
{
    int numVertices = 0;
    // each vertex is an integer in range 0..numVertices-1
    // returns a copy of graph with edges sorted ascending by edge weight
    Graph sort_edges() const;
    VertexList edges_from(Vertex vertex) const;
    inline friend istream& operator >>(istream& in, Graph & G)
    {
        if (!(in >> G.numVertices))
            error("unable to find input file");
        for ( Edge e; in >> e; )
            G.push_back(e);
        return in;
    }
};

EdgeList Kruskals(const Graph& G);

VertexList dfs(const Graph& graph, Vertex startVertex);
VertexList bfs(const Graph& graph, Vertex startVertex);
