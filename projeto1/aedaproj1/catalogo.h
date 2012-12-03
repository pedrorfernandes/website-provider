//  catalogo.h
//
//  Projeto 1 AEDA - Parte 2
//
//  Turma 1 Grupo 3
//
//  ei11111 - Armindo Carvalho
//  ei11078 - Pedro Rocha
//  ei11122 - Pedro Fernandes
//

#ifndef catalogo_h
#define _catalogo_h

#include <iostream>
#include "BST.h"
#include "website.h"
#include <list>

class Prototipo {
private:
    string tipo;
    float custo;
    unsigned int horas;
    list<string> tecnologias;
public:
    Prototipo();
    Prototipo(string t, float c, unsigned int h, list<string> tech);
    Prototipo(string t, float c, unsigned int h);
    string getTipo() const;
    void setTipo(const string &t);
    float getCusto() const;
    void setCusto(const float &c);
    unsigned int getHoras() const;
    void setHoras(const unsigned int &h);
    list<string> getTecnologias() const;
    void setTecnologias(const list<string> & tech);
    bool operator < (const Prototipo &p1) const;
    bool operator ==(const Prototipo &p1) const;
    friend ostream & operator<<(ostream &out, Prototipo p);
    
};

class Catalogo {
private:
    BST<Prototipo> prototipos;
public:
    Catalogo();
    ~Catalogo();
    BST<Prototipo> getPrototipos() const;
    void adicionar(Prototipo &p);
    bool alteraCusto(string prototipo, float custo);
    bool alteraHoras(string prototipo, unsigned int horas);
    bool alteraTecnologias(string prototipo, list<string> tecnologias);
    bool alteraTipo(string prototipo, string tipo);
    bool elimina(string prototipo);
    Prototipo consulta(const string prototipo) const;
};

class PrototipoNaoExistente{
private:
    Prototipo antes, depois;
public:
    PrototipoNaoExistente(Prototipo a, Prototipo d): antes(a), depois(d){}
    Prototipo getAntes() const {return antes;}
    Prototipo getDepois() const {return depois;}

};


#endif
