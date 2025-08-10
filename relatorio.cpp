#include "relatorio.hpp"

int calcularIdade(const tm& nascimento, const tm& referencia) {
    int idade = referencia.tm_year - nascimento.tm_year;

    // Ajusta se o aniversário ainda não ocorreu no ano de referência
    if (referencia.tm_mon < nascimento.tm_mon ||
        (referencia.tm_mon == nascimento.tm_mon && referencia.tm_mday < nascimento.tm_mday)) {
        idade--;
    }

    return idade;
}

Relatorio::Relatorio( const Listas& lis, int municipio)
    : municipio(municipio), qtdEleitos(0)
{
    // Filtra candidatos do município
    candidatosDoMunicipio.clear();
    for (const auto& c : lis.getCandidatos()) {
        if (c.getSgUE() == municipio) {
            candidatosDoMunicipio.push_back(c);
        }
    }

    // Filtra seccoes do município
    seccoesDoMunicipio.clear();
    for (const auto& s : lis.getSeccoes()) {
        if (s.getCdMunicipio() == municipio) {
            seccoesDoMunicipio.push_back(s);
        }
    }
    
    eleitos.clear();
    qtdEleitos = 0;
    for (const auto& c : candidatosDoMunicipio) {
        int sit = c.getCdSitTotTurno();
        if (sit == 2 || sit == 3) {
            eleitos.push_back(c);
            qtdEleitos++;
        }
    }


    mapaPartidos = lis.getPartidos();

    maisVotados.clear();
    maisVotadosN.clear();
    eleitosOrdenados.clear();
    votosPorCandidato.clear();
}

int Relatorio::contarDigitos(int numero) {
    if (numero == 0) return 1;
    int count = 0;
    int n = abs(numero);
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}


void Relatorio::gerarRelatorioEleitos() {
    // Filtra eleitos


    set<int> numerosEleitos;
    for (const auto& c : eleitos) {
        numerosEleitos.insert(c.getNrCandidato());
    }

    votosPorCandidato.clear();
    for (const auto& s : seccoesDoMunicipio) {
        if (numerosEleitos.count(s.getNrVotavel()) > 0) {
            votosPorCandidato[s.getNrVotavel()] += s.getQtVotos();
        }
    }

    // Ordena eleitos por votos decrescente
    eleitosOrdenados = eleitos;
    sort(eleitosOrdenados.begin(), eleitosOrdenados.end(),
        [this](const Candidato& a, const Candidato& b) {
            int va = votosPorCandidato.count(a.getNrCandidato()) ? votosPorCandidato[a.getNrCandidato()] : 0;
            int vb = votosPorCandidato.count(b.getNrCandidato()) ? votosPorCandidato[b.getNrCandidato()] : 0;
            return va > vb;
        });

    cout << "Número de vagas: " << qtdEleitos << "\n\n";
    cout << "Vereadores eleitos:\n";

    int i = 1;
    for (const auto& c : eleitosOrdenados) {
        int votos = votosPorCandidato.count(c.getNrCandidato()) ? votosPorCandidato[c.getNrCandidato()] : 0;
        cout << i << " - " << c.getNmUrnaCandidato() << " (" << c.getSgPartido() << ", " << votos << " votos)\n";
        i++;
    }
    cout << "\n\n";
}

void Relatorio::gerarRelatorioMaisVotados() {
    set<int> numerosCandidatos;
    for (const auto& c : candidatosDoMunicipio) {
        numerosCandidatos.insert(c.getNrCandidato());
    }

    map<int, int> votosLocal;
    for (const auto& s : seccoesDoMunicipio) {
        if (numerosCandidatos.count(s.getNrVotavel()) > 0) {
            votosLocal[s.getNrVotavel()] += s.getQtVotos();
        }
    }

    maisVotados = candidatosDoMunicipio;
    sort(maisVotados.begin(), maisVotados.end(),
        [&votosLocal](const Candidato& a, const Candidato& b) {
            int va = votosLocal.count(a.getNrCandidato()) ? votosLocal.at(a.getNrCandidato()) : 0;
            int vb = votosLocal.count(b.getNrCandidato()) ? votosLocal.at(b.getNrCandidato()) : 0;
            return va > vb;
        });

    maisVotadosN.clear();
    int limit = min(qtdEleitos, (int)maisVotados.size());
    for (int i = 0; i < limit; i++) {
        maisVotadosN.push_back(maisVotados[i]);
    }

    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";

    for (int i = 0; i < (int)maisVotados.size(); i++) {
        maisVotados[i].setPosicaoRankMaisVotado(i + 1);
        int votos = votosLocal.count(maisVotados[i].getNrCandidato()) ? votosLocal.at(maisVotados[i].getNrCandidato()) : 0;
        maisVotados[i].setVotos(votos);
    }

    for (const auto& c : maisVotadosN) {
        cout << c.getPosicaoRankMaisVotado() << " - " << c.getNmUrnaCandidato()
                  << " (" << c.getSgPartido() << ", " << c.getVotos() << " votos)\n";
    }

    cout << "\n\n";
}

