//
//  website.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef website_h
#define website_h

#include <iostream>

#include "utilizador.h"

using namespace std;

class Utilizador; // pre declaracao

class Erro{
    string msg;
public:
    Erro(string m): msg(m){}
    string getMsg(){return msg;}
};

/**
 * O website possui um identificador (URL) e um numero de paginas
 */
class Website{
protected:
    unsigned int numeroPaginas;
    string identificador;
public:
    Website(string i, unsigned int n);
    virtual ~Website();
    
    /**
     * Retorna o numero de paginas do website
     *
     * @return O numero de paginas
     */
    unsigned int getNumeroPaginas() const;
    
    /**
     * Modifica o numero de paginas do website
     *
     * @param n O novo numero de paginas
     *
     * @return Void
     */
    void setNumeroPaginas(unsigned int n);
    
    /**
     * Retorna o identificador do website
     *
     * @return A string identificadora do website
     */
    string getIdentificador() const;
    
    /**
     * Modifica o identificador do website
     *
     * @param i Referencia para a nova string identificador
     *
     * @return Void
     */
    void setIdentificador(string &i);
    
    /**
     * Retorna o custo do website
     *
     * @return O valor do custo do website
     */
    virtual float getCusto() = 0;
    
    /**
     * Adiciona o proprio website ao vector de sites responsaveis do novo gestor
     *
     * @param gestor Apontador para o novo gestor do site
     *
     * @return Void
     */
    void atribuiGestao(Utilizador* gestor);
    
    // membros funcao para aceder aos dados da filha siteParticular
    virtual string getTecnologia() const;
    virtual void setTecnologia(const string &t);
    virtual Utilizador* getGestor() const;
    virtual void setGestor(Utilizador* u);
    
    //virtual unsigned int getLimitePaginas() const;
    //virtual float getCustoPorPagina() const;
    
    // membros funcao para aceder aos dados da filha siteEmpresa
    virtual vector<string> getTecnologias() const;
    virtual void setTecnologias(const vector<string> &t);
    virtual vector<Utilizador *> & getGestores();
    virtual void setGestores(const vector<Utilizador*> g);
    virtual void novaTecnologia(const string &tech);
    virtual bool retiraTecnologia(const string & tech);
    virtual void novoGestor(Utilizador* u);
    virtual bool retiraGestor(Utilizador* u);

    /**
     * Compara o proprio website a outro
     *
     * @param w Apontador para o website a ser comparado
     *
     * @return True se o website for igual, False caso contrario
     */
    bool operator==(Website* w) const;
    
    friend ostream & operator<<(ostream &out, Website* w);

    
};

#endif
