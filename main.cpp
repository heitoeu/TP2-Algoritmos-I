#include "graph.hpp"

using namespace std;
vector<pair<string, int>> names;
int k = 0;

int get_index(string palavra)
{
    if (!names.empty())
    {
        for (auto n : names)
        {
            if (n.first == palavra)
            {
                return n.second;
            }
        }
        int k_aux = k;
        names.push_back({palavra, k_aux});
        k++;
        return k_aux;
    }
    else
    {
        names.push_back({palavra, 0});
        k++;
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    int usuarios, trabalhos, arestas;
    cin >> usuarios >> trabalhos >> arestas;
    Graph G(usuarios + trabalhos);

    while (arestas--)
    {
        string usuario, trabalho;
        cin >> usuario >> trabalho;

        G.adicionar_aresta(get_index(usuario), get_index(trabalho));
    }

    // cout << "Guloso: " << G.greedy() << endl;
    cout << "Exato: " << G.ford_fulkerson() << endl;

    return 0;
}
