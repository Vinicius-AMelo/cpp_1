# Guia GLFW (PT-BR)

## Objetivo deste arquivo
- Ser um mapa de retomada para criar janela, contexto OpenGL, input e loop principal do zero.
- Explicar cada funcao GLFW usada no projeto com linguagem de iniciante.
- Deixar claro nao so o que cada chamada faz, mas tambem por que ela vem naquela ordem.

## O que a GLFW faz neste projeto
- Cria a janela.
- Cria o contexto OpenGL.
- Entrega funcoes de input e eventos.
- Fornece tempo (`glfwGetTime`).
- Nao desenha triangulos, quadrados ou linhas.

## Frase-guia para lembrar
- `GLFW` prepara o palco.
- `GLAD` carrega as funcoes do OpenGL.
- `OpenGL` desenha.

## Ordem real de uso no projeto
1. `glfwInit()`
2. `glfwWindowHint(...)`
3. `glfwCreateWindow(...)`
4. `glfwMakeContextCurrent(window)`
5. `gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))`
6. `glfwSetFramebufferSizeCallback(window, resize_framebuffer_callback)`
7. `while (!glfwWindowShouldClose(window)) { ... }`
8. `glfwSwapBuffers(window)`
9. `glfwPollEvents()`
10. `glfwDestroyWindow(window)`
11. `glfwTerminate()`

## Mini tutorial mental: do zero ate a janela funcionando

### 1. Iniciar a biblioteca
#### `int glfwInit(void);`
- O que faz:
Inicializa a GLFW.
- Por que vem primeiro:
Quase todo o resto da GLFW depende disso.
- O que precisa existir antes:
Nada.
- O que passa a valer depois:
A biblioteca fica pronta para criar janela, contexto e ler input.
- Parametros:
Nao recebe parametros.
- Retorno:
`GLFW_TRUE` em sucesso.
`GLFW_FALSE` em falha.
- Leitura pratica:
Se falhar aqui, o programa nao deve continuar.
- Exemplo do projeto:
```cpp
if (glfwInit() != GLFW_TRUE)
{
    std::cout << "Falha ao iniciar GLFW!";
    return 1;
}
```

### 2. Pedir o tipo de contexto OpenGL que queremos
#### `void glfwWindowHint(int hint, int value);`
- O que faz:
Define uma preferencia para a proxima janela que sera criada.
- O que ela nao faz:
Nao cria janela.
Nao valida sozinha se a maquina suporta aquilo.
Nao altera janelas ja criadas.
- O que precisa existir antes:
A GLFW ja deve ter sido iniciada com `glfwInit()`.
- O que passa a valer depois:
A proxima chamada de `glfwCreateWindow(...)` tenta obedecer esses hints.
- Parametros:
`hint`: qual configuracao voce quer definir.
`value`: o valor desejado para essa configuracao.
- Hints usados no projeto:
`GLFW_CONTEXT_VERSION_MAJOR, 3`
Pede OpenGL major version 3.

`GLFW_CONTEXT_VERSION_MINOR, 3`
Pede OpenGL minor version 3.

`GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE`
Pede o perfil moderno Core Profile.
- Leitura didatica:
Aqui voce esta dizendo para a GLFW: "quando criar minha janela, eu quero um contexto OpenGL 3.3 Core".
- Exemplo do projeto:
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

### 3. Criar a janela e o contexto
#### `GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);`
- O que faz:
Cria a janela e tambem cria o contexto OpenGL associado a ela.
- Importante:
Criar a janela nao significa que o contexto ja esta "ativo" para uso.
Ele existe, mas ainda precisa ser tornado atual com `glfwMakeContextCurrent(window)`.
- O que precisa existir antes:
`glfwInit()`.
Se quiser configurar versao/profile, os `glfwWindowHint(...)` devem vir antes.
- O que passa a valer depois:
Se deu certo, voce recebe um ponteiro `GLFWwindow*` que representa essa janela.
- Parametros:
`width`: largura inicial da janela.
`height`: altura inicial da janela.
`title`: texto exibido no titulo da janela.
`monitor`: use `nullptr` para janela comum. Se passar um monitor, a janela tende a virar fullscreen.
`share`: use `nullptr` por enquanto. Serve para compartilhar recursos entre contextos.
- Retorno:
Um ponteiro para `GLFWwindow` em sucesso.
`nullptr` em falha.
- Leitura didatica do tipo:
`GLFWwindow*` e um ponteiro para um objeto interno da GLFW.
Voce nao cria esse objeto manualmente. Quem cria e devolve esse ponteiro e a propria GLFW.
- Exemplo do projeto:
```cpp
GLFWwindow *window = glfwCreateWindow(
    this->kWindowWidth,
    this->kWindowHeight,
    this->kWindowTitle,
    nullptr,
    nullptr
);
```
- Tratamento de falha:
Se vier `nullptr`, a janela nao foi criada e normalmente encerramos a GLFW.

