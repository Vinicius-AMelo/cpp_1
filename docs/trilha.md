# Trilha Integrada de C++ + OpenGL para chegar à simulação de universo

## Resumo
- Trilha em `8 etapas`, sempre com `1 entrega visual` + `1 bloco de conceitos de C++` + `1 exercício curto`.
- Ritmo escolhido: `quick wins com teoria embutida`, para manter motivação sem sacrificar fundamentos.
- Stack base definida: `C++17 + CMake + GLFW + GLAD + GLM + OpenGL 3.3 Core`.
- Meta final: uma cena com `planetas`, `gravidade`, `órbitas/atração`, e um `grid deformável` simples para representar influência gravitacional.

## Regra pedagógica de execução
- Cada avanço prático da trilha deve vir acompanhado de explicação do motivo técnico e do motivo pedagógico da mudança.
- Ao introduzir novos arquivos, ferramentas ou conceitos, explicar o papel de cada um antes de assumir familiaridade.
- Sempre que houver erro ou warning durante a trilha, registrar e explicar o significado antes de apenas corrigir.
- O sucesso de uma etapa depende de o código funcionar e de o conceito principal daquela etapa estar compreendido.
- Sempre que possivel, a implementacao deve ser guiada no chat para que o usuario escreva o codigo manualmente.
- Antes de grandes mudancas, apresentar o arquivo-alvo em blocos pequenos, com explicacao por trecho e pequenas tarefas praticas.
- Todo codigo compartilhado no chat deve incluir comentarios didaticos nos pontos centrais da logica, principalmente quando introduzir sintaxe nova para a etapa atual.
- Toda documentacao nova ou revisada deve seguir padrao alto de didatica, com explicacao suficiente para retomada futura do zero.
- Em documentacao tecnica, priorizar respostas para:
  - o que e;
  - o que faz;
  - por que existe;
  - o que precisa vir antes;
  - o que fica configurado ou salvo depois;
  - como isso aparece na ordem real do projeto.
- A referencia pedagogica desse padrao, no estado atual do projeto, e o modelo adotado em `docs/glfw.md` e `docs/glad.md`.

## Como este documento se relaciona com os outros
- `docs/trilha.md` é o plano macro e a fonte de verdade estratégica do projeto.
- `docs/status.md` mostra o estado atual e deve ser o primeiro arquivo aberto ao retomar o projeto.
- `docs/logbook.md` registra o histórico incremental das sessões de estudo.
- `docs/etapas.md` acompanha a execução prática de cada etapa da trilha.
- Regra de consistência:
  - `status.md` mostra o presente.
  - `logbook.md` preserva a história.
  - `etapas.md` compara planejado, feito e aprendido.
  - `trilha.md` define a direção maior.

## Mudanças e estrutura base do projeto
- Substituir a task atual baseada em `gcc` por build oficial com `CMake`; usar `g++` como compilador C++.
- Padronizar o projeto em módulos simples:
  - `app`: janela, loop principal, input, tempo.
  - `graphics`: shader, mesh, renderer, camera.
  - `simulation`: body, physics_system, integrator.
  - `core`: math helpers, timer, utilitários pequenos.
- Interface interna esperada ao longo da trilha:
  - `Shader` para compilar/linkar shaders e enviar uniforms.
  - `Mesh` para encapsular `VAO/VBO/EBO`.
  - `Body` com `position`, `velocity`, `mass`, `radius`.
  - `PhysicsSystem::update(deltaTime)` para evoluir a simulação.
- Padrão de evolução: começar procedural quando for didático e migrar para classes/RAII quando o ganho conceitual aparecer.

## Etapas
1. **Fundação do ambiente**
- Objetivo visual: abrir janela limpa com loop renderizando cor de fundo.
- C++: compilação, headers vs source files, `main`, namespaces, `std::cout`, tipos básicos, referência vs valor.
- OpenGL: contexto, game loop, clear color, double buffering.
- Exercício: mudar cor com tecla e explicar o papel do loop principal.
- Critério de saída: projeto compila via `CMake` e abre uma janela estável.

2. **Primeiro triângulo**
- Objetivo visual: desenhar um triângulo estático.
- C++: arrays, `std::array`, funções, escopo, `const`, erros de compilação vs linkedição.
- OpenGL: pipeline moderna, vertex data, `VAO`, `VBO`, vertex shader, fragment shader.
- Exercício: mover os vértices para formar outro triângulo sem copiar código.
- Critério de saída: você entende o caminho CPU -> buffer -> shader -> tela.

