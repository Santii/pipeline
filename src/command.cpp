/**
* @file 	command.cpp
* @brief	Arquivo de código fonte com  a implementação da classe Comando
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    12/04/2017
* @date     22/04/2017
*/

#include "command.h"

/**
* @brief     	Inicialização default da classe
*/
Comando::Comando() { 
    posicao  =  0;
    operador = "";
    opgravar = "";
    regist1  = "";
    regist2  = "";
    opextra  = "";
    jump     =  0;
}

/**
* @brief     	Função que detecta conflito entre dois comandos
* @param[in] 	cmdant Comando anterior para referência de conflito
* @return    	Retorna true se houve conflito.
*/
bool Comando::detConflito(Comando cmdant) {
    //Se operando anterior que grava for algum registrador lido agora = conflito
    if((cmdant.opgravar != "") && ((regist1 == cmdant.opgravar) || (regist2 == cmdant.opgravar)  || (opgravar == cmdant.opgravar))) 
        return true;            //Tem dependência
    return false;               //Não tem dependência
}

/**
* @brief     	Função que imprime na tela um comando
*/
void Comando::imprimirComando() {
    if((operador == "add") || (operador == "sub")) {
        cout << operador << ", " << opgravar << ", " << regist1 << ", " << regist2;
        return;
    }
    if(operador == "lw") {
        cout << operador << ", " << opgravar << ", " << opextra << "(" << regist1 << ")";
        return;
    }
    if(operador == "sw") {
        cout << operador << ", " << regist1 << ", " << opextra << "(" << opgravar << ")";
        return;
    }
    if((operador == "beq") || (operador == "bne")){
        cout << operador << ", " << regist1 << ", " << regist2 << ", " << jump;
        return;
    }
    if(operador == "j"){
        cout << operador << ", " << jump;
        return;
    }
    cout << "Tipo desconhecido: " << operador;
}

/**
* @brief     	Função que converte uma string em um Comando
* @param[in] 	s String com o comando e seus operandos
* @return    	Retorna um Comando com seus atributos
*/
Comando montarComando(string s) {
    Comando retorno;
    stringstream ss(s);
    stringstream sa;
    string lido = "";
    
    getline(ss, retorno.operador, ' ');
    if((retorno.operador == "add") || retorno.operador == "sub") {
        getline(ss, retorno.opgravar, ',');
        getline(ss, retorno.regist1, ',');
        getline(ss, retorno.regist2);
    }
    if(retorno.operador == "lw") {      /**< Em caso de lw o extra é o adicional de memória. Ex.: o valor 4 no comando lw $t1, 4($s0) */
        getline(ss, retorno.opgravar, ',');
        getline(ss, lido);
        int pos1 = lido.find('(');
        int pos2 = lido.find(')');
        retorno.opextra = lido.substr(0, pos1);                     //Separa o registrador do adicional
        retorno.regist1 = lido.substr(pos1+1, pos2 - pos1 - 1);
    }
    if(retorno.operador == "sw") {
        getline(ss, retorno.regist1, ',');
        getline(ss, lido);
        int pos1 = lido.find('(');
        int pos2 = lido.find(')');
        retorno.opextra = lido.substr(0, pos1);                     //Separa o registrador do adicional
        retorno.opgravar = lido.substr(pos1 + 1, pos2 - pos1 - 1);
    }
    if((retorno.operador == "beq") || (retorno.operador == "bne")) { 
        getline(ss, retorno.regist1, ',');
        getline(ss, retorno.regist2, ',');
        getline(ss, lido);
        sa << lido;
        sa >> retorno.jump;//Converte string para int
    }
    if(retorno.operador == "j") {
        string lido = "";
        getline(ss, lido);
        sa << lido;
        sa >> retorno.jump;//Converte string para int
    }

    //Remove espaços
    retorno.opgravar.erase(std::remove(retorno.opgravar.begin(), retorno.opgravar.end(), ' '), retorno.opgravar.end());
    retorno.regist1.erase(std::remove(retorno.regist1.begin(),     retorno.regist1.end(), ' '),   retorno.regist1.end());
    retorno.regist2.erase(std::remove(retorno.regist2.begin(),     retorno.regist2.end(), ' '),   retorno.regist2.end());
    retorno.opextra.erase(std::remove(retorno.opextra.begin(), retorno.opextra.end(), ' '), retorno.opextra.end());
    
    return retorno;
}

