#ifndef ExCLiente_h
#define ExCliente_h


#include <tr1/unordered_set>
#include <iostream>
#include <vector>
#include <string>

#include "utilizador.h"

using namespace std;


struct eqNome
{
	bool operator() (const Utilizador &u1, const Utilizador &u2)  const
		{
		return u1.getNome==u2.getNome;
		}

};

struct hNome
{

	int operator() (const Utilizador &u1) const {
	string s1=u1.getNome();
	int v = 0;
	for ( unsigned int i=0; i< s1.size(); i++ )
	v = 37*v + s1[i];
	return v;
	}

};

typedef tr1::unordered_set<Utilizador, hNome, eqNome> tabela_exclientes;

class ExClientes
{
	 tabela_exclientes exclientes;
public:
	 ExClientes();
	tabela_exclientes getExclientes();
	void insereExcliente(const Utilizador &u1);
	void removeExcliente(int anos);
	void alteraDadosExclienteNumBI(unsigned int numBI, Utilizador &u1);
	void alteraDadosExclienteNome(string nome, Utilizador &u1);

};

#endif
