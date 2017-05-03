# Projeto 2

Simulador de pipeline.

Para gerar o binários basta executar o comando make no diretório raiz do projeto.

Automaticamente será gerado o arquivo: ioac.exe dentro da pasta bin.

O programa sempre considera os saltos sendo executados. Neste caso, o alvo será o número da linha.

O programa está prédefinido para 5 estágios no pipelines (IF, ID, EX, MEM, WB). Para modificar, basta 
alterar o main redefinindo-o para a quantidade desejada e nomeando cada estágio.

A execução do aplicativo deve ser, por exemplo: ./bin/ioac.exe ./data/programa1.asm

Sendo ./data/programa1.asm o caminho/arquivo que contém a sequência de instruções à ser lida.

O relatório aparecerá na tela. Caso queira salvá-lo em arquivo, basta executar, por exemplo, ./bin/ioac.exe ./data/programa1.asm > resultado.txt
