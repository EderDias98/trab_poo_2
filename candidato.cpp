#include "candidato.hpp"
using namespace std;

Candidato::Candidato(const string& sgUE,
                     const string& nrCandidato,
                     const string& nmUrnaCandidato,
                     const string& nrPartido,
                     const string& sgPartido,
                     const string& nrFederacao,
                     const string& dtNascimento,
                     const string& cdSitTotTurno,
                     const string& cdGenero)
{
    this->sgUE = stoi(sgUE);
    this->cargo = "VEREADOR";
    this->nrCandidato = stoi(nrCandidato);
    this->nmUrnaCandidato = nmUrnaCandidato;
    this->nrPartido = stoi(nrPartido);
    this->sgPartido = sgPartido;
    this->nrFederacao = stoi(nrFederacao);

    // Converte "dd/MM/yyyy" para tm
    istringstream ss(dtNascimento);
    ss >> get_time(&this->dtNascimento, "%d/%m/%Y");

    this->cdSitTotTurno = stoi(cdSitTotTurno);
    this->posicaoRankMaisVotado = 0;
    this->votos = 0;

    int generoCodigo = stoi(cdGenero);
    switch (generoCodigo) {
        case 2: this->genero = Genero::MASCULINO; break;
        case 4: this->genero = Genero::FEMININO; break;
        default: this->genero = Genero::OUTRO; break;
    }
}

string Candidato::toString() const {
    ostringstream os;
    os << "Candidato: " << nmUrnaCandidato
       << " (" << nrCandidato << ") - Partido "
       << sgPartido << " (" << nrPartido << ") - Nascimento: "
       << put_time(&dtNascimento, "%d/%m/%Y")
       << " - Gênero: "
       << (genero == Genero::MASCULINO ? "Masculino" :
           genero == Genero::FEMININO ? "Feminino" : "Outro")
       << " - Situação: " << cdSitTotTurno;
    return os.str();
}

// Getters
string Candidato::getCargo() const { return cargo; }
int Candidato::getCdSitTotTurno() const { return cdSitTotTurno; }
tm Candidato::getDtNascimento() const { return dtNascimento; }
Candidato::Genero Candidato::getGenero() const { return genero; }
string Candidato::getNmUrnaCandidato() const { return nmUrnaCandidato; }
int Candidato::getNrCandidato() const { return nrCandidato; }
int Candidato::getNrFederacao() const { return nrFederacao; }
int Candidato::getNrPartido() const { return nrPartido; }
string Candidato::getSgPartido() const { return sgPartido; }
int Candidato::getSgUE() const { return sgUE; }
int Candidato::getPosicaoRankMaisVotado() const { return posicaoRankMaisVotado; }
int Candidato::getVotos() const { return votos; }

// Setters
void Candidato::setPosicaoRankMaisVotado(int posicao) { posicaoRankMaisVotado = posicao; }
void Candidato::setVotos(int votos) { this->votos = votos; }
