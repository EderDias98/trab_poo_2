#include "seccao.hpp"

Seccao::Seccao(const string& cdMunicipioStr, const string& nrVotavelStr, const string& qtVotosStr) {
    try {
        cdMunicipio = stoi(cdMunicipioStr);
        nrVotavel = stoi(nrVotavelStr);
        qtVotos = stoi(qtVotosStr);
    } catch (const invalid_argument& e) {
        // Tratar erro caso a string não seja um número válido
        cdMunicipio = 0;
        nrVotavel = 0;
        qtVotos = 0;
        // Opcional: lançar exceção, log, ou mensagem de erro
        // cerr << "Erro ao converter string para int: " << e.what() << endl;
    }
}

int Seccao::getCdMunicipio() const {
    return cdMunicipio;
}

int Seccao::getNrVotavel() const {
    return nrVotavel;
}

int Seccao::getQtVotos() const {
    return qtVotos;
}

string Seccao::toString() const {
    ostringstream oss;
    oss << "Município: " << cdMunicipio 
        << " - Número Votável: " << nrVotavel 
        << " - Quantidade de Votos: " << qtVotos;
    return oss.str();
}
