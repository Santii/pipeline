/**
* @file 	command.h
* @brief	Arquivo de cabecalho com a definicao da classe Comando
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    02/04/2017
* @date     22/04/2017
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <algorithm>

#include <sstream>
using std::stringstream;

/*! Classe de instrucoes e seus operandos */
class Comando {
public:
    static int estagios;    /**< Define a quantidade de estagios no pipeline */

    int posicao;        /**< Ciclo inicial do comando */
    string operador;    /**< Tipo do comando */
    string opgravar;    /**< Operando que grava em um registrador */
    string regist1;     /**< Operando que lê de um registrador */
    string regist2;     /**< Operando que lê de um registrador */
    string operandoext; /**< Dados adicionais de um operando */
    int jump;           /**< Definir salto para uma instrucao */
    
    /**
    * @brief Inicializacao default da classe
    */
    Comando();
    
    /**
    * @brief Funcao que verifica há presenca de conflito entre dois comandos
    * @param cmdant Comando anterior para conferencia de conflito
    * @return A situacao sobre a presenca de conflito.
    */  
    bool verificaConflito(Comando cmdant);
    
    /**
    * @brief Funcao que imprime cada comando na tela
    */
    void imprimirComando();
};

/**
* @brief Funcao que converte uma string em um Comando para montar o comando no formato do codigo Assembly
* @param s Conjunto de cada comando e seus operandos
* @return Comando com seus atributos
*/
Comando montarComando(string s);

/**
* @brief Funcao que recebe um vetor de strings e o converte em sequencia de comandos
* @param *linha Vetor de strings a ser convertido
* @param quant Quantidade de elementos no vetor de strings
* @param *codigo Vetor de comandos a ser devolvido sequenciado
* @return Retorna Vetor de inteiros com o total de ciclos na posicao 0 e o total de instrucoes na posicao 1
*/
int *sequenciarCodigo(string *linha, int quant, Comando *codigo);

/**
* @brief Funcao que imprime os ciclos de acordo com uma sequencia de codigos
* @param *total Vetor de inteiros com o total de ciclos (posicao 0) e o total de instrucoes (posicao 1)
* @param *codigo Vetor de Comandos ja sequenciados
* @param *nomesEstagios Vetor de strings com os nomes dos estagios no pipeline
*/
void imprimirResultado(int *total, Comando *codigo, string *nomes);

#endif