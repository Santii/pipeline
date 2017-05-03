/**
* @file     main.cpp
* @brief 	Arquivo de codigo principal do programa
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    02/04/2017
* @date     22/04/2017
*/

#include "files.h"
#include "command.h"

int Comando::estagios = 5; /**< Define a quantidade de estágios do pipeline */

/**
* @brief Funcao principal do programa
* @param argc Quantidade de argumentos
* @param *argv[] Localizacao do arquivo com o código Assembly
* @return Resultado
*/
int main(int argc, char* argv[]) {
    //Verifica se pelo menos dois argumentos (execucao e caminho do arquivo) estao sendo informados no momento da execucao
    if(argc < 2) {
        cout << "##################################################################################################################################" << endl;
        cout << "Por favor, execute novamente e informe a localização do arquivo, conforme mostrado abaixo:" << endl;
        cout << "1) Impressão na tela:    ./bin/pipeline.exe ./data/exemplo.dat" << endl;
        cout << "2) Impressão em arquivo: ./bin/pipeline.exe ./data/exemplo.dat > ./data/output/resultado.dat" << endl;
        cout << "Para o caso 2, o arquivo será gerado no diretório ./data/output/. E o nome fica a seu critério, 'resultado' é apenas uma sugestão" << endl;
        cout << "##################################################################################################################################" << endl;

        return 0;
    }

    //Definindo o nome de cada estagio do pipeline
    string *estagio = new string[Comando::estagios];
    estagio[0] = "IF";
    estagio[1] = "ID";
    estagio[2] = "EX";
    estagio[3] = "MEM";
    estagio[4] = "WB";

    //Verifica se o parametro com o local do arquivo eh valido
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
    Comando *codigo = new Comando[quant];
    int *total = sequenciarCodigo(linha, quant, codigo);

    //Imprime o relatório de ciclos
    imprimirResultado(total, codigo, estagio);

    //Libera memória
    delete[] estagio;
    delete[] linha;
    delete[] codigo;

    return 0;
}