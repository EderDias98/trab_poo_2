#ifndef DADOS_H
#define DADOS_H



#include "candidato.hpp"
#include "seccao.hpp"
#include "partido.hpp"

class Listas {
private:
    vector<Candidato> candidatos;
    vector<Seccao> seccoes;
    unordered_map<int, Partido> partidos;

    // Para simplificar, armazenar a data da eleição como string (ex: "2025-08-10")
    string dataEleicao;

public:
    Listas();

    // Getters
    const vector<Candidato>& getCandidatos() const;
    const vector<Seccao>& getSeccoes() const;
    const unordered_map<int, Partido>& getPartidos() const;
    const string& getDataEleicao() const;

    // Métodos para adicionar itens
    void addCandidato(const Candidato& c);
    void addSeccao(const Seccao& s);
    void adicionaPartido(const Partido& p);

    // Setter para data
    void setDataEleicao(const string& data);
};

#endif // DADOS_H
