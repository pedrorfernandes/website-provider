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


bool Menu::guardaDados(){
    /*
     Formatacao exemplo dos dados
     
     **Utilizador** Pedro 12345
     **Utilizador** Ze 123
     **SiteParticular** www.blog.com 10 Ruby Pedro | 12345
     **SiteEmpresa** www.google.com 100 2 c++ java 2 Pedro | 12345 Ze | 123
     **CUSTOPARTICULAR_PREDEFINIDO** 10
     **CUSTOEMPRESA_PREDEFINIDO** 100
     **LIMITEPAGINAS_PREDEFINIDO** 50
     */
    
    ofstream ficheiro;
    ficheiro.open(FICHEIRO);
    
    for (vector<Utilizador*>::iterator gestor_it = wsp->getGestores().begin(); gestor_it != wsp->getGestores().end() ; gestor_it++) {
        ficheiro << TAG_UTILIZADOR << " " << (*gestor_it) << endl;
    }
    
    for (vector<Website*>::iterator site_it = wsp->getWebsites().begin(); site_it != wsp->getWebsites().end(); site_it++) {
        SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(*site_it);
        SiteParticular* particular = dynamic_cast< SiteParticular* >(*site_it);
        if (empresa){
            ficheiro << TAG_EMPRESA << " " << empresa << endl;
        }
        if (particular) {
            ficheiro << TAG_PARTICULAR << " " << particular << endl;
        }
    }
    
    ficheiro << TAG_CUSTO_PARTICULAR << " " << SiteParticular::getCustoPorPagina() << endl;
    
    ficheiro << TAG_CUSTO_EMPRESA << " " << SiteEmpresa::getCustoPorPagina() << endl;
    
    ficheiro << TAG_LIMITE << " " << SiteParticular::getLimitePaginas() << endl;
    
    
    ficheiro.close();
    return true;

}


