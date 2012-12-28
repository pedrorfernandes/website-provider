//  catalogo.h
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef catalogo_h
#define catalogo_h

#include "BST.h"
#include "website.h"
#include <list>
#include <algorithm>

/**
 * Um prototipo de website contem um tipo (o titulo do prototipo), custo e horas de producao e uma lista de tecnologias que implementa
 */
class Prototipo {
private:
    string tipo; /**< O titulo do prototipo */
    float custo; /**< O custo (float) */
    unsigned int horas; /**< As horas de producao (unsigned int) */
    list<string> tecnologias; /**< A lista de tecnologias (strings) */
public:
    /**
     * Construtor de um prototipo
     */
    Prototipo();
    
    /**
     * Construtor de um wsp
     * @param t O tipo de prototipo
     * @param c O custo do prototipo
     * @param h As horas de producao do prototipo
     * @param tech A lista de tecnologias do prototipo
     */
    Prototipo(string t, float c, unsigned int h, list<string> tech);
    
    /**
     * Construtor de um wsp
     * @param t O tipo de prototipo
     * @param c O custo do prototipo
     * @param h As horas de producao do prototipo
     */
    Prototipo(string t, float c, unsigned int h);
    
    /**
     * @return O tipo de prototipo (titulo)
     */
    string getTipo() const;
    
    /**
     * Modifica o tipo de prototipo
     * @param t O novo tipo
     * @return Void
     */
    void setTipo(const string &t);
    
    /**
     * @return O custo do prototipo
     */
    float getCusto() const;
    
    /**
     * Modifica o custo do prototipo
     * @param c O novo custo
     * @return Void
     */
    void setCusto(const float &c);
    
    /**
     * @return O numero de horas de producao
     */
    unsigned int getHoras() const;
    
    /**
     * Modifica as horas de producao
     * @param h As novas horas
     * @return Void
     */
    void setHoras(const unsigned int &h);
    
    /**
     * @return As lista das tecnologias
     */
    list<string> getTecnologias() const;
    
    /**
     * Modifica a lista de tecnologias
     * @param tech A nova lista de tecnologias
     * @return Void
     */
    void setTecnologias(const list<string> & tech);
    
    /**
     * Verifica se um prototipo e' menor do que outro segundo a ordem alfabetica dos tipos (titulos)
     * @param p1 O apontador para o prototipo a comparar
     * @return True se o prototipo for inferior a p1, False caso contrario
     */
    bool operator < (const Prototipo * p1) const;
    
    /**
     * Verifica se um prototipo e' menor do que outro segundo a ordem alfabetica dos tipos (titulos)
     * @param p1 A referencia para o prototipo a comparar
     * @return True se o prototipo for inferior a p1, False caso contrario
     */
    bool operator < (const Prototipo & p1) const;
    
    /**
     * Verifica se um prototipo e' igual a outro, ou seja, se sao do mesmo tipo (mesmo titulo)
     * @param p1 O apontador para o prototipo a comparar
     * @return True se o prototipo for igual a p1, False caso contrario
     */
    bool operator ==(const Prototipo * p1) const;
    
    /**
     * Verifica se um prototipo e' igual a outro, ou seja, se sao do mesmo tipo (mesmo titulo)
     * @param p1 A referencia para o prototipo a comparar
     * @return True se o prototipo for igual a p1, False caso contrario
     */
    bool operator ==(const Prototipo & p1) const;
    
    /**
     * Funcao para escrita de informacoes de um prototipo
     * @param out Onde vao ser colocadas as informacoes do prototipo
     * @param u O prototipo que contem as informacoes
     * @return Devolve out modificado
     */
    friend ostream & operator<<(ostream &out, Prototipo &p);
    
};

/**
 * Um catalago contem uma BST de prototipos de website e o conjunto de funcoes necessarias para realizar todas as operacoes na BST
 */
class Catalogo {
private:
    BST<Prototipo*> prototipos; /**< A BST com apontadores para os prototipos de websites */
    int numPrototipos; /**< O numero de prototipos dentro da BST */
public:
    /**
     * Construtor de um catalogo
     */
    Catalogo();
    
    /**
     * Destrutor de um catalogo. Nota: o destrutor percorre toda a BST e elimina os apontadores para todos os prototipos e depois esvazia a BST.
     */
    ~Catalogo();
    
    /**
     * @return A referencia para a BST com os apontadores para os prototipos
     */
    BST<Prototipo*> & getPrototipos();
    
    /**
     * Funcao para adicionar um prototipo 'a BST. Se o prototipo ja existe na BST, nada acontece.
     * @param p O prototipo a ser adicionado
     */
    void adicionar(Prototipo* p);
    
    /**
     *
     */
    bool alteraCusto(string prototipo, float custo);
    bool alteraHoras(string prototipo, unsigned int horas);
    bool alteraTecnologias(string prototipo, list<string> tecnologias);
    bool alteraTipo(string prototipo, string tipo);
    bool elimina(string prototipo);
    Prototipo* consulta(const string prototipo) const;
    int getNumPrototipos() const;
    friend ostream & operator<<(ostream &out, Catalogo &c);
    void imprimePrototipos() const;
    vector<Prototipo*> pesquisaHoras(unsigned int horas, string criterio);
    vector<Prototipo*> pesquisaCusto(float custo, string criterio);
    vector<Prototipo*> pesquisaTecnologias(string pesquisa);

};

class PrototipoNaoExistente{
private:
    Prototipo* antes;
    Prototipo* depois;
public:
    PrototipoNaoExistente(Prototipo* a, Prototipo* d): antes(a), depois(d){}
    Prototipo* getAntes() {return antes;}
    Prototipo* getDepois() {return depois;}

};


#endif
