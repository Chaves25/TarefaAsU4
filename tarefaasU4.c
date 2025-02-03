#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_RED 2
#define LED_YELLOW 3
#define LED_GREEN 4
#define LED_BLUE 5
#define BUTTON 6

// Estado atual do semáforo
volatile int state = 0;
volatile bool button_pressed = false;

// Callback do temporizador periódico
bool repeating_timer_callback(struct repeating_timer *t) {
    // Alternar entre os estados do semáforo
    gpio_put(LED_RED, state == 0);
    gpio_put(LED_YELLOW, state == 1);
    gpio_put(LED_GREEN, state == 2);
    
    // Próximo estado
    state = (state + 1) % 3;
    return true; // Continua repetindo
}

// Callback do temporizador de um disparo
int64_t one_shot_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0); // Desliga o LED azul
    button_pressed = false; // Permite nova ativação
    return 0;
}

void button_callback(uint gpio, uint32_t events) {
    if (!button_pressed) {
        button_pressed = true;
        gpio_put(LED_BLUE, 1); // Liga o LED azul
        add_alarm_in_ms(3000, one_shot_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    // Inicializa o botão
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    // Configura temporizador periódico
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    
    while (true) {
        printf("Semáforo e temporizador ativos...\n");
        sleep_ms(1000);
    }
}
