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

#include "website.h"
#include "utilizador.h"
#include "siteEmpresa.h"
#include "siteParticular.h"

/**
 * O gestor de website provider contem o vector de utilizadores e de websites e as funcoes para gerir estes dois vectores.
 */
class GestorWSP{
    vector<Website*> websites;
    vector<Utilizador*> gestores;
    
    /**
     * Compara dois identificadores de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o identificador do primeiro site for menor do que o segundo, False caso contrario
     */
    static bool Alfabetico(Website* w1, Website* w2);
    /**
     * Compara dois identificadores de websites
     *
     * @param w1 O apontador para o primeiro website
     * @param w2 O apontador para o segundo website
     *
     * @return True se o identificador do primeiro site for maior do que o segundo, False caso contrario
     */
    static bool AlfabeticoContrario(Website* w1, Website* w2);


public:
    GestorWSP();
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
    vector<Website*> & getWebsites();
    
    /**
     * Retorna a referencia do vector de utilizadores
     *
     * @return Referencia do vector de apontadores para utilizadores
     */
    vector<Utilizador*> & getGestores();
    
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
     * Ordena o vector de websites alfabeticamente, segundo os identificadores
     *
     * @return Void
     */
    void ordenaWebsitesAlfabetico();
    /**
     * Ordena o vector de websites por ordem alfabetica decrescente, segundo os identificadores
     *
     * @return Void
     */
    void ordenaWebsitesAlfabeticoContrario();
    
    const vector<Utilizador *> getConstGestores();

    
};

#endif
