//
//  siteEmpresa.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef siteEmpresa_h
#define siteEmpresa_h

#include <iostream>
#include <vector>
#include <string>

#include "website.h"
#include "utilizador.h"

#define CUSTOEMPRESA_PREDEFINIDO 100

using namespace std;

class SiteEmpresa : public Website{
    vector<string> tecnologias;
    vector<Utilizador* > gestores;
    static float custoPorPagina;
public:
    SiteEmpresa(string i, unsigned int n, vector<string> tech, vector<Utilizador*> gest);
    ~SiteEmpresa();
    
    vector<string> getTecnologias() const;
    void setTecnologias(const vector<string> &t);
    vector<Utilizador *> & getGestores();  // endereco de memoria, assim da para ordenar o vector
    const vector<Utilizador *> getConstGestores();
    void setGestores(const vector<Utilizador*> &g);
    static void setCustoPorPagina(const float &custo);
    float getCustoPorPagina() const;
    
    
    float getCusto();
    
    void novaTecnologia(const string &tech);
    bool retiraTecnologia(const string &tech);
    void novoGestor(Utilizador* u);
    bool retiraGestor(Utilizador* u);

    // operador atribuicao = 
    // operador == !=
    
    
};

#endif
