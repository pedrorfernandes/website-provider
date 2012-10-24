//
//  gestorWSP.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "gestorWSP.h"

GestorWSP::GestorWSP(){}

GestorWSP::~GestorWSP(){
    for (vector<Website*>::iterator it = websites.begin(); it != websites.end(); it++) {
        delete (*it);
    }
}


bool GestorWSP::adicionaGestor(Utilizador* u){
    for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
        if ( (*(*it)) == u ) {
            return false;
        }
    }
    gestores.push_back(u);
    return true;
}


bool GestorWSP::novoSite(Website* w){
    for (vector<Website*>::iterator it = websites.begin(); it != websites.end(); it++) {
        if ( (*(*it)) == w) {
            return false;
        }
    }
    
    // para descobrir se o site eh de uma empresa ou particular
    SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(w);
    SiteParticular* particular = dynamic_cast< SiteParticular* >(w);
    
    
    // adicionar automaticamente os gestores do site ao vector de utilizadores do WSP
    if (empresa) {
        for (vector<Utilizador*>::iterator it = empresa->getGestores().begin(); it != empresa->getGestores().end(); it++) {
            adicionaGestor(*it);
            
        }
    }
    
    if (particular) {
        adicionaGestor(particular->getGestor() );
    }

    
    websites.push_back(w);
    return true;
}


vector<Website*> & GestorWSP::getWebsites(){
    return websites;
}
vector<Utilizador*> & GestorWSP::getGestores(){
    return gestores;
}

/*
const vector<Website*> & GestorWSP::getWebsites() const{
    return websites;
}
const vector<Utilizador*> & GestorWSP::getGestores() const{
    return gestores;
}
*/

bool GestorWSP::eliminaSite(Website* w){
    // eliminar um site nao elimina os gestores
    for (vector<Website*>::iterator it = websites.begin(); it != websites.end(); it++) {
        if ( (*(*it)) == w) {
            delete (*it);
            it = websites.erase(it);
            return true;
        }
    }
    return false;
}

bool GestorWSP::eliminaCliente(Utilizador *u){
    // eliminar um gestor elimina-o das listas dos sites de que sao responsaveis
     for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
        if ( (*(*it)) == u) {
            delete (*it);
            it = gestores.erase(it);
            return true;
        }
    }
    return false;
}
