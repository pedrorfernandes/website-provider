//
//  menu.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "menu.h"

unsigned int Menu::escolhe(vector<string> & escolhas, const string &perg){
    unsigned int i = 1;
    cout << perg << endl;
    for (vector<string>::iterator opcao = escolhas.begin(); opcao != escolhas.end() ; opcao++, i++) {
        cout << i << " - " << *opcao << endl;
    }
    i--;
    unsigned int escolha;
    cout << PROMPT;
    cin >> escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return escolha;
}

template<class T>
T Menu::escolhe(vector<T> & escolhas, const string & perg){
    unsigned int i = 1;
    cout << perg << endl;
    for (typename vector<T>::iterator opcao = escolhas.begin(); opcao != escolhas.end() ; opcao++, i++) {
        cout << i << " - " << *opcao << endl;
    }
    i--;
    unsigned int numero_escolha;
    cout << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        cin >> numero_escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    T escolha;
    if (numero_escolha == 0) {
        escolha = NULL;
    } else{
        escolha = escolhas.at(numero_escolha-1);
    }
    return escolha;
}

template<class T>
T Menu::escolheSemListagem(vector<T> & escolhas, const string & perg){
    unsigned int i = escolhas.size();
    cout << perg << endl;
    unsigned int numero_escolha;
    cout << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        cin >> numero_escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    T escolha;
    if (numero_escolha == 0) {
        escolha = NULL;
    } else{
        escolha = escolhas.at(numero_escolha-1);
    }
    return escolha;
}

template<class T>
T pergunta(const string &perg){
    cout << perg << endl << PROMPT;
    T resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() ) {
        cout << "Resposta invalida. Tente outra vez." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return resposta;
}

// especializacao para as strings serem recebidas por getline
template<>
string pergunta(const string &perg)
{
    string str = "";
    cout << perg << endl << PROMPT;
    while (str == "") {
        getline(cin, str);
        if (str == "")
            cout << PROMPT;
    }
    return str;
}

Utilizador* Menu::criar_utilizador(){ // falta seguranca para detetar se o utilizador ja existe
    string nome;
    unsigned int numIdentidade;
    nome = pergunta<string>("Escolha o nome do utilizador");
    numIdentidade = pergunta<unsigned int>("Indique o numero do bilhete de identidade");
    Utilizador* u_pointer;
    wsp->adicionaGestor(u_pointer = new Utilizador(numIdentidade, nome));
    return u_pointer;
}

Website* Menu::criar_website(){
    string identificador;
    unsigned int numeroPaginas;
    Website* site;
    bool ok = false;
    
    switch (escolhe(escolher_tipo_site, "Que tipo de website pretende criar?") ) {
        case 0:
            // voltar para tras
            break;
        case 1: // site particular
        {
            string tecnologia;
            Utilizador* gestor;
            
            identificador = pergunta<string>("Escolha um identificador (URL) para o website");
            
            tecnologia = pergunta<string>("Escolha a tecnologia que vai ser utilizada para o website");
            
            // escolher se quer criar um novo gestor ou escolher um do vector
            while (gestor == NULL) {
                switch (escolhe(escolher_utilizador, "Defina como quer escolher o gestor")) {
                    case 0: // utilizador cancelou
                        gestor = NULL;
                        break;
                    case 1: // criar um novo utilizador
                        gestor = criar_utilizador();
                        break;
                    case 2: // escolher um gestor ja existente
                        gestor = escolhe(wsp->getGestores(), "Escolha um gestor");
                    default:
                        break;
                }
            }
            
            numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas");
                        
            while (!ok) {
                try {
                    wsp->novoSite(site = new SiteParticular(identificador, numeroPaginas, tecnologia, gestor));
                    ok = true;
                    
                } catch (LimiteDePaginasUltrapassado &e) {
                    cout << e.getMsg() << endl;
                    numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas");
                }
            }
            cout << "O website " << identificador << " foi criado com sucesso!" << endl;
            return site;
            break;
        }
        case 2: // site empresa
        {
            vector<string> tecnologias;
            vector<Utilizador*> gestores;
            
            identificador = pergunta<string>("Escolha um identificador (URL) para o website");
            
            numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas");

            unsigned int repete = pergunta<unsigned int>("Quantas tecnologias vao ser utilizadas pelo website?");
            unsigned int i = 0;
            
            while (i < repete) {
                tecnologias.push_back(pergunta<string>("Escolha uma tecnologia"));
                i++;
            }
            repete = pergunta<unsigned int>("Quantos gestores tera o website?");
            i = 0;
            while (i < repete) {
                switch (escolhe(escolher_utilizador, "Defina como quer escolher o gestor")) {
                    case 0: // utilizador cancelou
                        i--;
                        break;
                    case 1: // criar um novo utilizador
                        gestores.push_back(criar_utilizador());
                        break;
                    case 2: // escolher utilizador ja existente
                    {
                        Utilizador* gestor = NULL;
                        gestor = escolhe(wsp->getGestores(), "Escolha um gestor");
                        if (gestor == NULL){
                            i--;
                            break;
                        } else
                        gestores.push_back(gestor);
                        break;
                    }
                    default:
                        break;
                }
                i++;
            }
            while (!ok) {
                try {
                    wsp->novoSite(site = new SiteEmpresa(identificador, numeroPaginas, tecnologias, gestores));
                    ok = true;
                } catch (...) {
                    cout << "Oops" << endl;
                }
            }
            cout << "O website " << identificador << " foi criado com sucesso!" << endl;
            return site;
            break;
        }
        default:
            return NULL;
            break;
    }
    return NULL;
}

