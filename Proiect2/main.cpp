#include <iostream>
#include <fstream>
#include <vector>
#define STATE_MAX 100
using namespace std;

ifstream in("input.in");
vector <pair<int, string>> _fa[STATE_MAX];

void input (int &n, int &m);
void step1 (int i);
void step2 (int &init, int &n, int nr_fin, int fin[]);
void step3 (int &nr_fin, int fin[], int &n);
void step4(int init, int fin, int n);

int main() {
    int n, m;
    input(n, m);

    int init, nr_fin;            // Starea initiala, numar stari finale
    in >> init >> nr_fin;

    int fin[nr_fin];            // Stari finale
    for (int i = 0; i < nr_fin; ++i)
        in >> fin[i];

    for (int i = 0; i < n; ++i)
        if (_fa[i].size() > 1)
        step1(i);

    step2(init, n, nr_fin, fin);
    step3(nr_fin, fin, n);

    for (int repet = 0; repet < n-2; ++repet)
        step4(init, fin[0], n);

    cout << _fa[init][0].second;

    in.close();
    return 0;
}

/// Citirea si constuirea automatului finit
void input (int &n, int &m) {
    in >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        string c;
        in >> a >> b >> c;
        _fa[a].push_back({b, c});
    }
}

/// Transformam _FA in EFA
void step1 (int k) {
    for (int i = 0; i < _fa[k].size()-1; ++i)
    for (int j = i+1; j < _fa[k].size(); ++j)
        if (_fa[k][i].first == _fa[k][j].first) {
            _fa[k].push_back({_fa[k][i].first, _fa[k][i].second + "|" + _fa[k][j].second});
            _fa[k].erase(_fa[k].begin() + j);
            _fa[k].erase(_fa[k].begin() + i);
        }
}

/// Modificare stare initiala
void step2 (int &init, int &n, int nr_fin, int fin[]) {
    bool k = true;

    // Verificam daca starea initiala este finala
    for (int i = 0; i < nr_fin; ++i)
        if (init == fin[i])
            k = false;

    // Verificam daca starea initiala are drumuri care vin spre ea
    for (int i = 0; i < n; ++i)
    for (int j = 0 ; j < _fa[i].size() && k == true; ++j)
        if (_fa[i][j].first == init)
            k = false;

    if ( k == false) {
        _fa[n].push_back({init, "0"});
        init = n;
        n++;
    }
}

/// Modificare stare finala
void step3 (int &nr_fin, int fin[] ,int &n) {
    bool k = true;

    // Verificam daca sunt mai multe stari finale
    if (nr_fin > 1)
        k = false;

    // Verificam daca exista sageti care pleaca din starea finala
    for (int i = 0; i < nr_fin && k == true; ++i)
        if(_fa[fin[i]].size() > 0) k = false;

    if ( k == false) {
        for (int i =0; i < nr_fin; ++i)
            _fa[fin[i]].push_back({n,"0"});
        nr_fin = 1;
        fin[0] = n;
        n++;
    }
}

/// Eliminarea starilor care nu sunt initiale/finale
void step4 (int init, int fin, int n) {
    // Cautam starea care trebuie stearsa
    int current = 0;
    while (current == init || current == fin || _fa[current].size() == 0)
        current++;

    // Cautam bucla
    string loop = "";
    for (int i = 0; i < _fa[current].size(); ++i)
        if(_fa[current][i].first == current) {
            loop = _fa[current][i].second;
            _fa[current].erase(_fa[current].begin() + i);
        }
    if (loop.size() > 1)
        loop = "(" + loop + ")*";
    else if (loop != "")
        loop = loop + "*";

    // Cautam starile care se duc in starea curenta
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < _fa[i].size(); ++i)
        if(_fa[i][j].first == current) {

            for (int k = 0; k < _fa[current].size(); ++k) {
                string exp = "";
                // Verificam daca exista drum direct
                for (int q = 0; q < _fa[i].size(); ++q)
                    if (_fa[i][q].first == _fa[current][k].first) {
                        exp = _fa[i][q].second + "|";
                        _fa[i].erase(_fa[i].begin() + q);
                    }

                // Construirea expresiei
                if (_fa[i][j].second[1] == '|')
                    exp += "(" + _fa[i][j].second + ")";
                else if (_fa[i][j].second != "0")
                    exp += _fa[i][j].second;
                exp += loop;
                if (_fa[current][k].second.size() > 1)
                    exp += "(" + _fa[current][k].second + ")";
                else if (_fa[current][k].second != "0")
                    exp += _fa[current][k].second;

                _fa[i].push_back({_fa[current][k].first, exp});
            }
            // Stergem nodul
            _fa[current].clear();
            _fa[i].erase(_fa[i].begin() + j);
        }
}
