//  exClientes.cpp
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "ExClientes.h"

ExClientes::ExClientes()
{};

ExClientes::~ExClientes(){
    HashClientes::const_iterator it;
    for (it = exclientes.begin(); it != exclientes.end() ; ++it) {
        delete (*it);
    }
    exclientes.clear();
}

const HashClientes & ExClientes::getHashClientes(){
    return exclientes;
}

void ExClientes::insereExcliente( Utilizador *u1)
{
    exclientes.insert(u1);
}

void ExClientes::insereExcliente(const unsigned int numIdentidade, const string nome)
{
    exclientes.insert(new Utilizador(numIdentidade, nome));
}

bool ExClientes::removeExcliente(const unsigned int numIdentidade, const string nome)
{
    Utilizador* identidade = new Utilizador (numIdentidade, nome);
	if ( exclientes.erase(identidade) == 1){ // foi encontrado e eliminado
        delete identidade;
        return true;
    } else {
        delete identidade;
        return false; // erase retornou 0, nao existe
    }
}


bool ExClientes::removeExcliente(Utilizador *u1){
    if (exclientes.erase(u1) == 1){
        return true;
    } else
        return false;
}

Utilizador* ExClientes::getExCliente(const unsigned int numIdentidade){
    HashClientes::const_iterator it;
	for (it = exclientes.begin(); it != exclientes.end(); ++it) {
        if ( (*it)->getNumIdentidade() == numIdentidade){
            return (*it);
        }
    }
    return NULL;
}

Utilizador* ExClientes::getExCliente(const unsigned int numIdentidade, const string nome){
    HashClientes::const_iterator it;
    Utilizador* u1 = new Utilizador (numIdentidade, nome);
	it = exclientes.find(u1);
    
	if(it!=exclientes.end())
	{
        return (*it);
	} else {
        throw ExClienteNaoExistente(*u1);
    }
}

vector<Utilizador*> ExClientes::pesquisaExClientes(const string nome){
    vector<Utilizador*> encontrados;
    HashClientes::const_iterator it;
    string aux;
    string pesquisa = nome;
    transform(pesquisa.begin(), pesquisa.end(), pesquisa.begin(), ::tolower);
    for (it = exclientes.begin(); it != exclientes.end(); ++it) {
        aux = (*it)->getNome();
        transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
        if (string::npos != aux.find(pesquisa))
        {
            encontrados.push_back(*it);
        }
    }
    return encontrados;
}


void ExClientes::alteraDadosExclienteNome(string nome, Utilizador *u1)
{
	HashClientes::const_iterator it;
	it = exclientes.find(u1);
	Utilizador* u = *it;
    
    
	if(it!=exclientes.end())
	{
        exclientes.erase(it);
		u->setNome(nome);
		exclientes.insert(u);
        
	}
    
	else {
        throw ExClienteNaoExistente(*u1);
    }
}

void ExClientes::alteraDadosExclienteNumBI(unsigned int numIdentidade, Utilizador *u1)
{
    
	HashClientes::const_iterator it;
	it = exclientes.find(u1);
	Utilizador* u = *it;
    
	if(it!=exclientes.end())
	{
        exclientes.erase(it);
		u->setNumIdentidade(numIdentidade);
		exclientes.insert(u);
        
	}
	else{
        throw ExClienteNaoExistente(*u1);
    }
}

unsigned int ExClientes::getNumeroExclientes() const{
    return (unsigned int) exclientes.size();
}


