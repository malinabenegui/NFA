#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ifstream f("nfa.in");

vector < pair < char, int > > adiac[100];

pair < char, int > read_pair() //citesc perechea p
{
    pair < char, int > p;

    f >> p.first >> p.second;

    return p;
}

void nod_final(int fin[], int &n, int &nr_fin) //citesc nodurile finale
{
    int i;
    f >> n >> nr_fin;
    for(i = 0; i < nr_fin; i++)
        f >> fin[i];
}

void creare() //citesc nodul
{
    int nod;
    while(f >> nod)
        adiac[nod].push_back(read_pair());
}

bool is_final(int fin[], int nr_fin, int nod_curr) //verific daca nodul meu e final
{
    for(int i = 0; i < nr_fin; i++)
        if(fin[i] == nod_curr)
            return 1;
    return 0;
}

void backtrack(int &ok, char *s, int k, int n, char *s1, int nod_curr, int fin[], int nr_fin)
{
    int i;

    if (k == n && is_final(fin, nr_fin, nod_curr) == 1)
    {
        ok = 1;
        return;
    }

    else if (k == n && is_final(fin, nr_fin, nod_curr) == 0)
        return;

    else if (k<n)
    {
        for(i = 0; i < adiac[nod_curr].size(); i++)
        {
            s1[k] = adiac[nod_curr][i].first;

            if(s1[k] == s[k])
                backtrack(ok, s, k+1, n, s1, adiac[nod_curr][i].second, fin, nr_fin);
        }
    }
}


int main()
{
    int fin[100], n,n1, nr_fin, ok = 0;
    char s[] = "aababba";
    char s1[100];

    n1 = strlen(s);

    nod_final(fin, n, nr_fin);
    creare();

    backtrack(ok, s, 0, n1, s1, 0, fin, nr_fin);
    cout << ok;

    return 0;
}
