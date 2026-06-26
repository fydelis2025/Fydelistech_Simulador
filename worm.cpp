#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Classe utilitária para gerenciar as saídas visuais de forma elegante
class Logger {
public:
    static void info(const std::string& msg) { std::cout << "[*] " << msg << "\n"; }
    static void success(const std::string& msg) { std::cout << "[+] " << msg << "\n"; }
    static void error(const std::string& msg) { std::cerr << "[-] " << msg << "\n"; }
    static void warning(const std::string& msg) { std::cout << "[!] " << msg << "\n"; }
};

class SimuladorAutomacao {
private:
    fs::path caminhoOrigem;
    std::string nomeArquivo;
    std::vector<fs::path> caminhosAlvo;
    bool modoSimulacao; // Flag de segurança

    void obterCaminhoProprio() {
        try {
            caminhoOrigem = fs::canonical("/proc/self/exe");
            nomeArquivo = caminhoOrigem.filename().string();
        } catch (const fs::filesystem_error& e) {
            Logger::error("Erro fatal ao localizar binario originario: " + std::string(e.what()));
        }
    }

    void processarCopia(const fs::path& destino) {
        if (modoSimulacao) {
            Logger::success("[SIMULAÇÃO] Copia seria criada em: " + destino.string());
            return;
        }

        try {
            fs::copy_file(caminhoOrigem, destino, fs::copy_options::overwrite_existing);
            Logger::success("Arquivo replicado com sucesso: " + destino.string());
        } catch (const fs::filesystem_error& e) {
            // Tratamento detalhado de erros baseado no código do sistema operacional
            if (e.code() == std::errc::permission_denied) {
                Logger::error("Falha: Permissao negada para escrever em " + destino.parent_path().string());
            } else {
                Logger::error("Falha no sistema de arquivos: " + std::string(e.code().message()));
            }
        }
    }

public:
    // Construtor exige definir se a execução é real ou apenas simulação
    SimuladorAutomacao(bool apenasSimular) : modoSimulacao(apenasSimular) {
        obterCaminhoProprio();
        
        // Define caminhos de teste relativos e seguros por padrão
        caminhosAlvo = {
            "./laboratorio_teste/pasta_a/",
            "./laboratorio_teste/pasta_b/"
        };
    }

    void executarMecanismo() {
        Logger::info("Iniciando rotina de replicacao conceitual...");
        if (modoSimulacao) {
            Logger::warning("MODO DE SIMULAÇÃO ATIVO. Nenhuma alteracao sera feita no disco.");
        }

        // Garante a existência dos diretórios de teste antes de prosseguir
        for (const auto& pasta : caminhosAlvo) {
            if (!fs::exists(pasta) && !modoSimulacao) {
                fs::create_directories(pasta);
            }
            
            fs::path destino = pasta / nomeArquivo;
            processarCopia(destino);
        }
    }
};

int main(int argc, char* argv[]) {
    std::cout << "==================================================\n";
    std::cout << "  ESTUDO DE ENGENHARIA: AUTOREPLICAÇÃO DE ARQUIVOS \n";
    std::cout << "==================================================\n\n";

    bool apenasSimular = true;

    // Se o usuário passar o argumento "--real", o programa executa de verdade
    if (argc > 1 && std::string(argv[1]) == "--real") {
        apenasSimular = false;
    }

    SimuladorAutomacao sim(apenasSimular);
    sim.executarMecanismo();

    if (apenasSimular) {
        std::cout << "\n[Dica] Para executar modificacoes reais no disco, rode com: ./programa --real\n";
    }

    return 0;
}