### 4. Tornar o contexto atual
#### `void glfwMakeContextCurrent(GLFWwindow* window);`
- O que faz:
Ativa o contexto OpenGL daquela janela na thread atual.
- O que isso significa na pratica:
A partir daqui, as chamadas OpenGL feitas nessa thread passam a usar o contexto dessa janela.
- Por que isso e obrigatorio:
Sem contexto atual, `glfwGetProcAddress(...)` e as chamadas `gl*` nao vao funcionar corretamente.
- O que precisa existir antes:
A janela precisa ter sido criada com sucesso.
- O que passa a valer depois:
Agora temos um contexto ativo para carregar funcoes OpenGL com GLAD e depois desenhar.
- Exemplo do projeto:
```cpp
glfwMakeContextCurrent(window);
```

### 5. Entregar funcoes OpenGL para o GLAD
#### `GLFWglproc glfwGetProcAddress(const char* procname);`
- O que faz:
Retorna o endereco de uma funcao OpenGL suportada pelo contexto atual.
- Onde ela entra no projeto:
Ela e passada para o `gladLoadGLLoader(...)`.
- O que precisa existir antes:
Um contexto OpenGL atual na thread, ou seja, `glfwMakeContextCurrent(window)` ja precisa ter sido chamado.
- O que passa a valer depois:
Sozinha, nada visual muda. Ela e uma funcao de suporte para o carregamento do GLAD.
- Parametro:
`procname`: nome da funcao OpenGL que se deseja localizar.
- Exemplo indireto no projeto:
```cpp
gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
```
- Regra pratica:
Sem contexto atual, essa etapa falha.

### 6. Registrar callback de resize
#### `void glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun cbfun);`
- O que faz:
Registra uma funcao callback que sera chamada quando o tamanho do framebuffer mudar.
- Tradução simples:
Quando a area real onde o OpenGL desenha muda de tamanho, a GLFW chama sua funcao.
- Por que isso importa:
O OpenGL precisa saber a nova area de desenho. No projeto, isso e feito com `glViewport(0, 0, width, height)`.
- O que precisa existir antes:
A janela precisa existir.
- O que passa a valer depois:
Sempre que houver resize, a callback registrada pode reajustar o viewport.
- Parametros:
`window`: janela observada.
`cbfun`: funcao com assinatura parecida com:
```cpp
void nomeDaFuncao(GLFWwindow *window, int width, int height)
```
- Exemplo do projeto:
```cpp
glfwSetFramebufferSizeCallback(window, resize_framebuffer_callback);
```
- Regra pratica:
A callback nao desenha por voce. Ela apenas responde ao evento.

### 7. Perguntar se a janela deve fechar
#### `int glfwWindowShouldClose(GLFWwindow* window);`
- O que faz:
Retorna o valor da flag de fechamento da janela.
- Uso no projeto:
Controla o `while` principal.
- O que precisa existir antes:
A janela precisa existir.
- O que passa a valer depois:
Nada muda. E apenas uma consulta.
- Parametro:
`window`: janela consultada.
- Retorno:
Valor diferente de zero significa "sim, pode fechar".
- Exemplo do projeto:
```cpp
while (!glfwWindowShouldClose(window))
{
    ...
}
```
- Leitura didatica:
O loop principal continua enquanto essa flag estiver desligada.

