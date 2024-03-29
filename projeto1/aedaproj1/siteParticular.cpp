//
//  siteParticular.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "siteParticular.h"

float SiteParticular::custoPorPagina = CUSTOPARTICULAR_PREDEFINIDO;

unsigned int SiteParticular::limitePaginas = LIMITEPAGINAS_PREDEFINIDO;

Website::Tipo SiteParticular::tipo = particular;

Website::Tipo SiteParticular::getTipo() const{
    return this->tipo;
}

SiteParticular::SiteParticular(string i, unsigned int n, string tech, Utilizador* gest): Website(i, n), tecnologia(tech), gestor(gest)
{
    if (n > limitePaginas) {
        stringstream ss;
        ss << "O numero limite de paginas para particulares " << limitePaginas << ".";
        string str = ss.str();
        throw LimiteDePaginasUltrapassado(str);
    }
    atribuiGestao(gestor);
}

SiteParticular::~SiteParticular(){ // eliminar do gestor este site
    gestor->retiraWebsiteResponsavel(this);
}

string SiteParticular::getTecnologia() const{
    return tecnologia;
}
void SiteParticular::setTecnologia(const string &t){
    tecnologia = t;
}
Utilizador* SiteParticular::getGestor() const{
    return gestor;
}
void SiteParticular::setGestor(Utilizador* u){
    gestor = u;
    return;
}

float SiteParticular::getCusto() const{
    return custoPorPagina*numeroPaginas;
}

void SiteParticular::setCustoPorPagina(const float &custo){
    custoPorPagina = custo;
    return;
}

void SiteParticular::setLimitePaginas(const unsigned int &limite){
    limitePaginas = limite;
    return;
}

unsigned int SiteParticular::getLimitePaginas(){
    return limitePaginas;
}

float SiteParticular::getCustoPorPagina(){
    return custoPorPagina;
}

void SiteParticular::setNumeroPaginas(unsigned int n){
    if (n > limitePaginas) {
        stringstream ss;
        ss << "O numero limite de paginas para particulares e' " << limitePaginas << ".";
        string str = ss.str();
        throw LimiteDePaginasUltrapassado(str);
    } else
        Website::setNumeroPaginas(n);

}




