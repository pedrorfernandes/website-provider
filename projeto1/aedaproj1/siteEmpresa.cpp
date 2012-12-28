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

Website::Tipo SiteEmpresa::tipo = empresa;

Website::Tipo SiteEmpresa::getTipo() const{
    return this->tipo;
}

SiteEmpresa::SiteEmpresa(string i, unsigned int n, vector<string> tech, vector<Utilizador*> gest): Website(i, n), tecnologias(tech), gestores(gest)
{
    for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
        atribuiGestao(*it);
    }
}

SiteEmpresa::~SiteEmpresa(){ // e' necessario eliminar os sites dos gestores
    for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end(); gestor_it++) {
        (*gestor_it)->retiraWebsiteResponsavel(this);
    }
}

const vector<string> & SiteEmpresa::getTecnologias() const{
    return tecnologias;
}

void SiteEmpresa::setTecnologias(const vector<string> &t){
    tecnologias = t;
    return;
}

const vector<Utilizador *> & SiteEmpresa::getGestores() const{
    return gestores;
}


void SiteEmpresa::setGestores(const vector<Utilizador*> &g){
    gestores = g;
    return;
}

float SiteEmpresa::getCusto() const{
    return custoPorPagina*numeroPaginas;
}

void SiteEmpresa::setCustoPorPagina(const float &custo){
    custoPorPagina = custo;
    return;
}

bool SiteEmpresa::novaTecnologia(string &tech){
    transform(tech.begin(), tech.end(), tech.begin(), ::tolower);
    string aux; // string auxiliar na pesquisa
    for (vector<string>::iterator tech_it = tecnologias.begin(); tech_it != tecnologias.end(); tech_it++) {
        aux = (*tech_it);
        transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
        if ( aux == tech){
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
