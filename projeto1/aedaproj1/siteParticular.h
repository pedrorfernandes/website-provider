//
//  siteParticular.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef siteParticular_h
#define siteParticular_h

#include <iostream>
#include <vector>
#include <sstream>

#include "website.h"
#include "utilizador.h"

#define CUSTOPARTICULAR_PREDEFINIDO 10
#define LIMITEPAGINAS_PREDEFINIDO 50

using namespace std;


class Utilizador;

/**
 * Classe para lancar excecoes quando se tenta criar ou alterar o numero de paginas de um website particular para um valor superior ao limite definido
 */
class LimiteDePaginasUltrapassado: public Erro{
public:
    /**
     * Construtor de um erro LimiteDePaginasUltrapassado
     * @param mensagem String que menciona o numero limite de paginas para websites particulares
     */
    LimiteDePaginasUltrapassado(string mensagem): Erro(mensagem){}
};

/**
 * O SiteParticular, para alem de um identificador e numero de paginas, possui um gestor, uma tecnologia e um limite no numero de paginas
 */
class SiteParticular: public Website{
    string tecnologia; /**< A tecnologia utilizada pelo website particular */
    Utilizador* gestor; /**< O apontador para o gestor do website particular */
    static float custoPorPagina; /**< O custo por pagina para todos os websites particulares */
    static unsigned int limitePaginas; /**< O limite de paginas para todos os websites particulares */
    static Website::Tipo tipo;
public:
    /**
     * Construtor de um objeto SiteParticular
     * @param i O identificador do website
     * @param n O numero de paginas
     * @param tech A tecnologia utilizada
     * @param gest O apontador para o gestor do website
     */
    SiteParticular(string i, unsigned int n, string tech, Utilizador* gest);
    ~SiteParticular();
    
    /**
     * Retorna a tecnologia utilizada pelo website particular
     * @return A string da tecnologia
     */
    string getTecnologia() const;
    
    /**
     * Modifica a tecnologia utilizada pelo website particular
     * @param t A string da nova tecnologia
     * @return Void
     */
    void setTecnologia(const string &t);
    
    /**
     * Retorna o gestor responsavel pelo website particular (caso nao exista gestor, retorna um apontador nulo)
     * @return O apontador para o gestor
     */
    Utilizador* getGestor() const;
    
    /**
     * Modifica o gestor responsavel pelo website particular
     * @param u O apontador para o novo gestor
     * @return Void
     */
    void setGestor(Utilizador* u);
    
    /**
     * Altera o custo por pagina para todos os websites particulares
     * @param custo O novo valor (float) do custo por pagina
     * @return Void
     */
    static void setCustoPorPagina(const float & custo);
    
    /**
     * Altera o limite de paginas para todos os websites particulares
     * @param limite O novo numero (int) limite de paginas
     * @return Void
     */
    static void setLimitePaginas(const unsigned int & limite);
    
    /**
     * Retorna o limite de paginas definido para todos os websites particulares
     * @return O numero limite de paginas
     */
    static unsigned int getLimitePaginas();
    
    /**
     * Retorna o custo por cada pagina para todos os websites particulares
     * @return O valor (float) do custo por pagina
     */
    static float getCustoPorPagina();
    
    /**
     * Altera o numero de paginas de um website particular (caso o numero de paginas ultrapassa o limite, e' atirada uma excepcao)
     * @param n O novo numero de paginas
     * @return Void
     */
    void setNumeroPaginas(unsigned int n);

    /**
     * Retorna o custo do website. O custo e' calculado multiplicando o numero de paginas pelo custo por pagina
     * @return O valor do custo do website particular
     */
    float getCusto() const;
    
    /**
     * @return Devolve o tipo de website (particular ou empresa)
     */
    Website::Tipo getTipo() const;
};

#endif
