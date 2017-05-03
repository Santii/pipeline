/**
* @file 	command.h
* @brief	Arquivo de cabeçalho com a definição da classe Comando
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    12/04/2017
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

/*! Classe para representar instruções e seus operandos */
class Comando {
public:
    static int estagios;    /**< Define a quantidade de estágios no pipeline */

    int posicao;            /**< Ciclo inicial do comando */
    string operador;            /**< Tipo do comando (instrução) */
    string opgravar;         /**< Operando que grava em um registrador */
    string regist1;           /**< Operando que lê de um registrador */
    string regist2;           /**< Operando que lê de um registrador */
    string opextra;         /**< Dados adicionais de um operando */
    int jump;              /**< Definir salto para uma instrução */
    
    /**
    * @brief     	Inicialização default da classe
    */
    Comando();
    
    /**
    * @brief     	Função que detecta conflito entre dois comandos
    * @param[in] 	c Comando anterior para referência de conflito
    * @return    	Retorna true se houve conflito.
    */
    bool detConflito(Comando c);
    
    /**
    * @brief     	Função que imprime na tela um comando
    */
    void imprimirComando();
};

/**
* @brief     	Função que converte uma string em um Comando
* @param[in] 	s String com o comando e seus operandos
* @return    	Retorna um Comando com seus atributos
*/
Comando montarComando(string s);

/**
* @brief     	Função que recebe um vetor de strings e o converte em sequencia de comandos
* @param[in] 	*linha Vetor de strings à ser convertido
* @param[in]    qtde Quantidade de elementos no vetor de strings
* @param[out]   *com Vetor de comandos à ser devolvido sequenciado
* @return    	Retorna um vetor de inteiros com o total de ciclos na posição 0 e o total de instruções na posição 1
*/
int *sequenciarCodigo(string *linha, int qtde, Comando *com);

/**
* @brief     	Função que imprime os ciclos de acordo com uma sequencia de códigos
* @param[in] 	*totais Vetor de inteiros com o total de ciclos (posição 0) e o total de instruções (posição 1)
* @param[in]    *com Vetor de Comandos já sequenciados
* @param[in]    *nomes Vetor de strings com os nomes dos estágios no pipeline
*/
void imprimirCiclos(int *totais, Comando *com, string *nomes);

#endif