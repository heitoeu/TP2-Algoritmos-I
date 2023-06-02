#include "graph.hpp"

using namespace std;
int adicionado(string u, vector<string> names, vector<int> names_num)
{
    int n = names.size();
    for (int i = 0; i < n; i++)
    {
        if (u == names[i])
        {
            return names_num[i];
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int user, job, user_job;
    cin >> user >> job >> user_job;
    Graph G(user + job);
    vector<string> names;
    vector<int> names_num;
    int k = 0;
    while (user_job--)
    {
        int pos_u, pos_j;
        string u, j;
        cin >> u >> j;
        pos_u = adicionado(u, names, names_num);
        pos_j = adicionado(j, names, names_num);

        if (pos_u == -1)
        {
            pos_u = k;
            names.push_back(u);
            names_num.push_back(k);
            k++;
        }
        if (pos_j == -1)
        {
            pos_j = k;
            names.push_back(j);
            names_num.push_back(k);
            k++;
        }

        G.adicionar_aresta(pos_u, pos_j);
    }

    // cout << "Guloso: " << G.greedy() << endl;
    cout << "Exato: " << G.Ed_karp() << endl;

    return 0;
}
