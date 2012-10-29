//
//  menu.h
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef menu_h
#define menu_h

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <fstream>

#define PROMPT "> "
#define ESPACO_LISTAGEM 20
#define ESPACO_PEQUENO 15
#define ESPACO_MUITO_PEQUENO 10

#define TAG_UTILIZADOR "**Utilizador**"
#define TAG_EMPRESA "**SiteEmpresa**"
#define TAG_PARTICULAR "**SiteParticular**"
#define TAG_CUSTO_PARTICULAR "**CUSTOPARTICULAR_PREDEFINIDO**"
#define TAG_CUSTO_EMPRESA "**CUSTOEMPRESA_PREDEFINIDO**"
#define TAG_LIMITE "**LIMITEPAGINAS_PREDEFINIDO**"
#define FIM_DE_STRING "|"
#define FIM_DE_STRING_OUTPUT " | "
#define FICHEIRO "wsp.txt"

#include "gestorWSP.h"
#include "utilizador.h"
#include "website.h"
#include "siteParticular.h"
#include "siteEmpresa.h"

using namespace std;

template<class T> T pergunta(const string &perg);
template<> string pergunta(const string &perg);

class Menu{
    GestorWSP* wsp;
    vector<string> opcoes_inicio;
    vector<string> escolher_tipo_site;
    vector<string> escolher_utilizador;
    vector<string> opcoes_website_particular;
    vector<string> opcoes_website_empresa;
    vector<string> opcoes_utilizador;
    vector<string> consulta_custos;
    vector<string> ordenar_utilizadores;
    vector<string> ordenar_websites;
    vector<string> pesquisa_websites;
    vector<string> pesquisa_utilizadores;
public:
    Menu();
    int inicio();
    void selecionarOpcao(unsigned int opcao);
    Utilizador* criar_utilizador();
    Website* criar_website();
    void listar_websites();
    void listar_utilizadores();
    void opcoes(Website* site);
    void opcoes(Utilizador* gestor);
    unsigned int escolhe(vector<string> & escolhas, const string &perg);
    Website* escolhe(vector<Website*> & escolhas, const string & perg);
    Utilizador* escolhe(vector<Utilizador*> & escolhas, const string & perg);

    template<class T> T escolheSemListagem(vector<T> & escolhas, const string & perg);
    
    bool guardaDados();
    bool leDados();
    
    void consultaCustos();
    void ordenaUtilizadoresCriterio();
    void ordenaWebsitesCriterio();
    void pesquisaNosWebsites();
    void pesquisaNosUtilizadores();

};

#endif