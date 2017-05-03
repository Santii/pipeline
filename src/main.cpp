/**
* @file     main.cpp
* @brief 	Arquivo de código principal do programa
* @author   Bianca Santiago (bianca.santiago72@gmail.com.
* @since    12/04/2017
* @date     22/04/2017
*/
#include <iostream>
#include <string>

#include "files.h"
#include "command.h"

using namespace std;

int Comando::estagios = 5; /**< Define a quantidade de estágios do pipeline */

/**
* @brief        Função principal do programa
* @param[in]	argc	Quantidade de argumentos
* @param[in]    *argv[]	Localização do arquivo com o código Assembly
* @return		Retorno
*/
int main(int argc, char* argv[]) {
    //Testa se o parâmetro com o nome do arquivo existe
    if(argc < 2) {
        cout << "Por favor, execute novamente e informe a localização do arquivo!" << endl;
        cout << "Impressão na tela:    ./bin/pipeline.exe ./data/exemplo.asm" << endl;
        cout << "Impressão em arquivo: ./bin/pipeline.exe ./data/exemplo.asm > resultado.asm (o arquivo será gerado no diretório raiz)" << endl;
        return 0;
    }

    //Definir o nome de cada estágio do pipeline
    string *estagio = new string[Comando::estagios];
    estagio[0] = "IF";
    estagio[1] = "ID";
    estagio[2] = "EX";
    estagio[3] = "MEM";
    estagio[4] = "WB";

    //Testa se o parâmetro com o nome do arquivo é valido
    int quant = readFile(argv[1]);
    if(quant <= 0) {
        cout << "Parâmetro inválido! Verifique o local do arquivo." << endl;
        delete[] estagio;
        return 0;
    }

    //Captura todas as linhas do arquivo texto
    string *linha = new string[quant];
    string mensagem = "";
    if(!loadFile(argv[1], linha, quant, mensagem)) {
        cout << mensagem << endl;
        delete[] estagio;
        delete[] linha;
        return 0;
    }

    //Sequencia o código (considerando os saltos) e definindo os conflitos
    Comando *com = new Comando[quant];
    int *totais = sequenciarCodigo(linha, quant, com);

    //Imprime o relatório de ciclos
    imprimirCiclos(totais, com, estagio);

    //Libera memória
    delete[] estagio;
    delete[] linha;
    delete[] com;

    return 0;
}