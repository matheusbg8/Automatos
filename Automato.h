#ifndef AUTOMATO_H
#define AUTOMATO_H

#include<vector>
#include<string>
#include<map>
#include<stack>
#include<set>

using namespace std;

class Automato
{
    vector<vector<pair<int,string> > > m_g;
    int m_a;
    int m_ini;

    set<string> m_arc;
    map<string, int> m_id;
    vector<string> m_nome;

public:
    Automato();

    bool existeEstado(string e) const;
    bool existeArco(string simb) const;
    bool existeArco(int de , int para, const string &simb) const;

    int id(string nome) const;
    int id(string nome);
    string nome(int id) const;

    int numArco(int e) const;
    int numArco(string e) const;
    int numArco() const;

    pair<int, string> arco(int e, int i) const;
    pair<int, string> arco(int i) const;

    void arco(int de, int para, string simb);
    void arco(string de, string para, string simb);

    bool processa(string s);

    void setEstadoInicial(string s);
    string estadoInicial() const;

    string estado() const;
    void setEstado(string nome);

    void imprime() const;
};

Automato Compoem(Automato a , Automato b);

#endif // AUTOMATO_H
