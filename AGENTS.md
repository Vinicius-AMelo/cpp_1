# AGENTS.md

## Objetivo deste arquivo
- Este arquivo é a porta de entrada documental do projeto.
- Antes de agir no código ou atualizar a documentação, consulte os arquivos em `docs/` conforme o tipo de tarefa.
- A ideia é separar:
  - contexto e motivação;
  - direção estratégica;
  - estado atual;
  - histórico de sessões;
  - acompanhamento operacional por etapa.

## Ordem recomendada de leitura
0. `docs/LearnOpenGL.pdf`
1. `docs/personalidade.md`
2. `docs/contexto.md`
3. `docs/status.md`
4. `docs/trilha.md`
5. `docs/etapas.md`
6. `docs/logbook.md`

## Papéis de cada documento

### `docs/contexto.md`
- Guarda o contexto autoral do projeto.
- Explica a motivação, o estilo de aprendizado desejado, a visão de longo prazo e o critério subjetivo de sucesso.
- Deve ser levado em consideração sempre que houver decisões sobre ritmo, didática, trade-offs entre teoria e prática, ou priorização de tarefas.

### `docs/status.md`
- É o painel principal do momento atual.
- Deve ser o primeiro arquivo aberto ao retomar o projeto.
- Informa onde o projeto parou, qual etapa está ativa, próximos passos, bloqueios e pontos de revisão.

### `docs/trilha.md`
- É a fonte de verdade estratégica.
- Define a jornada macro de aprendizado em C++ e OpenGL.
- Deve ser usado para orientar direção, sequência de evolução e critérios de saída das etapas.

### `docs/etapas.md`
- É o banco operacional da trilha.
- Mostra cada etapa com tarefas planejadas, tarefas concluídas, exercícios, evidências e status.
- Deve ser atualizado conforme o avanço real do projeto.

### `docs/logbook.md`
- É o diário incremental das sessões.
- Registra o que foi feito, o que foi aprendido, dificuldades, decisões e próximo passo.
- Deve ser atualizado a cada sessão, mesmo sem concluir uma etapa inteira.

## Regras de uso
- `docs/contexto.md` define a intenção humana e pedagógica do projeto.
- `docs/trilha.md` define a direção macro.
- `docs/status.md` define o presente.
- `docs/etapas.md` mede execução e progresso.
- `docs/logbook.md` preserva memória e continuidade.

## Regra de explicação didática
- Mudanças no projeto devem vir acompanhadas de explicação clara, não apenas da implementação.
- Sempre que codigo for enviado no chat, incluir comentarios didaticos detalhados nos pontos mais importantes da logica e nas sintaxes novas da trilha.
- Quando aparecer sintaxe mais densa (por exemplo `std::srand(static_cast<unsigned>(std::time(nullptr)));`), explicar no proprio trecho o que cada parte faz e por que ela existe.
- Sempre que arquivos forem criados, alterados ou removidos, explicar:
  - o que mudou;
  - por que mudou;
  - o que esse arquivo faz;
  - como isso se conecta ao aprendizado atual de C++ ou OpenGL.
- Sempre que houver erro, warning ou bloqueio, explicar:
  - o que o erro significa;
  - se ele vem do código, do editor ou do ambiente;
  - como investigar;
  - como corrigir.
- Evitar respostas que assumam entendimento prévio sem construir contexto.
- Priorizar explicações que façam o usuário entender a estrutura do projeto e não apenas aceitar a solução.

## Regra de alto padrão para documentacao e didatica
- Todo agente que atualizar arquivos em `docs/` deve preservar o mesmo nivel alto de clareza, densidade util e organizacao pedagogica ja adotado em `docs/glfw.md` e `docs/glad.md`.
- "Didatico" neste projeto nao significa resumido demais nem generico; significa explicar com precisao, em linguagem acessivel, sem pular as conexoes que um iniciante ainda nao enxerga sozinho.
- Sempre que uma documentacao tecnica for criada ou atualizada, ela deve responder de forma explicita, sempre que fizer sentido:
  - o que isso e;
  - o que isso faz;
  - por que isso existe;
  - o que precisa existir antes;
  - o que passa a valer depois;
  - em que ordem de uso isso aparece;
  - quais estados, objetos ou estruturas estao sendo afetados;
  - como isso aparece no projeto atual;
  - quais erros, confusoes ou armadilhas sao comuns.
- Evitar documentacao em tom de glossario seco ou lista vaga de definicoes.
- Evitar frases que so repetem o nome da funcao com palavras parecidas sem realmente explicar efeito, contexto e consequencia.
- Quando a documentacao for sobre APIs tecnicas como `GLFW`, `GLAD`, `OpenGL`, `CMake` ou recursos de `C++`, preferir estrutura de "mapa de uso" em vez de apenas "referencia rapida".
- Sempre que possivel, conectar a teoria com:
  - a ordem real de chamadas no codigo;
  - o estado atual da aplicacao;
  - o motivo pedagogico daquela explicacao existir.
- Se uma documentacao existente estiver abaixo desse padrao e precisar ser tocada, o agente deve aproveitar para elevá-la ao padrao atual, em vez de apenas inserir um bloco novo desconectado.
- O objetivo final da documentacao neste projeto e servir como material de retomada futura do zero, com autonomia real, e nao apenas como registro superficial.

## Regra de autoria do código
- Por padrão, evitar editar arquivos de código para o usuário.
- A abordagem preferida deve ser:
  - mostrar no chat como o arquivo deve ficar;
  - incluir comentarios explicativos no codigo mostrado, com foco nos conceitos novos da etapa atual;
  - separar a explicação em tópicos ou blocos pequenos;
  - explicar cada função, trecho ou conceito individualmente;
  - propor pequenas tarefas para o usuário digitar e testar pessoalmente.
- Só editar código diretamente quando o usuário pedir explicitamente para isso ou quando a mudança for documental/configuracional acordada.
- O objetivo é que o usuário escreva o máximo possível do código com entendimento real do que está fazendo.

## Regras de atualização
- Ao começar uma sessão:
  - ler `docs/status.md`;
  - confirmar a etapa atual em `docs/etapas.md`;
  - consultar `docs/contexto.md` se a decisão envolver forma de aprender, motivação ou nível de profundidade.
- Ao terminar ou pausar uma sessão:
  - atualizar `docs/logbook.md`;
  - atualizar `docs/status.md`;
  - refletir o avanço da etapa em `docs/etapas.md`.
- Quando houver mudança de direção relevante:
  - atualizar `docs/trilha.md`;
  - registrar a decisão no `docs/logbook.md`.
- Quando houver mudança no propósito, motivação ou critérios subjetivos do projeto:
  - atualizar `docs/contexto.md`.

## Princípios deste projeto
- O projeto existe para aprendizado real, não para apenas colocar algo na tela.
- O avanço deve equilibrar resultado visual, domínio de C++ e entendimento de OpenGL.
- O processo precisa ser leve, divertido e cumulativo para reduzir abandono.
- Sempre que possível, as próximas ações devem manter o projeto interessante e didático ao mesmo tempo.
- Código funcionando sem entendimento não é considerado sucesso completo neste projeto.
- Código escrito pelo próprio usuário, com orientação guiada, é preferível a código aplicado automaticamente.
