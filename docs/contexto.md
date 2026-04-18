# Contexto do Projeto

## Projeto de aprendizado C++/OpenGL

Esse projeto nasce da vontade de explorar linguagens mais clássicas, especialmente `C++`, saindo um pouco do contexto cotidiano de `JS/TS` e se aproximando mais do tipo de base técnica que pode sustentar um caminho futuro em `gamedev`.

O objetivo de longo prazo nao e apenas aprender uma linguagem nova, mas construir repertorio para criar jogos divertidos e interessantes no futuro. Por isso, este projeto deve ser tratado como uma jornada de formacao tecnica e criativa ao mesmo tempo.

## Aprendizado maximo

O foco deste projeto nao e fazer `vibecoding` para ver algo aparecendo na tela o mais rapido possivel. O foco e aprender de verdade:
- como escrever codigo em `C++`;
- como estruturar programas graficos;
- como pensar em renderizacao com `OpenGL`;
- como introduzir simulacao e fisica aos poucos;
- como transformar curiosidade visual em entendimento tecnico.

Sempre que possivel, o processo deve incluir:
- explicacoes curtas e didaticas;
- exemplos pequenos e objetivos;
- exercicios e tarefas praticas;
- conexao clara entre o que aparece na tela e o conceito por tras.
- espaco para o usuario escrever o codigo com as proprias maos, em vez de apenas receber arquivos prontos.

Sempre que arquivos, estruturas ou ferramentas novas forem introduzidos, a explicacao precisa cobrir:
- o que foi criado ou alterado;
- qual problema isso resolve;
- por que essa abordagem foi escolhida;
- como isso se encaixa no momento atual da trilha;
- quais erros podem aparecer e o que eles significam.

## Plano central

Uma referencia importante para este projeto e a ideia de uma simulacao inspirada em sistema solar:
- um grid horizontal sendo deformado pela massa dos planetas;
- simulacoes de gravidade;
- corpos se aproximando e interagindo no espaco;
- uma cena visualmente interessante para explorar.

O projeto sera considerado bem-sucedido quando houver uma simulacao com alguns planetas e gravidade agindo, de forma que seja possivel brincar com ela e observar comportamentos emergentes.

Existe consciencia de que isso toca em temas mais profundos de fisica e matematica, mas essa complexidade faz parte do objetivo e deve ser enfrentada de modo progressivo.

## Caminho do sucesso

Este projeto precisa ser leve e divertido. A sustentabilidade do aprendizado e tao importante quanto a qualidade tecnica.

Como existe risco real de abandonar projetos longos no meio do caminho, a jornada precisa ter:
- pequenas metricas de sucesso;
- entregas visuais frequentes;
- objetivos claros;
- marcos intermediarios;
- tarefas concretas;
- senso continuo de progresso.

O projeto deve manter a curiosidade viva. Isso significa evitar longos periodos de teoria desconectada da pratica. O ideal e sentir o OpenGL cedo, ver coisas acontecendo logo, e usar esses resultados como gancho para aprender conceitos mais profundos de `C++`, renderizacao e simulacao.

Como ja existe experiencia previa com programacao, a trilha nao precisa assumir um perfil de iniciante absoluto. O aprendizado de `C++` pode crescer junto com os problemas reais que surgirem em `OpenGL`, de forma natural e progressiva.

## Como este contexto deve influenciar o projeto
- Priorizar aprendizado real sobre velocidade bruta de implementacao.
- Evitar solucoes que escondam demais os conceitos importantes.
- Explicar o suficiente para consolidar entendimento sem transformar tudo em teoria pesada.
- Favorecer quick wins visuais quando isso ajudar a manter motivacao.
- Introduzir conceitos mais complexos de `C++` lado a lado com necessidades reais do projeto.

## Como a comunicacao deve acontecer
- Alteracoes no codigo devem ser acompanhadas de explicacao didatica.
- Nomes de arquivos, classes, ferramentas e configuracoes devem ser explicados quando aparecerem pela primeira vez.
- Erros nao devem ser apenas corrigidos; devem ser traduzidos para linguagem de aprendizado.
- Sempre que possivel, conectar cada mudanca a um conceito concreto de `C++`, build system ou `OpenGL`.
- O objetivo nao e apenas avancar no projeto, mas fazer o usuario entender o que acabou de acontecer.
- Documentacoes internas devem ser escritas como material de retomada futura, nao como anotacao vaga ou glossario seco.
- Sempre que uma documentacao tecnica for criada ou atualizada, ela deve deixar claro:
  - o que algo e;
  - o que faz;
  - por que existe;
  - o que precisa existir antes;
  - o que muda depois;
  - como isso entra na ordem real de uso;
  - quais confusoes um iniciante pode ter naquele ponto.
- O padrao de qualidade atual para esse tipo de escrita e o nivel pedagogico adotado em `docs/glfw.md` e `docs/glad.md`: explicacao objetiva, conectada ao projeto real e forte o suficiente para permitir retomada do zero no futuro.

## Como o codigo deve ser ensinado
- A resposta ideal deve mostrar como o arquivo deve ficar diretamente no chat.
- O conteudo deve ser quebrado em partes pequenas e compreensiveis.
- Cada funcao deve ser explicada individualmente: papel, uso, entradas, saidas e impacto no programa.
- Sempre que codigo for enviado no chat, incluir comentarios didaticos detalhados nos trechos centrais da logica.
- Sintaxes novas na trilha devem receber explicacao direta no proprio codigo comentado, com foco no "o que faz", "por que existe" e "quando usar" (exemplo: `std::srand(static_cast<unsigned>(std::time(nullptr)));`).
- Sempre que fizer sentido, propor microtarefas para o usuario digitar, testar e adaptar.
- Sempre que possivel, deixar espaco para exploracao pessoal, como trocar valores, nomes, cores ou pequenas estruturas.
- A escrita manual do codigo pelo usuario faz parte do aprendizado e deve ser incentivada.

## Como a documentacao tecnica deve ser ensinada
- Ao escrever documentacao para bibliotecas, funcoes, ferramentas ou arquitetura do projeto, assumir que o leitor futuro pode estar retomando do zero.
- Preferir estrutura em camadas:
  - visao geral;
  - ordem de uso;
  - funcao por funcao;
  - exemplos do projeto;
  - erros comuns;
  - checklist de retomada.
- Sempre que houver conceito com estado implicito, como `VAO`, `VBO`, `EBO`, shader program, contexto OpenGL ou pipeline de build, explicitar quem esta ativo, quem esta sendo configurado e qual efeito fica salvo depois da chamada.
- A documentacao ideal deve permitir que o usuario reconstrua a logica mental do projeto, e nao apenas reconheca nomes de funcoes quando voltar no futuro.
