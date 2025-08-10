#include "listas.hpp"

Listas::Listas() {
    // Inicialização automática dos vetores e mapa
}

const vector<Candidato>& Listas::getCandidatos() const {
    return candidatos;
}

const vector<Seccao>& Listas::getSeccoes() const {
    return seccoes;
}

const unordered_map<int, Partido>& Listas::getPartidos()  const{
    return partidos;
}

const string& Listas::getDataEleicao() const {
    return dataEleicao;
}

void Listas::addCandidato(const Candidato& c) {
    candidatos.push_back(c);
}

void Listas::addSeccao(const Seccao& s) {
    seccoes.push_back(s);
}

void Listas::adicionaPartido(const Partido& p) {
    // Insere apenas se não existir ainda
    int numero = p.getNumero();
    if (partidos.find(numero) == partidos.end()) {
        partidos[numero] = p;
    }
}

void Listas::setDataEleicao(const string& data) {
    dataEleicao = data;
}
