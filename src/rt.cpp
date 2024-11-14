#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <iomanip> // Para a formatação da data
#include <dirent.h>

// Função para exibir o uso com cores
void exibirUso()
{
    // Cores ANSI
    const std::string reset = "\033[0m";
    const std::string vermelho = "\033[1;31m";
    const std::string verde = "\033[32m";
    const std::string azul = "\033[1;34m";
    const std::string amarelo = "\033[1;33m";
    const std::string branco = "\033[1;37m";

    std::cout << reset << verde << "Uso: rms <caminho_do_arquivo_ou_diretorio>" << reset << std::endl;
    std::cout << reset << std::endl;
    std::cout << reset << "Este programa move um arquivo ou diretório para a Lixeira no Linux." << std::endl;
    std::cout << reset << "Quando movido para a Lixeira, o arquivo/diretório é armazenado em " << std::endl;
    std::cout << reset << verde << "~/.local/share/Trash/files/" << std::endl;
    std::cout << reset << "e uma informação sobre a exclusão é salva em" << std::endl;
    std::cout << reset << verde << "~/.local/share/Trash/info/." << std::endl;
    std::cout << std::endl;
    std::cout << reset << amarelo << "Opções:" << reset << std::endl;
    std::cout << reset << "  " << verde << "-h" << reset << "     Exibe este help." << std::endl;
    std::cout << std::endl;
    std::cout << reset << azul << "Exemplo de uso:" << reset << std::endl;
    std::cout << "  " << "./mover_para_lixeira /caminho/para/arquivo_ou_diretorio" << reset << std::endl;
}

void moverParaLixeira(const std::string &caminho)
{
    // Obtém o diretório de Lixeira do usuário
    const char *homeDir = getenv("HOME");
    if (homeDir == nullptr)
    {
        std::cerr << "Não foi possível obter o diretório HOME." << std::endl;
        return;
    }

    std::string lixeiraDir = std::string(homeDir) + "/.local/share/Trash/files/";
    std::string trashInfoDir = std::string(homeDir) + "/.local/share/Trash/info/";

    // Cria os diretórios de Lixeira, se não existirem
    struct stat st = {0};
    if (stat(lixeiraDir.c_str(), &st) == -1)
    {
        if (mkdir(lixeiraDir.c_str(), 0700) != 0)
        {
            std::cerr << "Erro ao criar o diretório da Lixeira." << std::endl;
            return;
        }
    }

    if (stat(trashInfoDir.c_str(), &st) == -1)
    {
        if (mkdir(trashInfoDir.c_str(), 0700) != 0)
        {
            std::cerr << "Erro ao criar o diretório de informações da Lixeira." << std::endl;
            return;
        }
    }

    // Obtém o nome do arquivo/diretório a partir do caminho
    std::string nomeItem = caminho.substr(caminho.find_last_of("/\\") + 1);
    std::string novoCaminho = lixeiraDir + nomeItem;

    // Verifica se o item já existe na Lixeira e, se necessário, gera um novo nome para ele
    int contador = 1;
    while (stat(novoCaminho.c_str(), &st) == 0)
    {
        novoCaminho = lixeiraDir + nomeItem + "." + std::to_string(contador);
        contador++;
    }

    // Verifica se é um diretório ou um arquivo
    if (S_ISDIR(st.st_mode))
    {
        // Mover diretório (com conteúdo)
        if (rename(caminho.c_str(), novoCaminho.c_str()) != 0)
        {
            std::cerr << "Erro ao mover o diretório para a Lixeira: " << strerror(errno) << std::endl;
            return;
        }
    }
    else if (S_ISREG(st.st_mode))
    {
        // Mover arquivo
        if (rename(caminho.c_str(), novoCaminho.c_str()) != 0)
        {
            std::cerr << "Erro ao mover o arquivo para a Lixeira: " << strerror(errno) << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "Tipo de arquivo não suportado: " << caminho << std::endl;
        return;
    }

    // Criação da data e hora atual no formato desejado: YYYY-MM-DDTHH:MM:SS
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now); // Obtém a data e hora local
    std::ostringstream dateStream;

    // Formata a data no formato "YYYY-MM-DDTHH:MM:SS"
    dateStream << std::put_time(localTime, "%Y-%m-%dT%H:%M:%S");

    std::string formattedDate = dateStream.str();

    // Cria o arquivo [Trash Info] com as informações
    std::string infoFilePath = trashInfoDir + nomeItem + ".trashinfo";
    std::ofstream infoFile(infoFilePath);
    if (!infoFile)
    {
        std::cerr << "Erro ao criar o arquivo [Trash Info]." << std::endl;
        return;
    }

    // Escreve as informações no arquivo [Trash Info]
    infoFile << "[Trash Info]" << std::endl;
    infoFile << "Path=" << caminho << std::endl;               // Caminho completo do arquivo ou diretório
    infoFile << "DeletionDate=" << formattedDate << std::endl; // Data de exclusão formatada

    infoFile.close();

    std::cout << "Item movido para a Lixeira: " << novoCaminho << std::endl;
    std::cout << "Informações salvas no arquivo: " << infoFilePath << std::endl;
}

int main(int argc, char *argv[])
{
    // Se nenhum parâmetro for passado ou se o parâmetro for "-h", exibe as informações de uso
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "-h"))
    {
        exibirUso();
        return 0;
    }

    // Verifica se o usuário forneceu um caminho válido
    std::string caminhoItem = argv[1];

    // Se o caminho não for absoluto, assume o diretório atual
    if (caminhoItem[0] != '/')
    {
        char *cwd = getcwd(nullptr, 0);
        if (cwd != nullptr)
        {
            caminhoItem = std::string(cwd) + "/" + caminhoItem;
            free(cwd);
        }
        else
        {
            std::cerr << "Erro ao obter o diretório atual." << std::endl;
            return 1;
        }
    }

    // Verifica se o arquivo/diretório existe
    struct stat buffer;
    if (stat(caminhoItem.c_str(), &buffer) != 0)
    {
        std::cerr << "Arquivo ou diretório não encontrado: " << caminhoItem << std::endl;
        return 1;
    }

    // Mover o arquivo ou diretório para a Lixeira
    moverParaLixeira(caminhoItem);

    return 0;
}