//
//  main.cpp
//
//  Projeto 1 AEDA
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include <iostream>

#include "main.h"

using namespace std;

int main(int argc, const char * argv[])
{
    /*
    Utilizador* pedro = new Utilizador(12345, "Pedro");
    Website* blog = new SiteParticular("www.umblog.com", 10, "Ruby", pedro);
    
    try {
        blog->getGestor();
    } catch (Erro &e) {
        cout << e.getMsg() << endl;
    }
    
    vector<Website*> sites;
    sites.push_back(blog);
    
    vector<Utilizador*> alta_empresa;
    Utilizador* ze = new Utilizador(123, "Ze");
    alta_empresa.push_back(ze); alta_empresa.push_back(pedro);
    vector<string> tecnologias;
    tecnologias.push_back("C++"); tecnologias.push_back("Java"); tecnologias.push_back("Python");
    Website* google = new SiteEmpresa("www.google.com", 100, tecnologias, alta_empresa);
    cout << "1o print" << endl;
    for (vector<string>::iterator it = google->getTecnologias().begin(); it != google->getTecnologias().end(); it++) {
        cout << (*it) << endl;
    }
    google->retiraTecnologia("Java");
    cout << "2o print" << endl;
    for (vector<string>::iterator it = google->getTecnologias().begin(); it != google->getTecnologias().end(); it++) {
        cout << (*it) << endl;
    }
    SiteEmpresa::setCustoPorPagina(500.45);
    cout << google->getCusto() << endl;
    vector<string> tecnologias2;
    tecnologias2.push_back("Scheme");
    google->setTecnologias(tecnologias2);
    google->novaTecnologia("ObjectiveC");
    cout << "3o print" << endl;
    for (vector<string>::iterator it = google->getTecnologias().begin(); it != google->getTecnologias().end(); it++) {
        cout << (*it) << endl;
    }
    
    GestorWSP* database = new GestorWSP();
    database->novoSite(blog);
    if (!database->novoSite(blog)) {
        cout << "nao me enganas" << endl;
    }
     
    database->novoSite(google);
    database->novoSite(blog);
    Website* blog2 = new SiteParticular("www.cenas.com", 10, "Ruby", pedro);
    database->novoSite(blog2);
    database->eliminaCliente(pedro);
    for (vector<Website*>::iterator it = database->getWebsites().begin(); it != database->getWebsites().end(); it++) {
        cout << (*it)->getIdentificador() << endl;
    }
    for (vector<Utilizador*>::iterator it = database->getGestores().begin(); it != database->getGestores().end(); it++) {
        cout << (*it)->getNome() << endl;
    }
    try {
        cout << blog2->getGestor()->getNome() << endl;
    } catch (...) {
        cout << "merdou" << endl;
    }
    
    return 0;
    */
    
    Menu();
}

