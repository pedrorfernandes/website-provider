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
    for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end(); gestor_it++) {
        if ( (*(*gestor_it)) == u ) {
            stringstream numero;
            numero << u->getNumIdentidade();
            throw UtilizadorJaExistente(numero.str());
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
    
    /*
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
     */
    websites.push_back(w);
    return true;
}


vector<Website*> & GestorWSP::getWebsites(){
    return websites;
}
vector<Utilizador*> & GestorWSP::getGestores(){
    return gestores;
}


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

bool GestorWSP::identificadorAlfabetico(Website* w1, Website* w2){
    return (w1->getIdentificador() < w2->getIdentificador() );
}

bool GestorWSP::identificadorAlfabeticoInverso(Website* w1, Website* w2){
    return (w1->getIdentificador() > w2->getIdentificador() );
}

bool GestorWSP::numeroPaginasAscendente(Website* w1, Website* w2){
    return (w1->getNumeroPaginas() < w2->getNumeroPaginas());
}

bool GestorWSP::numeroPaginasDescendente(Website* w1, Website* w2){
    return (w1->getNumeroPaginas() > w2->getNumeroPaginas());
}



void GestorWSP::ordenaWebsites(string criterio){
    if (criterio == "identificador alfabetico") {
        sort(websites.begin(), websites.end(), identificadorAlfabetico);
    } else if (criterio == "identificador alfabetico inverso"){
        sort(websites.begin(), websites.end(), identificadorAlfabeticoInverso);
    } else if (criterio == "numero paginas ascendente"){
        sort(websites.begin(), websites.end(), numeroPaginasAscendente);
    } else if (criterio == "numero paginas descendente"){
        sort(websites.begin(), websites.end(), numeroPaginasDescendente);
    }
    return;
}

bool GestorWSP::nomeAlfabetico(Utilizador* u1, Utilizador* u2){
    return (u1->getNome() < u2->getNome() );
}

bool GestorWSP::nomeAlfabeticoInverso(Utilizador* u1, Utilizador* u2){
    return (u1->getNome() > u2->getNome() );
}

bool GestorWSP::numeroAscendente(Utilizador* u1, Utilizador* u2){
    return (u1->getNumIdentidade() < u2->getNumIdentidade() );
}

bool GestorWSP::numeroDescendente(Utilizador* u1, Utilizador* u2){
    return (u1->getNumIdentidade() > u2->getNumIdentidade() );
}


void GestorWSP::ordenaUtilizadores(string criterio){
    if (criterio == "nome alfabetico"){
        sort(gestores.begin(), gestores.end(), nomeAlfabetico);
    } else if (criterio == "nome alfabetico inverso"){
        sort(gestores.begin(), gestores.end(), nomeAlfabeticoInverso);
    } else if (criterio == "numero ascendente"){
        sort(gestores.begin(), gestores.end(), numeroAscendente);
    } else if (criterio == "numero descendente"){
        sort(gestores.begin(), gestores.end(), numeroDescendente);
    }
    return;
}


Utilizador* GestorWSP::getGestorPointer(Utilizador u){
    for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end(); gestor_it++) {
        if ( (*(*gestor_it)) == u ) {
            return (*gestor_it);
            break;
        }
    }
    return NULL;
}

float GestorWSP::calculoCustoTotal(){
    float total = 0;
    for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
        total += (*site_it)->getCusto();
    }
    return total;
}

void GestorWSP::ajustarNumeroPaginasParaParticulares(){
    for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
        SiteParticular* particular = dynamic_cast< SiteParticular* >(*site_it);
        if (particular) {
            if ((*site_it)->getNumeroPaginas() > SiteParticular::getLimitePaginas()) {
                (*site_it)->setNumeroPaginas(SiteParticular::getLimitePaginas());
            }
        }
    }
    return;
}

vector<Website*> GestorWSP::pesquisaWebsite(string tipoCriterio, string criterio){
    vector<Website*> resultados;
    if (tipoCriterio == "identificador") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if (string::npos != (*site_it)->getIdentificador().find(criterio))
            {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "particulares") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            SiteParticular* particular = dynamic_cast< SiteParticular* >(*site_it);
            if (particular) {
                resultados.push_back(*site_it);
            }
        }
        
    } else if (tipoCriterio == "empresas") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(*site_it);
            if (empresa) {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "tecnologia") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            SiteParticular* particular = dynamic_cast< SiteParticular* >(*site_it);
            SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(*site_it);
            if (particular) {
                if (string::npos != (*site_it)->getTecnologia().find(criterio))
                {
                    resultados.push_back(*site_it);
                }
            }
            if (empresa) {
                for (vector<string>::iterator tech_it = (*site_it)->getTecnologias().begin(); tech_it != (*site_it)->getTecnologias().end(); tech_it++) {
                    if (string::npos != (*tech_it).find(criterio))
                    {
                        resultados.push_back(*site_it);
                        break;
                    }
                }
            }
            
        }
    }
    return resultados;
    
}

vector<Website*> GestorWSP::pesquisaWebsite(string tipoCriterio, unsigned int criterio){
    vector<Website*> resultados;
    return resultados;
}


vector<Utilizador*> GestorWSP::pesquisaUtilizador(string tipoCriterio, string criterio){
    vector<Utilizador*> resultados;
    if (tipoCriterio == "nome") {
        for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end();gestor_it++) {
            if (string::npos != (*gestor_it)->getNome().find(criterio))
            {
                resultados.push_back(*gestor_it);
            }
        }
    }
    return resultados;
}

vector<Utilizador*> GestorWSP::pesquisaUtilizador(string tipoCriterio, unsigned int criterio){
    vector<Utilizador*> resultados;
    if (tipoCriterio == "numero") {
        for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end();gestor_it++) {
            if ( (*gestor_it)->getNumIdentidade() == criterio ) {
                resultados.push_back(*gestor_it);
            }
        }
    }
    return resultados;
}

bool GestorWSP::identificadorValido(string identificador){
    bool jaExiste = false;
    for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
        if ( (*site_it)->getIdentificador() == identificador) {
            jaExiste = true;
            break;
        }
    }
    if (jaExiste) {
        return false;
    } else
        return true;
}

bool GestorWSP::numeroIdentidadeValido(unsigned int numero){
    for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end();gestor_it++) {
        if ((*gestor_it)->getNumIdentidade() == numero) {
            return false;
        }
    }
    return true;
}



