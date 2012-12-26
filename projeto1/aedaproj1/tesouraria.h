//  exClientes.h
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef tesouraria_h
#define tesouraria_h

#include <queue>

#include "website.h"
#include "siteEmpresa.h"
#include "siteParticular.h"

using namespace std;

struct ComparaEmpresas : public std::binary_function<SiteEmpresa*, SiteEmpresa*, bool>
{
    bool operator()(const SiteEmpresa* e1, const SiteEmpresa* e2) const
    {
        return e1->getCusto() < e2->getCusto();
    }
};

typedef priority_queue<SiteEmpresa*, vector<SiteEmpresa*>, ComparaEmpresas> HEAP_EMPRESAS;


class Tesouraria{
    queue<SiteParticular*> particulares;
    HEAP_EMPRESAS empresas;
public:
    Tesouraria();
    void adicionaPedidoEmpresa(SiteEmpresa* site);
    void adicionaPedidoParticular(SiteParticular* site);
    bool retiraPedido(Website* site);
    void atualizaPrioridades();
    
    
    void imprimeEmpresas();
    void imprimeParticulares();
};

#endif
