# Guia GLAD + OpenGL usado no projeto (PT-BR)

## Objetivo deste arquivo
- Explicar o papel real do `GLAD` no projeto.
- Documentar as chamadas `gl*` usadas hoje no codigo.
- Servir como tutorial de retomada para montar uma forma do zero sem depender de memoria vaga.

## Antes de tudo: GLAD nao e "a biblioteca que desenha"
- `GLAD` e um carregador de funcoes OpenGL.
- Ele resolve os enderecos das funcoes `gl*` que o driver oferece.
- Quem realmente desenha e o `OpenGL`.
- No projeto atual, a parte "GLAD de fato" aparece principalmente em:
`gladLoadGLLoader(...)`
- Ja chamadas como `glBindVertexArray`, `glBufferData`, `glDrawElements` e `glDrawArrays` sao chamadas do OpenGL, acessiveis porque o GLAD carregou esses ponteiros.

## Frase-guia para lembrar
- `GLFW` cria a janela e o contexto.
- `GLAD` habilita o acesso as funcoes OpenGL.
- `OpenGL` usa estados, buffers, shaders e draws para desenhar.

## Fluxo mental completo deste projeto
1. GLFW cria a janela.
2. GLFW torna o contexto atual com `glfwMakeContextCurrent(window)`.
3. GLAD carrega as funcoes OpenGL com `gladLoadGLLoader(...)`.
4. OpenGL recebe um viewport com `glViewport(...)`.
5. O codigo le os shaders do disco.
6. O OpenGL cria e compila os shaders.
7. O OpenGL linka esses shaders em um programa.
8. O OpenGL cria `VAO`, `VBO` e `EBO`.
9. O OpenGL recebe os vertices e indices com `glBufferData(...)`.
10. O `VAO` aprende como ler cada vertice com `glVertexAttribPointer(...)`.
11. No loop, o programa de shader e ativado com `glUseProgram(...)`.
12. O `VAO` certo e bindado.
13. O uniform `uOffset` e atualizado.
14. O draw acontece com `glDrawElements(...)` ou `glDrawArrays(...)`.
15. No final, os recursos sao liberados.

## Mapa mental dos objetos principais

### `VBO`
- Guarda os dados brutos de vertices na GPU.
- Exemplo no projeto:
posicao + cor de cada vertice.

### `EBO`
- Guarda indices.
- Serve para reaproveitar vertices sem duplicar tudo.
- Exemplo no projeto:
um quadrado com `4` vertices e `6` indices.

### `VAO`
- Guarda como os atributos devem ser lidos.
- Tambem guarda qual `EBO` esta associado a ele.
- Traducao pratica:
o `VAO` nao guarda os vertices em si; ele guarda o "mapa de leitura" desses vertices.

## Receita mental para criar uma forma nova
1. Defina os vertices.
2. Se quiser reaproveitar vertices, defina indices e use `EBO`.
3. Crie `VAO`, `VBO` e talvez `EBO`.
4. Binde o `VAO`.
5. Binde o `VBO` em `GL_ARRAY_BUFFER`.
6. Envie vertices com `glBufferData(...)`.
7. Se houver indices, binde o `EBO` em `GL_ELEMENT_ARRAY_BUFFER`.
8. Envie os indices com `glBufferData(...)`.
9. Configure os atributos com `glVertexAttribPointer(...)`.
10. Ative os atributos com `glEnableVertexAttribArray(...)`.
11. No loop, ative o shader, binde o `VAO` e desenhe.

## Parte 1. Carregamento do OpenGL

### `int gladLoadGLLoader(GLADloadproc load);`
- O que faz:
Carrega os ponteiros das funcoes OpenGL para o contexto atual.
- O que precisa existir antes:
Uma janela criada.
Um contexto atual com `glfwMakeContextCurrent(window)`.
- O que passa a valer depois:
As chamadas `gl*` modernas ficam disponiveis para uso.
- Parametro:
`load`: funcao que sabe buscar enderecos de funcoes OpenGL. No projeto usamos `glfwGetProcAddress`.
- Retorno:
Valor diferente de zero em sucesso.
Zero em falha.
- Exemplo do projeto:
```cpp
if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
{
    std::cout << "Falha ao carregar funcoes OpenGL com GLAD!";
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}
```
- Regra pratica:
Se isso falhar, nao adianta tentar desenhar nada.

