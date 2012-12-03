//  catalogo.cpp
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#include "catalogo.h"

// --------- Funcoes classe Prototipo ---------

Prototipo::Prototipo(): tipo(""), custo(0), horas(0){
    list<string> tech;
    tecnologias = tech;
}

Prototipo::Prototipo(string t, float c, unsigned int h, list<string> tech):
tipo(t), custo(c), horas(h), tecnologias(tech) {}

Prototipo::Prototipo(string t, float c, unsigned int h):
tipo(t), custo(c), horas(h){
    list<string> tech;
    tecnologias = tech;
}

string Prototipo::getTipo() const{
    return this->tipo;
}

void Prototipo::setTipo(const string &t){
    this->tipo = t;
    return;
}

float Prototipo::getCusto() const{
    return this->custo;
}

void Prototipo::setCusto(const float &c){
    this->custo = c;
    return;
}

unsigned int Prototipo::getHoras() const{
    return this->horas;
}

void Prototipo::setHoras(const unsigned int &h){
    this->horas = h;
    return;
}

list<string> Prototipo::getTecnologias() const{
    return this->tecnologias;
}

void Prototipo::setTecnologias(const list<string> & tech){
    this->tecnologias = tech;
    return;
}

bool Prototipo::operator < (const Prototipo &p1) const{
    /*
    cout << this->tipo << " < " << p1.tipo << ": ";
    if (tipo < p1.tipo ) cout << "true";
    else cout << "false";
    cout << endl;
     */
    string str1 = tipo; string str2 = p1.tipo;
    transform(str1.begin(), str1.end(),str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(),str2.begin(), ::toupper);
    return str1 < str2;
	//return tipo < p1.tipo;
}

bool Prototipo::operator ==(const Prototipo &p1) const{
    string str1 = tipo; string str2 = p1.tipo;
    transform(str1.begin(), str1.end(),str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(),str2.begin(), ::toupper);
    return str1 == str2;
	//return tipo == p1.tipo;
}

// --------- Funcoes classe Catalogo ---------

Catalogo::Catalogo(): prototipos(Prototipo() ){};

Catalogo::~Catalogo(){};

BST<Prototipo> Catalogo::getPrototipos() const{
    return prototipos;
}

void Catalogo::adicionar(Prototipo &p){
    prototipos.insert(p);
    return;
}

bool Catalogo::alteraCusto(string prototipo, float custo){
    Prototipo p1(prototipo, 0, 0);
    BSTItrIn<Prototipo> it(prototipos);
    while (!it.isAtEnd() && it.retrieve()<p1)
        it.advance();
    if (!it.isAtEnd() && it.retrieve()==p1) {
        it.retrieve().setCusto(custo);
        return true;
    }
    return false;
}

bool Catalogo::alteraHoras(string prototipo, unsigned int horas){
    Prototipo p1(prototipo, 0, 0);
    BSTItrIn<Prototipo> it(prototipos);
    while (!it.isAtEnd() && it.retrieve()<p1)
        it.advance();
    if (!it.isAtEnd() && it.retrieve()==p1) {
        it.retrieve().setHoras(horas);
        return true;
    }
    return false;
}

bool Catalogo::alteraTecnologias(string prototipo, list<string> tecnologias){
    Prototipo p1(prototipo, 0, 0);
    BSTItrIn<Prototipo> it(prototipos);
    while (!it.isAtEnd() && it.retrieve()<p1)
        it.advance();
    if (!it.isAtEnd() && it.retrieve()==p1) {
        it.retrieve().setTecnologias(tecnologias);
        return true;
    }
    return false;
}

bool Catalogo::alteraTipo(string prototipo, string tipo){
    Prototipo p1(prototipo, 0, 0);
    BSTItrIn<Prototipo> it(prototipos);
    while (!it.isAtEnd() && it.retrieve()<p1)
        it.advance();
    if (!it.isAtEnd() && it.retrieve()==p1) {
        p1 = it.retrieve();
        prototipos.remove(p1);
        p1.setTipo(tipo);
        prototipos.insert(p1);
        return true;
    }
    return false;
}

bool Catalogo::elimina(string prototipo){
    Prototipo p1(prototipo, 0, 0);
    Prototipo encontrado = prototipos.find(p1);
    Prototipo pNotFound;
    if (encontrado == pNotFound)
    {
        return false; // nao foi encontrado
    } else {
        prototipos.remove(encontrado);
        return true;
    }
        
}

Prototipo Catalogo::consulta(const string prototipo) const{
    Prototipo p1(prototipo,0,0);
    Prototipo encontrado = prototipos.find(p1);
    Prototipo pNotFound;
    if (encontrado == pNotFound)
    {
        BSTItrIn<Prototipo> it(prototipos);
        Prototipo antes, depois;
        while (!it.isAtEnd() && it.retrieve() < p1 )
        {
        	antes = it.retrieve();
            it.advance();
        }
        if (!it.isAtEnd())
        {
        	depois=it.retrieve();
        }
        throw PrototipoNaoExistente(antes,depois);
    }
    else
        return encontrado;
}




