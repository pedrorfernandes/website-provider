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
     * @param p O prototipo que contem as informacoes
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
     * @return Void
     */
    void adicionar(Prototipo* p);
    
    /**
     * Para modificar o custo de um prototipo.
     * É feita uma busca pelo prototipo, se for encontrado é removido, modificado e reinserido na BST novamente.
     * @param prototipo O tipo do prototipo a modificar (titulo)
     * @param custo O novo custo
     * @return Retorna true se o prototipo for modificado com sucesso, false caso nao exista no catalogo
     */
    bool alteraCusto(string prototipo, float custo);
    
    /**
     * Para modificar as horas de producao de um prototipo
     * É feita uma busca pelo prototipo, se for encontrado é removido, modificado e reinserido na BST novamente.
     * @param prototipo O prototipo a modificar (titulo)
     * @param horas As novas horas de producao
     * @return Retorna true se o prototipo for modificado com sucesso, false caso nao exista no catalogo
     */
    bool alteraHoras(string prototipo, unsigned int horas);
    
    /**
     * Para modificar as tecnologias de um prototipo
     * É feita uma busca pelo prototipo, se for encontrado é removido, modificado e reinserido na BST novamente.
     * @param prototipo O prototipo a modificar (titulo)
     * @param tecnologias A nova lista de tecnologias
     * @return Retorna true se o prototipo for modificado com sucesso, false caso nao exista no catalogo
     */
    bool alteraTecnologias(string prototipo, list<string> tecnologias);
    
    /**
     * Para modificar o tipo de um prototipo (alterar o titulo).
     * É feita uma busca pelo prototipo, se for encontrado é removido, modificado e reinserido na BST novamente.
     * @param prototipo O prototipo a modificar o tipo
     * @param tipo O novo tipo do prototipo (titulo)
     * @return Retorna true se o prototipo for modificado com sucesso, false caso nao exista no catalogo
     */
    bool alteraTipo(string prototipo, string tipo);
    
    /**
     * Para eliminar um prototipo da BST
     * @param prototipo O tipo de prototipo a ser eliminado (titulo)
     * @return True se o prototipo foi encontrado e eliminado com sucesso, false caso contrario
     */
    bool elimina(string prototipo);
    
    /**
     * Procura na BST o tipo de prototipo especificado e retorna o.
     * @param prototipo O tipo de prototipo a consultar
     * @return O apontador para o prototipo indicado. Retorna NULL caso nao seja encontrado
     */
    Prototipo* consulta(const string prototipo) const;
    
    /**
     * @return O numero de prototipos diferentes existentes na BST
     */
    int getNumPrototipos() const;
    
    /**
     * Funcao para escrita de informacoes de um catalogo
     * @param out Onde vao ser colocadas as informacoes do catalogo
     * @param c O catalogo que contem os prototipos
     * @return Devolve out modificado
     */
    friend ostream & operator<<(ostream &out, Catalogo &c);
    
    /**
     * Pesquisa prototipos com certo numero de horas, segundo o criterio.
     * Todos os resultados da pesquisa sao retornados sob a forma de um vector.
     * @param horas O numero de horas a pesquisar
     * @param criterio O criterio pode ser "superior" para pesquisar uma quantidade de horas superior ao argumento anterior. Tambem pode ser "inferior"
     * @return Um vector com os apontadores para os prototipos resultantes da pesquisa
     */
    vector<Prototipo*> pesquisaHoras(unsigned int horas, string criterio);
    
    /**
     * Pesquisa prototipos com certo custo, segundo o criterio.
     * Todos os resultados da pesquisa sao retornados sob a forma de um vector.
     * @param custo O custo a pesquisar
     * @param criterio O criterio pode ser "superior" para pesquisar um custo superior ao argumento anterior. Tambem pode ser "inferior"
     * @return Um vector com os apontadores para os prototipos resultantes da pesquisa
     */
    vector<Prototipo*> pesquisaCusto(float custo, string criterio);
    
    /**
     * Pesquisa todas as tecnologias utilizadas pelos prototipos. Se um prototipo utiliza uma tecnologia que contem a palavra da pesquisa, entao e' considerado um resultado.
     * Todos os resultados da pesquisa sao retornados sob a forma de um vector.
     * @param pesquisa A palavra da tecnologia a pesquisar
     * @return Um vector com os apontadores para os prototipos resultantes da pesquisa
     */
    vector<Prototipo*> pesquisaTecnologias(string pesquisa);
    
    /**
     * Funcao para imprimir um catalogo de prototipos
     */
    void imprimePrototipos() const;


};

/**
 * Uma excecao para lancar caso o utilizador queira consultar um prototipo que nao existe. Como o catalogo esta ordenado alfabeticamente, esta excecao guarda os prototipos existentes na BST anterior e posterior 'a pesquisa do utilizador
 */
class PrototipoNaoExistente: public Erro{
private:
    Prototipo* antes; /**< O prototipo anterior */
    Prototipo* depois; /**< O prototipo posterior */
public:
    /**
     * Construtor para uma excecao Prototipo Nao Existente
     * @param a Prototipo anterior
     * @param d Prototipo posterior
     */
    PrototipoNaoExistente(Prototipo* a, Prototipo* d): Erro("Prototipo nao existente"), antes(a), depois(d){}
    
    /**
     * @return O apontador para o prototipo anterior
     */
    Prototipo* getAntes() {return antes;}
    
    /**
     * @return O apontador para o prototipo posterior
     */
    Prototipo* getDepois() {return depois;}

};


#endif
