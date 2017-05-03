/**
* @file 	instruction.h
* @brief	Arquivo de cabecalho com a definicao da classe Instruction
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    02/04/2017
* @date     22/04/2017
*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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
class Instrucao {
public:
    static int estagios;    /**< Define a quantidade de estagios no pipeline */

    int posicao;        /**< Ciclo inicial da instrução */
    string operador;    /**< Tipo da instrução */
    string opgravar;    /**< Operando que grava em um registrador */
    string regist1;     /**< Operando que lê de um registrador */
    string regist2;     /**< Operando que lê de um registrador */
    string operandoext; /**< Dados adicionais de um operando */
    int jump;           /**< Definir salto para uma instrucao */
    
    /**
    * @brief Inicializacao default da classe
    */
    Instrucao();
    
    /**
    * @brief Funcao que verifica há presenca de conflito entre duas instruções
    * @param cmdant Instrução anterior para conferencia de conflito
    * @return A situacao sobre a presenca de conflito.
    */  
    bool verificaConflito(Instrucao cmdant);
    
    /**
    * @brief Funcao que imprime cada instrução na tela
    */
    void imprimirInstrucao();
};

/**
* @brief Funcao que converte uma string em uma Instrução para montar a instrução no formato do codigo Assembly
* @param s Conjunto de cada instrução e seus operandos
* @return Instrucao com seus atributos
*/
Instrucao montarInstrucao(string s);

/**
* @brief Funcao que recebe um vetor de strings e o converte em sequencia de instruções
* @param *linha Vetor de strings a ser convertido
* @param quant Quantidade de elementos no vetor de strings
* @param *codigo Vetor de instruções a ser devolvido sequenciado
* @return Retorna Vetor de inteiros com o total de ciclos na posicao 0 e o total de instrucoes na posicao 1
*/
int *sequenciarCodigo(string *linha, int quant, Instrucao *codigo);

/**
* @brief Funcao que imprime os ciclos de acordo com uma sequencia de codigos
* @param *total Vetor de inteiros com o total de ciclos (posicao 0) e o total de instrucoes (posicao 1)
* @param *codigo Vetor de instruções ja sequenciados
* @param *nomesEstagios Vetor de strings com os nomes dos estagios no pipeline
*/
void imprimirResultado(int *total, Instrucao *codigo, string *nomes);

#endif