#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

class Graph
{
private:
    int n;
    int fonte, terminal;

    vector<list<int>> grafo;
    vector<list<int>> grafo_residual;

    vector<vector<int>> capacidade_residual;
    vector<int> pai;
    queue<int> usuarios;

    bool BFS();

public:
    Graph(int num_vertices);
    void adicionar_aresta(int usuario, int vaga);
    int ford_fulkerson();
    int greedy();
};

#endif