//
//  gestorWSP.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef gestorWSP_h
#define gestorWSP_h


#include <iostream>

#include "website.h"
#include "utilizador.h"
#include "siteEmpresa.h"
#include "siteParticular.h"

class GestorWSP{
    vector<Website*> websites;
    vector<Utilizador*> gestores;
    
    // membros auxiliares de ordenacao, nao acessiveis a outras classes
    static bool Alfabetico(Website* w1, Website* w2);
    static bool AlfabeticoContrario(Website* w1, Website* w2);


public:
    GestorWSP();
    ~GestorWSP();
    bool novoSite(Website* w);
    bool adicionaGestor(Utilizador* u);
    
    //const vector<Website*> & getWebsites() const;
    //const vector<Utilizador*> & getGestores() const;
    
    vector<Website*> & getWebsites();
    vector<Utilizador*> & getGestores();
    bool eliminaSite(Website* w);
    bool eliminaCliente(Utilizador* u);
    
    // funcoes ordenacao
    
    void ordenaWebsitesAlfabetico();
    void ordenaWebsitesAlfabeticoContrario();

    
};

#endif
