//
//  utilizador.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef utilizador_h
#define utilizador_h

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define ESPACO 10

#include "website.h"
//#include "siteParticular.h"
//#include "siteEmpresa.h"


class Website;

using namespace std;

/**
 * Um utilizador possui um nome, um numero de bilhete de identidade e um vector dos websites que e' responsavel
 */
class Utilizador{
    unsigned int numIdentidade; /**< O numero de bilhete de identidade do utilizador (nao pode haver utilizadores com o mesmo numero) */
    string nome; /**< O nome do utilizador (pode haver utilizadores com o mesmo nome) */
    vector<Website*> sitesResponsavel; /**< O vector que contem apontadores para os sites que o utilizador assume gestao */
public:
    /**
     * Construtor de um objeto Utilizador
     * @param i O numero de bilhete de identidade
     * @param n O nome do utilizador
     */
    Utilizador(unsigned int i, string n);
    
    /**
     * Destrutor de um utilizador. De notar que um website (empresa ou particular) contem o apontador para os seu(s) gestor(es). Logo o destrutor de um utilizador tem de percorrer os seus websites responsaveis e eliminar o seu apontador desses websites
     */
    ~Utilizador();
    
    friend class SiteEmpresa;
    friend class SiteParticular;
    
    /**
     * Retorna o numero do bilhete de identidade do utilizador
     * @return O numero do B.I.
     */
    unsigned int getNumIdentidade() const;
    
    /**
     * Modifica o numero do bilhete de identidade do utilizador
     * @param n O novo numero do B.I.
     * @return Void
     */
    void setNumIdentidade(unsigned int &n);
    
    /**
     * Retorna o nome do utilizador
     * @return A string do nome
     */
    string getNome() const;
    
    /**
     * Modifica o nome do utilizador
     * @param n A string do novo nome
     * @return Void
     */
    void setNome(string &n);
    
    /**
     * Retorna o vector de websites responsaveis dos quais o utilizador e' gestor
     * @return O vector de apontadores para websites
     */
    const vector<Website*> & getSitesResponsavel() const;
    
    /**
     * Adiciona um novo website ao vector de websites que o utilizador e' responsavel
     * @param site O apontador para o website que o utilizador assume gestao
     * @return Void
     */
    void adicionaSite(Website *site);
    
    /**
     * Compara o utilizador a outro utilizador (dois utilizadores sao iguais se possuem o mesmo numero de bilhete de identidade)
     * @param u O utilizador a ser comparado
     * @return True se os utilizadores sao iguais, False caso contrario
     */
    bool operator==(Utilizador u) const;
    
    /**
     * Compara o utilizador a outro utilizador (dois utilizadores sao iguais se possuem o mesmo numero de bilhete de identidade)
     * @param u O apontador para o utilizador a ser comparado
     * @return True se os utilizadores sao iguais, False caso contrario
     */
    bool operator==(Utilizador* u) const;
    
    /**
     * Verifica se o utilizador e' eliminavel. Ou seja, se ha websites cujo unico gestor e' o utilizador em causa.
     * @return True se for eliminavel, false caso contrario
     */
    bool UtilizadorEliminavel();
    
    /**
     * Funcao para escrita de informacoes de um utilizador
     * @param out Onde vao ser colocadas as informacoes do utilizador
     * @param u O utilizador que contem as informacoes
     * @return Devolve out modificado
     */
    friend std::ostream & operator<<(std::ostream &out, Utilizador* u);
    
    /**
     * Calcula a diferenca entre um vector de utilizadores vec1 e outro vector vec2. O resultado e' um novo vector, vec3, que possui os membros de vec1 nao existentes em vec2
     * @return O vector vec3
     */
    friend vector<Utilizador*> operator-(const vector<Utilizador*> vec1, const vector<Utilizador*> vec2);

};

#endif 