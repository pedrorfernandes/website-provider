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
    if (site->getPedidoFinalizado() == false) {
        // o pedido nao foi finalizado, deve estar na fila
        empresas.push(site);
    } else
        pedidosRetirados.push_back(site);
}

void Tesouraria::adicionaPedidoParticular(SiteParticular* site){
    if (site->getPedidoFinalizado() == false) {
        particulares.push(site);
    } else
        pedidosRetirados.push_back(site);
}

bool Tesouraria::retiraPedido(Website* site){
    if (site->getTipo() == Website::empresa) {
        HEAP_EMPRESAS tmp;
        bool found = false;
        while ( !empresas.empty() ) {
            if ((*empresas.top() ) == site) {
                site->setPedidoFinalizado(true);
                pedidosRetirados.push_back(site);
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
                site->setPedidoFinalizado(true);
                pedidosRetirados.push_back(site);
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

const vector<Website*> & Tesouraria::getPedidosRetirados() const{
    return pedidosRetirados;
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

void Tesouraria::adicionaPedidoRetirado(Website* site){
    site->setPedidoFinalizado(false);
    if (site->getTipo() == Website::empresa) {
        SiteEmpresa * empresa = static_cast<SiteEmpresa*>(site);
        this->adicionaPedidoEmpresa(empresa);
    } else if (site->getTipo() == Website::particular){
        SiteParticular * particular = static_cast<SiteParticular*>(site);
        this->adicionaPedidoParticular(particular);
    }
    vector<Website*>::iterator it;
    for (it = pedidosRetirados.begin(); it != pedidosRetirados.end(); it++) {
        if ((*(*it)) == site ) {
            it = pedidosRetirados.erase(it);
            break;
        }
    }
    return;
}