### 8. Marcar a janela para fechar
#### `void glfwSetWindowShouldClose(GLFWwindow* window, int value);`
- O que faz:
Liga ou desliga a flag de fechamento da janela.
- Uso no projeto:
Quando `ESC` e pressionado, marcamos a janela para fechar.
- O que precisa existir antes:
A janela precisa existir.
- O que passa a valer depois:
Na proxima iteracao, `glfwWindowShouldClose(window)` vai enxergar essa flag ligada.
- Parametros:
`window`: janela alvo.
`value`: normalmente `GLFW_TRUE` para pedir fechamento.
- Exemplo do projeto:
```cpp
glfwSetWindowShouldClose(window, GLFW_TRUE);
```

### 9. Ler teclado
#### `int glfwGetKey(GLFWwindow* window, int key);`
- O que faz:
Retorna o ultimo estado conhecido de uma tecla para aquela janela.
- Retornos comuns:
`GLFW_PRESS`
`GLFW_RELEASE`
- O que precisa existir antes:
A janela precisa existir e os eventos precisam estar sendo processados com `glfwPollEvents()` para o estado ficar atualizado.
- O que passa a valer depois:
Nada muda. E uma leitura.
- Parametros:
`window`: janela da qual voce quer ler o teclado.
`key`: a tecla desejada, como `GLFW_KEY_ESCAPE` ou `GLFW_KEY_SPACE`.
- Exemplo do projeto:
```cpp
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
```
- Regra pratica importante:
`glfwGetKey` e leitura de estado, nao de evento unico.
Se a tecla ficar segurada, voce vai ler `GLFW_PRESS` em varios frames seguidos.
- Como o projeto lidou com isso no `SPACE`:
Guardamos um booleano anterior (`spaceWasPressed`) para detectar a transicao de "solta" para "pressionada".

### 10. Ler tempo
#### `double glfwGetTime(void);`
- O que faz:
Retorna o tempo atual da GLFW em segundos.
- Uso no projeto:
Animar a posicao do quadrado com `std::sin` e `std::cos`.
- O que precisa existir antes:
A GLFW precisa ter sido inicializada.
- O que passa a valer depois:
Nada muda. E apenas uma leitura de tempo.
- Retorno:
Um `double` com o tempo em segundos desde a inicializacao da GLFW, a menos que esse tempo tenha sido ajustado manualmente.
- Exemplo do projeto:
```cpp
const float t = static_cast<float>(glfwGetTime());
```
- Regra pratica:
Use esse valor para movimento baseado em tempo, em vez de tentar contar frames na mao.

### 11. Mostrar o frame pronto
#### `void glfwSwapBuffers(GLFWwindow* window);`
- O que faz:
Troca o buffer de tras pelo buffer visivel da janela.
- Tradução simples:
Voce desenha no "quadro escondido" e depois manda esse quadro aparecer.
- Por que isso importa:
Sem isso, o frame novo pode nao aparecer corretamente na tela.
- O que precisa existir antes:
A janela precisa existir e o frame atual ja deve ter sido desenhado.
- O que passa a valer depois:
O frame que estava pronto se torna o frame visivel.
- Exemplo do projeto:
```cpp
glfwSwapBuffers(window);
```

### 12. Processar eventos da janela
#### `void glfwPollEvents(void);`
- O que faz:
Processa a fila de eventos da janela e do input.
- Tradução simples:
Atualiza teclado, mouse, resize, clique no X da janela e outros eventos do sistema.
- O que precisa existir antes:
A GLFW precisa estar inicializada.
- O que passa a valer depois:
As consultas como `glfwGetKey(...)` passam a refletir eventos mais recentes.
- Exemplo do projeto:
```cpp
glfwPollEvents();
```
- Sintoma classico se esquecer:
A janela parece travada ou "nao responde".

### 13. Destruir a janela
#### `void glfwDestroyWindow(GLFWwindow* window);`
- O que faz:
Destroi a janela e o contexto associados.
- O que precisa existir antes:
A janela precisa existir.
- O que passa a valer depois:
Aquele `GLFWwindow*` deixa de representar uma janela valida.
- Exemplo do projeto:
```cpp
glfwDestroyWindow(window);
```

