//
//  utilizador.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef utilizador_h
#define utilizador_h

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define ESPACO 10

#include "website.h"

class Website;

using namespace std;


class Utilizador{
    unsigned int numIdentidade;
    string nome;
    vector<Website*> sitesResponsavel;
public:
    Utilizador(unsigned int i, string n);
    ~Utilizador();
    
    friend class SiteEmpresa;
    friend class SiteParticular;
    
    unsigned int getNumIdentidade() const;
    void setNumIdentidade(unsigned int &n);
    string getNome() const;
    void setNome(string &n);
    const vector<Website*> & getSitesResponsavel() const;
    
    void adicionaSite(Website *site);
    bool operator==(Utilizador u) const;
    bool operator==(Utilizador* u) const;
        
    friend std::ostream & operator<<(std::ostream &out, Utilizador* u);
    
    friend vector<Utilizador*> operator-(const vector<Utilizador*> vec1, const vector<Utilizador*> vec2);

};

#endif 