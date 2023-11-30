# Projeto de Balaça com Arduino para Medição de Amido de Milho

Este projeto foi desenvolvido do zero como parte da disciplina de Sistemas Embarcados sob a orientação do professor Péricles Anibal de Carvalho. O objetivo é aprimorar o processo de medição do amido de milho, um componente crucial nos tratamentos para controle da glicogenose.

## Descrição do Projeto

O projeto foi concebido integralmente, desde a construção física da caixa até a implementação do código da balança. Inicialmente, a proposta era criar uma balança com Arduino incorporada em uma caixa de MDF. A caixa abriga os componentes, incluindo o Arduino, a ponta da peneira, o motor responsável por vibrá-la e o recipiente sobre a balança.

## Passo a Passo da Construção

### 1. Fabricação da Caixa

1. **Materiais Utilizados:**
   - MDF para a caixa.
   - Componentes eletrônicos (Arduino, LCD, botões, motor, célula de carga).

2. **Construção da Estrutura:**
   - Corte e montagem do MDF conforme as dimensões especificadas.
   - Posicionamento adequado para acomodar os componentes eletrônicos.

3. **Adaptações Necessárias:**
   - Inclusão de suporte para o motor na caixa maior.
   - Preparação para fixação da célula de carga e demais componentes.

### 2. Desenvolvimento do Código

O código da balança foi desenvolvido do zero, utilizando o Arduino UNO e a linguagem de programação C++. O processo de implementação seguiu os seguintes passos:

1. **Configuração do Ambiente:**
   - Instalação e configuração do ambiente de desenvolvimento Arduino.

2. **Leitura da Célula de Carga:**
   - Desenvolvimento de rotinas para leitura precisa dos valores da célula de carga.

3. **Interação com o LCD:**
   - Implementação de funcionalidades para interação com o usuário através do LCD.

4. **Controle por Botões:**
   - Programação dos botões para tarar a balança e ajustar o valor de amido.

5. **Integração com o Motor:**
   - Lógica de controle para o motor vibrar a peneira de maneira eficiente.

## Como Montar o Circuito

Para montar o circuito, siga as instruções detalhadas nas imagens disponíveis na pasta [imagens](https://github.com/PATRICIAJUNQUEIRA/Projeto-Balanca/tree/master/Imagens-Balanca) deste repositório.

## Participantes

- Michele Fernandes dos Santos
- Patricia Miranda e Silva
- Pamela Borges
- Beatriz Christinny Martins
- Eloy D'Avila Menna Barreto
- Guilherme Ribeiro de Almeida

## Implementação e Contribuições

O código-fonte completo do projeto está disponível no [repositório deste projeto](https://github.com/PATRICIAJUNQUEIRA/Projeto-Balanca/blob/master/Balanca.ino). Contribuições são bem-vindas! Se você identificar melhorias ou correções, sinta-se à vontade para criar issues ou pull requests.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
