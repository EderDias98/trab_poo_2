#include "leitor.hpp"



// Remove aspas do início e do fim, e trim
string Leitor::removerAspas(const string& s) {
    string out = s;
    // Remove espaços extras
    out.erase(0, out.find_first_not_of(" \t\r\n"));
    out.erase(out.find_last_not_of(" \t\r\n") + 1);
    // Remove aspas
    if (!out.empty() && out.front() == '"') out.erase(out.begin());
    if (!out.empty() && out.back() == '"') out.pop_back();
    return out;
}

void Leitor::lerCandidatos(const string& caminhoArquivo, Listas& lis) {
    ifstream file(caminhoArquivo);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo: " << caminhoArquivo << endl;
        return;
    }

    string linha;
    getline(file, linha); // Lê o cabeçalho

    if (linha.empty()) {
        cerr << "Arquivo vazio!" << endl;
        return;
    }

    while (getline(file, linha)) {
        vector<string> campos;
        string campo;
        stringstream ss(linha);

        while (getline(ss, campo, ';')) {
       
            campos.push_back(removerAspas(campo));
        }

        try {
            if (campos.size() < 49) continue; // Evita out_of_range

            string sgUE = campos[11];
            string cdCargo = campos[13];

            if (cdCargo != "13") continue; // Apenas vereadores

            string nrCandidato = campos[16];
            string nmUrnaCandidato = campos[18];
            string nrPartido = campos[25];
            string sgPartido = campos[26];
            string nrFederacao = campos[28];
            string dtNascimento = campos[36];
            string cdSitTotTurno = campos[48];

            if (cdSitTotTurno == "-1") continue; // Candidatura inválida

            string cdGenero = campos[38];

            // Criar candidato e adicionar no objeto Listas
            Candidato candidato(
                sgUE, nrCandidato, nmUrnaCandidato,
                nrPartido, sgPartido, nrFederacao, dtNascimento,
                cdSitTotTurno, cdGenero
            );

            lis.addCandidato(candidato);
            lis.adicionaPartido(Partido(stoi(nrPartido), sgPartido));

        } catch (const exception& e) {
            cerr << "Erro na linha: " << linha << "\n" << e.what() << endl;
        }
    }
}

void Leitor::lerSeccoes(const string& caminhoArquivo, Listas& lis) {
    ifstream file(caminhoArquivo);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo: " << caminhoArquivo << endl;
        return;
    }

    string linha;
    getline(file, linha); // Lê cabeçalho

    if (linha.empty()) {
        cerr << "Arquivo vazio!" << endl;
        return;
    }

    while (getline(file, linha)) {
        vector<string> campos;
        string campo;
        stringstream ss(linha);

        while (getline(ss, campo, ';')) {
            campos.push_back(removerAspas(campo));
        }

        try {
            if (campos.size() < 22) continue;

            string cdCargo = campos[17];
            if (cdCargo != "13") continue; // só vereador

            string cdMunicipio = campos[13];
            string nrVotavel = campos[19];

            // Ignora votos inválidos
            if (nrVotavel == "95" || nrVotavel == "96" ||
                nrVotavel == "97" || nrVotavel == "98") {
                continue;
            }

            string qtVotos = campos[21];

            Seccao seccao(cdMunicipio, nrVotavel, qtVotos);
            lis.addSeccao(seccao);

        } catch (const exception& e) {
            cerr << "Erro na linha: " << linha << "\n" << e.what() << endl;
        }
    }

    
}
