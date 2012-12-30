//
//  website.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef website_h
#define website_h

#include <iostream>
//#include "main.h"
#include "utilizador.h"

using namespace std;

class Utilizador; // pre declaracao

/**
 * Classe geral para a criacao de excecoes que detetam erros internos do funcionamento do website provider
 */
class Erro{
    string msg; /**< A mensagem que contem informacoes do erro */
public:
    /**
     * Construtor de um objeto Erro.
     * @param m A mensagem que descreve o erro
     */
    Erro(string m): msg(m){}
    /**
     * Retorna a mensagem que caracteriza o erro
     * @return A mensagem de erro
     */
    string getMsg(){return msg;}
};

/**
 * O website possui um identificador (URL) e um numero de paginas
 */
class Website{
protected:
    unsigned int numeroPaginas; /**< O numero total de paginas do website */
    string identificador; /**< O identificador (URL) do website */
    bool pedidoFinalizado; /**< Estado do pedido do website (se o pedido ja foi concretizado ou nao) */
public:
    /**
     * Enumeracao dos tipos de websites
     */
    enum Tipo {
        particular, empresa
    };
    /**
     * Construtor de um objeto Website
     * @param i O identificador do website
     * @param n O numero de paginas
     */
    Website(string i, unsigned int n);
    virtual ~Website();
    
    /**
     * Retorna o numero de paginas do website
     *
     * @return O numero de paginas
     */
    unsigned int getNumeroPaginas() const;
    
    /**
     * Modifica o numero de paginas do website
     *
     * @param n O novo numero de paginas
     *
     * @return Void
     */
    virtual void setNumeroPaginas(unsigned int n);
    
    /**
     * Retorna o identificador do website
     *
     * @return A string identificadora do website
     */
    string getIdentificador() const;
    
    /**
     * Modifica o identificador do website
     *
     * @param i Referencia para a nova string identificador
     *
     * @return Void
     */
    void setIdentificador(string &i);
    
    /**
     * Retorna o custo do website
     *
     * @return O valor do custo do website
     */
    virtual float getCusto() const = 0;
    
    /**
     * Adiciona o proprio website ao vector de sites responsaveis do novo gestor
     *
     * @param gestor Apontador para o novo gestor do site
     *
     * @return Void
     */
    void atribuiGestao(Utilizador* gestor);
    
    // membros funcao para aceder aos dados da filha siteParticular
    
    /**
     * Retorna a tecnologia utilizada pelo website particular
     * @return A string da tecnologia
     */
    virtual string getTecnologia() const;
    
    /**
     * Modifica a tecnologia utilizada pelo website particular
     * @param t A string da nova tecnologia
     * @return Void
     */
    virtual void setTecnologia(const string &t);
    
    /**
     * Retorna o gestor responsavel pelo website particular (caso nao exista gestor, retorna um apontador nulo)
     * @return O apontador para o gestor
     */
    virtual Utilizador* getGestor() const;
    
    /**
     * Modifica o gestor responsavel pelo website particular
     * @param u O apontador para o novo gestor
     * @return Void
     */
    virtual void setGestor(Utilizador* u);
    
    // membros funcao para aceder aos dados da filha siteEmpresa
    
    /**
     * Retorna o vector de tecnologias do website empresa
     * @return O vector de tecnologias (strings)
     */
    virtual const vector<string> & getTecnologias() const;
    
    /**
     * Modifica o vector de tecnologias do website empresa
     * @param t O novo vector de tecnologias (strings)
     * @return Void
     */
    virtual void setTecnologias(const vector<string> &t);
    
    /**
     * Retorna o vector de utilizadores que sao gestores website empresa
     * @return O vector de gestores
     */
    virtual const vector<Utilizador *> & getGestores() const;
    
    /**
     * Retorna um vector imutavel de utilizadores que sao gestores website empresa
     * @return O vector constante de gestores
     */
    virtual void setGestores(const vector<Utilizador*> g);
    
    /**
     * Adiciona uma nova tecnologia ao vector de tecnologias do website empresa
     * @param tech A tecnologia a ser adicionada
     * @return True se a tecnologia foi adicionada com sucesso, False caso ja exista
     */
    virtual bool novaTecnologia(string &tech);
    
    /**
     * Retira a tecnologia especificada do vector de tecnologias do website empresa
     * @param tech A tecnologia a ser removida
     * @return True se a tecnologia foi removida, False caso nao exista
     */
    virtual bool retiraTecnologia(const string & tech);
    
    /**
     * Adiciona um novo utilizador ao vector de gestores responsaveis pelo website empresa
     * @param u O apontador para o novo utilizador
     * @return Void
     */
    virtual void novoGestor(Utilizador* u);
    
    /**
     * Retira um utilizador do vector de gestores responsaveis pelo website empresa
     * @param u O apontador para o utilizador a ser apagado
     * @return True se o gestor foi removido com sucesso, False caso nao exista
     */
    virtual bool retiraGestor(Utilizador* u);

    /**
     * Compara o proprio website a outro
     *
     * @param w Apontador para o website a ser comparado
     *
     * @return True se o website for igual, False caso contrario
     */
    bool operator==(Website* w) const;
    
    /**
     * Funcao para escrita de informacoes de um website
     *
     * @param out Onde vao ser colocadas as informacoes do website
     * @param w O website que contem as informacoes
     *
     * @return Devolve out modificado
     */
    friend ostream & operator<<(ostream &out, Website* w);

    /**
     * @return Devolve o tipo de website (particular ou empresa)
     */
    virtual Website::Tipo getTipo() const;
    
    /**
     * Construtor de um objeto Website. Necessario caso o pedido do website 
     * @param i O identificador do website
     * @param n O numero de paginas
     * @param pedido O estado do pedido do website
     */
    Website(string i, unsigned int n, bool pedido);
    
    /**
     * @return Retorna se true se o pedido do website foi finalizado, false caso contrario
     */
    bool getPedidoFinalizado() const;
    
    /**
     * Modifica o estado do pedido do website
     * @return Void
     */
    void setPedidoFinalizado(bool status);
};

#endif
