//
//  gestorWSP.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef gestorWSP_h
#define gestorWSP_h


#include <iostream>
#include <sstream>
#include <algorithm>

#include "website.h"
#include "utilizador.h"
#include "siteEmpresa.h"
#include "siteParticular.h"

#include "catalogo.h"
#include "exClientes.h"
#include "tesouraria.h"

/**
 * Uma classe de erro para identificar utilizadores que ja existem no gestorWSP
 */
class UtilizadorJaExistente: public Erro{
public:
    /**
     * Cria uma excecao de um utilizador ja existente
     * @param msg A messagem que deve identificar o bilhete de identidade do utilizador ja existente
     */
    UtilizadorJaExistente(string msg): Erro(msg){};
};

/**
 * O gestor de website provider contem o vector de utilizadores e de websites e as funcoes para gerir estes dois vectores.
 */
class GestorWSP{
    vector<Website*> websites; /**< O vector de apontadores para todos os websites */
    vector<Utilizador*> gestores; /**< O vector de apontadores para todos os gestores */
    
    Catalogo catalogo;
    ExClientes exclientes;
    Tesouraria tesouraria;
    
    /**
     * Compara dois identificadores de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o identificador do primeiro site for menor do que o segundo, False caso contrario
     */
    static bool identificadorAlfabetico(Website* w1, Website* w2);
    /**
     * Compara dois identificadores de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o identificador do primeiro site for maior do que o segundo, False caso contrario
     */
    static bool identificadorAlfabeticoInverso(Website* w1, Website* w2);
    
    /**
     * Compara dois numeros de paginas de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o numero de paginas do primeiro website for menor do que o segundo, False caso contrario
     */
    static bool numeroPaginasAscendente(Website* w1, Website* w2);
    
    /**
     * Compara dois numeros de paginas de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o numero de paginas do primeiro website for maior do que o segundo, False caso contrario
     */
    static bool numeroPaginasDescendente(Website* w1, Website* w2);
    /**
     * Compara dois custos de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o custo do primeiro website for menor do que o segundo, False caso contrario
     */
    static bool custoAscendente(Website* w1, Website* w2);
    /**
     * Compara dois custos de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o custo do primeiro website for maior do que o segundo, False caso contrario
     */
    static bool custoDescendente(Website* w1, Website* w2);
    
    /**
     * Compara dois nomes de utilizadores
     *
     * @param u1 O apontador para o primeiro utilizador
     * @param u2 O apontador para o segundo utilizador
     *
     * @return True se o nome do primeiro utilizador for menor do que o segundo, False caso contrario
     */
    static bool nomeAlfabetico(Utilizador* u1, Utilizador* u2);
    
    /**
     * Compara dois nomes de utilizadores
     *
     * @param u1 O apontador para o primeiro utilizador
     * @param u2 O apontador para o segundo utilizador
     *
     * @return True se o nome do primeiro utilizador for maior do que o segundo, False caso contrario
     */
    static bool nomeAlfabeticoInverso(Utilizador* u1, Utilizador* u2);
    
    /**
     * Compara dois numeros de identidade de utilizadores
     *
     * @param u1 O apontador para o primeiro utilizador
     * @param u2 O apontador para o segundo utilizador
     *
     * @return True se o numero do primeiro utilizador for menor do que o segundo, False caso contrario
     */
    static bool numeroAscendente(Utilizador* u1, Utilizador* u2);
    
    /**
     * Compara dois numeros de identidade de utilizadores
     *
     * @param u1 O apontador para o primeiro utilizador
     * @param u2 O apontador para o segundo utilizador
     *
     * @return True se o numero do primeiro utilizador for maior do que o segundo, False caso contrario
     */
    static bool numeroDescendente(Utilizador* u1, Utilizador* u2);

public:
    /**
     * Construtor de um wsp
     */
    GestorWSP();
    /**
     * Destrutor do wsp. Elimina todos os websites e utilizadores da memoria.
     */
    ~GestorWSP();
    /**
     * Adiciona um novo website ao vector de websites 
     *
     * @param w Apontador para o website que vai ser adicionado
     *
     * @return True se o website foi adicionado, False se ja existir no vector de websites
     */
    bool novoSite(Website* w);
    
    /**
     * Adiciona um novo utilizador ao vector de utilizadores 
     *
     * @param u Apontador para o utilizador que vai ser adicionado
     *
     * @return True se o utilizador foi adicionado, False se o utilizador ja existir no vector de gestores
     */
    bool adicionaGestor(Utilizador* u);
    
