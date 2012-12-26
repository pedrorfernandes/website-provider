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
    for (vector<Utilizador*>::iterator it = gestores.begin(); it != gestores.end(); it++) {
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
    websites.push_back(w);
    return true;
}


const vector<Website*> & GestorWSP::getWebsites() const{
    return websites;
}
const vector<Utilizador*> & GestorWSP::getGestores() const{
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
            if ( (*it)->UtilizadorEliminavel() ) {
                // O cliente a ser eliminado passa a fazer parte da tabela de Exclientes!
                exclientes.insereExcliente(*it);
				//delete (*it);
				it = gestores.erase(it);            
                return true;
            }
            
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
bool GestorWSP::custoAscendente(Website* w1, Website* w2){
    return (w1->getCusto() < w2->getCusto());
}
bool GestorWSP::custoDescendente(Website* w1, Website* w2){
    return (w1->getCusto() > w2->getCusto());
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
    } else if (criterio == "custo ascendente"){
        sort(websites.begin(), websites.end(), custoAscendente);
    } else if (criterio == "custo descendente"){
        sort(websites.begin(), websites.end(), custoDescendente);
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
        if((*site_it)->getTipo() == Website::particular)
            if ((*site_it)->getNumeroPaginas() > SiteParticular::getLimitePaginas()) {
                (*site_it)->setNumeroPaginas(SiteParticular::getLimitePaginas());
            }
    }
    
    return;
}

vector<Website*> GestorWSP::pesquisaWebsite(string tipoCriterio, string criterio){
    vector<Website*> resultados;
    transform(criterio.begin(), criterio.end(), criterio.begin(), ::tolower);
    string aux; // string auxiliar na pesquisa
    if (tipoCriterio == "identificador") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            aux = (*site_it)->getIdentificador();
            transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
            if (string::npos != aux.find(criterio))
            {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "particulares") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getTipo() == Website::particular) {
                resultados.push_back(*site_it);
            }
        }
        
    } else if (tipoCriterio == "empresas") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getTipo() == Website::empresa) {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "tecnologia") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getTipo() == Website::particular) {
                aux = (*site_it)->getTecnologia();
                transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
                if (string::npos != aux.find(criterio))
                {
                    resultados.push_back(*site_it);
                }
            }
            if ((*site_it)->getTipo() == Website::empresa) {
                for (vector<string>::const_iterator tech_it = (*site_it)->getTecnologias().begin(); tech_it != (*site_it)->getTecnologias().end(); tech_it++) {
                    aux = (*tech_it);
                    transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
                    if (string::npos != aux.find(criterio))
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
    if (tipoCriterio == "numero paginas superior a") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getNumeroPaginas() > criterio) {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "numero paginas inferior a") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getNumeroPaginas() < criterio) {
                resultados.push_back(*site_it);
            }
        }
    }
    
    return resultados;
}

vector<Website*> GestorWSP::pesquisaWebsite(string tipoCriterio, float criterio){
    vector<Website*> resultados;
    if (tipoCriterio == "custo superior a") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getCusto() > criterio) {
                resultados.push_back(*site_it);
            }
        }
    } else if (tipoCriterio == "custo inferior a") {
        for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
            if ((*site_it)->getCusto() < criterio) {
                resultados.push_back(*site_it);
            }
        }
    }
    
    return resultados;
}



vector<Utilizador*> GestorWSP::pesquisaUtilizador(string tipoCriterio, string criterio){
    vector<Utilizador*> resultados;
    transform(criterio.begin(), criterio.end(), criterio.begin(), ::tolower);
    string aux; // string auxiliar na pesquisa
    if (tipoCriterio == "nome") {
        for (vector<Utilizador*>::iterator gestor_it = gestores.begin(); gestor_it != gestores.end();gestor_it++) {
            aux = (*gestor_it)->getNome();
            transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
            if (string::npos != aux.find(criterio))
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
    transform(identificador.begin(), identificador.end(), identificador.begin(), ::tolower);
    string aux; // string auxiliar na pesquisa
    for (vector<Website*>::iterator site_it = websites.begin(); site_it != websites.end(); site_it++) {
        aux = (*site_it)->getIdentificador();
        transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
        if ( aux == identificador) {
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

Catalogo & GestorWSP::getCatalogo(){
    return this->catalogo;
}

ExClientes & GestorWSP::getExClientes(){
    return this->exclientes;
}

Tesouraria & GestorWSP::getTesouraria(){
    return this->tesouraria;
}


bool GestorWSP::novoSite(SiteEmpresa* w){
    for (vector<Website*>::iterator it = websites.begin(); it != websites.end(); it++) {
        if ( (*(*it)) == w) {
            return false;
        }
    }
    tesouraria.adicionaPedidoEmpresa(w);
    websites.push_back(w);
    return true;
}

bool GestorWSP::novoSite(SiteParticular* w){
    for (vector<Website*>::iterator it = websites.begin(); it != websites.end(); it++) {
        if ( (*(*it)) == w) {
            return false;
        }
    }
    tesouraria.adicionaPedidoParticular(w);
    websites.push_back(w);
    return true;
}

