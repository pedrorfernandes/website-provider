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

class Website{
protected:
    unsigned int numeroPaginas;
    string identificador;
public:
    Website(string i, unsigned int n);
    virtual ~Website();
    
    unsigned int getNumeroPaginas() const;
    virtual void setNumeroPaginas(unsigned int n);
    string getIdentificador() const;
    void setIdentificador(string &i);
    
    virtual float getCusto() = 0;
    
    void atribuiGestao(Utilizador*);
    
    // membros funcao para aceder aos dados da filha siteParticular
    virtual string getTecnologia() const;
    virtual void setTecnologia(const string &t);
    virtual Utilizador* getGestor() const;
    virtual void setGestor(Utilizador* u);
    
    virtual unsigned int getLimitePaginas() const;
    virtual float getCustoPorPagina() const;
    
    // membros funcao para aceder aos dados da filha siteEmpresa
    virtual vector<string> getTecnologias() const;
    virtual void setTecnologias(const vector<string> &t);
    virtual vector<Utilizador *> & getGestores();
    virtual void setGestores(const vector<Utilizador*> g);
    virtual void novaTecnologia(const string &tech);
    virtual bool retiraTecnologia(const string & tech);
    virtual void novoGestor(Utilizador* u);
    virtual bool retiraGestor(Utilizador* u);

    
    bool operator==(Website* w) const;
    
    friend std::ostream & operator<<(std::ostream &out, Website* w);

    
};

#endif