/**
* @brief     	Função que recebe um vetor de strings e o converte em sequencia de comandos
* @param[in] 	*linha Vetor de strings à ser convertido
* @param[in]    quant Quantidade de elementos no vetor de strings
* @param[out]   *com Vetor de comandos à ser devolvido sequenciado
* @return    	Retorna um vetor de inteiros com o total de ciclos na posição 0 e o total de instruções na posição 1
*/
int *sequenciarCodigo(string *linha, int quant, Comando *com) {
    int *ret = new int[2];
    int j = 0, pos = 0;
    ret[0] = 0;     //Zera o contador de ciclos
    ret[1] = 0;     //Zera o contador de instruções
    while(j < quant) {
        com[ret[1]] = montarComando(linha[j]);       //Converte a string em comando
        if(ret[1] > 0) {
            pos = com[ret[1] - 1].posicao + Comando::estagios;                           //Inicializa a posição sem dependência
            for(int k = 0; ((k < 3) && (k < j)); k++) {                                 //Testa dependência do atual com até 3 anteriores
                if(com[ret[1]].detConflito(com[ret[1] - (k + 1)])) {                     //Testa dependência com anteriores
                    while((pos - com[ret[1] - (k + 1)].posicao) < (Comando::estagios * (Comando::estagios - 1))) //Afasta 1 estágio até que não haja mais a dependência
                        pos += Comando::estagios;
                    break;                                                               //Houve dependência, sair do loop
                } else
                    pos = com[ret[1] - 1].posicao + Comando::estagios;
            }
            com[ret[1]].posicao = pos;
        }
        if(com[ret[1]].jump > 0)
            j = com[ret[1]].jump - 1;                     //Se houver jump, ir direto para a linha indicada
        else
            j++;
        ret[0] = Comando::estagios + (com[ret[1]].posicao / Comando::estagios); //Ajusta o total de ciclos
        ret[1]++;
    }
    return ret;
}

/**
* @brief     	Função que imprime os ciclos de acordo com uma sequencia de códigos
* @param[in] 	*totais Vetor de inteiros com o total de ciclos (posição 0) e o total de instruções (posição 1)
* @param[in]    *com Vetor de Comandos já sequenciados
* @param[in]    *nomes Vetor de strings com os nomes dos estágios no pipeline
*/
void imprimirCiclos(int *totais, Comando *com, string *nomes) {
    cout << endl << "Quantidade de ciclos total: " << totais[0] << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    
    int *aux = new int[totais[1]];      //Variável auxiliar para contar onde cada comando está no pipeline
    for(int i = 0; i < totais[1]; i++)  //Zera todas as auxiliares
        aux[i] = 0;

    for(int i = 0; i < totais[0]; i++) {                        //Loop para todos os ciclos
        cout << "Ciclo " << (i + 1) << endl;
        for(int j = 0; j < Comando::estagios; j++) {            //Loop para cada estágio
            cout << nomes[j] << ": ";
            for(int k = 0; k < totais[1]; k++) {                                //Loop em todos as instruções
                if((com[k].posicao+aux[k]) == ((i * Comando::estagios) + j)) {  //Se o comando é para o ciclo atual, imprima-o
                    com[k].imprimirComando();
                    aux[k] += 1 + Comando::estagios;
                    if(aux[k] >= (Comando::estagios * (Comando::estagios + 1))) aux[k] = 0; //Se o comando já passou por todos os estágios, zere a auxiliar dele
                    break;
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------------------" << endl;
    }
}

