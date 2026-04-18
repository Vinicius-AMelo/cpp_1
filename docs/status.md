# Status do Projeto

## Resumo atual
- Projeto em fase inicial de estruturação.
- A trilha principal já foi definida em `docs/trilha.md`.
- O acompanhamento contínuo agora passa a ser feito por este painel, pelo `logbook` e pelo banco de etapas.
- Preferência pedagógica atual:
  - evitar edição automática de código sempre que possível;
  - mostrar no chat como o arquivo deve ficar;
  - explicar por partes;
  - deixar a digitação principal com o usuário.
  - incluir comentarios didaticos detalhados no codigo enviado no chat, com foco especial nas sintaxes novas da trilha.
  - manter documentacoes tecnicas no mesmo padrao alto de didatica e retomada adotado em `docs/glfw.md` e `docs/glad.md`.
  - manter as retomadas documentais sincronizadas com o ultimo checkpoint registrado antes de abrir nova frente.
- Estado do código hoje:
  - `main.cpp` agora delega a execução para uma classe `App`.
  - Já existe um `CMakeLists.txt` com `C++17`, `OpenGL`, `GLFW` e warnings habilitados.
  - O projeto ganhou separação simples entre `main.cpp`, `include/` e `src/`.
  - O fluxo com `CMake` e `Ninja` já foi validado com sucesso no ambiente.
  - O workspace do VS Code agora tem configuração para build, execução e formatação.

## Etapa atual
- Etapa ativa: `2. Primeiro triângulo`
- Status da etapa: `em_andamento`
- Objetivo visual atual: manter o triângulo estático renderizando de forma estável e consolidar entendimento de pipeline.
- Observacao de fechamento da etapa: a entrega visual base ja existe; a etapa permanece aberta para consolidacao conceitual (`uniform`, `stride`, `offset` e explicacao autoral do fluxo completo).
- Resultado esperado para fechar a etapa:
  - compilar e linkar shaders sem erro;
  - configurar `VAO`/`VBO` com entendimento de layout;
  - explicar em palavras próprias o fluxo CPU -> VBO -> vertex shader -> fragment shader -> tela.

## Última atualização
- Data: `2026-04-16 18:20:00 -03:00`
- Contexto: consolidacao do setup CMake/Ninja para CLion em Windows e Linux, com estrategia hibrida para `GLFW`, fallback local para `GLAD` e presets dedicados para CLion MinGW.

## Feito recentemente
- Definida a trilha integrada de `C++ + OpenGL` em `8 etapas`.
- Definido o stack base: `C++17 + CMake + GLFW + GLAD + GLM + OpenGL 3.3 Core`.
- Identificado o estado inicial do projeto:
  - ainda não há dependências gráficas integradas ao projeto;
- Estruturado o primeiro passo de código da Etapa 1:
  - criado `CMakeLists.txt`;
  - criada a classe `App`;
  - criada separação entre header e source file;
  - criada task de `CMake` no VS Code.
- Validado o ambiente atual:
  - `gcc-c++`, `make`, `pkg-config`, `cmake` e `ninja` estão instalados;
  - `glfw-devel`, `glm-devel` e `mesa-libGL-devel` estão instalados;
  - os headers de `GLFW`, `GLM` e `OpenGL` já são encontrados pelo compilador;
  - o projeto já configura, compila e executa com `CMake` + `Ninja`.
- Entrega visual atual da Etapa 1:
  - a aplicação abre uma janela real com `GLFW`;
  - existe loop principal de renderização;
  - a tela é limpa com uma cor fixa;
  - `ESC` fecha a janela.
- Entrega visual atual da Etapa 2:
  - triangulo renderizando em OpenGL moderno;
  - shaders separados em `assets/shaders/triangle.vert` e `assets/shaders/triangle.frag`;
  - leitura dos shaders por arquivo no `app.cpp`;
  - primeiro uso pratico de `VAO` e `VBO`.
  - evolucao para quadrado com `EBO` e trilha em linha (`GL_LINE_STRIP`) para visualizacao do caminho da animacao.
