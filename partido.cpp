#include "partido.hpp"


    Partido:: Partido() 
        : numero(0), sigla(""), votosNominais(0),
          votosLegenda(0), totalVotos(0), candidatosEleitos(0) {}

Partido::Partido(int numero, const std::string& sigla)
    : numero(numero), sigla(sigla),
      votosNominais(0), votosLegenda(0), totalVotos(0), candidatosEleitos(0) {

}

void Partido::adicionarVotosNominais(int votos) {
    votosNominais += votos;
    totalVotos += votos;
}

void Partido::adicionarVotosLegenda(int votos) {
    votosLegenda += votos;
    totalVotos += votos;
}

void Partido::incrementarEleito() {
    candidatosEleitos++;
}

int Partido::getNumero() const {
    return numero;
}

const std::string& Partido::getSigla() const {
    return sigla;
}

int Partido::getVotosNominais() const {
    return votosNominais;
}

int Partido::getVotosLegenda() const {
    return votosLegenda;
}

int Partido::getTotalVotos() const {
    return totalVotos;
}

int Partido::getCandidatosEleitos() const {
    return candidatosEleitos;
}

void Partido::adicionarCandidato(const Candidato& c) {
    candidatosDoPartido.push_back(c);
}

const std::vector<Candidato>& Partido::getCandidatosDoPartido() const {
    return candidatosDoPartido;
}

void Partido::imprime(std::ostream& os) const {
    os << toString();
}

std::string Partido::toString() const {
    std::ostringstream oss;
    std::string s = (votosNominais < 2) ? "nominal" : "nominais";

    oss << sigla << " - " << numero << ", " << totalVotos << " votos ("
        << votosNominais << " " << s << " e " << votosLegenda
        << " de legenda), " << candidatosEleitos << " candidatos eleitos\n";

    return oss.str();
}
