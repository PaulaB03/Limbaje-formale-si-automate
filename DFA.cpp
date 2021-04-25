#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#define STATE_MAX 1000
using namespace std;

ifstream in("text.in");
ofstream out("text.out");
vector <pair<int, string>> dfa[STATE_MAX];

void input(int &n, int &m) {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        string c;
        in >> a >> b >> c;
        dfa[a].push_back({b, c});
    }
}



void check(string test, int init, int nf, int fin[]) {
    int q = init;            /// q - numarul starii curente
    vector <int> states;     /// vectorul starilor
    states.push_back(q);

    for (int i = 0; i < test.size(); ++i)
    for (int j = 0; j < dfa[q].size(); ++j)
        if (dfa[q][j].second[0] == test[i]) {
            q = dfa[q][j].first;
            states.push_back(q);
            break;
        }

    /// Verficifare daca ultima stare e finala
    int k = 0, aux = states[states.size() - 1];
    for (int i = 1; i <= nf && k == 0; ++i)
        if (fin[i] == aux) k = 1;

    /// Afisare
    if (k == 0)
        out << "NU\n";
    else {
        out << "DA\nTraseu: ";
        for (int i = 0; i < states.size(); ++i)
            out << states[i] << " ";
        out << "\n";
    }

    states.clear();
}

int main() {
    int n, m;
    /// Citire DFA
    input(n,m);

    int init, nf; // Starea initiala, numar stari finale
    in >> init >> nf;

    int fin[nf]; // Stari finale
    for (int i = 1; i <= nf; ++i)
        in >>fin[i];

    int nr_teste;
    in >> nr_teste;

    string test;
    for (int i = 0; i < nr_teste; ++i) {
        in >>test;
        /// Verificare daca cuvantul este acceptat
        check(test, init, nf, fin);
    }

    in.close();
    out.close();
    return 0;
}