## Parte 2. Ajustar a area onde o OpenGL desenha

### `void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);`
- O que faz:
Define a regiao da janela onde o OpenGL vai desenhar.
- O que precisa existir antes:
Um contexto OpenGL valido.
- O que passa a valer depois:
O OpenGL passa a mapear o resultado final para essa area.
- Parametros:
`x`, `y`: canto inferior esquerdo da area de desenho.
`width`, `height`: tamanho dessa area.
- Exemplo do projeto:
```cpp
glViewport(0, 0, this->kWindowWidth, this->kWindowHeight);
```
- Onde mais aparece:
Dentro da callback de resize:
```cpp
glViewport(0, 0, width, height);
```
- Regra pratica:
Se a janela mudar de tamanho e o viewport nao acompanhar, a imagem pode ficar cortada ou deformada.

## Parte 3. Criacao e compilacao de shaders

### `GLuint glCreateShader(GLenum type);`
- O que faz:
Cria um objeto shader vazio na GPU.
- O que precisa existir antes:
Contexto OpenGL valido.
- O que passa a valer depois:
Voce ganha um ID de shader para preencher com codigo-fonte.
- Parametro:
`type`: tipo do shader.
No projeto usamos `GL_VERTEX_SHADER` e `GL_FRAGMENT_SHADER`.
- Exemplo do projeto:
```cpp
GLuint shader = glCreateShader(shaderType);
```
- Regra pratica:
Criar o shader nao compila nada ainda. So cria o objeto.

### `void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);`
- O que faz:
Entrega o codigo-fonte ao shader criado.
- O que precisa existir antes:
Um shader valido retornado por `glCreateShader(...)`.
- O que passa a valer depois:
O objeto shader agora conhece o texto que sera compilado.
- Parametros importantes:
`shader`: ID do shader.
`count`: quantidade de strings. No projeto usamos `1`.
`string`: ponteiro para a string do codigo-fonte.
`length`: `nullptr` quando a string termina com `\0` normalmente.
- Exemplo do projeto:
```cpp
glShaderSource(shader, 1, &shaderSource, nullptr);
```
- Leitura didatica do `&shaderSource`:
A funcao espera um ponteiro para uma lista de strings. Como estamos enviando apenas uma string, passamos o endereco dela.

### `void glCompileShader(GLuint shader);`
- O que faz:
Compila o codigo-fonte que foi entregue ao shader.
- O que precisa existir antes:
`glShaderSource(...)` ja deve ter sido chamado.
- O que passa a valer depois:
O shader tenta virar codigo executavel da GPU.
- Exemplo do projeto:
```cpp
glCompileShader(shader);
```
- Regra pratica:
Sempre valide a compilacao logo depois.

### `void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);`
- O que faz:
Consulta uma informacao sobre o shader.
- O que precisa existir antes:
Um shader valido.
- O que passa a valer depois:
Nada muda; e apenas uma leitura de status.
- Parametros importantes:
`shader`: ID do shader.
`pname`: qual informacao queremos consultar.
No projeto usamos `GL_COMPILE_STATUS`.
`params`: onde o OpenGL vai escrever a resposta.
- Exemplo do projeto:
```cpp
GLint success = 0;
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
```
- Regra pratica:
Se `success` vier como falha, chame `glGetShaderInfoLog(...)`.

### `void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);`
- O que faz:
Busca a mensagem de erro ou aviso da compilacao do shader.
- O que precisa existir antes:
Tentativa de compilacao feita.
- O que passa a valer depois:
Nada muda; voce apenas ganha texto para depurar.
- Parametros importantes:
`shader`: ID do shader.
`maxLength`: tamanho maximo do buffer que vai receber a mensagem.
`length`: pode ser `nullptr` se voce nao precisa do tamanho final.
`infoLog`: array de caracteres que recebera a mensagem.
- Exemplo do projeto:
```cpp
char infoLog[512];
glGetShaderInfoLog(shader, 512, nullptr, infoLog);
```
- Regra pratica:
Essa e a primeira funcao para consultar quando o shader "nao funciona".

