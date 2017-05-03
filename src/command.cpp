/**
* @file 	command.cpp
* @brief	Arquivo de código fonte com  a implementacao da classe Comando
* @author   Bianca Santiago (bianca.santiago72@gmail.com)
* @since    02/04/2017
* @date     22/04/2017
*/

#include "command.h"

/**
* @brief Inicializacao default da classe
*/
Comando::Comando() { 
    posicao     =  0;
    operador    = "";
    opgravar    = "";
    regist1     = "";
    regist2     = "";
    operandoext   = "";
    jump        =  0;
}

/**
* @brief Funcao que verifica há presenca de conflito entre dois comandos
* @param cmdant Comando anterior para conferencia de conflito
* @return A situacao sobre a presenca de conflito.
*/
bool Comando::verificaConflito(Comando cmdant) {
        if((cmdant.opgravar != "") && ((regist1 == cmdant.opgravar) || (regist2 == cmdant.opgravar)  || (opgravar == cmdant.opgravar))) 
        return true;            //Existe dependencia (causa conflito)
    return false;               //Não existe dependencia (nao causa conflito)
}

/**
* @brief Funcao que imprime cada comando na tela
*/
void Comando::imprimirComando() {
    if((operador == "add") || (operador == "sub")) {
        cout << operador << ", " << opgravar << ", " << regist1 << ", " << regist2;
        return;
    }
    if(operador == "lw") {
        cout << operador << ", " << opgravar << ", " << operandoext << "(" << regist1 << ")";
        return;
    }
    if(operador == "sw") {
        cout << operador << ", " << regist1 << ", " << operandoext << "(" << opgravar << ")";
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
    cout << "Tipo desconhecido, verifique o codigo Assembly!: " << operador;
}

/**
* @brief Funcao que converte uma string em um Comando para montar o comando no formato do codigo Assembly
* @param s Conjunto de cada comando e seus operandos
* @return Comando com seus atributos
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
    if(retorno.operador == "lw") {      /**< Em caso de lw o operandoext (extra) eh o adicional de memoria. Por exemplo.: o 4 no comando lw $t1, 4($s0) */
        getline(ss, retorno.opgravar, ',');
        getline(ss, lido);
        int pos1 = lido.find('(');
        int pos2 = lido.find(')');
        retorno.operandoext = lido.substr(0, pos1);                     //Separa o registrador do adicional de memoria
        retorno.regist1 = lido.substr(pos1+1, pos2 - pos1 - 1);
    }
    if(retorno.operador == "sw") {
        getline(ss, retorno.regist1, ',');
        getline(ss, lido);
        int pos1 = lido.find('(');
        int pos2 = lido.find(')');
        retorno.operandoext = lido.substr(0, pos1);                     //Separa o registrador do adicional de memoria
        retorno.opgravar = lido.substr(pos1 + 1, pos2 - pos1 - 1);
    }
    if((retorno.operador == "beq") || (retorno.operador == "bne")) { 
        getline(ss, retorno.regist1, ',');
        getline(ss, retorno.regist2, ',');
        getline(ss, lido);
        sa << lido;
        sa >> retorno.jump;             //Converte string para int
    }
    if(retorno.operador == "j") {
        string lido = "";
        getline(ss, lido);
        sa << lido;
        sa >> retorno.jump;             //Converte string para int
    }

    //Remove os espacos
    retorno.opgravar.erase(std::remove(retorno.opgravar.begin(), retorno.opgravar.end(), ' '), retorno.opgravar.end());
    retorno.regist1.erase(std::remove(retorno.regist1.begin(),     retorno.regist1.end(), ' '),   retorno.regist1.end());
    retorno.regist2.erase(std::remove(retorno.regist2.begin(),     retorno.regist2.end(), ' '),   retorno.regist2.end());
    retorno.operandoext.erase(std::remove(retorno.operandoext.begin(), retorno.operandoext.end(), ' '), retorno.operandoext.end());
    
    return retorno;
}

/**
* @brief Funcao que recebe um vetor de strings e o converte em sequencia de comandos
* @param *linha Vetor de strings a ser convertido
* @param quant Quantidade de elementos no vetor de strings
* @param *codigo Vetor de comandos a ser devolvido sequenciado
* @return Vetor de inteiros com o total de ciclos na posicao 0 e o total de instrucoes na posicao 1
*/
int *sequenciarCodigo(string *linha, int quant, Comando *codigo) {
    int *ret = new int[2];
    int j = 0, pos = 0;
    ret[0] = 0;     //Zera o contador de ciclos
    ret[1] = 0;     //Zera o contador de instruções
    while(j < quant) {
        codigo[ret[1]] = montarComando(linha[j]);       //Converte a string em comando
        if(ret[1] > 0) {
            pos = codigo[ret[1] - 1].posicao + Comando::estagios;                       //Inicializa a posicao sem dependencia
            for(int k = 0; ((k < 3) && (k < j)); k++) {                                 //Testa dependencia do atual com ate 3 anteriores
                if(codigo[ret[1]].verificaConflito(codigo[ret[1] - (k + 1)])) {                     //Testa dependencia com anteriores
                    while((pos - codigo[ret[1] - (k + 1)].posicao) < (Comando::estagios * (Comando::estagios - 1))) //Empurra 1 estagio ate que não haja mais a dependencia
                        pos += Comando::estagios;
                    break;                                                               //Houve dependencia, sai do loop
                } else
                    pos = codigo[ret[1] - 1].posicao + Comando::estagios;
            }
            codigo[ret[1]].posicao = pos;
        }
        if(codigo[ret[1]].jump > 0)
            j = codigo[ret[1]].jump - 1;                     //Se houver jump, ir direto para a linha indicada
        else
            j++;
        ret[0] = Comando::estagios + (codigo[ret[1]].posicao / Comando::estagios); //Ajusta o total de ciclos
        ret[1]++;
    }
    return ret;
}

/**
* @brief Funcao que imprime os ciclos de acordo com uma sequencia de codigos
* @param *total Vetor de inteiros com o total de ciclos (posicao 0) e o total de instrucoes (posicao 1)
* @param *codigo Vetor de Comandos ja sequenciados
* @param *nomesEstagios Vetor de strings com os nomes dos estagios no pipeline
*/
void imprimirResultado(int *total, Comando *codigo, string *nomesEstagios) {
    cout << endl << "Quantidade de ciclos total: " << total[0] << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    
    int *cont = new int[total[1]];      //Variavel auxiliar para contar onde cada comando esta no pipeline
    for(int i = 0; i < total[1]; i++)  //Zera todas as auxiliares
        cont[i] = 0;

    for(int i = 0; i < total[0]; i++) {                        //Loop para todos os ciclos
        cout << "Ciclo " << (i + 1) << endl;
        for(int j = 0; j < Comando::estagios; j++) {            //Loop para cada estáaio
            cout << nomesEstagios[j] << ": ";
            for(int k = 0; k < total[1]; k++) {                                //Loop em todas instrucoes
                if((codigo[k].posicao+cont[k]) == ((i * Comando::estagios) + j)) {  //Se o comando eh para o ciclo atual, imprimi-lo
                    codigo[k].imprimirComando();
                    cont[k] += 1 + Comando::estagios;
                    if(cont[k] >= (Comando::estagios * (Comando::estagios + 1))) cont[k] = 0; //Se o comando ja passou por todos os estagios, zerar a auxiliar dele
                    break;
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------------------" << endl;
    }
}