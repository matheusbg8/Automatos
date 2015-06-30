#include <iostream>
#include<Automato.h>

using namespace std;

int main()
{
/*
 *    Este código encontra o autômato que controla um sistema
 * que existem 3 máquinas , m1 , m2 e m3. A máquina m1 e
 * m2 descarregam suas peças em um espaço B, a máquina m3
 * pega as peças do espaço B e realiza uma segunda etapa de produção.
 *     O Autômato deve controlar o sistema de forma a evitar overflow
 * e underflow de peças no espaço B. As máquinas são definidas por
 * dois eventos. Evento a, maquina retira uma peça e começa o trabalho,
 * evento b, a máquina termina o trabalho e larga a peça em sua saída.
 *
 *     O autômato final foi encontrado a partir da composição de 5 autômatos.
 * Os autômatos m1, m2 e m3 definem as máquinas, e os autômatos c1 e c2
 * impoem restrições aos autômatos das máquina.
 *
 *     Automato final =  ( m1 || m2 || m3 ) || ( c1 || c2 )
 *
 *
 */

    Automato m1, m2, m3, c1,c2, G, C,E;

    // Define autômato da Máquina 1
    m1.arco("a" , "b" , "a3");   // Do estado "a" para o estado "b" com síbolo "a3" (alpha3)
    m1.arco("b" , "a" , "b3");   // Do estado "b" para o estado "a" com síbolo "b3" (beta3)
    m1.setEstadoInicial("a");  // Define o estado a como estado inicial

    // Define autômato da Máquina 2
    m2.arco("c" , "d" , "a1");
    m2.arco("d" , "c" , "b1");
    m2.setEstadoInicial("c");

    // Define autômato da Máquina 3
    m3.arco("e" , "f" , "a2");
    m3.arco("f" , "e" , "b2");
    m3.setEstadoInicial("e");

    // Define autômato de controle 1
    c1.arco("1" , "2" , "a3");
    c1.arco("1" , "3" , "a1");
    c1.arco("2" , "1" , "b3");
    c1.arco("3" , "1" , "b1");
    c1.setEstadoInicial("1");

    // Define autômato de controle 2
    c2.arco("1" , "2" , "b1");
    c2.arco("1" , "2" , "b3");
    c2.arco("2" , "1" , "a2");
    c2.setEstadoInicial("1");

    // Encontra autômato da planta G , compoem m1, m2 e m3
    G = Compoem(m1,m2);
    G = Compoem(G,m3);

    // Encontra automato de controle C , compoem c1 com c2
    C = Compoem(c1, c2);

    // Encontra autômato final E, composição da planta com controle G || C
    E = Compoem(G, C);

    // Imprime as respostas
    cout << "M1:" << endl;
    m1.imprime();

    cout << endl <<  "M2:" << endl;
    m2.imprime();

    cout << endl <<  "M3:" << endl;
    m3.imprime();

    cout << endl <<  "C1:" << endl;
    c1.imprime();

    cout << endl <<  "C2:" << endl;
    c2.imprime();

    cout << endl <<  "G:" << endl;
    G.imprime();

    cout << endl << "C:" << endl;
    C.imprime();

    cout << endl << "E:" << endl;
    E.imprime();

    cout << endl << "Mesmo E:" << endl;
    Compoem( Compoem(Compoem(m1,m2),m3), Compoem(c1, c2) ).imprime();

    return 0;
}

/*
int main()
{
    // Cria 3 Autômatos
    Automato m1, m2, G;

    // Define autômato da Máquina 1
    m1.arco("a" , "b" , "a1");   // de "a" para "b" com símbolo "a1"
    m1.arco("b" , "a" , "b1");   // de "b" para "a" com símbolo "b1"

    // Define autômato da Máquina 2
    m2.arco("c" , "d" , "a2");
    m2.arco("d" , "c" , "b2");

    G = Compoem(m1, m2);

    G.imprime();
    return 0;
}
*/

/*

int main()
{
    Automato a, b,c,d;
    string s;

    a.arco("0" , "1" , "r1");
    a.arco("1" , "0" , "l1");
    a.setEstadoInicial("0");

    b.arco("0" , "1" , "g2");
    b.arco("1" , "0" , "l2");
    b.setEstadoInicial("0");

    c.arco("0" , "2" , "l2");
    c.arco("0" , "1" , "l1");
    c.arco("1" , "0" , "g2");
    c.arco("2" , "0" , "g");

    cout << endl << endl << "1" << endl;
    d = ComposicaoSincrona(a , b);
    d.imprime();

    cout << endl << endl << "2 " << endl;
    ComposicaoSincrona(d, c).imprime();

    return 0;
}

*/

/*
int main()
{
    Automato a, b, c, d;

    a.arco("a" , "b" , "i0");
    a.arco("b" , "c" , "i1");
    a.arco("c" , "a" , "i2");
    a.setEstadoInicial("a");

    b.arco("d" , "e" , "j0");
    b.arco("e" , "f" , "j1");
    b.arco("f" , "d" , "j2");
    b.setEstadoInicial("d");

    c.arco("1", "2", "i0");
    c.arco("1", "1", "j1");
    c.arco("2", "1", "i1");
    c.setEstadoInicial("1");

    d = ComposicaoSincrona(a , b);

    d = ComposicaoSincrona(d , c);
    d.imprime();

    return 0;
}
*/

/*
int main()
{
    Automato a, b, c, d;

    a.arco("a" , "b" , "a0");
    a.arco("a" , "d" , "b0");

    a.arco("b" , "c" , "a1");
    a.arco("b" , "e" , "b0");

    a.arco("c" , "a" , "a2");
    a.arco("c" , "f" , "b0");

    a.arco("d" , "e" , "a0");
    a.arco("d" , "g" , "b1");

    a.arco("e" , "f" , "a1");
    a.arco("e" , "h" , "b1");

    a.arco("f" , "d" , "a2");
    a.arco("f" , "i" , "b1");

    a.arco("g" , "h" , "a0");
    a.arco("g" , "a" , "b2");

    a.arco("h" , "b" , "b2");
    a.arco("h" , "i" , "a1");

    a.arco("i" , "g" , "a2");
    a.arco("i" , "c" , "b2");

    a.setEstadoInicial("a");

    b.arco("0" , "1" , "a1");
    b.arco("1" , "0" , "a2");
    b.arco("0" , "2" , "b1");
    b.arco("2" , "0" , "b2");
    b.setEstadoInicial("0");

    c.arco("0" , "0" , "b1");
    c.arco("0" , "1" , "a0");
    c.arco("1" , "0" , "a1");

    d = ComposicaoSincrona(b , c);
    d = ComposicaoSincrona(a , d);
    d.imprime();

    return 0;
}
*/
