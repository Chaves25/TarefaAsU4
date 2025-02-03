# TarefaAsU4

# Projeto: Temporizadores no Raspberry Pi Pico W

## Descrição
Este projeto implementa dois sistemas utilizando temporizadores no Raspberry Pi Pico W:
1. **Semáforo com temporizador periódico**: Alterna entre os LEDs vermelho, amarelo e verde a cada 3 segundos.
2. **Temporizador de um disparo (One Shot)**: Aciona um LED azul por 3 segundos ao pressionar um botão.

## Requisitos
- Microcontrolador Raspberry Pi Pico W
- 4 LEDs (vermelho, amarelo, verde e azul)
- 4 resistores de 330 Ω
- 1 pushbutton
- Ambiente de desenvolvimento VS Code
- Pico SDK instalado
- Simulação no Wokwi

## Configuração dos GPIOs
- **Semáforo**:
  - LED vermelho: GPIO 2
  - LED amarelo: GPIO 3
  - LED verde: GPIO 4
- **Temporizador de um disparo**:
  - LED azul: GPIO 5
  - Botão: GPIO 6

## Compilação e Execução
1. Clone o repositório:
   ```sh
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DO_REPOSITORIO>
   ```
2. Compile o projeto:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Envie o código para o Raspberry Pi Pico W:
   ```sh
   cp projeto.uf2 /media/<USUARIO>/RPI-RP2
   ```
4. Para simular no Wokwi, importe o projeto e execute a simulação.

## Notas
- O botão possui debounce via software.
- O LED azul só pode ser acionado novamente após desligar.
- O código é versionado no GitHub.

