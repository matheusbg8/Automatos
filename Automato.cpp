#include "Automato.h"
#include<iostream>

Automato::Automato()
{
    m_a = 0;
    m_ini = 0;
}

bool Automato::existeEstado(string e) const
{
    map<string, int>::const_iterator i = m_id.find(e);
    if( i == m_id.end())
       return false;
    return true;
}

bool Automato::existeArco(string simb) const
{
    set<string>::iterator i = m_arc.find(simb);
    if(i == m_arc.end())
        return false;
    return true;
}

bool Automato::existeArco(int de, int para,  const string &simb) const
{
    int i;
    if(de < m_g.size())
    for(i = 0 ; i < m_g[de].size() ; i++)
    {
        if(m_g[de][i].first == para && m_g[de][i].second == simb)
            return true;
    }
    return false;
}

int Automato::id(string nome) const
{
    map<string, int>::const_iterator i = m_id.find(nome);

    if( i == m_id.end())
    {
        return -1;
    }

    return i->second;
}

int Automato::id(string nome)
{
    map<string, int>::iterator i = m_id.find(nome);

    if( i == m_id.end())
    {
        m_nome.push_back(nome);
        m_id[nome] = m_nome.size()-1;
        return m_nome.size()-1;
    }

    return i->second;
}

string Automato::nome(int id) const
{
    return m_nome[id];
}

void Automato::arco(int de, int para, string simb)
{
    if(de >= m_g.size())
        m_g.resize((de+1)*2);
    if(para >= m_g.size())
        m_g.resize((para+1)*2);

    if(!existeArco(de,para,simb))
    {
        m_arc.insert(simb);
        m_g[de].push_back(make_pair(para, simb));
    }
}

void Automato::arco(string de, string para, string simb)
{
    int ide = id(de), ipara = id(para);
    arco(ide, ipara , simb);
}

int Automato::numArco(int e) const
{
    return m_g[e].size();
}

int Automato::numArco(string e) const
{
    int es = id(e);
    return m_g[es].size();
}

int Automato::numArco() const
{
    return m_g[m_a].size();
}

pair<int, string> Automato::arco(int e, int i) const
{
    return m_g[e][i];
}

pair<int, string> Automato::arco(int i) const
{
    return m_g[m_a][i];
}

bool Automato::processa(string s)
{
    int i, u = m_a , v;
    for(i = 0 ; i < m_g[u].size() ; i++)
    {
        if(s == m_g[u][i].second)
        {
            m_a = m_g[u][i].first;
            return true;
        }
    }
    return false;
}

void Automato::setEstadoInicial(string s)
{
    m_ini = id(s);
}

string Automato::estadoInicial() const
{
    return m_nome[m_ini];
}


string Automato::estado() const
{
    if(m_nome.size() == 0)
        return string();

    return m_nome[m_a];
}

void Automato::setEstado(string nome)
{
    m_a = id(nome);
}

void Automato::imprime() const
{
    int i ,j;

    for( i = 0 ; i < m_g.size(); i++)
    {
        for( j = 0 ; j < m_g[i].size() ; j++)
        {
            cout << m_nome[i] << " - " << m_g[i][j].second << " -> " << m_nome[m_g[i][j].first] << endl;
        }
    }
}

Automato Compoem(Automato a , Automato b)
{
    Automato r;
    stack< pair<string,string> > pilha;
    pair<string,string> u, v;
    string s;
    int i, na , nb;

    pilha.push( make_pair(a.estadoInicial(), b.estadoInicial()));

    while(!pilha.empty())
    {
        u = pilha.top();
        pilha.pop();

        a.setEstado(u.first);
        b.setEstado(u.second);

        na = a.numArco();
        nb = b.numArco();

        for(i = 0 ; i < na ; i++)
        {
            s = a.arco(i).second;
            if(b.existeArco(s))
            {
                if(b.processa(s))
                {// Sincrono
                    a.processa(s);
                }else // Não possivel
                    continue;
            }else
            { // Assincrono
                a.processa(s);
                b.processa(s);
            }

            if(!r.existeEstado(a.estado() + b.estado()))
                pilha.push(make_pair(a.estado() , b.estado()));

            r.arco(u.first + u.second , a.estado() + b.estado(), s );

            a.setEstado(u.first);
            b.setEstado(u.second);
        }

        for(i = 0 ; i < nb ; i++)
        {
            s = b.arco(i).second;
            if(a.existeArco(s))
            {
                if(a.processa(s))
                {// Sincrono
                    b.processa(s);
                }else // Não possivel
                    continue;
            }else
            { // Assincrono
                a.processa(s);
                b.processa(s);
            }

            if(!r.existeEstado(a.estado() + b.estado()))
                pilha.push(make_pair(a.estado() , b.estado()));

            r.arco(u.first + u.second , a.estado() + b.estado(), s );

            a.setEstado(u.first);
            b.setEstado(u.second);
        }
    }
    return r;
}
