#include "ExClientes.h"

ExClientes::ExClientes()
{};

void ExClientes::insereExcliente(const Utilizador &u1)
{
exclientes.insert(u1);
}

void ExClientes::removeExcliente(int anos)
{
	/*tabela_exclientes::iterator it = exclientes.begin();

	while(it != exclientes.end())
	{
		if((*it).getAnosSemContrato()  <= anos)
		{

			exclientes.erase(it);
			it--;

		}

		it++;
	}

*/
}
void ExClientes::alteraDadosExclienteNome(string nome, Utilizador &u1)
{
	tabela_exclientes::iterator it;
	it = exclientes.find(u1);
	Utilizador u = *it;


	if(it!=exclientes.end())
	{
		u.setNome(nome);
		exclientes.erase(it);
		exclientes.insert(u);

	}

	else {}
	//lan�ar excep�ao para o caso do utilizador em questao nao existir na tabela de disper�ao
}

void ExClientes::alteraDadosExclienteNumBI(unsigned int numBI, Utilizador &u1)
{

	tabela_exclientes::iterator it;
	it = exclientes.find(u1);
	Utilizador u = *it;

	if(it!=exclientes.end())
	{
		u.setNumIdentidade(numBI);
		exclientes.erase(it);
		exclientes.insert(u);

	}
	else{}
	// lancar excep�ao caso o o cliente nao seja encontrado na tabela de ex-clientes.
}