### `void glDeleteShader(GLuint shader);`
- O que faz:
Libera um objeto shader.
- Quando usamos no projeto:
1. Se a compilacao falha, para nao vazar recurso.
2. Depois que o programa foi linkado com sucesso.
- Por que depois do link pode:
Depois do link, o programa ja incorporou o necessario para executar.
- Exemplo do projeto:
```cpp
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

## Parte 4. Criacao e link do programa de shader

### `GLuint glCreateProgram(void);`
- O que faz:
Cria um programa de shader vazio.
- O que passa a valer depois:
Voce recebe um ID de programa para anexar shaders.
- Exemplo do projeto:
```cpp
GLuint program = glCreateProgram();
```

### `void glAttachShader(GLuint program, GLuint shader);`
- O que faz:
Anexa um shader compilado ao programa.
- O que precisa existir antes:
Um programa valido e um shader valido.
- O que passa a valer depois:
Esse shader passa a fazer parte da tentativa de link daquele programa.
- Exemplo do projeto:
```cpp
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);
```
- Regra pratica:
O programa final precisa de um conjunto compativel de shaders.

### `void glLinkProgram(GLuint program);`
- O que faz:
Tenta conectar os shaders anexados em um programa executavel.
- Tradução pratica:
E aqui que o OpenGL verifica se a saida do vertex shader conversa com a entrada do fragment shader, por exemplo.
- O que precisa existir antes:
Os shaders necessarios ja devem estar anexados.
- O que passa a valer depois:
Se tudo der certo, o programa pode ser ativado com `glUseProgram(...)`.
- Exemplo do projeto:
```cpp
glLinkProgram(program);
```

### `void glGetProgramiv(GLuint program, GLenum pname, GLint* params);`
- O que faz:
Consulta uma informacao sobre o programa.
- O que precisa existir antes:
Um programa valido.
- O que passa a valer depois:
Nada muda; e uma leitura de status.
- Parametros importantes:
`program`: ID do programa.
`pname`: no projeto usamos `GL_LINK_STATUS`.
`params`: onde o resultado sera escrito.
- Exemplo do projeto:
```cpp
GLint success = 0;
glGetProgramiv(program, GL_LINK_STATUS, &success);
```

### `void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);`
- O que faz:
Busca a mensagem de erro ou aviso do link do programa.
- Quando usar:
Quando `glGetProgramiv(..., GL_LINK_STATUS, ...)` indicar falha.
- Exemplo do projeto:
```cpp
char infoLog[512];
glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
```

### `void glDeleteProgram(GLuint program);`
- O que faz:
Libera o programa de shader.
- Quando usar:
No encerramento, quando ele nao sera mais usado.
- Exemplo do projeto:
```cpp
glDeleteProgram(shaderProgram);
```

## Parte 5. Criacao dos objetos de geometria

### `void glGenVertexArrays(GLsizei n, GLuint* arrays);`
- O que faz:
Gera IDs de `VAO`.
- O que ela nao faz:
Nao configura atributos.
Nao envia vertices.
- O que precisa existir antes:
Contexto OpenGL valido.
- O que passa a valer depois:
Voce passa a ter um nome/ID para usar com `glBindVertexArray(...)`.
- Parametros:
`n`: quantos VAOs gerar.
`arrays`: ponteiro para onde os IDs serao escritos.
- Exemplo do projeto:
```cpp
glGenVertexArrays(1, &VAO);
```
- Regra pratica:
Pense assim: esta funcao so entrega o cracha do VAO. A configuracao vem depois.

### `void glGenBuffers(GLsizei n, GLuint* buffers);`
- O que faz:
Gera IDs de buffers.
- Uso no projeto:
Criar `VBO`, `EBO` e tambem o `trailVBO`.
- O que ela nao faz:
Nao envia dados ainda.
- Exemplo do projeto:
```cpp
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);
```

### `void glBindVertexArray(GLuint array);`
- O que faz:
Ativa o `VAO` que sera o atual.
- Traducao pratica:
A partir daqui, configuracoes de atributo vao para esse `VAO`.
- O que precisa existir antes:
Um ID valido gerado por `glGenVertexArrays(...)`.
- O que passa a valer depois:
`glVertexAttribPointer(...)`, `glEnableVertexAttribArray(...)` e o binding do `GL_ELEMENT_ARRAY_BUFFER` passam a se relacionar com esse `VAO` atual.
- Parametro:
`array`: ID do VAO. `0` significa desbindar e ficar sem VAO ativo.
- Exemplo do projeto:
```cpp
glBindVertexArray(VAO);
```
- Exemplo de desbind:
```cpp
glBindVertexArray(0);
```
- Regra pratica mais importante deste arquivo:
`glBindVertexArray(...)` e o "agora estou configurando este VAO".

### `void glBindBuffer(GLenum target, GLuint buffer);`
- O que faz:
Ativa um buffer em um alvo especifico.
- Tradução pratica:
Voce diz ao OpenGL: "quando eu falar desse alvo agora, use este buffer aqui".
- O que precisa existir antes:
Um ID valido gerado por `glGenBuffers(...)`.
- O que passa a valer depois:
Chamadas como `glBufferData(...)` vao atuar sobre o buffer que estiver bindado naquele `target`.
- Parametros:
`target`: qual tipo de uso o buffer tera naquele momento.
`buffer`: qual ID sera associado a esse alvo.
- Targets usados no projeto:
`GL_ARRAY_BUFFER`
Usado para dados de vertices.

`GL_ELEMENT_ARRAY_BUFFER`
Usado para indices.
- Regra didatica importante:
`glBindBuffer(GL_ARRAY_BUFFER, VBO)` define o VBO atual para vertices.

`glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO)` define o EBO atual de indices.
Quando isso acontece com um `VAO` ativo, essa associacao fica guardada dentro do `VAO`.
- Exemplo do projeto:
```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
```

### `void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);`
- O que faz:
Cria ou substitui os dados do buffer atualmente bindado naquele `target`.
- O que precisa existir antes:
Um buffer correto bindado no `target` correspondente.
- O que passa a valer depois:
A GPU passa a ter uma copia desses dados naquele buffer.
- Parametros:
`target`: alvo do buffer.
`size`: tamanho em bytes.
`data`: ponteiro para os dados, ou `nullptr` para apenas reservar/criar armazenamento.
`usage`: dica de uso.
- Leitura de `usage` no projeto:
`GL_STATIC_DRAW`
Use quando os dados quase nao mudam.
Exemplo: vertices fixos do quadrado.

`GL_DYNAMIC_DRAW`
Use quando os dados vao mudar com frequencia.
Exemplo: trilha atualizada quase todo frame.
- Exemplo do quadrado:
```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
```
- Exemplo dos indices:
```cpp
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
```
- Exemplo da trilha inicial:
```cpp
glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
```
- Exemplo da trilha por frame:
```cpp
glBufferData(
    GL_ARRAY_BUFFER,
    static_cast<GLsizeiptr>(trailVertices.size() * sizeof(float)),
    trailVertices.data(),
    GL_DYNAMIC_DRAW
);
```
- Regra pratica:
`glBufferData(...)` nao escolhe sozinho o buffer. Ele usa o buffer que estiver bindado naquele alvo.

### `void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);`
- O que faz:
Ensina ao `VAO` atual como ler um atributo de vertice a partir do `GL_ARRAY_BUFFER` atualmente bindado.
- Esta e uma das funcoes mais importantes do projeto.
- O que precisa existir antes:
Um `VAO` ativo com `glBindVertexArray(...)`.
Um `VBO` ativo em `GL_ARRAY_BUFFER`.
- O que passa a valer depois:
O atributo `index` fica configurado dentro do `VAO` atual.
Mais importante ainda: o `VAO` guarda qual `VBO` era a fonte desse atributo naquele momento.
- Traducao pratica:
Se voce chamou `glBindVertexArray(VAO)` e depois `glVertexAttribPointer(...)`, essa configuracao pertence a esse `VAO`.
- Parametros:
`index`: qual atributo do shader esta sendo configurado.
No projeto:
`0` -> posicao
`1` -> cor

`size`: quantos componentes esse atributo tem.
No projeto, `3` porque usamos `vec3`.

`type`: tipo de dado de cada componente.
No projeto, `GL_FLOAT`.

`normalized`: se o OpenGL deve normalizar automaticamente certos tipos inteiros.
No projeto, `GL_FALSE` porque os dados ja sao floats.

`stride`: quantos bytes precisam ser pulados para chegar ao proximo vertice completo.
No projeto, cada vertice tem `6` floats: `3` de posicao + `3` de cor.
Por isso:
```cpp
const GLsizei stride = 6 * static_cast<GLsizei>(sizeof(float));
```

`pointer`: deslocamento inicial dentro do vertice.
- Exemplo do atributo de posicao:
```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
```
Leitura:
- atributo `0`
- pega `3` floats
- comeca no inicio do vertice (`nullptr` equivale a offset `0`)

- Exemplo do atributo de cor:
```cpp
glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    stride,
    reinterpret_cast<void *>(3 * sizeof(float))
);
```
Leitura:
- atributo `1`
- pega `3` floats
- comeca depois dos `3` floats da posicao
- por isso o offset e `3 * sizeof(float)`
- Regra pratica mais importante:
`glVertexAttribPointer(...)` aplica a configuracao no `VAO` atual ativado por `glBindVertexArray(...)`.

## Parte 6. Ativar atributos

### `void glEnableVertexAttribArray(GLuint index);`
- O que faz:
Liga o atributo configurado no indice informado.
- O que precisa existir antes:
O atributo ja deve ter sido descrito por `glVertexAttribPointer(...)` no `VAO` atual.
- O que passa a valer depois:
Esse atributo passa a participar do draw.
- Parametro:
`index`: qual atributo sera ativado.
- Exemplo do projeto:
```cpp
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
```
- Regra pratica:
Descrever um atributo sem habilitar costuma resultar em leitura incorreta ou ausencia do dado esperado no shader.

## Parte 7. Uniforms e uso do programa

### `GLint glGetUniformLocation(GLuint program, const GLchar* name);`
- O que faz:
Pergunta ao programa de shader onde esta um uniform com determinado nome.
- O que precisa existir antes:
Programa linkado com sucesso.
- O que passa a valer depois:
Voce ganha uma localizacao inteira para reutilizar depois nas chamadas `glUniform*`.
- Parametros:
`program`: programa em que voce vai procurar.
`name`: nome exato do uniform no shader.
- Exemplo do projeto:
```cpp
GLint uOffsetLocation = glGetUniformLocation(shaderProgram, "uOffset");
```
- Retorno especial:
`-1` significa que o uniform nao foi encontrado ou foi otimizado fora.
- Regra pratica:
Costuma ser feito uma vez, logo depois do link, e guardado em variavel.

### `void glUseProgram(GLuint program);`
- O que faz:
Ativa o programa de shader que sera usado nos draws seguintes.
- O que precisa existir antes:
Programa linkado com sucesso.
- O que passa a valer depois:
As chamadas de draw passam a usar esse programa ate outro ser ativado.
- Exemplo do projeto:
```cpp
glUseProgram(shaderProgram);
```
- Regra pratica:
Normalmente voce ativa o programa antes de enviar uniforms e antes de desenhar.

### `void glUniform2f(GLint location, GLfloat v0, GLfloat v1);`
- O que faz:
Envia dois `float` para um uniform `vec2` do programa atual.
- O que precisa existir antes:
Um programa ativo com `glUseProgram(...)`.
Uma localizacao valida obtida por `glGetUniformLocation(...)`.
- O que passa a valer depois:
O uniform recebe os novos valores para os draws seguintes desse programa.
- Parametros:
`location`: localizacao do uniform.
`v0`, `v1`: os dois floats enviados.
- Exemplo do projeto:
```cpp
glUniform2f(uOffsetLocation, centerX, centerY);
```
- Relacao com o shader do projeto:
Esse uniform alimenta `uOffset`, usado no vertex shader para deslocar a forma na tela.

## Parte 8. Limpeza da tela e render por frame

### `void glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);`
- O que faz:
Define qual cor sera usada quando o buffer de cor for limpo.
- O que precisa existir antes:
Contexto OpenGL valido.
- O que passa a valer depois:
A proxima chamada de `glClear(GL_COLOR_BUFFER_BIT)` usa essa cor.
- Parametros:
`r`, `g`, `b`, `a`: componentes da cor.
- Exemplo do projeto:
```cpp
glClearColor(
    this->backgroundColor.r,
    this->backgroundColor.g,
    this->backgroundColor.b,
    this->backgroundColor.a
);
```
- Regra pratica:
`glClearColor(...)` so define a cor de limpeza. Quem realmente limpa e `glClear(...)`.

### `void glClear(GLbitfield mask);`
- O que faz:
Limpa um ou mais buffers.
- O que precisa existir antes:
Normalmente a cor de limpeza ja foi definida, se o buffer de cor for limpo.
- O que passa a valer depois:
A tela fica pronta para o novo frame.
- Parametro usado no projeto:
`GL_COLOR_BUFFER_BIT`
Limpa o buffer de cor.
- Exemplo do projeto:
```cpp
glClear(GL_COLOR_BUFFER_BIT);
```

## Parte 9. Draw calls

### `void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);`
- O que faz:
Desenha usando indices do `EBO` associado ao `VAO` atual.
- O que precisa existir antes:
Programa ativo.
`VAO` correto bindado.
`EBO` associado a esse `VAO`.
Atributos configurados e habilitados.
- O que passa a valer depois:
A forma indexada e renderizada.
- Parametros:
`mode`: tipo de primitiva. No projeto usamos `GL_TRIANGLES`.
`count`: quantos indices serao lidos.
`type`: tipo do indice. No projeto usamos `GL_UNSIGNED_INT`.
`indices`: offset inicial dentro do `EBO`. `nullptr` significa comecar do inicio.
- Exemplo do projeto:
```cpp
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
```
- Leitura didatica:
O quadrado tem `6` indices porque ele e formado por `2` triangulos.
- Regra pratica:
Use `glDrawElements(...)` quando quiser reaproveitar vertices com indices.

### `void glDrawArrays(GLenum mode, GLint first, GLsizei count);`
- O que faz:
Desenha vertices em sequencia, sem usar indices.
- O que precisa existir antes:
Programa ativo.
`VAO` correto bindado.
Atributos configurados e habilitados.
- O que passa a valer depois:
A sequencia de vertices e desenhada.
- Parametros:
`mode`: tipo de primitiva. No projeto usamos `GL_LINE_STRIP`.
`first`: indice inicial do primeiro vertice. No projeto usamos `0`.
`count`: quantos vertices consecutivos desenhar.
- Exemplo do projeto:
```cpp
glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(trailVertices.size() / 6));
```
- Leitura didatica do `trailVertices.size() / 6`:
Cada vertice da trilha tem `6` floats:
`3` de posicao + `3` de cor.
Entao o total de vertices e a quantidade total de floats dividida por `6`.
- Regra pratica:
Use `glDrawArrays(...)` quando os vertices ja estao na ordem certa e voce nao precisa de indices.

## Parte 10. Liberacao de recursos

### `void glDeleteBuffers(GLsizei n, const GLuint* buffers);`
- O que faz:
Libera buffers como `VBO` e `EBO`.
- Exemplo do projeto:
```cpp
glDeleteBuffers(1, &VBO);
glDeleteBuffers(1, &EBO);
```

### `void glDeleteVertexArrays(GLsizei n, const GLuint* arrays);`
- O que faz:
Libera `VAOs`.
- Exemplo do projeto:
```cpp
glDeleteVertexArrays(1, &VAO);
```

### `void glDeleteProgram(GLuint program);`
- O que faz:
Libera o programa de shader quando ele nao sera mais usado.
- Exemplo do projeto:
```cpp
glDeleteProgram(shaderProgram);
```

## Tutorial comentado: montagem do quadrado do projeto

### Passo 1. Criar os IDs
```cpp
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);
```
- Aqui ainda nao existe layout configurado.
- So estamos pedindo os IDs dos objetos.

### Passo 2. Ativar o VAO que sera configurado
```cpp
glBindVertexArray(VAO);
```
- A partir daqui, a configuracao de atributo vai para esse `VAO`.
- O `EBO` bindado agora tambem fica associado a ele.

### Passo 3. Ativar o VBO de vertices
```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
```
- Agora o alvo `GL_ARRAY_BUFFER` aponta para `VBO`.
- O proximo `glBufferData(GL_ARRAY_BUFFER, ...)` vai escrever nele.

### Passo 4. Enviar vertices
```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
```
- Os vertices do array do C++ vao para a GPU.

### Passo 5. Ativar o EBO de indices
```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
```
- Como o `VAO` esta ativo, esse `EBO` passa a ficar vinculado a ele.

### Passo 6. Enviar indices
```cpp
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
```
- Agora o quadrado tem indices na GPU.

### Passo 7. Ensinar como ler a posicao
```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
glEnableVertexAttribArray(0);
```
- Isso diz ao `VAO` atual:
"o atributo `0` do shader vem do `VBO` atual, tem `3` floats, comeca no inicio do vertice e cada vertice completo ocupa `stride` bytes".

### Passo 8. Ensinar como ler a cor
```cpp
glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    stride,
    reinterpret_cast<void *>(3 * sizeof(float))
);
glEnableVertexAttribArray(1);
```
- Isso diz ao `VAO` atual:
"o atributo `1` tambem vem do mesmo `VBO`, tem `3` floats, mas comeca depois dos `3` floats da posicao".

### Passo 9. Encerrar a configuracao do VAO
```cpp
glBindVertexArray(0);
```
- Desbinda o `VAO` atual.
- Isso ajuda a deixar claro que a fase de configuracao terminou.

### Passo 10. Desenhar no loop
```cpp
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glUniform2f(uOffsetLocation, centerX, centerY);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
```
- `glUseProgram(...)`: ativa o shader.
- `glBindVertexArray(VAO)`: ativa o mapa de leitura da malha.
- `glUniform2f(...)`: manda o deslocamento para o shader.
- `glDrawElements(...)`: desenha o quadrado usando os indices.

## Comparacao rapida: quadrado vs trilha

### Quadrado
- Usa `VAO + VBO + EBO`.
- Usa `glDrawElements(...)`.
- Os dados base quase nao mudam.
- `usage`: `GL_STATIC_DRAW`.

### Trilha
- Usa `VAO + VBO`.
- Nao usa `EBO`.
- Usa `glDrawArrays(GL_LINE_STRIP, ...)`.
- Os dados mudam com frequencia.
- `usage`: `GL_DYNAMIC_DRAW`.

## Pegadinhas comuns para lembrar depois
- `GLAD` so pode ser carregado depois de `glfwMakeContextCurrent(window)`.
- `glBindVertexArray(VAO)` define em qual `VAO` as proximas configuracoes vao cair.
- `glVertexAttribPointer(...)` usa o `GL_ARRAY_BUFFER` atual como fonte do atributo e salva isso no `VAO` atual.
- O binding de `GL_ELEMENT_ARRAY_BUFFER` fica associado ao `VAO` atual.
- `glClearColor(...)` nao limpa a tela sozinho.
- `glUseProgram(...)` normalmente vem antes de `glUniform*` e antes do draw.
- `glDrawElements(...)` e para desenho com indices.
- `glDrawArrays(...)` e para vertices sequenciais.

## Checklist rapido para desenhar sua propria forma
1. O contexto OpenGL ja esta atual?
2. O GLAD carregou sem erro?
3. O shader compilou e linkou sem erro?
4. Os vertices estao em um `VBO`?
5. Se houver indices, eles estao em um `EBO`?
6. O `VAO` certo estava ativo durante `glVertexAttribPointer(...)`?
7. O layout do shader bate com os indices dos atributos (`layout(location = 0/1)`)?
8. O `stride` e o `offset` batem com o formato real do vertice?
9. O programa certo esta ativo com `glUseProgram(...)`?
10. O draw escolhido faz sentido para sua forma (`glDrawElements` ou `glDrawArrays`)?

## Referencias oficiais
- Docs OpenGL navegavel:
https://docs.gl/
- Refpages oficiais da Khronos:
https://registry.khronos.org/OpenGL-Refpages/gl4/
- Exemplo de pagina citada como modelo neste projeto:
https://docs.gl/gl3/glDrawElements
- Guia de contexto do GLFW com GLAD:
https://www.glfw.org/docs/latest/context_guide.html
