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

#define PROMPT "> "
#define ESPACO_LISTAGEM 20
#define ESPACO_PEQUENO 15
#define ESPACO_MUITO_PEQUENO 10

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
    template<class T> T escolhe(vector<T> & escolhas, const string & perg);
    template<class T> T escolheSemListagem(vector<T> & escolhas, const string & perg);

};

#endif