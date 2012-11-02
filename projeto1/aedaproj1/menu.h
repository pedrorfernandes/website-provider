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
#define CENTIMOS 2

#include "gestorWSP.h"
#include "utilizador.h"
#include "website.h"
#include "siteParticular.h"
#include "siteEmpresa.h"

using namespace std;

template<class T> T pergunta(const string &perg);
template<> string pergunta(const string &perg);

/**
 * O menu trata de todos os outputs do programa, cria um GestorWSP e gere todas as introducoes de dados no WSP
 */
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
    /**
     * Funcao para aceder ao menu inicial do programa
     * @return 0 caso o utilizador termine a aplicacao, 1 se o utilizador regressa para este menu
     */
    int inicio();
    
    /**
     * Submenu para criar um novo utilizador
     * @return O apontador para o utilizador criado
     */
    Utilizador* criar_utilizador();
    
    /**
     * Submenu para criar um novo website
     * @return O apontador para o website criado
     */
    Website* criar_website();
    
    /**
     * Submenu para listar todos os websites existentes no WSP
     * @return Void
     */
    void listar_websites();
    
    /**
     * Submenu para listar todos os utilizadores existentes no WSP
     */
    void listar_utilizadores();
    
    /**
     * Lista todas as opcoes disponiveis para a modificacao de informacoes de um website
     * @return Void
     */
    void opcoes(Website* site);
    
    /**
     * Lista todas as opcoes disponiveis para a modificacao de informacoes de um gestor
     * @return Void
     */
    void opcoes(Utilizador* gestor);
    
    /**
     * Faz uma pergunta, lista todas as escolhas possiveis e retorna o valor da posicao da escolha no vector. Nota: o utilizador pode selecionar 0, que significa cancelar
     * @param escolhas O vector das escolhas disponiveis
     * @param perg A pergunta a ser lancada
     * @return O valor da posicao da escolha no vector, ou 0
     */
    unsigned int escolhe(vector<string> & escolhas, const string &perg);
    
    /**
     * Faz uma pergunta, lista um vector de websites que sao as escolhas possiveis e retorna o website que foi escolhido pelo utilizador do programa
     * @param escolhas O vector de apontadores para websites
     * @param perg A pergunta a ser lancada
     * @return O apontador para o website escolhido
     */
    Website* escolhe(vector<Website*> & escolhas, const string & perg);
    
    /**
     * Faz uma pergunta, lista um vector de gestores que sao as escolhas possiveis e retorna o gestor que foi escolhido pelo utilizador do programa
     * @param escolhas O vector de apontadores para gestores
     * @param perg A pergunta a ser lancada
     * @return O apontador para o gestor escolhido
     */
    Utilizador* escolhe(vector<Utilizador*> & escolhas, const string & perg);
    
    /**
     * Faz uma pergunta e retorna uma escolha do vector de escolhas possiveis. Util para escolher gestores ou websites quando foi previamente feita a listagem destes
     * @param escolhas O vector de escolhas
     * @param perg A pergunta a ser lancada
     * @return A escolha
     */
    template<class T> T escolheSemListagem(vector<T> & escolhas, const string & perg);
    
    /**
     * Funcao que guarda todos os dados do WSP para um ficheiro .txt, segundo uma formatacao especial
     * @return True se os dados foram guardados com sucesso, False caso contrario
     */
    bool guardaDados();
    
    /**
     * Funcao que le todos os dados do ficheiro .txt gerado pela funcao guardaDados(), e regista estas informacoes no WSP
     * @return True se os dados foram lidos com sucesso, False caso contrario
     */
    bool leDados();
    
    /**
     * Submenu para a consulta dos custos por pagina de websites empresa, particulares, custo total de todos os websites e tambem para modificar o limite de paginas de websites particulares
     * @return Void
     */
    void consultaCustos();
    
    /**
     * Submenu para ordenar os utilizadores segundo varios criterios
     * @return Void
     */
    void ordenaUtilizadoresCriterio();
    
    /**
     * Submenu para ordenar os websites segundo varios criterios
     * @return Void
     */
    void ordenaWebsitesCriterio();
    
    /**
     * Submenu para pesquisar informacoes nos websites do WSP. Tambem lista os websites particulares e empresa
     * @return Void
     */
    void pesquisaNosWebsites();
    
    /**
     * Submenu para pesquisar informacoes nos utilizadores do WSP
     * @return Void
     */
    void pesquisaNosUtilizadores();

};

#endif