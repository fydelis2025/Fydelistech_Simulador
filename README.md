# 🔬 Simulador de Autorreplicação de Arquivos e Persistência (C++17)

Este repositório contém um modelo conceitual desenvolvido estritamente para fins de estudo, documentação acadêmica e análise de engenharia de software no Linux. O objetivo do projeto é demonstrar, de forma controlada e segura, os mecanismos lógicos de replicação e persistência frequentemente analisados por equipes de auditoria de segurança e resposta a incidentes.

> ⚠️ **AVISO LEGAL E ÉTICO:** Este código foi desenhado exclusivamente para uso educacional em ambientes de laboratório isolados (Sandboxes). Ele possui mecanismos internos de segurança (Modo de Simulação ativo por padrão) para garantir que nenhuma alteração inadvertida aconteça no sistema do usuário.

---

## 🧠 Características do Projeto

O código utiliza recursos nativos do C++17 (`std::filesystem`) para interagir com o sistema operacional, demonstrando três pilares comuns na automação de processos em segundo plano:

1. **Descoberta de Caminho de Origem:** Identificação dinâmica de onde o próprio binário está sendo executado através do link simbólico `/proc/self/exe`.
2. **Mecanismo de Replicação Controlada:** Demonstração teórica de cópia de arquivos para diretórios específicos através de uma rotina automatizada.
3. **Demonstração de Persistência:** Criação simulada de um arquivo de inicialização `.desktop` em `~/.config/autostart/` para ilustrar como o ambiente gráfico carrega rotinas de usuário no login.

---

## 🔒 Mecanismos de Segurança (Seguro por Design)

Para garantir a conformidade ética e a segurança de quem estuda o código, o programa implementa as seguintes proteções:
* **Modo de Simulação (*Dry-Run*) Padrão:** Ao ser executado normalmente, o programa apenas imprime no terminal o que ele *faria* no disco, sem copiar nenhum arquivo real.
* **Isolamento de Diretórios:** O escopo de execução padrão é limitado a pastas de testes locais (`./laboratorio_teste/`), impedindo a poluição de diretórios reais do sistema operacional.

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
* Compilador com suporte a **C++17** (como `g++`).
* Sistema operacional Linux.

### Compilação
No terminal, execute o comando abaixo para compilar o código:
```bash
g++ -std=c++17 worm.cpp -o simulador_automacao
