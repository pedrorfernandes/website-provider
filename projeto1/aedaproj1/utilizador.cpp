//
//  utilizador.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "utilizador.h"

Utilizador::Utilizador(unsigned int i, string n): numIdentidade(i), nome(n){}

Utilizador::~Utilizador(){
    // para cada site responsavel, o utilizador sera eliminado da lista de gestores desse site
     for (vector<Website*>::iterator site = sitesResponsavel.begin(); site != sitesResponsavel.end(); site++) {
         if ((*site)->getTipo() == Website::empresa){
             (*site)->retiraGestor(this);
         }
     }
}

bool Utilizador::UtilizadorEliminavel(){
    for (vector<Website*>::iterator site = sitesResponsavel.begin(); site != sitesResponsavel.end(); site++) {
        if ((*site)->getTipo() == Website::empresa){
            if ((*site)->getGestores().size() == 1) {
                return false;
            }
        }
        if ((*site)->getTipo() == Website::particular){
            return false;
        }
    }
    return true;
}

unsigned int Utilizador::getNumIdentidade() const{
    return numIdentidade;
}
void Utilizador::setNumIdentidade(unsigned int &n){
    numIdentidade = n;
    return;
}
string Utilizador::getNome() const{
    /*
     if (this == NULL) {
        return "Nenhum";    // o menu deve tratar de output correto
    } else
     */
        return nome;
}
void Utilizador::setNome(string &n){
    nome = n;
}

const vector<Website*> & Utilizador::getSitesResponsavel() const{
    return sitesResponsavel;
}

void Utilizador::adicionaSite(Website* site){
    sitesResponsavel.push_back(site);
}

bool Utilizador::operator==(Utilizador u) const{
    return (numIdentidade == u.numIdentidade);
}

bool Utilizador::operator==(Utilizador* u) const{
    return (numIdentidade == u->numIdentidade);
}

vector<Utilizador*> operator-(const vector<Utilizador*> vec1, const vector<Utilizador*> vec2){
    // o vector vec1 menos o vector vec2 da um vector v3 com os elementos de vec1 que nao existem em vec2
    vector<Utilizador*> vec3;
    for (vector<Utilizador*>::const_iterator vec1_it = vec1.begin(); vec1_it != vec1.end(); vec1_it++) {
        bool encontrado = false;
        Utilizador* utilizador = (*vec1_it);
        for (vector<Utilizador*>::const_iterator vec2_it = vec2.begin(); vec2_it != vec2.end(); vec2_it++) {
            if (utilizador == (*vec2_it)) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            vec3.push_back(utilizador);
        }
    }
    return vec3;
}

bool Utilizador::retiraWebsiteResponsavel(Website* w){
    for (vector<Website*>::iterator site_it = sitesResponsavel.begin(); site_it != sitesResponsavel.end() ; site_it++) {
        if ( (*(*site_it)) == w ){
            site_it = sitesResponsavel.erase(site_it);
            return true;
        }
    }
    return false;
}



