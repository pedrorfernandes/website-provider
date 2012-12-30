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

/**
 * Estrutura necessaria para comparar apontadores para websites empresa
 */
struct ComparaEmpresas : public std::binary_function<SiteEmpresa*, SiteEmpresa*, bool>
{
    /**
     * Funcao de comparacao de dois apontadores para site empresa, para determinar qual e' o pedido mais prioritario
     * Um site empresa e' maior que outro se o seu custo for superior.
     * @param e1 O apontador para o primeiro site empresa
     * @param e2 O apontador para o segundo site empresa
     * @return True se e1 for menor que e2, False caso contrario
     */
    bool operator()(const SiteEmpresa* e1, const SiteEmpresa* e2) const
    {
        return e1->getCusto() < e2->getCusto();
    }
};

typedef priority_queue<SiteEmpresa*, vector<SiteEmpresa*>, ComparaEmpresas> HEAP_EMPRESAS;

/**
 * A classe tesouraria contem uma queue com apontadores para websites particulares, ordenados pela ordem do pedido efetuado, uma priority queue para os websites empresa, cuja ordem de pedido esta determinada pelo custo e ainda um vector com os websites cujo pedido ja foi satisfeito (ou cancelado)
 */
class Tesouraria{
    queue<SiteParticular*> particulares; /**< A fila com os pedidos de websites particulares */
    HEAP_EMPRESAS empresas; /**< A fila de prioridade com os pedidos de websites empresa */
    vector<Website*> pedidosRetirados; /**< Um vector com os websites cujos pedidos ja foram removidos das filas */
public:
    /**
     * Construtor da classe tesouraria
     */
    Tesouraria();
    
    /**
     * Adiciona um pedido de um website empresa 'a fila de prioridade
     * @param site O website empresa cujo pedido foi requisitado
     * @return Void
     */
    void adicionaPedidoEmpresa(SiteEmpresa* site);
    
    /**
     * Adiciona um pedido de um website particular 'a fila dos pedidos particulares
     * @param site O website particular cujo pedido foi requisitado
     * @return Void
     */
    void adicionaPedidoParticular(SiteParticular* site);
    
    /**
     * Retira um pedido de website das filas e adiciona o ao vector dos pedidos retirados.
     * @param site O site cujo pedido deve ser removido (particular ou empresa)
     * @return True se o pedido do site foi encontrado e removido, False caso contrario.
     */
    bool retiraPedido(Website* site);
    
    /**
     * Atualiza as prioridades na fila dos pedidos de websites empresa.
     * Os websites de pedido mais prioritario sao os de maior custo
     * @return Void
     */
    void atualizaPrioridades();
    
    /**
     * @return O numero total de pedidos nas filas
     */
    unsigned int getNumPedidos() const;
    
    /**
     * @return Um vector com os pedidos das empresas
     */
    vector<Website*> getPedidosEmpresas() const;
    
    /**
     * @return Um vector com os pedidos dos particulares
     */
    vector<Website*> getPedidosParticulares() const;
    
    /**
     * @return Um vector com os pedidos ja retirados das filas
     */
    const vector<Website*> & getPedidosRetirados() const;
    
    /**
     * Para adicionar um pedido caso este ja tenha sido removido das filas
     * @param site O site cujo pedido foi novamente requisitado
     * @return Void
     */
    void adicionaPedidoRetirado(Website* site);
    
    /**
     * Funcao para imprimir os conteudos da fila de sites empresa
     * @return Void
     */
    void imprimeEmpresas();
    
    /**
     * Funcao para imprimir os conteudos da fila de sites particulares
     */
    void imprimeParticulares();
};

#endif
