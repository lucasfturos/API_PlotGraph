# API Plot Graphics

Projeto OpenSource focado em exibir gráficos. A ferramenta tem o propósito de facilitar o plot de gráficos nos mais diversos tipos. Os gráficos que serão montados são:

 - Gráfico de Linhas.
 - Gráfico de Barras.
 - Gráfico de Área.
 - Gráfico de Rosquinha.
 - Gráfico de Pizza.

Para montar esta API esta sendo usado a biblioteca SFML e a linguagem de programação C++

## Instalação

Para instalar é necessário ter o gcc, g++, cmake e make, além da biblioteca do SFML.

<details><summary>Mostrar orientações</summary>

**Veja se ao instalar a versão do SFML é a 2.5.1, pois é a versão que estou usando no projeto.**

**Instalação no Linux baseado em Debian:**
```
sudo apt install build-essential cmake libsfml-dev
```

Para instalar as dependências do projeto no Windows tem alguns tutoriais no YouTube para instalar o gcc, g++, cmake e make.

Tem dois tutoriais que recomendo para fazer a instalação, são do site Terminal Root:
 - [Como Instalar GCC/G++ MinGW no Windows](https://terminalroot.com.br/2022/12/como-instalar-gcc-gpp-mingw-no-windows.html).
 - [Como Compilar Seus Jogos em SFML com GCC MinGW no Windows](https://terminalroot.com.br/2023/03/como-compilar-seus-jogos-em-sfml-com-gcc-mingw-no-windows.html).

Após realizar a instalação das dependências, faça os seguintes passos:

```
git clone https://github.com/lucasfturos/API_PlotGraph.git
cd API_PlotGraph
mkdir build && cd build
cmake ..
make
```

E para testar é só colocar:
```
./PlotGraph Barra
```

</details>

## Créditos

[SFML](https://www.sfml-dev.org/).

## Contribuição

Constribuições são bem vindas! Faça seu fork e comece a ajudar mandando seu Pull Request.

Caso queira relatar bugs, erros ou sugestões, ou também queira dar ideias de novas features não deixe de fazer um issues

Para Contribuir siga as seguintes orientações.

<details><summary>Mostrar orientações</summary>

Caso tenha feito fork para contribuir com o projeto, faça os seguintes passos:

```
git clone --recursive https://github.com/<seu usuário do GitHub>/API_PlotGraph.git
git remote add upstream https://github.com/lucasfturos/API_PlotGraph.git
```

E crie seu branch com o nome do seu usuário:
```
git checkout -b seu_usuario
```

Antes de começar a contruibuir, é necessário reiniciar o número de commits na sua máquina. Faça o seguinte:
```
git remote update
git reset upstream/master --hard
```
Trabalhe normalmente no branch. Quando desejar enviar seu resultado para o seu repositório, faça o push com:
```
git push origin seu_usuario --force
```

Assim seu repositório que foi feito o fork será atualizado.

</details>

## Licença

Este projeto está licenciado sob a licença MIT.

Consulte o arquivo LICENSE para saber mais.