void Relatorio::gerarRelatorioNaoEleitosMajoritaria() {
    vector<Candidato> seriamEleitosMajoritaria;
    for (const auto& m : maisVotadosN) {
        auto it = find_if(eleitosOrdenados.begin(), eleitosOrdenados.end(),
            [&m](const Candidato& c) { return c.getNrCandidato() == m.getNrCandidato(); });
        if (it == eleitosOrdenados.end()) {
            seriamEleitosMajoritaria.push_back(m);
        }
    }

    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n"
              << "(com sua posição no ranking de mais votados)\n";

    for (const auto& c : seriamEleitosMajoritaria) {
        cout << c.getPosicaoRankMaisVotado() << " - " << c.getNmUrnaCandidato()
                  << " (" << c.getSgPartido() << ", " << c.getVotos() << " votos)\n";
    }
    cout << "\n\n";
}

void Relatorio::gerarRelatorioEleitosBeneficiados() {
    vector<Candidato> beneficiados;
    for (const auto& e : eleitosOrdenados) {
        auto it = find_if(maisVotadosN.begin(), maisVotadosN.end(),
            [&e](const Candidato& c) { return c.getNrCandidato() == e.getNrCandidato(); });
        if (it == maisVotadosN.end()) {
            beneficiados.push_back(e);
        }
    }

    cout << "Eleitos, que se beneficiaram do sistema proporcional:\n"
              << "(com sua posição no ranking de mais votados)\n";

    for (const auto& c : beneficiados) {
        int votos = votosPorCandidato.count(c.getNrCandidato()) ? votosPorCandidato[c.getNrCandidato()] : 0;
        cout << c.getPosicaoRankMaisVotado() << " - " << c.getNmUrnaCandidato()
                  << " (" << c.getSgPartido() << ", " << votos << " votos)\n";
    }
    cout << "\n\n";
}

void Relatorio::gerarPartidos() {
    for (auto& c : candidatosDoMunicipio) {
        int numeroPartido = c.getNrPartido();
        Partido* p = nullptr;

        auto it = mapaPartidos.find(numeroPartido);
        if (it != mapaPartidos.end()) {
            p = &(it->second);
        }

        if (p != nullptr) {
            p->adicionarVotosNominais(c.getVotos());
            if (c.getCdSitTotTurno() == 2 || c.getCdSitTotTurno() == 3) {
                p->incrementarEleito();
            }
            if (c.getVotos() > 0) {
                p->adicionarCandidato(c);
            }
        }
    }
}

void Relatorio::contarVotosDeLegenda() {
    set<int> numerosDosPartidos;
    for (const auto& entry : mapaPartidos) {
        numerosDosPartidos.insert(entry.first);
    }

    map<int, int> votosPorLegenda;
    for (const auto& s : seccoesDoMunicipio) {
        if (numerosDosPartidos.count(s.getNrVotavel()) > 0) {
            votosPorLegenda[s.getNrVotavel()] += s.getQtVotos();
        }
    }

    for (const auto& entry : votosPorLegenda) {
        int numeroPartido = entry.first;
        int votosLegenda = entry.second;

        auto it = mapaPartidos.find(numeroPartido);
        if (it != mapaPartidos.end()) {
            it->second.adicionarVotosLegenda(votosLegenda);
        }
    }
}

void Relatorio::gerarRelatorioPartidosEVotos() {
    gerarPartidos();
    contarVotosDeLegenda();

    cout << "Votação dos partidos e número de candidatos eleitos:\n";

    // Ordenar por total de votos decrescente
    vector <Partido> partidosOrdenados;
    for (auto& par : mapaPartidos) {
        partidosOrdenados.push_back(par.second);
    }

    sort(partidosOrdenados.begin(), partidosOrdenados.end(),
        [](const Partido& a, const Partido& b) {
            return a.getTotalVotos() > b.getTotalVotos();
        });

    for (auto& p : partidosOrdenados) {
        p.imprime();
    }

    cout << "\n\n";
}

