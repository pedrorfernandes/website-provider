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

ostream & operator<<(ostream &os, Utilizador* u){
    os << u->getNome() << FIM_DE_STRING_OUTPUT << u->getNumIdentidade();
    return os;
}

ostream & operator<<(ostream &out, Website* site){
    if (site->getTipo() == Website::empresa) {
        out << site->getIdentificador() << " " << site->getNumeroPaginas() << " ";
        out << site->getTecnologias().size() << " ";
        for (vector<string>::const_iterator tech_it = site->getTecnologias().begin(); tech_it != site->getTecnologias().end() ; tech_it++) {
            out << (*tech_it) << FIM_DE_STRING_OUTPUT;
        }
        out << site->getGestores().size() << " ";
        for (vector<Utilizador*>::const_iterator gestor_it = site->getGestores().begin(); gestor_it != site->getGestores().end(); gestor_it++) {
            if (gestor_it == site->getGestores().end()-1) {
                out << (*gestor_it);
            } else
                out << (*gestor_it) << " ";
        }
        return out;
    } else if (site->getTipo() == Website::particular){
        out << site->getIdentificador() << " " << site->getNumeroPaginas() << " " << site->getTecnologia() << FIM_DE_STRING_OUTPUT << site->getGestor();
        return out;
    } else {
        out << site->identificador;
        return out;
    }
}


ostream & operator<<(ostream &out, Prototipo p){
    out.setf(ios::fixed);
    out << p.tipo << FIM_DE_STRING_OUTPUT
        << setprecision(CENTIMOS) << p.custo << " "
        << p.horas << " "
        << p.tecnologias.size() << " ";
    for (list<string>::const_iterator it = p.tecnologias.begin() ; it != p.tecnologias.end() ; it++) {
        out << (*it) << FIM_DE_STRING_OUTPUT;
    }
    return out;
}

ostream & operator<<(ostream &out, Catalogo c){
    BSTItrIn<Prototipo*> it(c.prototipos);
    while (!it.isAtEnd()){
        out << TAG_PROTOTIPO << " " << (*it.retrieve()) << endl;
        it.advance();
    }
    return out;
}


bool Menu::guardaDados(){
    /*
     Formatacao exemplo dos dados
     
     *UTILIZADOR* Pedro | 12345
     *UTILIZADOR* Ze | 123
     *SITEPARTICULAR* www.blog.com 10 Ruby | Pedro | 12345
     *SITEEMPRESA* www.google.com 100 2 c++ | java | 2 Pedro | 12345 Ze | 123
     *PROTOTIPO* Faculdade | 100.00 20 2 Python | Ruby |
     *CUSTOPARTICULAR_PREDEFINIDO* 10
     *CUSTOEMPRESA_PREDEFINIDO* 100
     *LIMITEPAGINAS_PREDEFINIDO* 50
     */
    
    ofstream ficheiro;
    ficheiro.open(FICHEIRO);
    
    for (vector<Utilizador*>::const_iterator gestor_it = wsp->getGestores().begin(); gestor_it != wsp->getGestores().end() ; gestor_it++) {
        ficheiro << TAG_UTILIZADOR << " " << (*gestor_it) << endl;
    }
    
    for (vector<Website*>::const_iterator site_it = wsp->getWebsites().begin(); site_it != wsp->getWebsites().end(); site_it++) {
        if ((*site_it)->getTipo() == Website::empresa){
            ficheiro << TAG_EMPRESA << " " << (*site_it) << endl;
        }
        if ((*site_it)->getTipo() == Website::particular) {
            ficheiro << TAG_PARTICULAR << " " << (*site_it) << endl;
        }
    }
    ficheiro.setf(ios::fixed);
    
    ficheiro << wsp->getCatalogo();
    
    ficheiro << TAG_CUSTO_PARTICULAR << " " << setprecision(CENTIMOS) << SiteParticular::getCustoPorPagina() << endl;
    
    ficheiro << TAG_CUSTO_EMPRESA << " " << setprecision(CENTIMOS) << SiteEmpresa::getCustoPorPagina() << endl;
    
    ficheiro << TAG_LIMITE << " " << setprecision(CENTIMOS) << SiteParticular::getLimitePaginas() << endl;
    
    
    ficheiro.close();
    return true;

}


