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

#include "utilizador.h"

using namespace std;


struct clientesHash
{
	bool operator() (const Utilizador *u1, const Utilizador *u2)  const
    {
        if (u1->getNome() == u2->getNome() ){
            return u1->getNumIdentidade() == u2->getNumIdentidade();
        } else
            return false;
    }
    
    // Algoritmo djb2
    // http://www.cse.yorku.ca/~oz/hash.html
    
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

class ExClientes
{
    HashClientes exclientes;
public:
    ExClientes();
    ~ExClientes();
	const HashClientes & getHashClientes();
	void insereExcliente(Utilizador *u1);
    void insereExcliente(const unsigned int numIdentidade, const string nome);
	bool removeExcliente(const unsigned int numIdentidade, const string nome);
    bool removeExcliente(Utilizador *u1);
    Utilizador* getExCliente(const unsigned int numIdentidade);
    Utilizador* getExCliente(const unsigned int numIdentidade, const string nome);
    vector<Utilizador*> pesquisaExClientes(const string nome);
	void alteraDadosExclienteNumBI(unsigned int numBI, Utilizador *u1);
	void alteraDadosExclienteNome(string nome, Utilizador *u1);
    unsigned int getNumeroExclientes() const;
    friend ostream & operator<<(ostream &out, ExClientes &ex);
    
};

class ExClienteNaoExistente{
private:
    Utilizador clienteNaoExistente;
public:
    ExClienteNaoExistente(Utilizador u): clienteNaoExistente(u){};
    Utilizador getClienteNaoExistente() const{return clienteNaoExistente;};
    
};

#endif
