#include "graph.hpp"
#include <iostream>

using namespace std;

Graph::Graph(int num_vertices)
{
  // Armazenar os vertices adicionais de saida e chegada (+2)
  this->n = num_vertices + 2;
  this->grafo = vector<list<int>>(n);
  this->grafo_residual = vector<list<int>>(n);

  this->fonte = num_vertices;
  this->terminal = num_vertices + 1;
  this->pai = vector<int>(n, -1);
  this->capacidade_residual = vector<vector<int>>(n, vector<int>(n, 0));
}

void Graph::adicionar_aresta(int usuario, int vaga)
{
  // Adiciona as arestas do grafo original
  grafo[usuario].push_back(vaga);
  if (grafo[usuario].size() == 1)
  {
    usuarios.push(usuario);
  }

  // Adiciona as arestas do grafo residual
  // Aresta original e de arrependimento
  grafo_residual[usuario].push_back(vaga);
  grafo_residual[vaga].push_back(usuario);

  // Adiciona fonte e terminal no grafo residual
  grafo_residual[fonte].push_back(usuario);
  grafo_residual[vaga].push_back(terminal);

  // Cada emprego só pode ser escolhido por um usuário
  capacidade_residual[usuario][vaga] = 1;
  capacidade_residual[fonte][usuario] = 1;
  capacidade_residual[vaga][terminal] = 1;
}

// Solução gulosa
int Graph::greedy()
{
  int guloso = 0;
  vector<int> visitados(n, false);
  // Para cada usuario:
  while (!usuarios.empty())
  {
    int usuario = usuarios.front();
    usuarios.pop();

    for (auto vizinho : grafo[usuario])
    {
      // Se ainda existe vaga de emprego escolha ela
      if (visitados[vizinho] == false)
      {
        guloso++;
        visitados[vizinho] = true;
        break;
      }
    }
  }
  return guloso;
}

// Solução ótima com fluxo máximo
bool Graph::BFS()
{
  vector<int> visitados(n, false);
  queue<int> fila;
  fila.push(fonte);
  visitados[fonte] = true;

  while (!fila.empty())
  {
    int w = fila.front();
    fila.pop();

    for (auto vizinho : grafo_residual[w])
    {
      // Encontrar o menor caminho aumentante disponível
      if (visitados[vizinho] == false && capacidade_residual[w][vizinho] > 0)
      {
        visitados[vizinho] = true;
        fila.push(vizinho);
        pai[vizinho] = w;
      }
    }
  }
  // Retorna se foi possível chegar no terminal, ou seja, se existe caminho aumentante
  return visitados[terminal];
}

int Graph::ford_fulkerson()
{
  int fluxo_max = 0;

  // Enqunto existir caminho aumentante
  while (BFS())
  {
    int fluxo_gargalo = INF;
    int temp = terminal;

    // Atualizar o fluxo caminhando do terminal até a fonte
    while (temp != fonte)
    {
      int u = pai[temp];
      fluxo_gargalo = min(fluxo_gargalo, capacidade_residual[u][temp]);
      temp = u;
    }

    // Atualizar as capacidades residuais
    temp = terminal;
    while (temp != fonte)
    {
      int u = pai[temp];
      // Aresta original
      capacidade_residual[u][temp] -= fluxo_gargalo;
      // Aresta de arrependimento
      capacidade_residual[temp][u] += fluxo_gargalo;
      temp = u;
    }

    fluxo_max += fluxo_gargalo;
  }

  return fluxo_max;
}