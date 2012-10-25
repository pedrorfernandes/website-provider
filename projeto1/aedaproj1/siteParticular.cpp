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
    vector<Website*> & sites = gestor->sitesResponsavel;
    for (vector<Website*>::iterator site_it = sites.begin(); site_it != sites.end() ; ++site_it) {
        if ( (*(*site_it)) == this) {
            site_it = sites.erase(site_it);
            break;
        }
    }
}

string SiteParticular::getTecnologia() const{
    return tecnologia;
}
void SiteParticular::setTecnologia(const string &t){
    tecnologia = t;
}
Utilizador* SiteParticular::getGestor() const{
    // if (gestor == NULL) throw Erro("null"); // o programa ira lidar com NULL
    return gestor;
}
void SiteParticular::setGestor(Utilizador* u){
    gestor = u;
    return;
}

float SiteParticular::getCusto(){
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
        ss << "O numero limite de paginas para particulares e'" << limitePaginas << ".";
        string str = ss.str();
        throw LimiteDePaginasUltrapassado(str);
    } else
        Website::setNumeroPaginas(n);

}

ostream & operator<<(ostream &out, SiteParticular* site){
    out << site->getIdentificador() << " " << site->getNumeroPaginas() << " " << site->tecnologia << " " << site->gestor;
    return out;
}