### 14. Encerrar a biblioteca
#### `void glfwTerminate(void);`
- O que faz:
Finaliza a GLFW e libera recursos globais da biblioteca.
- Quando usar:
No encerramento do programa.
- O que precisa existir antes:
Normalmente nada alem de a GLFW ter sido inicializada em algum momento.
- O que passa a valer depois:
Para usar GLFW de novo, seria preciso chamar `glfwInit()` novamente.
- Exemplo do projeto:
```cpp
glfwTerminate();
```

## Tutorial comentado: como a base do projeto se encaixa

### Bloco 1. Preparar a biblioteca
```cpp
if (glfwInit() != GLFW_TRUE)
{
    std::cout << "Falha ao iniciar GLFW!";
    return 1;
}
```
- Aqui a regra e simples:
se a GLFW nao inicializou, nada do resto faz sentido.

### Bloco 2. Pedir um contexto OpenGL 3.3 Core
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```
- Isso nao cria nada ainda.
- Isso apenas prepara a "encomenda" da proxima janela.

### Bloco 3. Criar a janela
```cpp
GLFWwindow *window = glfwCreateWindow(
    this->kWindowWidth,
    this->kWindowHeight,
    this->kWindowTitle,
    nullptr,
    nullptr
);
```
- `width` e `height`: tamanho inicial.
- `title`: texto no topo da janela.
- `nullptr, nullptr`: por enquanto, janela comum e sem compartilhamento de contexto.

### Bloco 4. Validar a janela
```cpp
if (!window)
{
    std::cout << "Falha ao criar a janela GLFW!";
    glfwTerminate();
    return 1;
}
```
- Se `window` vier nulo, a criacao falhou.
- Aqui faz sentido encerrar a GLFW antes de sair.

### Bloco 5. Ativar o contexto
```cpp
glfwMakeContextCurrent(window);
```
- So agora o contexto da janela virou o contexto atual.
- So agora faz sentido carregar OpenGL com GLAD.

### Bloco 6. Entrar no loop principal
```cpp
while (!glfwWindowShouldClose(window))
{
    this->event_listener(window);

    // chamadas OpenGL de render

    glfwSwapBuffers(window);
    glfwPollEvents();
}
```
- `event_listener(window)`: decide o que fazer com teclado.
- OpenGL desenha o frame.
- `glfwSwapBuffers(window)`: mostra o frame.
- `glfwPollEvents()`: atualiza eventos para o proximo frame.

### Bloco 7. Encerrar corretamente
```cpp
glfwDestroyWindow(window);
glfwTerminate();
```
- Primeiro destruimos a janela.
- Depois encerramos a biblioteca.

## Pegadinhas comuns para lembrar depois
- `glfwWindowHint(...)` so afeta a proxima janela criada.
- `glfwCreateWindow(...)` cria o contexto, mas nao o torna atual.
- `glfwGetProcAddress(...)` depende de contexto atual.
- `glfwGetKey(...)` le estado atual conhecido, entao tecla segurada aparece em varios frames.
- `glfwPollEvents()` e obrigatoria para a janela continuar responsiva.
- `glfwSwapBuffers(window)` deve vir depois do desenho do frame atual.

## Checklist rapido de retomada
1. Iniciei a GLFW com `glfwInit()`?
2. Configurei os `glfwWindowHint(...)` antes da criacao da janela?
3. Validei se `glfwCreateWindow(...)` retornou um ponteiro valido?
4. Chamei `glfwMakeContextCurrent(window)` antes do GLAD?
5. O loop principal usa `glfwWindowShouldClose(window)`?
6. O loop chama `glfwSwapBuffers(window)`?
7. O loop chama `glfwPollEvents()`?
8. No final, chamei `glfwDestroyWindow(window)` e `glfwTerminate()`?

## Referencias oficiais
- GLFW docs index:
https://www.glfw.org/docs/
- GLFW window reference:
https://www.glfw.org/docs/latest/group__window.html
- GLFW context guide:
https://www.glfw.org/docs/latest/context_guide.html
- GLFW input reference:
https://www.glfw.org/docs/latest/group__input.html
