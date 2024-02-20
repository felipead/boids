Trablaho Prático 2 de Computação Gráfica - Boids
Aluno: Felipe Augusto Dornelas

===========================================

Este trabalho compila e roda no Linux e no Mac OS X. Foi testado no Ubuntu Linux 10.04 e no Mac OS X 10.7.2.

Para compilar no Linux, é necessário instalar as bibliotecas para desenvolvimento em X11 e OpenGL (GL, GLU, GLUT). No Ubuntu Linux, basta instalar o pacote "freeglut3-dev", que contém todas estas dependências. Também é necessário instalar o compilador C++, disponível no pacote "g++". Tais pacotes podem ser facilmente instalados através dos seguintes comandos:

    # apt-get install freeglut3-dev
    # apt-get install g++

Para compilar no Mac OS X, é necessário instalar os compiladores C/C++, a ferramenta make, e o ambiente X11. Os compiladores e ferramentas são automaticamente instalados durante a instalação do Xcode (foi testada a versão 4.2.1). O ambiente X11 pode ser encontrado no DVD de instalação do Mac OS X Leopard/Snow Leopard, e já vem instalado por padrão no Mac OS X Lion.

Uma vez configurado o ambiente, compile e execute o programa ao invocar o comando "make" dentro do diretório "Boids".

===========================================

A simulação começa apenas com o boid líder, que executa um movimento circular contínuo ao redor da torre. Boids podem ser criados pelo usuário, os quais seguirão o boid líder e formarão um bando.

Para adicionar boids ao jogo, utilize a tecla '+' do teclado. Adicione quantos boids quiser. A tecla '-' remove, aleatoriamente, um boid do jogo.

As teclas '1' e '2' alternam entre os possíveis modos de visualização.

A tecla 'P' pausa ou despausa a simulação. A tecla 'Q' sai da simulação e fecha o programa.