void Menu::opcoes(Website* site){
    SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(site);
    SiteParticular* particular = dynamic_cast< SiteParticular* >(site);
    
    if (particular)
    {
        bool acabado = false;
        while (!acabado)
        {
            // vamos imprimir informacoes do site
            cout << "Informacoes do website particular " << site->getIdentificador() << endl;
            cout << "Tecnologia utilizada: " << site->getTecnologia() << endl;
            cout << "Gestor: " << site->getGestor()->getNome() << " (BI n. " << site->getGestor()->getNumIdentidade() << ")" << endl;
            cout << "Numero de paginas: " << site->getNumeroPaginas() << " (max. " << site->getLimitePaginas() << " / custo por pagina: " << site->getCustoPorPagina() << ")" << endl;
            cout << "Custo total do site: " << site->getCusto() << " $" <<  endl;
            switch (escolhe(opcoes_website_particular, "Selecione uma opcao"))
            {
                case 0:
                    acabado = true;
                    break;
                case 1: // alterar o gestor
                    switch (escolhe(escolher_utilizador, "Defina como quer escolher o novo gestor para o site"))
                {
                    case 0: // utilizador cancelou
                        break;
                    case 1: // criar um novo utilizador
                        site->setGestor(criar_utilizador());
                        break;
                    case 2: // escolher um gestor ja existente
                        site->setGestor(escolhe(wsp->getGestores(), "Escolha um gestor"));
                    default:
                        break;
                }
                    break;
                case 2: // alterar a tecnologia
                    site->setTecnologia(pergunta<string>("Escolha a nova tecnologia"));
                    break;
                case 3: // alterar numero de paginas do site
                {
                    bool ok = false;
                    while (!ok)
                    {
                        try {
                            unsigned int numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas");
                            if (numeroPaginas == 0){
                                cout << "Operacao cancelada" << endl;
                                break;
                            } else {
                            site->setNumeroPaginas(numeroPaginas);
                            ok = true;
                            }
                        } catch (LimiteDePaginasUltrapassado &e) {
                            cout << e.getMsg() << endl;
                        }
                    }
                    break;
                }
                case 4: // eliminar website
                    cout << "O website" << site->getIdentificador() << " foi eliminado!" << endl;
                    wsp->eliminaSite(site);
                    return;
                    break;
                default:
                    break;
            }
        }
    }
    
    if (empresa)
    {
        bool acabado = false;
        while (!acabado)
        {
            
            cout << "Informacoes do website empresa " << site->getIdentificador() << endl;
            cout << "Tecnologias utilizadas: ";
            for (vector<string>::iterator tecnologia = site->getTecnologias().begin(); tecnologia != site->getTecnologias().end(); tecnologia++) {
                if (tecnologia == site->getTecnologias().end()-1) {
                    cout << *tecnologia << "." << endl;
                } else
                    cout << *tecnologia << ", ";
            }
            cout << "Gestores: ";
            for (vector<Utilizador*>::iterator gestor = site->getGestores().begin(); gestor != site->getGestores().end() ; gestor++)
            {
                if (gestor == site->getGestores().end()-1 )
                {
                    cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << ")." << endl;
                } else
                    cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << "), ";
            }
            
            //cout << "Numero de paginas: " << site->getNumeroPaginas() << " (custo por pagina: " << site->getCustoPorPagina() << ")" << endl;
            cout << "Custo total do site: " << site->getCusto() << " $" <<  endl;
            
            switch (escolhe(opcoes_website_empresa, "Selecione uma opcao"))
            {
                case 0: // utilizador termina as modificacoes
                    acabado = true;
                    break;
                case 1: // adicionar um gestor
                    switch (escolhe(escolher_utilizador, "Defina como quer escolher o novo gestor para o site"))
                {
                    case 0: // utilizador cancelou
                        break;
                    case 1: // criar um novo utilizador
                        site->novoGestor(criar_utilizador());
                        break;
                    case 2: // escolher um gestor ja existente que nao pertence ao website
                    {
                        /*
                        vector<Utilizador*> vector1 = wsp->getGestores();
                        vector<Utilizador*> vector2 = empresa->getConstGestores();
                        cout << "ola" << endl;
                        vector<Utilizador*> gestores_que_nao_estao_no_site;
                        gestores_que_nao_estao_no_site = vector1 - vector2;
                        cout << "ole" << endl;
                        site->novoGestor(escolhe(gestores_que_nao_estao_no_site, "Escolha um gestor"));
                         // ISTO NAO FUNCIONA, a funcao operator- esta a destruir os gestores do website
                         */
                        site->novoGestor(escolhe(wsp->getGestores(), "Escolha um gestor"));

                        break;
                    }
                    default:
                        break;
                }
                    break;
                    
                case 2: // Retirar gestor
                    site->retiraGestor(escolhe(site->getGestores(), "Escolha que gestor pretende retirar"));
                    break;
                case 3: // Adicionar tecnologia
                    site->novaTecnologia(pergunta<string>("Escolhe uma nova tecnologia para o website"));
                    break;
                case 4: // Retirar tecnologia
                {
                    // e' necessario utilizar a funcao escolhe() para permitir cancelar com 0
                    vector<string> tecnologias = site->getTecnologias();
                    unsigned int tech_pos = escolhe(tecnologias, "Escolhe que tecnologia pretende remover");
                    if (tech_pos == 0)
                        break;
                    else
                        site->retiraTecnologia(site->getTecnologias().at(tech_pos));
                    break;
                }
                case 5: // Alterar numero de paginas
                {
                    unsigned int numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas");
                    if (numeroPaginas == 0){
                        cout << "Operacao cancelada" << endl;
                        break;
                    } else {
                        site->setNumeroPaginas(numeroPaginas);
                        break;
                    }
                }
                case 6: // Eliminar website
                    cout << "O website" << site->getIdentificador() << " foi eliminado!" << endl;
                    wsp->eliminaSite(site);
                    return;
                    break;
                    
                default:
                    break;
            }
            
        }
    }
    
}


