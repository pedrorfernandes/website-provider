//
//  siteEmpresa.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "siteEmpresa.h"

float SiteEmpresa::custoPorPagina = CUSTOEMPRESA_PREDEFINIDO;

SiteEmpresa::SiteEmpresa(string i, unsigned int n, vector<string> tech, vector<Utilizador*> gest): Website(i, n), tecnologias(tech), gestores(gest)
{
    for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
        atribuiGestao(*it);
    }

}

SiteEmpresa::~SiteEmpresa(){ // e' necessario eliminar os sites dos gestores
    for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end(); gestor_it++) {
        vector<Website*> & sites = (*gestor_it)->sitesResponsavel;
        for (vector<Website*>::iterator site_it = sites.begin(); site_it != sites.end() ; site_it++) {
            if ( (*site_it) == this ){
                site_it = sites.erase(site_it);
                break;
            }
        }
    }
}

vector<string> SiteEmpresa::getTecnologias() const{
    return tecnologias;
}

void SiteEmpresa::setTecnologias(const vector<string> &t){
    tecnologias = t;
    return;
}

vector<Utilizador *> & SiteEmpresa::getGestores(){
    return gestores;
}

const vector<Utilizador *> SiteEmpresa::getConstGestores(){
    return gestores;
}

void SiteEmpresa::setGestores(const vector<Utilizador*> &g){
    gestores = g;
    return;
}

float SiteEmpresa::getCusto(){
    return custoPorPagina*numeroPaginas;
}

void SiteEmpresa::setCustoPorPagina(const float &custo){
    custoPorPagina = custo;
    return;
}

bool SiteEmpresa::novaTecnologia(const string &tech){
    for (vector<string>::iterator tech_it = tecnologias.begin(); tech_it != tecnologias.end(); tech_it++) {
        if ( (*tech_it) == tech){
            return false;
            break;
        }
    }
    tecnologias.push_back(tech);
    return true;
}

bool SiteEmpresa::retiraTecnologia(const string &tech){
    for (vector<string>::iterator it = tecnologias.begin(); it != tecnologias.end(); it++) {
        if ( (*it) == tech){
            it = tecnologias.erase(it);
            return true;
        }
    }
    return false;
}

bool SiteEmpresa::retiraGestor(Utilizador* u){
    for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
        if ( *(*it) == u){
            it = gestores.erase(it);
            return true;
        }
    }
    return false;
}

void SiteEmpresa::novoGestor(Utilizador* u){
    gestores.push_back(u);
    return;
}

float SiteEmpresa::getCustoPorPagina(){
    return custoPorPagina;
}

