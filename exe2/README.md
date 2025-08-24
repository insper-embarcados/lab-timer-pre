# exe 1

![](func.gif)

Árvore de natal

O mesmo comportamento do exe1, só que agora com vezes dois (deve utilizar dois timers). Para o LED vermelho usar **500 ms** e para o LED Verde usar **250 ms**.

- Os LED devem sempre começar e terminar no estado apagado!

## Regras de implementação do firmware:

- Baremetal (sem RTOS).
- Utilizar timers.
    - Não é permitido usar `sleep_ms(), sleep_us(), get_absolute_time()`.
- **Deve trabalhar com interrupções nos botões**.  
    - Nao e permitido usar `gpio_get()`.
- **printf** pode atrapalhar o tempo de simulação, comenta/remova antes de testar.

## Testes

O código deve passar em todos os testes para ser aceito:

- `embedded_check`
- `firmware_check`
- `wokwi`

