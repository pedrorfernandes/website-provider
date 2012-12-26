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

#define TAG_UTILIZADOR "*UTILIZADOR*"
#define TAG_EMPRESA "*SITEEMPRESA*"
#define TAG_PARTICULAR "*SITEPARTICULAR*"
#define TAG_CUSTO_PARTICULAR "*CUSTOPARTICULAR_PREDEFINIDO*"
#define TAG_CUSTO_EMPRESA "*CUSTOEMPRESA_PREDEFINIDO*"
#define TAG_LIMITE "*LIMITEPAGINAS_PREDEFINIDO*"
#define FIM_DE_STRING "|"
#define FIM_DE_STRING_OUTPUT " | "
#define FICHEIRO "wsp.txt"
#define CENTIMOS 2
#define MAX_ELEMENTOS_LISTAGEM 50

#define TAG_PROTOTIPO "*PROTOTIPO*"
#define TAG_EXCLIENTE "*EXCLIENTE*"

#include "gestorWSP.h"
#include "utilizador.h"
#include "website.h"
#include "siteParticular.h"
#include "siteEmpresa.h"
#include "catalogo.h"

using namespace std;

/**
 * Funcao que faz uma pergunta e recebe o input do utilizador, devolvendo este mesmo.
 * @param perg A pergunta a ser lancada
 * @return O input do utilizador
 */
template<class T> T pergunta(const string &perg);
/**
 * Especializacao da a funcao pergunta() para strings. Nesta situacao, sera feito o getline do input do utilizador e devolvido este sob a forma de string
 * @param perg A pergunta a ser lancada
 * @return A string com o input do utilizador
 */
template<> string pergunta(const string &perg);
/**
 * Especializacao da a funcao pergunta() para unsigned ints. Nesta situacao, o numero sera gravado como int e sera feita a verificacao que e' positivo. Depois disto sera guardado como unsigned. Deste modo, sao evitados erros de overflow com o input
 * @param perg A pergunta a ser lancada
 * @return O numero inteiro sem sinal que o utilizador submeteu
 */
template<> unsigned int pergunta(const string &perg);


/**
 * O menu trata de todos os outputs do programa, cria um GestorWSP e gere todas as introducoes de dados no WSP
 */
class Menu{
    GestorWSP* wsp; /**< O apontador para o gestor de website provider associado ao menu */
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
    vector<string> escolher_tecnologias;
    vector<string> website_ou_utilizador;
    vector<string> superior_ou_inferior;
    vector<string> gestores_empresa;
    vector<string> consulta_catalogo;
    vector<string> opcoes_prototipo;
    vector<string> consulta_exclientes;
    vector<string> opcoes_excliente;

public:
    /**
     * Construtor de Menu. Neste construtor sao preenchidos os vectores com todos os menus que o utilizador ira visualizar, e' criado um objeto gestor de website provider, sao lidos e guardados todos os dados utilizados pelo website provider. Quando esta funcao termina, o programa tambem termina.
     */
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
    unsigned int escolhe(const vector<string> & escolhas, const string &perg);
    
    /**
     * Faz uma pergunta, lista um vector de websites que sao as escolhas possiveis e retorna o website que foi escolhido pelo utilizador do programa
     * @param escolhas O vector de apontadores para websites
     * @param perg A pergunta a ser lancada
     * @return O apontador para o website escolhido
     */
    Website* escolhe(const vector<Website*> & escolhas, const string & perg);
    
    /**
     * Faz uma pergunta, lista um vector de gestores que sao as escolhas possiveis e retorna o gestor que foi escolhido pelo utilizador do programa
     * @param escolhas O vector de apontadores para gestores
     * @param perg A pergunta a ser lancada
     * @return O apontador para o gestor escolhido
     */
    Utilizador* escolhe(const vector<Utilizador*> & escolhas, const string & perg);
    
    /**
     * Faz uma pergunta e retorna uma escolha do vector de escolhas possiveis. Util para escolher gestores ou websites quando foi previamente feita a listagem destes
     * @param escolhas O vector de escolhas
     * @param perg A pergunta a ser lancada
     * @return A escolha
     */
    template<class T> T escolheSemListagem(const vector<T> & escolhas, const string & perg);
    
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
    
    /**
     * Funcao destinada para permitir o utilizador ler uma informacao importante e so depois de carregar no ENTER pode prosseguir para o menu seguinte
     */
    inline void pressEnter();
    
    void consultaCatalogo();
    
    Prototipo* escolhe(const BST<Prototipo*> & escolhas, const string & perg);
    
    void opcoes(Prototipo* proto);
    
    void consultaExClientes();
    
    Utilizador* escolhe(const HashClientes & exclientes, const string & perg);
    
    void opcoesExcliente(Utilizador* gestor);
    
    Utilizador* criar_excliente();



};

#endif