void Menu::listar_websites(){
    cout << left << setw(ESPACO_MUITO_PEQUENO) << "Numero" << setw(ESPACO_PEQUENO) << "Tipo" << setw(ESPACO_LISTAGEM) << "Identificador" << setw(ESPACO_LISTAGEM) << "Gestor(es)" << setw(ESPACO_LISTAGEM) << "Tecnologia(s)" << setw(ESPACO_PEQUENO) << "Paginas" << endl;
    unsigned int numero = 1;
    for (vector<Website*>::iterator site_it = wsp->getWebsites().begin(); site_it != wsp->getWebsites().end(); site_it++) {
        Website* site = *site_it;
        SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(site);
        SiteParticular* particular = dynamic_cast< SiteParticular* >(site);
        
        if (particular){  // como listar as informacoes se o site for particular
            cout << left << setw(ESPACO_MUITO_PEQUENO) << numero << setw(ESPACO_PEQUENO) <<  "Particular" << setw(ESPACO_LISTAGEM)<< site->getIdentificador() << setw(ESPACO_LISTAGEM) << site->getGestor()->getNome() << setw(ESPACO_LISTAGEM) << site->getTecnologia() << setw(ESPACO_LISTAGEM) << site->getNumeroPaginas() << endl;
        } 
        if (empresa){ // como listar as informacoes se o site for de uma empresa
            stringstream tecnologias;
            tecnologias << site->getTecnologias()[0] << " e mais " << site->getTecnologias().size()-1;
            stringstream gestores;
            gestores << site->getGestores()[0]->getNome() << " e mais " << site->getGestores().size()-1;
            cout << left << setw(ESPACO_MUITO_PEQUENO) << numero << setw(ESPACO_PEQUENO) << "Empresa" << setw(ESPACO_LISTAGEM) << site->getIdentificador() << setw(ESPACO_LISTAGEM) << gestores.str() << setw(ESPACO_LISTAGEM) << tecnologias.str() << setw(ESPACO_PEQUENO) << site->getNumeroPaginas() << endl;
        }
        numero++;
    }
    Website* site = NULL;
    site = escolheSemListagem(wsp->getWebsites(), "Escolha um website para ver as informacoes");
    if (site == NULL){ // se o utilizador cancelou, volta para o menu anterior
        return;
    } else{
        opcoes(site);
    }
    
    return;
}

