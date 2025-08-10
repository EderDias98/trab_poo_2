#ifndef PARTIDO_H
#define PARTIDO_H

#include "candidato.hpp"


class Partido {
private:
    int numero;
    std::string sigla;
    int votosNominais;
    int votosLegenda;
    int totalVotos;
    int candidatosEleitos;
    std::vector<Candidato> candidatosDoPartido;

public:
    Partido();
    Partido(int numero, const std::string& sigla);

    // Métodos para adicionar votos
    void adicionarVotosNominais(int votos);
    void adicionarVotosLegenda(int votos);
    void incrementarEleito();

    // Getters
    int getNumero() const;
    const std::string& getSigla() const;
    int getVotosNominais() const;
    int getVotosLegenda() const;
    int getTotalVotos() const;
    int getCandidatosEleitos() const;

    void adicionarCandidato(const Candidato& c);
    const std::vector<Candidato>& getCandidatosDoPartido() const;

    void imprime(std::ostream& os = std::cout) const;
    std::string toString() const;
};

#endif // PARTIDO_H
