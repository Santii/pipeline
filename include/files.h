/**
* @file 	arquivos.h
* @brief	Arquivo de cabeçalho com a definição de funções para a gravação de arquivos
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    20/04/2017
* @date     20/04/2017
*/

#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;

#include <sstream>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include "command.h"

/**
* @brief Funcao que carrega o arquivo com o codigo Assembly
* @param arquivo Localizacao do arquivo que vai ser lido
* @param comandos Comandos lidos do arquivo
* @param linhas Numero de linhas de dados no arquivo
* @param *mensagem Mensagem de retorno
* @return A situacao da leitura
*/
bool loadFile(string arquivo, string *comandos, int linhas, string& mensagem);

/**
* @brief Funcao que abre o arquivo com o codigo Assembly e verifica a quantidade de linhas
* @param arquivo Localizacao do arquivo que vai ser lido
* @return A quantidade de linhas lidas no arquivo (-1 em caso de erro na abertura do arquivo)
*/
int readFile(string arquivo);

#endif