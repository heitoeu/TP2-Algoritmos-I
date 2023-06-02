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
  this->capacidade_residual = vector<vector<int>>(n, vector<int>(n, 0));
}

void Graph::adicionar_aresta(int u, int v)
{
  g[u].push_back(v);
  // cada emprego só pode ser escolhido por um usuário
  capacidade_residual[u][v] = 1;

  // ligando o grafo bipartido na fonte e na chegada
  g[s].push_back(u);
  capacidade_residual[s][u] = 1;

  g[v].push_back(t);
  capacidade_residual[v][t] = 1;

  // greedy?
  //  users.push(u);
  //  jobs.push(v);
}

bool Graph::BFS()
{
  vector<int> visitados(n, false);
  queue<int> q;
  q.push(s);
  visitados[s] = true;
  pai[s] = -1;

  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    for (int u = 0; u < n; u++)
    {
      if (visitados[u] == false and capacidade_residual[v][u] > 0) // ainda pode passar fluxo
      {
        if (u == t)
        {
          pai[u] = v;
          return true;
        }
        visitados[u] = true;
        q.push(u);
        pai[u] = v;
      }
    }
  }
  return false;
}

int Graph::ford_fulkerson()
{
  int max_flow = 0;

  // encontrar o caminho aumentante
  while (BFS())
  {

    int fluxo_gargalo = INF;
    int v = t;

    // atualizar o fluxo
    while (v != s)
    {
      int p = pai[v];
      fluxo_gargalo = min(fluxo_gargalo, capacidade_residual[p][v]);
      v = p;
    }

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

    max_flow += fluxo_gargalo;
  }

  return max_flow;
}

int Graph::greedy()
{
  vector<list<int>> g_greedy = g;
  return 10;
}