    /**
     * Retorna a referencia do vector de websites
     *
     * @return Referencia do vector de apontadores para websites
     */
    const vector<Website*> & getWebsites() const;
    
    /**
     * Retorna a referencia do vector de utilizadores
     *
     * @return Referencia do vector de apontadores para utilizadores
     */
    const vector<Utilizador*> & getGestores() const;
    
    /**
     * Elimina um website do vector de websites
     *
     * @param w Apontador para o website a ser eliminado
     *
     * @return True se o website for eliminado, False se o website nao existir
     */
    bool eliminaSite(Website* w);
    
    /**
     * Elimina um cliente do vector de utilizadores 
     *
     * @param u O utilizador a ser eliminado
     *
     * @return True se o cliente for eliminado, False se o cliente nao existe
     */
    bool eliminaCliente(Utilizador* u);
    
    /**
     * Encontra o gestor no vector de utilizadores e retorna o apontador para esse gestor
     * @param u copia do utilizador a encontrar
     *
     * @return Apontador para o gestor
     */
    // funcao auxiliar para escrita ficheiro
    Utilizador* getGestorPointer(Utilizador u);
    
    /**
     * Ordena o vector de websites segundo varios criterios
     * @param criterio O criterio para ordenar o vector. Ex: "Alfabetico"
     *
     * @return Void
     */
    void ordenaWebsites(string criterio);
    
    /**
     * Ordena o vector de utilizadores segundo varios criterios
     * @param criterio O criterio para ordenar o vector. Ex: "nome ascendente"
     *
     * @return Void
     */
    void ordenaUtilizadores(string criterio);
    
    /**
     * Lista so os websites que estao incluidos dentro do criterio indicado
     * @param tipoCriterio O tipo de criterio a ser pesquisado. Ex: "identificador", "tecnologia"
     * @param criterio A string a pesquisar
     *
     * @return O vector dos websites encontrados
     */
    vector<Website*> pesquisaWebsite(string tipoCriterio, string criterio);
    
    /**
     * Lista so os websites que estao incluidos dentro do criterio indicado
     * @param tipoCriterio O tipo de criterio a ser pesquisado. Ex: "paginas inferiores a"
     * @param criterio O numero a pesquisar
     *
     * @return O vector dos websites encontrados
     */
    vector<Website*> pesquisaWebsite(string tipoCriterio, unsigned int criterio);
    /**
     * Lista so os websites que estao incluidos dentro do criterio indicado
     * @param tipoCriterio O tipo de criterio a ser pesquisado. Ex: "custo superior a"
     * @param criterio O numero a pesquisar
     *
     * @return O vector dos websites encontrados
     */
    vector<Website*> pesquisaWebsite(string tipoCriterio, float criterio);

    
    /**
     * Lista so os gestores que estao incluidos dentro do criterio indicado
     * @param tipoCriterio O tipo de criterio a ser pesquisado. Ex: "nome"
     * @param criterio A string a pesquisar
     *
     * @return O vector dos gestores encontrados
     */
    
    vector<Utilizador*> pesquisaUtilizador(string tipoCriterio, string criterio);
    
    /**
     * Lista so os gestores que estao incluidos dentro do criterio indicado
     * @param tipoCriterio O tipo de criterio a ser pesquisado. Ex: "numero"
     * @param criterio O numero a pesquisar
     *
     * @return O vector dos gestores encontrados
     */
    vector<Utilizador*> pesquisaUtilizador(string tipoCriterio, unsigned int criterio);
    
    /**
     * Calcula custo total para todos os websites no vector
     * @return O valor do custo total
     */
    float calculoCustoTotal();
    
    /**
     * Ao definir um novo limite no numero de paginas para sites particulares, esta funcao ajusta o numero de paginas dos sites que ultrapassam o novo limite
     * @return Void
     */
    void ajustarNumeroPaginasParaParticulares();
    
    /**
     * Verifica se um identificador de website existe no vector de websites
     * @param identificador O identificador a ser verificado
     * @return True se o identificador nao existir, False se ja existir um website ja possui esse identificador
     */
    bool identificadorValido(string identificador);
    
    /**
     * Verifica se um numero de bilhete de identidade ja pertence a um utilizador no vector de utilizadores
     * @param numero O numero de B.I. a ser verificado
     * @return True se o numero nao pertencer a ninguem, False caso contrario
     */
    bool numeroIdentidadeValido(unsigned int numero);
    
    Catalogo & getCatalogo();
    
    ExClientes & getExClientes();
    
    bool novoSite(SiteEmpresa* w);
        
    bool novoSite(SiteParticular* w);
    
    Tesouraria & getTesouraria();

    
};

#endif
