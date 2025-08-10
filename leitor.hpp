#ifndef LEITOR_H
#define LEITOR_H

#include "candidato.hpp"
#include "listas.hpp"
using namespace std;

class Leitor {
public:
    static void lerCandidatos(const string& caminhoArquivo, Listas& d);
    static void lerSeccoes(const string& caminhoArquivo, Listas& d);

private:
    static string removerAspas(const string& s);
};

#endif
