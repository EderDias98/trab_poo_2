
#include "listas.hpp"     // Sua classe Listas
#include "leitor.hpp"    // Sua classe Leitor
#include "relatorio.hpp" // Sua classe Relatorio

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <municipio> <arquivo_candidatos> <arquivo_seccoes>\n";
        return 1;
    }

    int muni = std::atoi(argv[1]);

    Listas lis;

    // Leitura dos Listas
    Leitor::lerCandidatos(argv[2], lis);
    Leitor::lerSeccoes(argv[3], lis);

    Relatorio re(lis, muni);



    re.gerarRelatorioEleitos();
    re.gerarRelatorioMaisVotados();
    re.gerarRelatorioNaoEleitosMajoritaria();
    re.gerarRelatorioEleitosBeneficiados();
    re.gerarRelatorioPartidosEVotos();
    re.gerarRelatorioPrimeiroEUltimoPorPartido();
    re.gerarRelatorioEleitosPorFaixaEtaria(argv[4]);
    re.gerarRelatorioEleitosPorGenero();
    re.gerarRelatorioVotosValidos();

    return 0;
}
