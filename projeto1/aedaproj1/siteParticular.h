//
//  siteParticular.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef siteParticular_h
#define siteParticular_h

#include <iostream>
#include <vector>
#include <sstream>

#include "website.h"
#include "utilizador.h"

#define CUSTOPARTICULAR_PREDEFINIDO 10
#define LIMITEPAGINAS_PREDEFINIDO 50

using namespace std;

/* erros a implementar:
    - gestor inexistente
 */

class Utilizador;

class LimiteDePaginasUltrapassado: public Erro{
public:
    LimiteDePaginasUltrapassado(string mensagem): Erro(mensagem){}
};

class SiteParticular: public Website{
    string tecnologia;
    Utilizador* gestor;
    static float custoPorPagina;
    static unsigned int limitePaginas;
public:
    SiteParticular(string i, unsigned int n, string tech, Utilizador* gest);
    ~SiteParticular();
    
    string getTecnologia() const;
    void setTecnologia(const string &t);
    Utilizador* getGestor() const;
    void setGestor(Utilizador* u);
    static void setCustoPorPagina(const float & custo);
    static void setLimitePaginas(const unsigned int & limite);
    unsigned int getLimitePaginas() const;
    float getCustoPorPagina() const;
    
    void setNumeroPaginas(unsigned int n);

    
    float getCusto();
    
    
};

#endif