bool Menu::leDados(){
    /*
     Formatacao exemplo dos dados
     
     *UTILIZADOR* Pedro | 12345
     *UTILIZADOR* Ze | 123
     *SITEPARTICULAR* www.blog.com 10 Ruby | Pedro | 12345
     *SITEEMPRESA* www.google.com 100 2 c++ | java | 2 Pedro | 12345 Ze | 123
     *PROTOTIPO* Faculdade | 100.00 20 2 Python | Ruby |
     *CUSTOPARTICULAR_PREDEFINIDO* 10
     *CUSTOEMPRESA_PREDEFINIDO* 100
     *LIMITEPAGINAS_PREDEFINIDO* 50
     
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
            while (str != FIM_DE_STRING) {
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
            string str = ""; // string auxiliar
            unsigned int numeroGestor;
            ficheiro >> identificador;
            ficheiro >> numeroPaginas;
            ficheiro >> tecnologia;
            ficheiro >> str;
            while (str != FIM_DE_STRING) {
                tecnologia += " ";
                tecnologia += str;
                ficheiro >> str;
            }
            ficheiro >> nomeGestor;
            ficheiro >> str;
            while (str != FIM_DE_STRING) {
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
            string str = ""; // string auxiliar
            unsigned int numeroGestor;
            Utilizador* gestor;
            vector<Utilizador*> gestores;
            //*SiteEmpresa* www.google.com 100 2 c++ | java | 2 Pedro | 12345 Ze | 123
            ficheiro >> identificador;
            ficheiro >> numeroPaginas;
            ficheiro >> numTecnologias;
            unsigned int counter;
            for (counter = 1; counter <= numTecnologias; counter++) {
                ficheiro >> tecnologia;
                ficheiro >> str;
                while (str != FIM_DE_STRING) {
                    tecnologia += " ";
                    tecnologia += str;
                    ficheiro >> str;
                }
                tecnologias.push_back(tecnologia);
            }
            ficheiro >> numGestores;
            for (counter = 1; counter <= numGestores; counter++) {
                ficheiro >> nomeGestor;
                ficheiro >> str;
                while (str != FIM_DE_STRING) {
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
        
        if (ficheiro.good() && str == TAG_PROTOTIPO) {
            // *PROTOTIPO* Faculdade | 100.00 20 2 Python | Ruby |
            string tipo;
            float custo;
            unsigned int horas;
            list<string> tecnologias;
            string tecnologia;
            int numTecnologias;
            ficheiro >> tipo;
            ficheiro >> str;
            while (str != FIM_DE_STRING) {
                tipo += " ";
                tipo += str;
                ficheiro >> str;
            }
            ficheiro >> custo;
            ficheiro >> horas;
            ficheiro >> numTecnologias;
            unsigned int counter;
            for (counter = 1; counter <= numTecnologias; counter++) {
                ficheiro >> tecnologia;
                ficheiro >> str;
                while (str != FIM_DE_STRING) {
                    tecnologia += " ";
                    tecnologia += str;
                    ficheiro >> str;
                }
                tecnologias.push_back(tecnologia);
            }
            Prototipo* p = new Prototipo (tipo, custo, horas, tecnologias);
            wsp->getCatalogo().adicionar(p);
        }
        
        ficheiro >> str;
    }

    ficheiro.close();
    
    cout << "Ficheiro de texto encontrado e lido com sucesso!" << endl;
    
    return true;
}

unsigned int Menu::escolhe(const vector<string> & escolhas, const string &perg){
    unsigned int i = 0;
    cout << perg << endl;
    for (vector<string>::const_iterator opcao = escolhas.begin(); opcao != escolhas.end() ; opcao++, i++) {
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

Website* Menu::escolhe(const vector<Website*> & escolhas, const string & perg){
    unsigned long i = escolhas.size();
    if (escolhas.size() == 0) {
        cout << "Nao existem websites na base de dados!" << endl;
        return NULL;
    }
    cout << perg << endl;
    // Codigo igual ao da funcao listar_websites() ------------------
    cout << left
    << setw(ESPACO_MUITO_PEQUENO) << "Numero"
    << setw(ESPACO_PEQUENO) << "Tipo"
    << setw(ESPACO_LISTAGEM) << "Identificador"
    << setw(ESPACO_LISTAGEM) << "Gestor(es)"
    << setw(ESPACO_LISTAGEM) << "Tecnologia(s)"
    << setw(ESPACO_PEQUENO) << "Paginas"
    << setw(ESPACO_LISTAGEM) << "Custo" << endl;
    unsigned int numero = 1;
    for (vector<Website*>::const_iterator site_it = escolhas.begin(); site_it != escolhas.end(); site_it++, numero++) {
        Website* site = *site_it;

        // seguranca para um numero exagerado de websites no vector
        if (numero > MAX_ELEMENTOS_LISTAGEM) {
            cout << "Foram listados " << MAX_ELEMENTOS_LISTAGEM << " websites, mas existem " << escolhas.size() << " nesta listagem." << endl;
            cout << "Se pretende encontrar um website, por favor utilize a pesquisa." << endl;
            break;
        }
        
        if ((*site_it)->getTipo() == Website::particular){// como listar as informacoes se o site for particular
            string nome;
            if (site->getGestor() == NULL) { // verificar se existe gestor
                nome = "Nenhum";
            } else {
                nome = site->getGestor()->getNome();
            }
            cout.setf(ios::fixed);
            cout << left
            << setw(ESPACO_MUITO_PEQUENO) << numero
            << setw(ESPACO_PEQUENO) <<  "Particular"
            << setw(ESPACO_LISTAGEM)<< site->getIdentificador()
            << setw(ESPACO_LISTAGEM) << nome
            << setw(ESPACO_LISTAGEM) << site->getTecnologia()
            << setw(ESPACO_PEQUENO) << site->getNumeroPaginas()
            << "$" << setw(ESPACO_LISTAGEM) << setprecision(CENTIMOS) << site->getCusto() << endl;
        }
        if ((*site_it)->getTipo() == Website::empresa){ // como listar as informacoes se o site for de uma empresa
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
            cout.setf(ios::fixed);
            cout << left
            << setw(ESPACO_MUITO_PEQUENO) << numero
            << setw(ESPACO_PEQUENO) << "Empresa"
            << setw(ESPACO_LISTAGEM) << site->getIdentificador()
            << setw(ESPACO_LISTAGEM) << gestores.str()
            << setw(ESPACO_LISTAGEM) << tecnologias.str()
            << setw(ESPACO_PEQUENO) << site->getNumeroPaginas()
            << "$" << setw(ESPACO_LISTAGEM) << setprecision(CENTIMOS) << site->getCusto() << endl;
        }
    }

    //---------------------------------------------------
    unsigned int numero_escolha;
    cout << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

Utilizador* Menu::escolhe(const vector<Utilizador*> & escolhas, const string & perg){
    unsigned int i = 1;
    if (escolhas.size() == 0) {
        cout << "Nao existem utilizadores na base de dados!" << endl;
        return NULL;
    }
    cout << perg << endl;
    for (vector<Utilizador*>::const_iterator gestor_it = escolhas.begin(); gestor_it != escolhas.end() ; gestor_it++, i++) {
        // seguranca para um numero exagerado de utilizadores no vector
        if (i > MAX_ELEMENTOS_LISTAGEM) {
            cout << "Foram listados " << MAX_ELEMENTOS_LISTAGEM << " utilizadores, mas existem " << escolhas.size() << " nesta listagem." << endl;
            cout << "Se pretende encontrar um website, por favor utilize a pesquisa." << endl;
            break;
        }
        
        cout << i << " - "
        << setw(ESPACO_PEQUENO) << (*gestor_it)->getNome()
        << setw(ESPACO_PEQUENO) << (*gestor_it)->getNumIdentidade() << endl;

    }
    i--;
    unsigned int numero_escolha;
    cout << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
T Menu::escolheSemListagem(const vector<T> & escolhas, const string & perg){
    unsigned long i = escolhas.size();
    cout << perg << endl;
    unsigned int numero_escolha;
    cout << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > i ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << i << "." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        if (string::npos != str.find("*")){
            cout << "Nao e' permitido o uso de asteriscos (*). Tente novamente" << endl << PROMPT;
            str = "";
        } else if (str == "")
            cout << PROMPT;
    }
    return str;
}

// especializacao para evitar overflows (windows nao deteta cin.fail e faz overflow)
template<>
unsigned int pergunta(const string &perg){
    cout << perg << endl << PROMPT;
    int resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || resposta < 0 ) {
        cout << "Resposta invalida. Tente outra vez." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    unsigned int resposta_unsigned = resposta;
    return resposta_unsigned;
}

inline void Menu::pressEnter(){
    cout << "Pressione ENTER para continuar..." << endl;
    getchar();
    return;
}


Utilizador* Menu::criar_utilizador(){
    string nome;
    unsigned int numIdentidade = 1;
    bool ok = false;
    Utilizador* u_pointer = NULL;
    while (!ok) {
        
        nome = pergunta<string>("Escolha o nome do utilizador (Introduza 0 para cancelar)");
        if (nome == "0") {
            cout << "Operacao cancelada." << endl;
            pressEnter();
            break;
        }
        numIdentidade = pergunta<unsigned int>("Indique o numero do bilhete de identidade, com 8 digitos (Introduza 0 para cancelar)");
        while (numIdentidade <= 10000000 || numIdentidade >= 99999999) {
            if (numIdentidade == 0) {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return u_pointer;
            }
            numIdentidade = pergunta<unsigned int>("Numero invalido.\nPor favor indique um numero com 8 digitos (Introduza 0 para cancelar)");
        }
        u_pointer = new Utilizador(numIdentidade, nome);
        try {
            wsp->adicionaGestor(u_pointer);
            ok = true;
        } catch (UtilizadorJaExistente &e) {
            cout << "O utilizador com B.I. " << e.getMsg() << " ja existe. Por favor selecione um novo." << endl;
        }
    }
    return u_pointer;
}

Website* Menu::criar_website(){
    string identificador;
    unsigned int numeroPaginas;
    Website* site = NULL;
    bool ok = false;
    
    switch (escolhe(escolher_tipo_site, "Que tipo de website pretende criar?") ) {
        case 0:
            // voltar para tras
            break;
        case 1: // site particular
        {
            string tecnologia;
            Utilizador* gestor = NULL;
    
            identificador = pergunta<string>("Escolha um identificador (URL) para o website (Introduza 0 para cancelar)");
            if (identificador == "0") {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return site;
            }
            while (!wsp->identificadorValido(identificador)) {
                identificador = pergunta<string>("Esse identificador ja pertence a outro website.\nPor favor escolha um identificador diferente");
            }
            
            tecnologia = pergunta<string>("Escolha a tecnologia que vai ser utilizada para o website (Introduza 0 para cancelar");
            
            if (tecnologia == "0") {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return site;
            }
            
            // escolher se quer criar um novo gestor ou escolher um do vector
            while (gestor == NULL) {
                switch (escolhe(escolher_utilizador, "Defina como quer escolher o gestor")) {
                    case 0: // utilizador cancelou
                        cout << "Todos os websites devem ter um gestor." << endl << "Criacao de website cancelada" << endl;
                        return NULL;
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
            
            numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas (0 para cancelar)");
            if (numeroPaginas == 0) {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return site;
            } 
            
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
            
            // Perguntar o identificador
            identificador = pergunta<string>("Escolha um identificador (URL) para o website (Introduza 0 para cancelar)");
            if (identificador == "0") {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return site;
            }
            while (!wsp->identificadorValido(identificador)) {
                identificador = pergunta<string>("Esse identificador ja pertence a outro website.\nPor favor escolha um identificador diferente");
            }
            
            // Perguntar o numero de paginas
            numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas (0 para cancelar)");
            if (numeroPaginas == 0) {
                cout << "Operacao cancelada." << endl;
                pressEnter();
                return site;
            }
            
            // Perguntar as tecnologias
            bool acabado = false;
            while (!acabado) {
                if (tecnologias.size() > 0) { // escrever que tecnologias ja foram selecionadas
                    cout << "Tecnologias ja adicionadas: ";
                    for (vector<string>::const_iterator tech_it = tecnologias.begin(); tech_it != tecnologias.end(); tech_it++) {
                        if (tech_it == tecnologias.end()-1) {
                            cout << (*tech_it) << "." << endl;
                        } else
                            cout << (*tech_it) << ", ";
                    }
                } else if (tecnologias.size() == 0) // escolher a primeira tecnologia
                    tecnologias.push_back(pergunta<string>("Indique o nome da primeira tecnologia"));
                // comecar o loop da escolha de tecnologias seguintes
                switch (escolhe(escolher_tecnologias, "Escolha uma opcao")) {
                    case 0: // terminar a escolha das tecnologias
                        if (tecnologias.size() > 0) {
                            acabado = true;
                        } else
                            cout << "O website deve ter no minimo uma tecnologia!" << endl;
                        break;
                    case 1: // adicionar tecnologia
                        tecnologias.push_back(pergunta<string>("Indique o nome da tecnologia"));
                        break;
                    default:
                        break;
                }
            }
            
            // Perguntar quem sao os gestores
            cout << "Agora deve escolher quais sao os gestores do seu website empresa" << endl;
            acabado = false;
            while (!acabado) {
                if (gestores.size() > 0) {
                    cout << "Gestores ja adicionados: ";
                    for (vector<Utilizador*>::const_iterator gestor_it = gestores.begin(); gestor_it != gestores.end(); gestor_it++) {
                        if (gestor_it == gestores.end()-1) {
                            cout << (*gestor_it)->getNome() << "." << endl;
                        } else
                            cout << (*gestor_it)->getNome() << ", ";
                    }
                }
                switch (escolhe(gestores_empresa, "Defina como quer escolher um gestor")) {
                    case 0: // utilizador cancelou
                        if (gestores.size() > 0) {
                            acabado = true;
                            break;
                        } else
                            cout << "Todos os websites devem ter no minimo um gestor!" << endl;
                        break;
                    case 1: // criar um novo utilizador
                    {
                        Utilizador* novo_gestor = criar_utilizador();
                        if (novo_gestor != NULL) {
                            gestores.push_back(novo_gestor);
                        }
                        break;
                    }
                    case 2: // escolher utilizador ja existente
                    {
                        Utilizador* gestor = NULL;
                        gestor = escolhe(wsp->getGestores(), "Escolha um gestor");
                        if (gestor == NULL){
                            break;
                        } else
                            gestores.push_back(gestor);
                        break;
                    }
                    default:
                        break;
                }
            }
            while (!ok) {
                try {
                    wsp->novoSite(site = new SiteEmpresa(identificador, numeroPaginas, tecnologias, gestores));
                    ok = true;
                } catch (...) {
                    cout << "Erro. Nao foi possivel adicionar o website empresa." << endl;
                    break;
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
    
    if (site->getTipo() == Website::particular)
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
            cout.setf(ios::fixed);
            cout << "Numero de paginas: " << site->getNumeroPaginas() << " (max. " << SiteParticular::getLimitePaginas() << " / custo por pagina: " << setprecision(CENTIMOS) << SiteParticular::getCustoPorPagina() << " $)" << endl;
            cout << "Custo total do site: " << setprecision(CENTIMOS) << site->getCusto() << " $" <<  endl;
            
            // definir escolhas para alteracoes
            switch (escolhe(opcoes_website_particular, "Selecione uma opcao"))
            {
                case 0: // utilizador acaba alteracoes
                    acabado = true;
                    break;
                case 1: // alterar o gestor
                    switch (escolhe(escolher_utilizador, "Defina como quer escolher o novo gestor para o site"))
                {
                    case 0: // utilizador cancelou
                        break;
                    case 1: // criar um novo utilizador
                    {
                        Utilizador* novo_gestor = criar_utilizador();
                        if (novo_gestor != NULL) {
                            site->setGestor(novo_gestor);
                        }
                        break;
                    }
                    case 2: // escolher um gestor ja existente
                    {
                        Utilizador* gestor = escolhe(wsp->getGestores(), "Escolha um gestor");
                        if (gestor == NULL) {
                            break;
                        } else
                            site->setGestor(gestor);
                    }
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
    
    if (site->getTipo() == Website::empresa)
    {
        bool acabado = false;
        while (!acabado)
        {
            // imprimir informacoes do website
            cout << "Informacoes do website empresa " << site->getIdentificador() << endl;
            
            if (site->getTecnologias().size() == 0) {
                cout << "Este site nao utiliza qualquer tecnologia!" << endl;
            } else {
                cout << "Tecnologias utilizadas: ";
                for (vector<string>::const_iterator tecnologia = site->getTecnologias().begin(); tecnologia != site->getTecnologias().end(); tecnologia++) {
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
                for (vector<Utilizador*>::const_iterator gestor = site->getGestores().begin(); gestor != site->getGestores().end() ; gestor++)
                {
                    if (gestor == site->getGestores().end()-1 )
                    {
                        cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << ")." << endl;
                    } else
                        cout << (*gestor)->getNome() << " (BI n. " << (*gestor)->getNumIdentidade() << "), ";
                }
            }
            cout.setf(ios::fixed);
            cout << "Numero de paginas: " << site->getNumeroPaginas() << " (custo por pagina: " << setprecision(CENTIMOS) << SiteEmpresa::getCustoPorPagina() << " $)" << endl;
            cout << "Custo total do site: " << setprecision(CENTIMOS)<< site->getCusto() << " $" <<  endl;
            
            // as escolhas para o utilizador fazer alteracoes
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
                    {
                        Utilizador* novo_gestor = criar_utilizador();
                        if (novo_gestor != NULL) {
                            site->novoGestor(novo_gestor);
                        }
                        break;
                    }
                    case 2: // escolher um gestor ja existente que nao pertence ao website
                    {
                        vector<Utilizador*> gestores_que_nao_estao_no_site = wsp->getGestores() - site->getGestores();
                        Utilizador* gestor = escolhe(gestores_que_nao_estao_no_site, "Escolha um gestor");
                        if (gestor == NULL) {
                            break;
                        } else
                            site->novoGestor(gestor);
                        break;
                    }
                    default:
                        break;
                }
                    break;
                    
                case 2: // Retirar gestor
                    if (site->getGestores().size() == 1) {
                        cout << "O site so possui um gestor. Este nao pode ser eliminado." << endl;
                        pressEnter();
                        break;
                    }
                    site->retiraGestor(escolhe(site->getGestores(), "Escolha que gestor pretende retirar"));
                    break;
                case 3: // Adicionar tecnologia
                {
                    while (true) {
                        string tecnologia = pergunta<string>("Escolhe uma nova tecnologia para o website (para cancelar, introduza 0)");
                        if (tecnologia == "0") // utilizador cancelou
                            break;
                        else if ( site->novaTecnologia(tecnologia) )
                            break;
                        else {
                            cout << "A tecnologia ja se encontra implementada no website" << endl;
                            pressEnter();
                        }
                    }
                    break;
                }
                case 4: // Retirar tecnologia
                {
                    if (site->getTecnologias().size() == 1) {
                        cout << "O site so utiliza uma tecnologia. Esta nao pode ser eliminada." << endl;
                        pressEnter();
                        break;
                    }
                    // e' necessario utilizar a funcao escolhe() para permitir cancelar com 0
                    vector<string> tecnologias = site->getTecnologias();
                    cout << "0 - Cancelar"; // maneira simples para informar o utilizador que pode cancelar
                    unsigned int tech_pos = escolhe(tecnologias, "Escolhe que tecnologia pretende remover");
                    if (tech_pos == 0)
                        break;
                    else
                        site->retiraTecnologia(site->getTecnologias().at(tech_pos-1));
                    break;
                }
                case 5: // Alterar numero de paginas
                {
                    unsigned int numeroPaginas = pergunta<unsigned int>("Escolha um numero de paginas (0 para cancelar)");
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
        
        if (gestor->getSitesResponsavel().size() == 0) {
            cout << "Nao e' gestor de nenhum website" << endl;
        } else {
            cout << "Sites responsavel: ";
            for (vector<Website*>::const_iterator site_it = gestor->getSitesResponsavel().begin(); site_it != gestor->getSitesResponsavel().end() ; site_it++) {
                if (site_it == gestor->getSitesResponsavel().end()-1) {
                    cout << (*site_it)->getIdentificador() << "." << endl;
                } else
                    cout << (*site_it)->getIdentificador() << ", ";
            }
        }
        switch (escolhe(opcoes_utilizador, "Selecione uma opcao")) {
            case 0: // cancelar
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
                while (true) {
                    unsigned int numero = pergunta<unsigned int>("Selecione um novo numero de bilhete de identidade");
                    while (numero <= 10000000 || numero >= 99999999) {
                        if (numero == 0) {
                            cout << "Operacao cancelada." << endl;
                            pressEnter();
                            break;
                        }
                        numero = pergunta<unsigned int>("Numero invalido.\nPor favor indique um numero com 8 digitos (Introduza 0 para cancelar)");
                    }
                    if (wsp->numeroIdentidadeValido(numero) ){
                        gestor->setNumIdentidade(numero);
                        break;
                    }
                    cout << "Numero de bilhete de identidade ja existente." << endl;
                }
                break;
            }
            case 3: // Aceder a um website responsavel
            {
                vector<Website*> sites = gestor->getSitesResponsavel();
                if (sites.size() == 0) {
                    cout << "Este utilizador nao e' gestor de qualquer website na base de dados." << endl;
                    pressEnter();
                    break;
                }
                opcoes(escolhe(sites, "Escolha o website a que quer aceder (0 para cancelar)"));
                cout << "A regressar para o utilizador..." << endl;
                break;
            }
            case 4:
                if (!wsp->eliminaCliente(gestor) ){
                    cout << "Existem websites cujo unico gestor e' o que pretende eliminar."<< endl;
                    cout << "Por favor primeiro elimine esses websites ou atribuia-lhes um novo gestor" << endl;
                    pressEnter();
                } else
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
    cout << left
    << setw(ESPACO_MUITO_PEQUENO)<< "Numero"
    << setw(ESPACO_PEQUENO) << "Tipo"
    << setw(ESPACO_LISTAGEM) << "Identificador"
    << setw(ESPACO_LISTAGEM) << "Gestor(es)"
    << setw(ESPACO_LISTAGEM) << "Tecnologia(s)"
    << setw(ESPACO_PEQUENO) << "Paginas"
    << setw(ESPACO_LISTAGEM) << "Custo"
    << endl;
    unsigned int numero = 1;
    for (vector<Website*>::const_iterator site_it = wsp->getWebsites().begin(); site_it != wsp->getWebsites().end(); site_it++, numero++) {
        // seguranca para um numero exagerado de websites no vector
        if (numero > MAX_ELEMENTOS_LISTAGEM) {
            cout << "Foram listados " << MAX_ELEMENTOS_LISTAGEM << " websites, mas existem no total " << wsp->getWebsites().size() << "." << endl;
            cout << "Se pretende encontrar um website, por favor utilize a pesquisa." << endl;
            break;
        }
        
        Website* site = *site_it;
        
        if (site->getTipo() == Website::particular){// como listar as informacoes se o site for particular
            string nome;
            if (site->getGestor() == NULL) { // verificar se existe gestor
                nome = "Nenhum";
            } else {
                nome = site->getGestor()->getNome();
            }
            cout.setf(ios::fixed);
            cout << left
            << setw(ESPACO_MUITO_PEQUENO) << numero
            << setw(ESPACO_PEQUENO) <<  "Particular"
            << setw(ESPACO_LISTAGEM)<< site->getIdentificador()
            << setw(ESPACO_LISTAGEM) << nome
            << setw(ESPACO_LISTAGEM) << site->getTecnologia()
            << setw(ESPACO_PEQUENO) << site->getNumeroPaginas()
            << "$" << setw(ESPACO_LISTAGEM) << setprecision(CENTIMOS) << site->getCusto() << endl;
        } 
        if (site->getTipo() == Website::empresa){ // como listar as informacoes se o site for de uma empresa
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
            cout.setf(ios::fixed);
            cout << left
            << setw(ESPACO_MUITO_PEQUENO) << numero
            << setw(ESPACO_PEQUENO) << "Empresa"
            << setw(ESPACO_LISTAGEM) << site->getIdentificador()
            << setw(ESPACO_LISTAGEM) << gestores.str()
            << setw(ESPACO_LISTAGEM) << tecnologias.str()
            << setw(ESPACO_PEQUENO) << site->getNumeroPaginas()
            << "$" << setw(ESPACO_LISTAGEM) << setprecision(CENTIMOS) << site->getCusto() << endl;
        }
    }
    Website* site = NULL;
    site = escolheSemListagem(wsp->getWebsites(), "Escolha um website para ver as informacoes (0 para cancelar)");
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
    
    cout << left
    << setw(ESPACO_MUITO_PEQUENO) << "Numero"
    << setw(ESPACO_LISTAGEM) << "Nome"
    << setw(ESPACO_PEQUENO) << "Numero de B.I." << endl;
    unsigned int numero = 1;
    for (vector<Utilizador*>::const_iterator gestor_it = wsp->getGestores().begin(); gestor_it != wsp->getGestores().end(); gestor_it++, numero++)
    {
        // seguranca para um numero exagerado de utilizadores no vector
        if (numero > MAX_ELEMENTOS_LISTAGEM) {
            cout << "Foram listados " << MAX_ELEMENTOS_LISTAGEM << " utilizadores, mas existem no total " << wsp->getWebsites().size() << "." << endl;
            cout << "Se pretende encontrar um utilizador, por favor utilize a pesquisa." << endl;
            break;
        }
        
        cout << left
        << setw(ESPACO_MUITO_PEQUENO)<< numero
        << setw(ESPACO_LISTAGEM) << (*gestor_it)->getNome()
        << setw(ESPACO_PEQUENO) << (*gestor_it)->getNumIdentidade() << endl;
    }
    Utilizador* gestor = NULL;
    gestor = escolheSemListagem(wsp->getGestores(), "Escolha um gestor para aceder as informacoes (0 para cancelar)");
    if (gestor == NULL){ // se o utilizador cancelou, volta para o menu anterior
        return;
    } else{
        opcoes(gestor);
    }
    
    return;
}

void Menu::consultaCustos(){
    bool acabado = false;
    
    while (!acabado) {
        cout.setf(ios::fixed);
        cout << "Custo por pagina para websites particulares: "
        << setprecision(CENTIMOS) << SiteParticular::getCustoPorPagina() << " $" << endl;
        cout << "Custo por paginas para websites empresa: "
        << setprecision(CENTIMOS) << SiteEmpresa::getCustoPorPagina() << " $" << endl;
        cout << "Limite de paginas para websites particulares: "
        << setprecision(CENTIMOS) << SiteParticular::getLimitePaginas() << endl;
        cout << "Custo total de todos os websites: "
        << setprecision(CENTIMOS)<< wsp->calculoCustoTotal() << " $" << endl;
        
        switch (escolhe(consulta_custos, "Selecione uma opcao")) {
            case 0: // utilizador terminou
                acabado = true;
                break;
            case 1: // alterar custo particular
                SiteParticular::setCustoPorPagina(pergunta<float>("Defina o custo por pagina particular"));
                break;
            case 2: // alterar custo empresa
                SiteEmpresa::setCustoPorPagina(pergunta<float>("Defina o custo por pagina empresa"));
                break;
            case 3: // definir limite de paginas para particulares
                SiteParticular::setLimitePaginas(pergunta<unsigned int>("Defina o maximo numero paginas para websites particulares"));
                wsp->ajustarNumeroPaginasParaParticulares();
                break;
            default:
                break;
        }
    }
    return;
}

void Menu::ordenaWebsitesCriterio(){
    switch (escolhe(ordenar_websites, "Escolha um criterio") ) {
        case 0: // cancelar
            return;
            break;
        case 1: // identificador alfabetico
            wsp->ordenaWebsites("identificador alfabetico");
            listar_websites();
            return;
            break;
        case 2: // identificador alfabetico
            wsp->ordenaWebsites("identificador inverso");
            listar_websites();
            return;
            break;
        case 3: // numero paginas ascendente
            wsp->ordenaWebsites("numero paginas ascendente");
            listar_websites();
            return;
            break;
        case 4: // numero paginas descendente
            wsp->ordenaWebsites("numero paginas descendente");
            listar_websites();
            return;
            break;
        case 5: // custo ascendente
            wsp->ordenaWebsites("custo ascendente");
            listar_websites();
            break;
        case 6: // custo descendente
            wsp->ordenaWebsites("custo descendente");
            listar_websites();
            break;
        default:
            break;
    }
    return;

}


void Menu::ordenaUtilizadoresCriterio(){
    switch (escolhe(ordenar_utilizadores, "Escolha um criterio") ) {
        case 0: // cancelar
            return;
            break;
        case 1: // nome alfabetico
            wsp->ordenaUtilizadores("nome alfabetico");
            listar_utilizadores();
            return;
            break;
        case 2: // nome alfabetico inverso
            wsp->ordenaUtilizadores("nome alfabetico inverso");
            listar_utilizadores();
            return;
            break;
        case 3: // numero ascendente
            wsp->ordenaUtilizadores("numero ascendente");
            listar_utilizadores();
            return;
            break;
        case 4: // numero descendente
            wsp->ordenaUtilizadores("numero descendente");
            listar_utilizadores();
            return;
            break;
        default:
            break;
    }
    return;
}

void Menu::pesquisaNosUtilizadores(){
    bool acabado = false;
    while (!acabado) {
        switch (escolhe(pesquisa_utilizadores, "Escolha um criterio a pesquisar")) {
            case 0:
                acabado = true;
                break;
            case 1: // pesquisar nome
            {
                string pesquisa = pergunta<string>("Que nome quer pesquisar?");
                while (true) {
                    stringstream resultados_da_pesquisa;
                    vector<Utilizador*> resultados = wsp->pesquisaUtilizador("nome", pesquisa);
                    if (resultados.size() == 0) {
                        cout << "Nao foram encontrados resultados para a pesquisa \"" << pesquisa << "\""<< endl;
                        break;
                    }
                    resultados_da_pesquisa << "A pesquisa do nome \"" << pesquisa << "\"" << " retornou os resultados abaixo. Escolha um utilizador (0 para cancelar)";
                    Utilizador* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                    if (escolha == NULL) {
                        break;
                    }
                    opcoes(escolha);
                    // utilizador termina de mexer no site e regressa aqui
                }
                break;
            }
            case 2: // pesquisar numero
            {
                unsigned int pesquisa = pergunta<unsigned int>("Que numero quer pesquisar?");
                while (true) {
                    stringstream resultados_da_pesquisa;
                    vector<Utilizador*> resultados = wsp->pesquisaUtilizador("numero", pesquisa);
                    if (resultados.size() == 0) {
                        cout << "Nao foram encontrados resultados para a pesquisa \"" << pesquisa << "\""<< endl;
                        break;
                    }
                    resultados_da_pesquisa << "A pesquisa do nome \"" << pesquisa << "\"" << " retornou os resultados abaixo. Escolha um utilizador (0 para cancelar)";
                    Utilizador* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                    if (escolha == NULL) {
                        break;
                    }
                    opcoes(escolha);
                    // utilizador termina de mexer no site e regressa aqui
                }
                break;
            }

                
            default:
                break;
        }
        
        
    }
}

void Menu::pesquisaNosWebsites(){
    bool acabado = false;
    while (!acabado) {
        
        switch (escolhe(pesquisa_websites, "Escolha um criterio a pesquisar") ) {
            case 0: // cancelar
                acabado = true;
                break;
            case 1: // listar sites particulares
            {
                while (true) { // so termina quando o utilizador quer cancelar ou nao ha resultados
                    vector<Website*> resultados = wsp->pesquisaWebsite("particulares", "");
                    if (resultados.size() == 0) {
                        cout << "Nao existem ainda sites particulares" << endl;
                        break;
                    }
                    Website* escolha = escolhe(resultados, "Escolhe um site particular (0 para cancelar)");
                    if (escolha == NULL) {
                        break;
                    } else {
                        opcoes(escolha);
                    }
                    
                }
                break;
            }
            case 2: // listar sites empresas
            {
                while (true) {
                    vector<Website*> resultados = wsp->pesquisaWebsite("empresas", "");
                    if (resultados.size() == 0) {
                        cout << "Nao existem sites empresa" << endl;
                        break;
                    }
                    Website* escolha = escolhe(resultados, "Escolhe um site empresa (0 para cancelar)");
                    if (escolha == NULL) {
                        break;
                    } else {
                        opcoes(escolha);
                    }
                    
                }
                break;
            }
            case 3: // pesquisar identificador
            {
                string pesquisa = pergunta<string>("Que identificador quer pesquisar?");
                while (true) {
                    stringstream resultados_da_pesquisa;
                    vector<Website*> resultados = wsp->pesquisaWebsite("identificador", pesquisa);
                    if (resultados.size() == 0) {
                        cout << "Nao foram encontrados resultados da pesquisa \"" << pesquisa << "\""<< endl;
                        break;
                    }
                    resultados_da_pesquisa << "A pesquisa \"" << pesquisa << "\"" << " retornou os resultados abaixo. Escolha um website (0 para cancelar)";
                    Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                    if (escolha == NULL) {
                        break;
                    }
                    opcoes(escolha);
                    // utilizador termina de mexer no site e regressa aqui
                }
                break;
            }
            case 4: // pesquisa tecnologia
            {
                string pesquisa = pergunta<string>("Que tecnologia quer pesquisar?");
                while (true) {
                    stringstream resultados_da_pesquisa;
                    vector<Website*> resultados = wsp->pesquisaWebsite("tecnologia", pesquisa);
                    if (resultados.size() == 0) {
                        cout << "Nao foram encontrados resultados da pesquisa \"" << pesquisa << "\""<< endl;
                        break;
                    }
                    resultados_da_pesquisa << "A pesquisa \"" << pesquisa << "\"" << " retornou os resultados abaixo. Escolha um website";
                    Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                    if (escolha == NULL) {
                        break;
                    }
                    opcoes(escolha);
                    // utilizador termina de mexer no site e regressa aqui
                }
                break;
            }
            case 5: // pesquisa custo
            {
                switch (escolhe(superior_ou_inferior, "Escolha como pretende pesquisar um custo")) {
                    case 0: // cancelar
                        break;
                    case 1: // superior a um valor
                    {
                        float custo = pergunta<float>("Quer pesquisar um website com custo superior a? (0 para cancelar)");
                        if (custo <= 0){
                            cout << "Pesquisa cancelada." << endl;
                            break;
                        }
                        while (true) {
                            stringstream resultados_da_pesquisa;
                            vector<Website*> resultados = wsp->pesquisaWebsite("custo superior a", custo);
                            if (resultados.size() == 0) {
                                cout << "Nao foram encontrados websites de custo superior a $" << custo<< endl;
                                break;
                            }
                            resultados_da_pesquisa << "Os seguintes websites sao de custo superior a $" << custo << " Escolha um.";
                            Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                            if (escolha == NULL) {
                                break;
                            }
                            opcoes(escolha);
                            // utilizador termina de mexer no site e regressa aqui
                        }
                        break;
                    }
                    case 2: // inferior a um valor
                    {
                        
                        float custo = pergunta<float>("Quer pesquisar um website com custo inferior a? (0 para cancelar)");
                        if (custo <= 0){
                            cout << "Pesquisa cancelada." << endl;
                            break;
                        }
                        while (true) {
                            stringstream resultados_da_pesquisa;
                            vector<Website*> resultados = wsp->pesquisaWebsite("custo inferior a", custo);
                            if (resultados.size() == 0) {
                                cout << "Nao foram encontrados websites de custo inferior a $" << custo << endl;
                                break;
                            }
                            resultados_da_pesquisa << "Os seguintes websites sao de custo inferior a $" << custo << " Escolha um (0 para cancelar)";
                            Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                            if (escolha == NULL) {
                                break;
                            }
                            opcoes(escolha);
                            // utilizador termina de mexer no site e regressa aqui
                        }
                        
                        break;
                    }
                    default:
                        break;
                }
                
            }
                
                break;
            case 6: // pesquisa numero de paginas
                switch (escolhe(superior_ou_inferior, "Escolha como pretende pesquisar um numero de paginas")) {
                    case 0: // cancelar
                        break;
                    case 1: // superior a um valor
                    {
                        unsigned int numero = pergunta<unsigned int>("Quer pesquisar um website com numero de paginas superior a? (0 cancela)");
                        if (numero == 0){
                            cout << "Pesquisa cancelada." << endl;
                            break;
                        }
                        while (true) {
                            stringstream resultados_da_pesquisa;
                            vector<Website*> resultados = wsp->pesquisaWebsite("numero paginas superior a", numero);
                            if (resultados.size() == 0) {
                                cout << "Nao foram encontrados websites com numero de paginas superior a " <<numero<< endl;
                                break;
                            }
                            resultados_da_pesquisa << "Os seguintes websites tem numero de paginas superior a " <<numero<< " Escolha um (0 para cancelar)";
                            Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                            if (escolha == NULL) {
                                break;
                            }
                            opcoes(escolha);
                            // utilizador termina de mexer no site e regressa aqui
                        }
                        break;
                    }
                    case 2: // inferior a um valor
                    {
                        
                        unsigned int numero = pergunta<unsigned int>("Quer pesquisar um website com numero de paginas inferior a? (0 cancela)");
                        if (numero == 0){
                            cout << "Pesquisa cancelada." << endl;
                            break;
                        }
                        while (true) {
                            stringstream resultados_da_pesquisa;
                            vector<Website*> resultados = wsp->pesquisaWebsite("numero paginas inferior a", numero);
                            if (resultados.size() == 0) {
                                cout << "Nao foram encontrados websites com numero de paginas inferior a " << numero << endl;
                                break;
                            }
                            resultados_da_pesquisa << "Os seguintes websites tem numero de paginas inferior a " << numero << " Escolha um (0 para cancelar)";
                            Website* escolha = escolhe(resultados, resultados_da_pesquisa.str());
                            if (escolha == NULL) {
                                break;
                            }
                            opcoes(escolha);
                            // utilizador termina de mexer no site e regressa aqui
                        }
                        
                        break;
                    }
                    default:
                        break;
                }
                
            default:
                break;
        }
    }
    return;
}


Prototipo* Menu::escolhe(const BST<Prototipo*> & escolhas, const string & perg){
    //Prototipo notFound = Prototipo();
    BSTItrIn<Prototipo*> it(escolhas);
    int counter = 0;
    vector<Prototipo*> vecEscolhas;
    cout << left
    << setw(ESPACO_MUITO_PEQUENO) << "Numero"
    << setw(ESPACO_LISTAGEM) << "Tipo"
    << setw(ESPACO_LISTAGEM) << "Custo"
    << setw(ESPACO_PEQUENO) << "Tempo prod."
    << setw(ESPACO_LISTAGEM) << "Tecnologia(s)" << endl;
    while (!it.isAtEnd() ){
        vecEscolhas.push_back(it.retrieve());
        counter++;
        Prototipo* p = it.retrieve();
        cout.setf(ios::fixed);
        cout << left
        << setw(ESPACO_MUITO_PEQUENO) << counter
        << setw(ESPACO_LISTAGEM) << p->getTipo()
        << "$" << setw(ESPACO_LISTAGEM) << setprecision(CENTIMOS) << p->getCusto()
        << setw(ESPACO_PEQUENO) << p->getHoras();
        if (p->getTecnologias().size() == 1) {
            cout << setw(ESPACO_LISTAGEM) << p->getTecnologias().front() << endl;
        } else {
            stringstream tecnologias;
            tecnologias << p->getTecnologias().front() << " e mais " << p->getTecnologias().size() -1;
            cout << setw(ESPACO_LISTAGEM) << tecnologias.str() << endl;
        }
        it.advance();
    }
    
    unsigned int numero_escolha;
    cout << perg << endl << PROMPT;
    cin >> numero_escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ( cin.fail() || numero_escolha > counter ) {
        cout << "Escolha invalida. Selecione uma opcao de 0 a " << counter << "." << endl << PROMPT;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numero_escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    Prototipo* escolha;
    if (numero_escolha == 0) {
        //escolha = notFound;
        escolha = NULL;
    } else{
        escolha = vecEscolhas.at(numero_escolha-1);
    }
    return escolha;

}

void Menu::opcoes(Prototipo * proto){
    while (true) {
        // imprimir as informacoes do prototipo
        cout.setf(ios::fixed);
        cout << "Prototipo para uma pagina do tipo: " << proto->getTipo() << endl;
        cout << "Custo de producao: " << "$" << setprecision(CENTIMOS) << proto->getCusto() << endl;
        cout << "Horas de desenvolvimento necessarias: " << proto->getHoras() << endl;
        cout << "Tecnologias implementadas: ";
        list<string> tecnologias = proto->getTecnologias();
        for (list<string>::iterator it = tecnologias.begin(); it!= tecnologias.end(); it++) {
            if ( (*it) == tecnologias.back() ) {
                cout << (*it) << "." << endl;
            } else {
                cout << (*it) << ", ";
            }
        }
        switch (escolhe(opcoes_prototipo, "Selecione uma opcao") ) {
            case 0: // voltar atras
                return;
                break;
            case 1: // modificar o tipo
            {
                string tipo;
                tipo = pergunta<string>("Qual o novo nome do tipo prototipo? (introduza 0 para cancelar)");
                
                if (tipo == "0") break;
                
                wsp->getCatalogo().alteraTipo(proto->getTipo(), tipo); // modificar o tipo

                break;
            }
            case 2: // modificar o custo
            {
                float custo;
                custo = pergunta<float>("Qual sera o custo de um website deste prototipo? (0 para cancelar)");
                
                if (custo < 0) {
                    custo = pergunta<float>("Custo invalido. Por favor escolha um custo superior a 0");
                } else if (custo == 0) break;
                
                wsp->getCatalogo().alteraCusto(proto->getTipo(), custo);
                
                break;
            }
            case 3: // modificar o tempo de desenvolvimento
            {
                unsigned int horas;
                horas = pergunta<unsigned int>("Qual sera o custo de um website deste prototipo? (0 para cancelar)");
                
                if (horas == 0) break;
                
                wsp->getCatalogo().alteraHoras(proto->getTipo(), horas);
                break;
            }
            case 4: // modificar as tecnologias
            {
                string tecnologia;
                list<string> tecnologias;
                tecnologia = pergunta<string>("Que tecnologia um website deste prototipo implementa?");
                tecnologias.push_back(tecnologia);
                
                while (true) {
                    tecnologia = pergunta<string>("Que outra tecnologia implementa? (introduza 0 para terminar)");
                    if (tecnologia == "0"){
                        break;
                    } else {
                        tecnologias.push_back(tecnologia);
                    }
                }
                
                wsp->getCatalogo().alteraTecnologias(proto->getTipo(), tecnologias);

                break;
            }
            case 5: // eliminar proto
            {
                cout << "O prototipo " << proto->getTipo() << " foi eliminado!" << endl;
                pressEnter();
                wsp->getCatalogo().elimina(proto->getTipo());
                return;
                break;
            }
            default:
                break;
        }
    }
}

void Menu::consultaCatalogo(){
    while (true) {
        cout << "Numero de prototipos de websites: " << wsp->getCatalogo().getNumPrototipos() << endl;
        switch (escolhe(consulta_catalogo, "Escolha uma operacao")) {
            case 0: // voltar ao menu anterior
                return;
                break;
            case 1: // listar
            {
                Prototipo* escolha = escolhe(wsp->getCatalogo().getPrototipos(), "Escolha um prototipo (0 para cancelar)");
                if (escolha == NULL )
                    break;
                opcoes(escolha);
                break;
            }
            case 2: // pesquisar um proto
            {
                string tipo;
                tipo = pergunta<string>("Indique o tipo do prototipo que pretende pesquisar");
                try {
                    opcoes(wsp->getCatalogo().consulta(tipo));
                } catch (PrototipoNaoExistente &e) {
                    cout << "Esse tipo de prototipo nao existe no catalogo." << endl;
                    Prototipo* notFound = new Prototipo();
                    BST<Prototipo*> outrosResultados (notFound);
                    if ( e.getAntes() != NULL ){
                        outrosResultados.insert(e.getAntes() );
                    }
                    if ( e.getDepois() != NULL ){
                        outrosResultados.insert(e.getDepois() );
                    }
                    Prototipo* escolha = escolhe(outrosResultados, "");
                    if (escolha == NULL) {
                        break;
                    }
                    
                    opcoes(escolha);
                    
                }
                
                break;
            }
            case 3: // adicionar proto
            {
                string tipo;
                float custo;
                unsigned int horas;
                list<string> tecnologias;
                string tecnologia;
                
                tipo = pergunta<string>("O prototipo sera de que tipo de pagina? (Ex: Faculdade, Livraria / 0 para cancelar)");
                
                if (tipo == "0") break;
                
                custo = pergunta<float>("Qual sera o custo de um website deste prototipo? (0 para cancelar)");
                
                if (custo < 0) {
                    custo = pergunta<float>("Custo invalido. Por favor escolha um custo superior a 0");
                } else if (custo == 0) break;
                
                horas = pergunta<unsigned int>("Quantas horas demora a criar um website baseado neste prototipo? (0 para cancelar)");
                if (horas == 0) break;
                
                tecnologia = pergunta<string>("Que tecnologia um website deste prototipo implementa?");
                tecnologias.push_back(tecnologia);
                                
                while (true) {
                    tecnologia = pergunta<string>("Que outra tecnologia implementa? (introduza 0 para terminar)");
                    if (tecnologia == "0"){
                        break;
                    } else {
                        tecnologias.push_back(tecnologia);
                    }
                }
                
                Prototipo* p = new Prototipo(tipo, custo, horas, tecnologias);
                wsp->getCatalogo().adicionar(p);
                
                break;

            }
            
            default:
                break;
        }
    }
}


int Menu::inicio(){
    cout << "--------- Menu Principal ---------" << endl;
    switch (escolhe(opcoes_inicio, "Selecione uma opcao")) {
        case 0: // Terminar aplicacao
            return 1;
            break;
        case 1: // Criar
            switch (escolhe(website_ou_utilizador, "Escolha o que pretende criar")) {
                case 0:
                    return 0;
                    break;
                case 1: // website
                    criar_website();
                    return 0;
                    break;
                case 2: // utilizador
                    criar_utilizador();
                    return 0;
                    break;
                default:
                    break;
            }
            return 0;
            break;
        case 2: // Listar
            switch (escolhe(website_ou_utilizador, "Escolha o que pretende listar (na totalidade)")) {
                case 0:
                    return 0;
                    break;
                case 1: // website
                    listar_websites();
                    return 0;
                    break;
                case 2: // utilizador
                    listar_utilizadores();
                    return 0;
                    break;
                default:
                    break;
            }
            return 0;
            break;
        case 3: // pesquisar
            switch (escolhe(website_ou_utilizador, "Escolha o que pretende pesquisar")) {
                case 0:
                    return 0;
                    break;
                case 1: // website
                    pesquisaNosWebsites();
                    return 0;
                    break;
                case 2: // utilizador
                    pesquisaNosUtilizadores();
                    return 0;
                    break;
                default:
                    break;
            }
            return 0;
            break;
        case 4: // ordenar
            switch (escolhe(website_ou_utilizador, "Escolha o que pretende ordenar e listar")) {
                case 0:
                    return 0;
                    break;
                case 1: // website
                    ordenaWebsitesCriterio();
                    return 0;
                    break;
                case 2: // utilizador
                    ordenaUtilizadoresCriterio();
                    return 0;
                    break;
                default:
                    break;
            }
            return 0;
            break;
        case 5: // consultar os custos
            consultaCustos();
            return 0;
            break;
        case 6:
            consultaCatalogo();
            return 0;
            break;
        default:
            return 0;
            break;
    }
    return 0;
}

Menu::Menu(){
    opcoes_inicio.push_back("Terminar aplicacao");
    opcoes_inicio.push_back("Criar");
    opcoes_inicio.push_back("Listar");
    opcoes_inicio.push_back("Pesquisar");
    opcoes_inicio.push_back("Ordernar");
    opcoes_inicio.push_back("Consultar custos");
    opcoes_inicio.push_back("Catalogo de Prototipos");
    
    escolher_tipo_site.push_back("Cancelar");
    escolher_tipo_site.push_back("Site para particular");
    escolher_tipo_site.push_back("Site para empresa");
    
    escolher_utilizador.push_back("Cancelar");
    escolher_utilizador.push_back("Criar novo utilizador");
    escolher_utilizador.push_back("Escolher um utilizador ja existente");
    
    opcoes_website_particular.push_back("Voltar ao menu anterior");
    opcoes_website_particular.push_back("Alterar o gestor");
    opcoes_website_particular.push_back("Alterar a tecnologia usada pelo website");
    opcoes_website_particular.push_back("Alterar o numero de paginas do website");
    opcoes_website_particular.push_back("Eliminar o website");

    opcoes_website_empresa.push_back("Voltar ao menu anterior");
    opcoes_website_empresa.push_back("Adicionar gestor");
    opcoes_website_empresa.push_back("Retirar gestor");
    opcoes_website_empresa.push_back("Adicionar tecnologia");
    opcoes_website_empresa.push_back("Retirar tecnologia");
    opcoes_website_empresa.push_back("Alterar o numero de paginas");
    opcoes_website_empresa.push_back("Eliminar website");
    
    opcoes_utilizador.push_back("Voltar ao menu anterior");
    opcoes_utilizador.push_back("Alterar nome");
    opcoes_utilizador.push_back("Alterar numero do bilhete de identidade");
    opcoes_utilizador.push_back("Aceder a um wesite responsavel");
    opcoes_utilizador.push_back("Eliminar utilizador");
    
    consulta_custos.push_back("Voltar ao menu anterior");
    consulta_custos.push_back("Alterar custo para particulares");
    consulta_custos.push_back("Alterar custo para empresas");
    consulta_custos.push_back("Definir limite de paginas para particulares");
    
    ordenar_utilizadores.push_back("Cancelar");
    ordenar_utilizadores.push_back("Nome (alfabetico)");
    ordenar_utilizadores.push_back("Nome (alfabetico inverso)");
    ordenar_utilizadores.push_back("Numero de B.I. (ascendente)");
    ordenar_utilizadores.push_back("Numero de B.I. (descendente)");
    
    ordenar_websites.push_back("Cancelar");
    ordenar_websites.push_back("Identificador (alfabetico)");
    ordenar_websites.push_back("Identificador (alfabetico inverso)");
    ordenar_websites.push_back("Numero paginas (ascendente)");
    ordenar_websites.push_back("Numero paginas (descendente)");
    ordenar_websites.push_back("Custo (ascendente)");
    ordenar_websites.push_back("Custo (descendente)");
    
    pesquisa_websites.push_back("Cancelar");
    pesquisa_websites.push_back("Listar sites particulares");
    pesquisa_websites.push_back("Listar sites empresa");
    pesquisa_websites.push_back("Pesquisar identificador");
    pesquisa_websites.push_back("Pesquisar tecnologia");
    pesquisa_websites.push_back("Pesquisar custo");
    pesquisa_websites.push_back("Pesquisar numero de paginas");

    pesquisa_utilizadores.push_back("Cancelar");
    pesquisa_utilizadores.push_back("Nome");
    pesquisa_utilizadores.push_back("Numero de B.I.");
    
    escolher_tecnologias.push_back("Terminar escolha das tecnologias");
    escolher_tecnologias.push_back("Adicionar uma nova tecnologia");
    
    website_ou_utilizador.push_back("Cancelar");
    website_ou_utilizador.push_back("Websites");
    website_ou_utilizador.push_back("Utilizadores");
    
    superior_ou_inferior.push_back("Cancelar");
    superior_ou_inferior.push_back("Superior a um valor");
    superior_ou_inferior.push_back("Inferior a um valor");
    
    gestores_empresa.push_back("Terminar escolha dos gestores");
    gestores_empresa.push_back("Criar um novo utilizador");
    gestores_empresa.push_back("Escolher um utilizador ja existente");
    
    consulta_catalogo.push_back("Voltar ao menu anterior");
    consulta_catalogo.push_back("Listar catalogo");
    consulta_catalogo.push_back("Pesquisar um prototipo de website");
    consulta_catalogo.push_back("Adicionar um prototipo de website");

    opcoes_prototipo.push_back("Voltar ao menu anterior");
    opcoes_prototipo.push_back("Modificar tipo");
    opcoes_prototipo.push_back("Modificar custo");
    opcoes_prototipo.push_back("Modificar tempo de desenvolvimento");
    opcoes_prototipo.push_back("Modificar tecnologias");
    opcoes_prototipo.push_back("Eliminar prototipo");


    wsp = new GestorWSP();
    cout << "Bem vindo ao gestor de website provider!" << endl;
    leDados();
    while (inicio() != 1) {
        guardaDados();
    }
    cout << "A terminar aplicacao..." << endl;
}
