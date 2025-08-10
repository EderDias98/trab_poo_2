#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include "candidato.hpp"
#include "seccao.hpp"
#include "partido.hpp"
#include "listas.hpp"



class Relatorio {
private:
    int municipio;

    vector<Candidato> candidatosDoMunicipio;
    vector<Seccao> seccoesDoMunicipio;
    vector<Candidato> eleitos;
    vector<Candidato> maisVotados;
    vector<Candidato> maisVotadosN;
    vector<Candidato> eleitosOrdenados;
    map<int, int> votosPorCandidato; // nrCandidato -> votos
    unordered_map<int, Partido> mapaPartidos;

    int qtdEleitos;

public:
    Relatorio(const Listas& lis, int municipio);

    static int contarDigitos(int numero);

  

    void gerarRelatorioEleitos();
    void gerarRelatorioMaisVotados();
    void gerarRelatorioNaoEleitosMajoritaria();
    void gerarRelatorioEleitosBeneficiados();

    void gerarPartidos();
    void contarVotosDeLegenda();
    void gerarRelatorioPartidosEVotos();

    void gerarRelatorioPrimeiroEUltimoPorPartido();

    void gerarRelatorioEleitosPorFaixaEtaria(const string &data);
    void gerarRelatorioEleitosPorGenero();

    void gerarRelatorioVotosValidos();

private:
    static double percentual(int quantidade, int total);
};

#endif
