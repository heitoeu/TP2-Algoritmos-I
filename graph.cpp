#include "graph.hpp"
#include <iostream>

using namespace std;

Graph::Graph(int num_vertices)
{
  this->n = num_vertices + 2;
  this->g = vector<list<int>>(n);

  // armazenar os vertices adicionais de saida e chegada
  this->s = num_vertices;
  this->t = num_vertices + 1;
  this->pai = vector<int>(n, -1);
  this->capacidade = vector<vector<int>>(n, vector<int>(n, 0));
}

void Graph::adicionar_aresta(int u, int v)
{
  g[u].push_back(v);

  // ligando o grafo bipartido na fonte e na chegada
  g[s].push_back(u);
  capacidade[s][u] = INF;
  g[v].push_back(t);
  capacidade[v][t] = INF;

  // greedy?
  //  users.push(u);
  //  jobs.push(v);

  // cada emprego só pode ser escolhido por um usuário
  capacidade[u][v] = 1;
}

bool Graph::BFS()
{
  vector<int> visitados(n, false);
  queue<int> q;
  q.push(s);
  visitados[s] = true;
  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    visitados[v] = true;
    for (auto u : g[v])
    {
      if (visitados[u] == false and capacidade_residual[u][v] > 0) // ainda pode passar fluxo
      {
        q.push(u);
        pai[u] = v;
      }
    }
  }
  return (visitados[t]);
}

int Graph::Ed_karp()
{
  int max_flow = 0;

  // grafo residual
  capacidade_residual = capacidade;

  // encontrar o caminho aumentante
  while (BFS())
  {
    cout << "BFS!!" << endl;
    int fluxo_gargalo = INF;
    int v = t;

    // atualizar o fluxo
    while (v != s)
    {
      int p = pai[v];
      fluxo_gargalo = min(fluxo_gargalo, capacidade_residual[p][v]);
      v = p;
    }

    max_flow += fluxo_gargalo;

    // atualizar as capacidades residuais
    v = t;
    while (v != s)
    {
      int p = pai[v];
      // foward edge
      capacidade_residual[p][v] -= fluxo_gargalo;
      // backward edge
      capacidade_residual[v][p] += fluxo_gargalo;
      v = p;
    }
  }

  return max_flow;
}

int Graph::greedy()
{
  vector<list<int>> g_greedy = g;
}