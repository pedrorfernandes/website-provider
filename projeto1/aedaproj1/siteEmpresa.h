//
//  siteEmpresa.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef siteEmpresa_h
#define siteEmpresa_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "website.h"
#include "utilizador.h"

#define CUSTOEMPRESA_PREDEFINIDO 100

using namespace std;

/**
 * O SiteEmpresa, para alem de um identificador e numero de paginas, possui um vector com as tecnologias que usa, um vector com os gestores do site e um custo por pagina para sites empresa
 */
class SiteEmpresa : public Website{
    vector<string> tecnologias; /**< O vector que contem as tecnologias usadas pelo website empresa */
    vector<Utilizador* > gestores; /**< O vector que contem os apontadores para os gestores do website empresa */
    static float custoPorPagina; /**< O custo por pagina para todos os websites empresa */
    static Website::Tipo tipo;
public:
    /**
     * Construtor de um SiteEmpresa
     * @param i O identificador do website
     * @param n O numero de paginas
     * @param tech O vector com as tecnologias utilizadas
     * @param gest O vector com os apontadores para os gestores do website
     */
    SiteEmpresa(string i, unsigned int n, vector<string> tech, vector<Utilizador*> gest);
    
    /**
     * Destrutor de um SiteEmpresa. De notar que um utilizador tem apontadores para os websites de que e' gestor. Logo este destrutor tem de percorrer os seus gestores e eliminar o seu apontador
     */
    ~SiteEmpresa();
    
    /**
     * Retorna o vector de tecnologias do website empresa
     * @return O vector de tecnologias (strings)
     */
    const vector<string> getTecnologias() const;
    
    /**
     * Modifica o vector de tecnologias do website empresa
     * @param t O novo vector de tecnologias (strings)
     * @return Void
     */
    void setTecnologias(const vector<string> &t);
    
    /**
     * Retorna o vector de utilizadores que sao gestores website empresa
     * @return O vector de gestores
     */
    const vector<Utilizador *> & getGestores() const;
    
    /**
     * Modifica o vector de gestores do website empresa
     * @param g O novo vector de gestores (utilizadores)
     * @return Void
     */
    void setGestores(const vector<Utilizador*> &g);
    
    /**
     * Modifica o custo por pagina de todos os website empresa
     * @param custo O novo valor do custo
     * @return Void
     */
    static void setCustoPorPagina(const float &custo);
    
    /**
     * Retorna um o custo por pagina de todos os websites empresa
     * @return O valor de custo por pagina
     */
    static float getCustoPorPagina();
    
    /**
     * Retorna o custo do website empresa. O custo e' calculado atraves da multiplicacao do numero de paginas do website com o custo por paginas
     * @return O valor do custo total do website empresa
     */
    float getCusto() const;
    
    /**
     * Adiciona uma nova tecnologia ao vector de tecnologias do website empresa
     * @param tech A tecnologia a ser adicionada
     * @return True se a tecnologia foi adicionada com sucesso, False caso ja exista
     */
    bool novaTecnologia(string &tech);
    
    /**
     * Retira a tecnologia especificada do vector de tecnologias do website empresa
     * @param tech A tecnologia a ser removida
     * @return True se a tecnologia foi removida, False caso nao exista
     */
    bool retiraTecnologia(const string &tech);
    
    /**
     * Adiciona um novo utilizador ao vector de gestores responsaveis pelo website empresa
     * @param u O apontador para o novo utilizador
     * @return Void
     */
    void novoGestor(Utilizador* u);
    
    /**
     * Retira um utilizador do vector de gestores responsaveis pelo website empresa
     * @param u O apontador para o utilizador a ser apagado
     * @return True se o gestor foi removido com sucesso, False caso nao exista
     */
    bool retiraGestor(Utilizador* u);
    
    Website::Tipo getTipo() const;

};

#endif