- Progresso pedagógico recente:
  - explicacao linha a linha de `app.cpp`;
  - entendimento de callback de resize vs redimensionamento real da janela;
  - introducao de `struct Color` como modelagem de estado;
  - entendimento de `constexpr`, convencao `k`, diferenca entre constante inicial e estado mutavel;
  - entendimento do erro de metodo `const` ao tentar alterar `backgroundColor`;
  - consolidacao do uso de `this->` como apoio visual para aprendizado;
  - entendimento de `static_cast<float>` e da divisao entre inteiros e floats;
  - entendimento de por que a cor piscava ao segurar a tecla: input continuo por frame, nao atribuicao parcial da struct.
  - ajuste manual de estilo em trechos de `switch` e chamadas longas para reforcar leitura vertical;
  - criacao de regras mais especificas no `.clang-format` para aproximar o resultado do estilo desejado.
  - formalizacao da regra de comentarios didaticos detalhados em codigo enviado no chat, com enfase em sintaxes novas da trilha.
  - consolidacao do papel de `vertex shader` e `fragment shader`;
  - entendimento inicial de `VAO` (configuracao/layout) e `VBO` (dados de vertices na GPU);
  - consolidacao de que coordenadas do triangulo estao em NDC (faixa principal de `-1` a `1`).
  - documentacao tutorial criada para `GLFW` e `GLAD/OpenGL`, com explicacao por funcao, parametros e ordem de uso no projeto.
  - refinamento dos guias para um nivel mais didatico, deixando explicito:
    - o que precisa existir antes de cada chamada;
    - o que passa a valer depois dela;
    - em qual estado (`VAO`, `VBO`, `EBO`, shader program) a chamada atua;
    - como repetir a sequencia em um projeto novo sem depender de memoria.
  - formalizacao de que esse padrao alto de explicacao passa a ser preferencia persistente do projeto e deve orientar futuras atualizacoes documentais.
- Observacao de ambiente:
  - o binario `clang-format` nao esta instalado no sistema no momento; o projeto depende do formatter da extensao no editor ou da instalacao do pacote no sistema para formatacao por CLI.
- Criada a base documental para acompanhar progresso, retomada e aprendizado.
- Retomada documental registrada em `2026-04-16` para manter continuidade da trilha a partir do ultimo checkpoint valido.
- Reestruturado o build system com foco em portabilidade entre Windows/Fedora:
  - `CMakeLists.txt` com descoberta hibrida de dependencias;
  - `CMakePresets.json` com presets Ninja genericos e presets CLion MinGW (Windows);
  - `SHADER_DIR_PATH` injetado no build para desacoplar caminho de shader do diretorio de execucao.
- Validacao realizada no fluxo real do CLion com Ninja no Windows (`configure + build` concluido).
- Diagnostico de ambiente consolidado:
  - falha anterior no CLion MinGW era de toolchain/PATH (DLL), nao de sintaxe CMake;
  - warning de `pwsh.exe` observado no gerador Visual Studio vem da integracao global do `vcpkg`, nao do projeto.

## Próximo passo
- Consolidar na próxima sessão prática, revisando rapidamente:
  - diferenca entre atributo de vertice e `uniform`;
  - significado de `stride` e `offset` no `glVertexAttribPointer`.
- Implementar consolidacao da Etapa 2:
  - usar `docs/glfw.md` e `docs/glad.md` como guia para montar uma forma nova sem copiar bloco pronto;
  - tentar descrever em voz propria o efeito de `glBindVertexArray`, `glBindBuffer` e `glVertexAttribPointer` antes de codar;
  - consolidar a organizacao de `VAO/VBO/EBO` (quadrado) e `VAO/VBO` (trilha) sem confundir estados;
  - registrar no logbook um "passo a passo autoral" de criacao de forma.

## Bloqueios
- Nenhum bloqueio tecnico ativo no momento para build no Windows (CLion + Ninja validado).
- Pendencia de validacao manual restante: executar o preset Ninja em Fedora para fechar check multiplataforma no ambiente Linux real.

## Aprendizados consolidados
- O projeto tem uma meta clara de longo prazo: simulação de universo com gravidade.
- A trilha precisa equilibrar resultado visual rápido com fundamentos de C++.
- O acompanhamento deve ser incremental, sem depender de concluir etapas inteiras para registrar avanço.
- A Etapa 1 já começou introduzindo uma primeira abstração pequena em C++ sem perder simplicidade.
- Em C/C++, biblioteca instalada para rodar e biblioteca preparada para compilar são coisas diferentes.
- Em `CMake`, configurar e compilar são etapas diferentes: `cmake -S . -B build` gera o projeto, e `cmake --build build` executa a compilação.
- Ferramentas como `Code Runner` costumam compilar apenas o arquivo ativo, o que não funciona bem para projetos com vários arquivos e pasta `include/`.
- Uma janela OpenGL mínima depende de três peças trabalhando juntas: contexto criado pelo `GLFW`, loop principal e chamada de limpeza da tela.
- A forma de ensino mais adequada para este projeto privilegia escrita manual guiada, explicacao por partes e pequenos experimentos.
- Input por frame e input por evento de pressionamento sao coisas diferentes e isso impacta diretamente o comportamento visual da aplicacao.

## Pontos para revisar
- Confirmar instalação e uso do stack escolhido no ambiente.
- Revisar a task do editor depois do primeiro build real.
- Confirmar se `GLM` entra já na primeira janela ou apenas na etapa de transformações.
- Definir a estratégia de `GLAD` para o projeto.
