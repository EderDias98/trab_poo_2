#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <bits/stdc++.h> // Inclui praticamente todas as bibliotecas padrão
using namespace std;

class Candidato {
public:
    enum class Genero {
        MASCULINO,
        FEMININO,
        OUTRO,
        NAO_INFORMADO
    };

private:
    int sgUE;
    string cargo;
    int nrCandidato;
    string nmUrnaCandidato;
    int nrPartido;
    string sgPartido;
    int nrFederacao;
    tm dtNascimento{};
    int cdSitTotTurno;
    Genero genero;
    int posicaoRankMaisVotado;
    int votos;

public:
    Candidato(const string& sgUE,
              const string& nrCandidato,
              const string& nmUrnaCandidato,
              const string& nrPartido,
              const string& sgPartido,
              const string& nrFederacao,
              const string& dtNascimento,
              const string& cdSitTotTurno,
              const string& cdGenero);

    string toString() const;

    // Getters
    string getCargo() const;
    int getCdSitTotTurno() const;
    tm getDtNascimento() const;
    Genero getGenero() const;
    string getNmUrnaCandidato() const;
    int getNrCandidato() const;
    int getNrFederacao() const;
    int getNrPartido() const;
    string getSgPartido() const;
    int getSgUE() const;
    int getPosicaoRankMaisVotado() const;
    int getVotos() const;

    // Setters
    void setPosicaoRankMaisVotado(int posicao);
    void setVotos(int votos);
};

#endif
