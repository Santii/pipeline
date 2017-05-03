/**
* @file 	files.cpp
* @brief	Arquivo de codigo fonte com a implementacao de funcoes para a leitura do 
            arquivo com o codigo Assembly
* @author   Bianca Santiago (bianca.santiago72@gmailcom)
* @since    02/04/2017
* @date     22/04/2017
*/

#include "files.h"

/**
* @brief Funcao que carrega o arquivo com o codigo Assembly
* @param arquivo Localizacao do arquivo que vai ser lido
* @param comandos Comandos lidos do arquivo
* @param linhas Numero de linhas de dados no arquivo
* @param *mensagem Mensagem de retorno
* @return A situacao da leitura
*/
bool loadFile(string arquivo, string *comandos, int linhas, string& mensagem) {
    ifstream localizacao(arquivo);
    if(!localizacao) {
        mensagem = "Erro ao abrir arquivo! :("; //Erro ao abrir o arquivo
        return false;
    }

    mensagem = "Tudo certo ;)";
    localizacao.clear();
    localizacao.seekg(0);
    
    for(int i = 0; i < linhas; i++) //Le o arquivo ate antes da linha do total
        getline(localizacao, comandos[i]);//Lê a linha
        
    localizacao.close();
    if(mensagem == "Tudo certo ;)")
        return true;
    return false;
}

/**
* @brief Funcao que abre o arquivo com o codigo Assembly e verifica a quantidade de linhas
* @param arquivo Localizacao do arquivo que vai ser lido
* @return A quantidade de linhas lidas no arquivo (-1 em caso de erro na abertura do arquivo)
*/
int readFile(string arquivo) {
    ifstream localizacao(arquivo);
    if(!localizacao)
        return -1; //Erro ao abrir o arquivo
    
    int linhas = 0;
    string lido = "";
    while(!localizacao.eof()) { //Conta as linhas do arquivo
        getline(localizacao, lido);
        if(lido != "")
            linhas++;
    }
    localizacao.close();
    return linhas;
}