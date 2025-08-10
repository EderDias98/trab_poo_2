#ifndef SECCAO_HPP
#define SECCAO_HPP


#include <bits/stdc++.h> // Inclui praticamente todas as bibliotecas padrão
using namespace std;
class Seccao {
private:
    int cdMunicipio;
    int nrVotavel;
    int qtVotos;

public:
    // Construtor que recebe strings e converte para int
    Seccao(const string& cdMunicipioStr, const string& nrVotavelStr, const string& qtVotosStr);

    // Getters
    int getCdMunicipio() const;
    int getNrVotavel() const;
    int getQtVotos() const;

    // Representação em string formatada
    string toString() const;
};

#endif // SECCAO_HPP
