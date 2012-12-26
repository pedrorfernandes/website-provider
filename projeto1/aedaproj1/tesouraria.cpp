//  exClientes.cpp
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "tesouraria.h"

Tesouraria::Tesouraria(){}

void Tesouraria::adicionaPedidoEmpresa(SiteEmpresa* site){
    empresas.push(site);
}

void Tesouraria::adicionaPedidoParticular(SiteParticular* site){
    particulares.push(site);
}

bool Tesouraria::retiraPedido(Website* site){
    if (site->getTipo() == Website::empresa) {
        HEAP_EMPRESAS tmp;
        bool found = false;
        while ( !empresas.empty() ) {
            if ((*empresas.top() ) == site) {
                found = true;
            } else
                tmp.push(empresas.top() );
            empresas.pop();
        }
        empresas = tmp;
        return found;
    } else if (site->getTipo() == Website::particular){
        queue<SiteParticular*> tmp;
        bool found = false;
        while ( !particulares.empty() ) {
            if ((*particulares.front()) == site) {
                found = true;
            } else
                tmp.push(particulares.front() );
            particulares.pop();
        }
        particulares = tmp;
        return found;
    }
    return false;
}

void Tesouraria::atualizaPrioridades(){
    HEAP_EMPRESAS tmp;
    while ( !empresas.empty() ) {
        tmp.push(empresas.top() );
        empresas.pop();
    }
    empresas = tmp;
}

unsigned int Tesouraria::getNumPedidos() const{
    return (int)(particulares.size() + empresas.size() );
}

vector<Website*> Tesouraria::getPedidosEmpresas() const{
    HEAP_EMPRESAS tmp = empresas;
    vector<Website*> pedidosEmpresas;
    while ( !tmp.empty() ) {
        pedidosEmpresas.push_back(tmp.top() );
        tmp.pop();
    }
    return pedidosEmpresas;
}
vector<Website*> Tesouraria::getPedidosParticulares() const{
    queue<SiteParticular*> tmp = particulares;
    vector<Website*> pedidosParticulares;
    while ( !tmp.empty() ) {
        pedidosParticulares.push_back(tmp.front() );
        tmp.pop();
    }
    return pedidosParticulares;
}

void Tesouraria::imprimeEmpresas(){
    HEAP_EMPRESAS tmp = empresas;
    while (!tmp.empty() ) {
        cout << tmp.top() << endl;
        tmp.pop();
    }
}

void Tesouraria::imprimeParticulares(){
    queue<SiteParticular*> tmp = particulares;
    while (!tmp.empty() ) {
        cout << tmp.front() << endl;
        tmp.pop();
    }
}
