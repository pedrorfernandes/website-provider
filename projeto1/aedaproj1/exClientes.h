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

#ifndef exCLiente_h
#define exCliente_h


#include <tr1/unordered_set>
#include <algorithm>

#include "utilizador.h"

using namespace std;

/**
 * Estrutura que contem as funcoes de igualdade e de hash para inserir exclientes na tabela de dispersao
 */
struct clientesHash
{
    /**
     * Funcao de igualdade entre dois utilizadores.
     * Dois utilizadores sao diferentes caso o nome deles seja diferente.
     * Se o nome for igual, e' comparado o numero de identidade de ambos.
     * @param u1 O primeiro utilizador a ser comparado
     * @param u2 O segundo utilizador a ser comparado
     * @return True se os utilizadores forem iguais, false caso sejam diferentes
     */
	bool operator() (const Utilizador *u1, const Utilizador *u2)  const
    {
        if (u1->getNome() == u2->getNome() ){
            return u1->getNumIdentidade() == u2->getNumIdentidade();
        } else
            return false;
    }
    
    /**
     * Funcao de hash para os exclientes. E' utilizado o nome do excliente para determinar a sua posicao na tabela de dispersao.
     * Para melhorar a eficacia, esta funcao utiliza o algoritmo djb2
     * http://www.cse.yorku.ca/~oz/hash.html
     */
	int operator() (const Utilizador *u1) const {
        string nome = u1->getNome();
        string::iterator it = nome.begin();
        unsigned int hash = 5381;
        
        while (it != nome.end()){
            hash = ((hash << 5) + hash) + (*it); /* hash * 33 + c */
            it++;
        }
        return hash;
	}
    
};

typedef tr1::unordered_set<Utilizador*, clientesHash, clientesHash> HashClientes;

/**
 * A classe excliente contem a tabela de dispersao e todas a funcoes para manusear os conteudos da tabela
 */
class ExClientes
{
    HashClientes exclientes; /**< A tabela de dispersao */
public:
    /**
     * Construtor da classe excliente
     */
    ExClientes();
    
    /**
     * Destrutor da classe excliente. Este destrutor percorre toda a tabela de dispersao e elimina os apontadores de todos os objetos excliente.
     */
    ~ExClientes();
    
    /**
     * @return Retorna a referencia para a tabela de dispersao de exclientes
     */
	const HashClientes & getHashClientes();
    
    /**
     * Insere um excliente na tabela de dispersao. Caso o excliente ja exista na tabela, nada acontece.
     * @param u1 O apontador para o excliente a ser inserido
     * @return Void
     */
	void insereExcliente(Utilizador *u1);
    
    /**
     * Cria um excliente e insere-o na tabela de dispersao.
     * @param numIdentidade O numero de identidade do novo excliente
     * @param nome O nome do novo excliente
     * @return Void
     */
    void insereExcliente(const unsigned int numIdentidade, const string nome);
    
    /**
     * Remove um excliente da tabela de dispersao.
     * @param numIdentidade O numero de identidade do excliente a ser eliminado
     * @param nome O nome do excliente a ser eliminado
     * @return True se o excliente foi eliminado com sucesso, False caso nao seja encontrado na tabela.
     */
	bool removeExcliente(const unsigned int numIdentidade, const string nome);
    
    /**
     * Remove um excliente da tabela de dispersao.
     * @param u1 O apontador para o excliente a ser removido
     * @return True se o excliente foi eliminado com sucesso, False caso nao seja encontrado na tabela.
     */
    bool removeExcliente(Utilizador *u1);
    
    /**
     * Devolve o excliente pedido para consultar informacoes
     * @param numIdentidade O numero de identidade do excliente a ser consultado
     * @return O apontador para o excliente pedido, NULL caso nao exista na tabela.
     */
    Utilizador* getExCliente(const unsigned int numIdentidade);
    
    /**
     * Devolve o excliente pedido para consultar informacoes. 
     * Atira excecao caso o excliente nao exista na tabela.
     * @param numIdentidade O numero de identidade do excliente a ser consultado
     * @param nome O nome do excliente a ser consultado
     * @return O apontador para o excliente pedido
     */
    Utilizador* getExCliente(const unsigned int numIdentidade, const string nome);
    
    /**
     * Pesquisa em toda a tabela de dispersao os clientes com nome segundo a pesquisa
     * @param nome O nome (ou parte do nome) a ser pesquisado
     * @return Um vector com os apontadores dos exclientes que satisfazem o criterio da pesquisa
     */
    vector<Utilizador*> pesquisaExClientes(const string nome);
    
    /**
     * Para alterar o numero de identidade de um excliente.
     * O excliente e' removido, modificado e reinserido na tabela de dispersao.
     * Atira excecao caso o excliente nao exista na tabela.
     * @param numBI O novo numero de bilhete de identidade
     * @param u1 O apontador para o excliente a ser modificado
     * @return Void
     */
	void alteraDadosExclienteNumBI(unsigned int numBI, Utilizador *u1);
    
    /**
     * Para alterar o nome de um excliente.
     * O excliente e' removido, modificado e reinserido na tabela de dispersao.
     * Atira excecao caso o excliente nao exista na tabela.
     * @param nome O novo numero de bilhete de identidade
     * @param u1 O apontador para o excliente a ser modificado
     * @return Void
     */
	void alteraDadosExclienteNome(string nome, Utilizador *u1);
    
    /**
     * @return O tamanho da tabela de dispersao de exclientes
     */
    unsigned int getNumeroExclientes() const;
    
    /**
     * Funcao para escrita de informacoes de uma tabela de exclientes
     * @param out Onde vao ser colocadas as informacoes da tabela
     * @param ex O catalogo que contem os prototipos
     * @return Devolve out modificado
     */
    friend ostream & operator<<(ostream &out, ExClientes &ex);
};

/**
 * Classe de excecao para ser lancada quando e' consultado um excliente que nao existe
 */
class ExClienteNaoExistente: public Erro{
private:
    Utilizador clienteNaoExistente; /**< O excliente que nao existe na tabela */
public:
    /**
     * Construtor da excecao
     * @param u O excliente que nao existe na tabela
     */
    ExClienteNaoExistente(Utilizador u): Erro("Excliente nao existente"), clienteNaoExistente(u){};
    
    /**
     * @return O excliente que nao existe na tabela
     */
    Utilizador getClienteNaoExistente() const{return clienteNaoExistente;};
};

#endif