bool Menu::leDados(){
    /*
     Formatacao exemplo dos dados
     
     **Utilizador** Pedro 12345
     **Utilizador** Ze 123
     **SiteParticular** www.blog.com 10 Ruby Pedro | 12345
     **SiteEmpresa** www.google.com 100 2 c++ java 2 Pedro | 12345 Ze | 123
     **CUSTOPARTICULAR_PREDEFINIDO** 10
     **CUSTOEMPRESA_PREDEFINIDO** 100
     **LIMITEPAGINAS_PREDEFINIDO** 50
     */
    
    ifstream ficheiro;
    ficheiro.open (FICHEIRO);
    string str;
    
    if(!ficheiro.good())
    {
        cout << "Ficheiro de dados nao existe. Foi criado " << FICHEIRO << "." << endl;
        return false;
    }
    
    // Primeiro temos de ter o vector de gestores completo
    // So assim podemos criar sites com apontadores para gestores
    while (ficheiro.good() )
    {
        if (ficheiro.good() && str == TAG_UTILIZADOR) {
            string nome;
            string str; // string auxiliar para o nome
            unsigned int numero;
            ficheiro >> nome;
            ficheiro >> str;
            while (str != FIM_DE_NOME) {
                nome += " ";
                nome += str;
                ficheiro >> str;
            }
            ficheiro >> numero;
            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
            wsp->adicionaGestor(new Utilizador(numero,nome));
        }
        
        if (ficheiro.good() && str == TAG_CUSTO_PARTICULAR) {
            float preco;
            ficheiro >> preco;
            SiteParticular::setCustoPorPagina(preco);
            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if (ficheiro.good() && str == TAG_CUSTO_EMPRESA) {
            float preco;
            ficheiro >> preco;
            SiteEmpresa::setCustoPorPagina(preco);
            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if (ficheiro.good() && str == TAG_LIMITE) {
            unsigned int limite;
            ficheiro >> limite;
            SiteParticular::setLimitePaginas(limite);
            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        ficheiro >> str;
    }
    
    ficheiro.close();
    // de volta ao inicio do ficheiro, agora vamos criar os websites,
    // pois ja temos acesso aos apontadores dos gestores
    ficheiro.open(FICHEIRO);
    while (ficheiro.good() )
    {
        if (ficheiro.good() && str == TAG_PARTICULAR) {
            string identificador;
            unsigned int numeroPaginas;
            string tecnologia;
            string nomeGestor;
            string str = ""; // string auxiliar para o nome do gestor
            unsigned int numeroGestor;
            ficheiro >> identificador;
            ficheiro >> numeroPaginas;
            ficheiro >> tecnologia;
            ficheiro >> nomeGestor;
            ficheiro >> str;
            while (str != FIM_DE_NOME) {
                nomeGestor += " ";
                nomeGestor += str;
                ficheiro >> str;
            }
            ficheiro >> numeroGestor;
            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
            Utilizador* gestor = wsp->getGestorPointer(Utilizador(numeroGestor, nomeGestor));
            if (gestor != NULL) {
                Website* site = new SiteParticular(identificador, numeroPaginas, tecnologia, gestor);
                wsp->novoSite(site);
            }
        }
        
        if (ficheiro.good() && str == TAG_EMPRESA) {
            string identificador;
            unsigned int numeroPaginas;
            unsigned int numTecnologias;
            string tecnologia;
            vector<string> tecnologias;
            unsigned int numGestores;
            string nomeGestor;
            string str = ""; // string auxiliar para o nome do gestor
            unsigned int numeroGestor;
            Utilizador* gestor;
            vector<Utilizador*> gestores;
            ficheiro >> identificador;
            ficheiro >> numeroPaginas;
            ficheiro >> numTecnologias;
            unsigned int counter;
            for (counter = 1; counter <= numTecnologias; counter++) {
                ficheiro >> tecnologia;
                tecnologias.push_back(tecnologia);
            }
            ficheiro >> numGestores;
            for (counter = 1; counter <= numGestores; counter++) {
                ficheiro >> nomeGestor;
                ficheiro >> str;
                while (str != FIM_DE_NOME) {
                    nomeGestor += " ";
                    nomeGestor += str;
                    ficheiro >> str;
                }
                ficheiro >> numeroGestor;
                gestor = wsp->getGestorPointer(Utilizador(numeroGestor, nomeGestor));
                if (gestor != NULL){
                    gestores.push_back(gestor);
                }
            }
            
            Website* site = new SiteEmpresa(identificador, numeroPaginas, tecnologias, gestores);
            wsp->novoSite(site);

            ficheiro.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        ficheiro >> str;
    }

    ficheiro.close();
    
    cout << "Ficheiro de texto encontrado e lido com sucesso!" << endl;
    
    return true;
}

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return escolha;
}
/* // PRECISO DO OPERADOR << PARA GRAVAR AS INFOS
template<class T>
T Menu::escolhe(vector<T> & escolhas, const string & perg){
    unsigned int i = 1;
    cout << perg << endl;
    for (typename vector<T>::iterator opcao = escolhas.begin(); opcao != escolhas.end() ; opcao++, i++) {
        // cout << i << " - " << *opcao << endl;
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
 */

Website* Menu::escolhe(vector<Website*> & escolhas, const string & perg){
    unsigned int i = 1;
    if (escolhas.size() == 0) {
        cout << "Nao existem websites na base de dados!" << endl;
        return NULL;
    }
    cout << perg << endl;
    for (vector<Website*>::iterator site_it = escolhas.begin(); site_it != escolhas.end() ; site_it++, i++) {
            cout << i << " - " << (*site_it)->getIdentificador() << endl;
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
    Website* escolha;
    if (numero_escolha == 0) {
        escolha = NULL;
    } else{
        escolha = escolhas.at(numero_escolha-1);
    }
    return escolha;
}

Utilizador* Menu::escolhe(vector<Utilizador*> & escolhas, const string & perg){
    unsigned int i = 1;
    if (escolhas.size() == 0) {
        cout << "Nao existem utilizadores na base de dados!" << endl;
        return NULL;
    }
    cout << perg << endl;
    for (vector<Utilizador*>::iterator gestor_it = escolhas.begin(); gestor_it != escolhas.end() ; gestor_it++, i++) {
        cout << i << " - " << setw(ESPACO_PEQUENO) << (*gestor_it)->getNome() << setw(ESPACO_PEQUENO) << (*gestor_it)->getNumIdentidade() << endl;

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
    Utilizador* escolha;
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
    Utilizador* u_pointer = new Utilizador(numIdentidade, nome);
    wsp->adicionaGestor(u_pointer);
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
            Utilizador* gestor = NULL;
            
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
            string nome;
            if (site->getGestor() == NULL) {
            }
            
            // imprimir informacoes do site
            cout << "Informacoes do website particular " << site->getIdentificador() << endl;
            
            if (site->getTecnologia() == "") {
                cout << "Este site nao usa uma tecnologia!" << endl;
            } else {
                cout << "Tecnologia utilizada: " << site->getTecnologia() << endl;
            }
            
            if (site->getGestor() == NULL) {
                cout << "Este website nao tem gestor!" << endl;
            } else {
                cout << "Gestor: " << site->getGestor()->getNome() << " (BI n. " << site->getGestor()->getNumIdentidade() << ")" << endl;
            }
            
            cout << "Numero de paginas: " << site->getNumeroPaginas() << " (max. " << SiteParticular::getLimitePaginas() << " / custo por pagina: " << SiteParticular::getCustoPorPagina() << ")" << endl;
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
            
            if (site->getTecnologias().size() == 0) {
                cout << "Este site nao utiliza qualquer tecnologia!" << endl;
            } else {
                cout << "Tecnologias utilizadas: ";
                for (vector<string>::iterator tecnologia = site->getTecnologias().begin(); tecnologia != site->getTecnologias().end(); tecnologia++) {
                    if (tecnologia == site->getTecnologias().end()-1) {
                        cout << *tecnologia << "." << endl;
                    } else
                        cout << *tecnologia << ", ";
                }
            }
            
            if (site->getGestores().size() == 0) {
                cout << "Este site nao tem gestores!" << endl;
            } else {
                cout << "Gestores: ";
                for (vector<Utilizador*>::iterator gestor = site->getGestores().begin(); gestor != site->getGestores().end() ; gestor++)
                {
                    if (gestor == site->getGestores().end()-1 )
                    {
                        cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << ")." << endl;
                    } else
                        cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << "), ";
                }
            }
            
            cout << "Numero de paginas: " << site->getNumeroPaginas() << " (custo por pagina: " << SiteEmpresa::getCustoPorPagina() << ")" << endl;
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
                         // NEED FIX!!
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
                        site->retiraTecnologia(site->getTecnologias().at(tech_pos-1));
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

void Menu::opcoes(Utilizador* gestor){
    bool acabado = false;
    while (!acabado)
    {
        cout << "Nome do utilizador: " << gestor->getNome() << endl;
        cout << "Numero de identidade: " << gestor->getNumIdentidade() << endl;
        cout << "Sites responsavel: ";
        for (vector<Website*>::const_iterator site_it = gestor->getSitesResponsavel().begin(); site_it != gestor->getSitesResponsavel().end() ; site_it++) {
            if (site_it == gestor->getSitesResponsavel().end()-1) {
                cout << (*site_it)->getIdentificador() << "." << endl;
            } else
                cout << (*site_it)->getIdentificador() << ", ";
        }
        switch (escolhe(opcoes_utilizador, "Selecione uma opcao")) {
            case 0:
                acabado = true;
                break;
            case 1: // Alterar o nome do utilizador
            {
                string nome = pergunta<string>("Selecione um novo nome de utilizador");
                gestor->setNome(nome);
                break;
            }
            case 2: // Alterar o numero do BI
            {
                unsigned int numero = pergunta<unsigned int>("Selecione um novo numero de bilhete de identidade");
                gestor->setNumIdentidade(numero);
                break;
            }
            case 3: // Aceder a um website responsavel
            {
                vector<Website*> sites = gestor->getSitesResponsavel();
                opcoes(escolhe(sites, "Escolha o website a que quer aceder"));
                cout << "A regressar para o utilizador..." << endl;
                break;
            }
            case 4:
                wsp->eliminaCliente(gestor);
                return;
                break;
            default:
                break;
        }
        
    }
    
    return;
}


void Menu::listar_websites(){
    if (wsp->getWebsites().size() == 0) {
        cout << "Nao existem websites na base de dados! Por favor crie um website primeiro." << endl;
        return;
    }
    cout << left << setw(ESPACO_MUITO_PEQUENO) << "Numero" << setw(ESPACO_PEQUENO) << "Tipo" << setw(ESPACO_LISTAGEM) << "Identificador" << setw(ESPACO_LISTAGEM) << "Gestor(es)" << setw(ESPACO_LISTAGEM) << "Tecnologia(s)" << setw(ESPACO_PEQUENO) << "Paginas" << endl;
    unsigned int numero = 1;
    for (vector<Website*>::iterator site_it = wsp->getWebsites().begin(); site_it != wsp->getWebsites().end(); site_it++, numero++) {
        Website* site = *site_it;
        SiteEmpresa* empresa = dynamic_cast< SiteEmpresa* >(site);
        SiteParticular* particular = dynamic_cast< SiteParticular* >(site);
        
        if (particular){// como listar as informacoes se o site for particular
            string nome;
            if (site->getGestor() == NULL) { // verificar se existe gestor
                nome = "Nenhum";
            } else {
                nome = site->getGestor()->getNome();
            }
            
            cout << left << setw(ESPACO_MUITO_PEQUENO) << numero << setw(ESPACO_PEQUENO) <<  "Particular" << setw(ESPACO_LISTAGEM)<< site->getIdentificador() << setw(ESPACO_LISTAGEM) << nome << setw(ESPACO_LISTAGEM) << site->getTecnologia() << setw(ESPACO_LISTAGEM) << site->getNumeroPaginas() << endl;
        } 
        if (empresa){ // como listar as informacoes se o site for de uma empresa
            stringstream gestores;
            if (site->getGestores().size() == 0) {
                gestores << "Nenhum";
            } else if (site->getGestores().size() == 1) {
                gestores << site->getGestores()[0]->getNome();
            } else {
                gestores << site->getGestores()[0]->getNome() << " e mais " << site->getGestores().size()-1;
            }
            stringstream tecnologias;
            if (site->getTecnologias().size() == 0) {
                tecnologias << "Nenhuma";
            } else if (site->getTecnologias().size() == 1) {
                tecnologias << site->getTecnologias()[0];
            } else {
                tecnologias << site->getTecnologias()[0] << " e mais " << site->getTecnologias().size()-1;

            }
            cout << left << setw(ESPACO_MUITO_PEQUENO) << numero << setw(ESPACO_PEQUENO) << "Empresa" << setw(ESPACO_LISTAGEM) << site->getIdentificador() << setw(ESPACO_LISTAGEM) << gestores.str() << setw(ESPACO_LISTAGEM) << tecnologias.str() << setw(ESPACO_PEQUENO) << site->getNumeroPaginas() << endl;
        }
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
    if (wsp->getGestores().size() == 0) {
        cout << "Nao existem utilizadores na base de dados! Por favor crie um utilizador primeiro." << endl;
        return;
    }
    
    cout << left << setw(ESPACO_MUITO_PEQUENO) << "Numero" << setw(ESPACO_LISTAGEM) << "Nome" << setw(ESPACO_PEQUENO) << "Numero de B.I." << endl;
    unsigned int numero = 1;
    for (vector<Utilizador*>::iterator gestor_it = wsp->getGestores().begin(); gestor_it != wsp->getGestores().end(); gestor_it++, numero++)
    {
        cout << left << setw(ESPACO_MUITO_PEQUENO) << numero << setw(ESPACO_LISTAGEM) << (*gestor_it)->getNome() << setw(ESPACO_PEQUENO) << (*gestor_it)->getNumIdentidade() << endl;
    }
    Utilizador* gestor = NULL;
    gestor = escolheSemListagem(wsp->getGestores(), "Escolha um gestor para aceder as informacoes");
    if (gestor == NULL){ // se o utilizador cancelou, volta para o menu anterior
        return;
    } else{
        opcoes(gestor);
    }
    
    return;
}

int Menu::inicio(){
    switch (escolhe(opcoes_inicio, "Selecione uma opcao")) {
        case 0: // Terminar aplicacao
            return 1;
            break;
        case 1: // Criar website
            criar_website();
            return 0;
            break;
        case 2: // Criar um novo utilizador
            criar_utilizador();
            return 0;
            break;
        case 3: // listar todos os websites
            listar_websites();
            return 0;
            break;
        case 4: // listar todos os utilizadores
            listar_utilizadores();
            return 0;
            break;
        case 5: // ordenar websites
            wsp->ordenaWebsitesAlfabetico();
            listar_websites();
            break;
            
        default:
            return 0;
            break;
    }
    return 0;
}

Menu::Menu(){
    opcoes_inicio.push_back("Criar website");
    opcoes_inicio.push_back("Criar utilizador");
    opcoes_inicio.push_back("Listar websites");
    opcoes_inicio.push_back("Listar utilizadores");
    opcoes_inicio.push_back("Ordernar websites");
    //opcoes_inicio.push_back("Ordenar utilizadores");
    
    
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
    
    opcoes_utilizador.push_back("Alterar nome");
    opcoes_utilizador.push_back("Alterar numero do bilhete de identidade");
    opcoes_utilizador.push_back("Aceder a um wesite responsavel");
    opcoes_utilizador.push_back("Eliminar utilizador");
    
    wsp = new GestorWSP();
    cout << "Bem vindo ao gestor de website provider!" << endl << "NOTA: escolher 0 cancela a opcao e regressa para o menu anterior (quando possivel)" << endl;
    leDados();
    while (inicio() != 1) {
        guardaDados();
    }
    cout << "A terminar aplicacao..." << endl;
}