3. **Triângulos melhores e organização**
- Objetivo visual: desenhar quadrado com `EBO` e múltiplas cores.
- C++: structs, constructors, separação em `.hpp/.cpp`, enums, `std::vector`.
- OpenGL: `EBO`, atributos de vértice, interpolação de cor, uniforms.
- Exercício: criar uma struct `Vertex` e justificar seu layout.
- Critério de saída: primeira refatoração real sem perder clareza.

4. **Transformações e câmera 2D/3D simples**
- Objetivo visual: objetos transladando, rotacionando e escalando.
- C++: classes pequenas, encapsulamento, RAII, inicialização por lista, overload básico.
- OpenGL: matrizes, model/view/projection, coordenadas normalizadas, uso de `GLM`.
- Exercício: fazer um objeto girar em torno de outro com hierarquia simples.
- Critério de saída: domínio prático de transformações e uniforms de matriz.

5. **Cena com múltiplos corpos**
- Objetivo visual: vários corpos na tela, cada um com posição e velocidade próprias.
- C++: `std::vector<Body>`, passagem por referência, funções puras vs mutáveis, organização por responsabilidade.
- OpenGL: render loop com múltiplos draws, cores por objeto, atualização por frame.
- Exercício: spawnar corpos aleatórios e pausar/retomar a simulação.
- Critério de saída: separar claramente `update` de `render`.

6. **Física básica e gravidade**
- Objetivo visual: corpos atraindo-se e alterando trajetória.
- C++: modelagem de dados, invariantes, funções matemáticas, debugging numérico, `constexpr` onde fizer sentido.
- Física/OpenGL: vetor força, aceleração, velocidade, integração de Euler semi-implícita, `deltaTime`.
- Exercício: comparar simulação com `deltaTime` fixo vs variável e anotar diferenças.
- Critério de saída: sistema estável o suficiente para brincar com massas e velocidades.

7. **Escala, estabilidade e arquitetura**
- Objetivo visual: mini sistema solar jogável, com câmera navegável e trilhas opcionais.
- C++: ownership, ponteiros inteligentes apenas se necessários, composição, separação entre dados e comportamento, profiling básico.
- OpenGL: câmera melhor, trail rendering simples, controle de zoom, organização de shaders.
- Exercício: limitar explosões numéricas e documentar a causa.
- Critério de saída: código já parece “engine pequena” e não só experimento solto.

8. **Grid deformável e apresentação final**
- Objetivo visual: grid horizontal sendo deformado pela influência de massa + planetas orbitando.
- C++: algoritmos sobre coleções, abstrações pequenas, manutenção/refatoração guiada por clareza.
- OpenGL: malha em grid, atualização de vértices, visualização de campo/curvatura simplificada.
- Exercício: testar duas fórmulas de deformação e escolher a melhor visualmente.
- Critério de saída: demo final alinhada ao objetivo original do projeto.

## Testes e critérios de aceitação
- Em cada etapa, validar:
  - build limpo via `CMake`;
  - execução sem crash;
  - entrega visual da etapa funcionando;
  - explicação curta, em palavras suas, do conceito principal de C++ e do conceito principal de OpenGL usados ali.
  - entendimento básico dos novos arquivos, ferramentas ou mensagens de erro introduzidos na etapa.
  - participação ativa do usuário na escrita ou adaptação dos trechos principais da etapa, sempre que viável.
- Marcos de sucesso:
  - Etapa 2: “entendo por que o triângulo aparece”.
  - Etapa 4: “consigo manipular objetos com matrizes sem copiar tutorial cegamente”.
  - Etapa 6: “consigo explicar como massa, força e `deltaTime` afetam a simulação”.
  - Etapa 8: “tenho uma demo divertida e extensível”.
- Regra pedagógica: ao fim de cada etapa, refazer uma parte pequena “de cabeça”, sem olhar código, para consolidar aprendizado.

## Assumptions e defaults
- Sistema alvo: Linux Fedora, com instalação das dependências necessárias para `GLFW`, `GLM`, `OpenGL` e `CMake`.
- Padrão de linguagem: `C++17`.
- API gráfica: `OpenGL 3.3 Core`.
- Math library: `GLM`, sem criar biblioteca própria de álgebra no início.
- Integração física inicial: `Euler semi-implícita`; métodos mais avançados só depois da versão jogável.
- Prioridade do plano: aprendizado progressivo e motivador, não otimização máxima nem física academicamente perfeita na v1.
