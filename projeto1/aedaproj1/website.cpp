//
//  website.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "website.h"


Website::Website(string i, unsigned int n): identificador(i), numeroPaginas(n){}

Website::~Website(){}


unsigned int Website::getNumeroPaginas() const{
    return numeroPaginas;
}

void Website::setNumeroPaginas(unsigned int n){
    numeroPaginas = n;
    return;
}

string Website::getIdentificador() const{
    return identificador;
}


void Website::setIdentificador(string &i){
    identificador = i;
    return;
}


void Website::atribuiGestao(Utilizador * gestor){
    gestor->adicionaSite(this);
}

bool Website::operator==(Website* w) const{
    return (identificador == w->identificador);
}

// membros funcao para aceder aos dados da filha siteParticular
string Website::getTecnologia() const{throw Erro("getTecnologia(): so acessivel a partir de SiteParticular");}
void Website::setTecnologia(const string &t){throw Erro("setTecnologia(): so acessivel a partir de SiteParticular");}
Utilizador* Website::getGestor() const{throw Erro("getGestor(): so acessivel a partir de SiteParticular");}
void Website::setGestor(Utilizador* u){throw Erro("setGestor(): so acessivel a partir de SiteParticular");}
//unsigned int Website::getLimitePaginas() const{throw Erro("getLimitePaginas(): so acessivel a partir de SiteParticular");}
//float Website::getCustoPorPagina() const{throw Erro("getCustoPorPagina(): so acessivel a partir de SiteParticular");}

// membros funcao para aceder aos dados da filha siteEmpresa
vector<string> Website::getTecnologias() const{throw Erro("getTecnologias(): so acessivel a partir de SiteEmpresa");}
void Website::setTecnologias(const vector<string> &t){throw Erro("setTecnologias(): so acessivel a partir de SiteEmpresa");}
vector<Utilizador *> & Website::getGestores(){throw Erro("getGestores(): so acessivel a partir de SiteEmpresa");}
void Website::setGestores(const vector<Utilizador*> g){throw Erro("setGestores(): so acessivel a partir de SiteEmpresa");}
void Website::novaTecnologia(const string &tech){throw Erro("novaTecnologia(): so acessivel a partir de SiteEmpresa");}
bool Website::retiraTecnologia(const string & tech){throw Erro("retiraTecnologia(): so acessivel a partir de SiteEmpresa");}
void Website::novoGestor(Utilizador* u){throw Erro("novoGestor(): so acessivel a partir de SiteEmpresa");}
bool Website::retiraGestor(Utilizador* u){throw Erro("novoGestor(): so acessivel a partir de SiteEmpresa");}