void Relatorio::gerarRelatorioPrimeiroEUltimoPorPartido() {
    cout << "Primeiro e último colocados de cada partido:\n";

    int contador = 1;

    // Ordena partidos por voto máximo do candidato
    vector<reference_wrapper<Partido>> partidosOrdenados;
    for (auto& par : mapaPartidos) {
        partidosOrdenados.push_back(par.second);
    }

    sort(partidosOrdenados.begin(), partidosOrdenados.end(),
        [](const Partido& a, const Partido& b) {
            int maxA = 0, maxB = 0;
            if (!a.getCandidatosDoPartido().empty())
                maxA = max_element(a.getCandidatosDoPartido().begin(), a.getCandidatosDoPartido().end(),
                    [](const Candidato& c1, const Candidato& c2) { return c1.getVotos() < c2.getVotos(); })->getVotos();
            if (!b.getCandidatosDoPartido().empty())
                maxB = max_element(b.getCandidatosDoPartido().begin(), b.getCandidatosDoPartido().end(),
                    [](const Candidato& c1, const Candidato& c2) { return c1.getVotos() < c2.getVotos(); })->getVotos();
            return maxA > maxB;
        });

    for (auto& p : partidosOrdenados) {
        Partido& partido = p.get();
        auto& lista = partido.getCandidatosDoPartido();

        if (lista.size() < 2) continue;

        // Ordena candidatos por votos decrescentes
        vector<Candidato> copiaLista = lista;
        sort(copiaLista.begin(), copiaLista.end(),
            [](const Candidato& a, const Candidato& b) {
                return a.getVotos() > b.getVotos();
            });

        const Candidato& maisVotado = copiaLista.front();
        const Candidato& menosVotado = copiaLista.back();

        string a = (maisVotado.getVotos() < 2) ? "voto" : "votos";
        string b = (menosVotado.getVotos() < 2) ? "voto" : "votos";

        cout << contador << " - " << partido.getSigla() << " - " << partido.getNumero() << ", "
                  << maisVotado.getNmUrnaCandidato() << " (" << maisVotado.getNrCandidato() << ", "
                  << maisVotado.getVotos() << " " << a << ") / "
                  << menosVotado.getNmUrnaCandidato() << " (" << menosVotado.getNrCandidato() << ", "
                  << menosVotado.getVotos() << " " << b << ")\n";

        contador++;
    }

    cout << "\n\n";
}

void Relatorio::gerarRelatorioEleitosPorFaixaEtaria(const string &data) {
    int faixaMenor30 = 0;
    int faixa30a39 = 0;
    int faixa40a49 = 0;
    int faixa50a59 = 0;
    int faixa60ouMais = 0;

    int totalEleitos = (int)eleitosOrdenados.size();

    for (const auto& c : eleitosOrdenados) {
        // Calcula idade em anos baseado na data da eleição (lis.dataEleicao)
        auto nascimento = c.getDtNascimento();
        tm eleicao;
        
        istringstream de(data);
        de >> get_time(&eleicao, "%d/%m/%Y");

        int idade = calcularIdade(nascimento,eleicao);


        if (idade < 30)
            faixaMenor30++;
        else if (idade < 40)
            faixa30a39++;
        else if (idade < 50)
            faixa40a49++;
        else if (idade < 60)
            faixa50a59++;
        else
            faixa60ouMais++;
    }

    cout << "Eleitos, por faixa etária (na data da eleição):\n";

    cout << "Idade < 30: " << faixaMenor30 << " (" << fixed << setprecision(2) << percentual(faixaMenor30, totalEleitos) << "%)\n";
    cout << "30 <= Idade < 40: " << faixa30a39 << " (" << percentual(faixa30a39, totalEleitos) << "%)\n";
    cout << "40 <= Idade < 50: " << faixa40a49 << " (" << percentual(faixa40a49, totalEleitos) << "%)\n";
    cout << "50 <= Idade < 60: " << faixa50a59 << " (" << percentual(faixa50a59, totalEleitos) << "%)\n";
}

void Relatorio::gerarRelatorioEleitosPorGenero() {
    int feminino = 0;
    int masculino = 0;

    int totalEleitos = static_cast<int>(this->eleitosOrdenados.size());

    for (const Candidato& c : this->eleitosOrdenados) {
        if (c.getGenero() == Candidato::Genero::MASCULINO) {
            masculino++;
        } else {
            feminino++;
        }
    }

    cout << "Eleitos, por gênero:\n";

    cout << "Feminino: " << feminino
              << " (" << fixed << setprecision(2)
              << percentual(feminino, totalEleitos) << "%)\n";

    cout << "Masculino: " << masculino
              << " (" << fixed << setprecision(2)
              << percentual(masculino, totalEleitos) << "%)\n\n";
}



// Dentro da classe Relatorio
double Relatorio::percentual(int quantidade, int total) {
    if (total == 0)
        return 0.0;
    return (quantidade * 100.0) / total;
}

void Relatorio::gerarRelatorioVotosValidos() {
    int votosNominais = 0;
    int votosLegenda = 0;

    // mapaPartidos é um map<int, Partido>
    for (const auto& par : this->mapaPartidos) {
        const Partido& p = par.second;
        votosNominais += p.getVotosNominais();
        votosLegenda += p.getVotosLegenda();
    }

    int totalValidos = votosNominais + votosLegenda;

    cout << fixed << setprecision(0);
    cout << "Total de votos válidos: " << static_cast<float>(totalValidos) << "\n";

    cout << "Total de votos nominais: " << static_cast<float>(votosNominais)
              << " (" << fixed << setprecision(2)
              << percentual(votosNominais, totalValidos) << "%)\n";

    cout << "Total de votos de legenda: " << static_cast<float>(votosLegenda)
              << " (" << fixed << setprecision(2)
              << percentual(votosLegenda, totalValidos) << "%)\n";
}

