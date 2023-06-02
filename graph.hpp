#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

class Graph
{
private:
    int n;
    vector<list<int>> g;
    vector<vector<int>> capacidade;
    vector<vector<int>> capacidade_residual;
    // queue<int> users;
    // queue<int> jobs;
    vector<int> pai;
    int s, t;
    bool BFS();

public:
    Graph(int num_vertices);
    void adicionar_aresta(int u, int v);
    int Ed_karp();
    int greedy();
};

#endif // GRAPH_HPP