void Menu::listar_utilizadores(){
    escolhe(wsp->getGestores(), "Escolhe um utilizador para efetuar modificacoes");
}

int Menu::inicio(){
    switch (escolhe(opcoes_inicio, "Selecione uma opcao")) {
        case 0:
            return 1;
        case 1:
            criar_website();
            return 0;
            break;
        case 2:
            wsp->getGestores().push_back(criar_utilizador());
            return 0;
            break;
        case 3:
            listar_websites();
            return 0;
            break;
        case 4:
            listar_utilizadores();
            return 0;
            break;
        default:
            return 0;
            break;
    }
}

Menu::Menu(){
    opcoes_inicio.push_back("Criar website");
    opcoes_inicio.push_back("Criar utilizador");
    opcoes_inicio.push_back("Listar websites");
    opcoes_inicio.push_back("Listar utilizadores");
    
    escolher_tipo_site.push_back("Site para particular");
    escolher_tipo_site.push_back("Site para empresa");
    
    escolher_utilizador.push_back("Criar novo utilizador");
    escolher_utilizador.push_back("Escolher um utilizador ja existente");
    
    opcoes_website_particular.push_back("Alterar o gestor");
    opcoes_website_particular.push_back("Alterar a tecnologia usada pelo website");
    opcoes_website_particular.push_back("Alterar o numero de paginas do website");
    opcoes_website_particular.push_back("Eliminar o website");

    opcoes_website_empresa.push_back("Adicionar gestor");
    opcoes_website_empresa.push_back("Retirar gestor");
    opcoes_website_empresa.push_back("Adicionar tecnologia");
    opcoes_website_empresa.push_back("Retirar tecnologia");
    opcoes_website_empresa.push_back("Alterar o numero de paginas");
    opcoes_website_empresa.push_back("Eliminar website");
    
    // TESTES
    wsp = new GestorWSP();
    Utilizador* pedro = new Utilizador(12345, "Pedro");
    Utilizador* ze = new Utilizador(123, "Ze");
    wsp->adicionaGestor(pedro);
    wsp->adicionaGestor(ze);
    Website* blog = new SiteParticular("www.umblog.com", 10, "Ruby", pedro);
    wsp->novoSite(blog);
    vector<Utilizador*> empresa;
    empresa.push_back(ze); empresa.push_back(pedro);
    vector<string> tecnologias;
    tecnologias.push_back("c++"); tecnologias.push_back("java"); tecnologias.push_back("python");
    Website* google = new SiteEmpresa("www.google.com", 100, tecnologias, empresa);
    wsp->novoSite(google);

    cout << "Bem vindo ao gestor de website provider!" << endl << "NOTA: escolher 0 cancela a opcao e regressa para o menu anterior (quando possivel)" << endl;
    while (inicio() != 1) {
        
    }
    cout << "A terminar aplicacao..." << endl;
}
