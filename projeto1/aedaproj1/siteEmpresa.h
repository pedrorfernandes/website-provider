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

/**
 * O SiteEmpresa, para alem de um identificador e numero de paginas, possui um vector com as tecnologias que usa, um vector com os gestores do site e um custo por pagina para sites empresa
 */
class SiteEmpresa : public Website{
    vector<string> tecnologias;
    vector<Utilizador* > gestores;
    static float custoPorPagina;
public:
    SiteEmpresa(string i, unsigned int n, vector<string> tech, vector<Utilizador*> gest);
    ~SiteEmpresa();
    
    /**
     * Retorna o vector de tecnologias do website empresa
     * @return O vector de tecnologias (strings)
     */
    vector<string> getTecnologias() const;
    
    /**
     * Modifica o vector de tecnologias do website empresa
     * @param t O novo vector de tecnologias (strings)
     * @return Void
     */
    void setTecnologias(const vector<string> &t);
    
    /**
     * Retorna o vector de utilizadores que sao gestores website empresa
     * @return O vector de gestores
     */
    vector<Utilizador *> & getGestores();  // endereco de memoria, assim da para ordenar o vector
    
    /**
     * Retorna um vector imutavel de utilizadores que sao gestores website empresa
     * @return O vector constante de gestores
     */
    const vector<Utilizador *> getConstGestores();
    void setGestores(const vector<Utilizador*> &g);
    static void setCustoPorPagina(const float &custo);
    static float getCustoPorPagina();
    
    
    float getCusto();
    
    void novaTecnologia(const string &tech);
    bool retiraTecnologia(const string &tech);
    void novoGestor(Utilizador* u);
    bool retiraGestor(Utilizador* u);

    friend ostream & operator<<(ostream &out, SiteEmpresa* site);
    // operador atribuicao = 
    // operador == !=
    
    
};

#endif
