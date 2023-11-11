# Philosopher Dining Problem

Este programa simula el problema clásico de los filósofos comensales en una mesa redonda utilizando hilos y mutex en C.

## Descripción del Problema

En esta representación, cada filósofo está modelado como un hilo y cada tenedor como un recurso compartido.
- Un filósofo solo puede comer si tiene dos tenedores adyacentes libres
- Después de comer, el filósofo pasa un tiempo pensando antes de intentar comer nuevamente
- Si un filósofo no come en un intervalo de tiempo especificado, muere

## Requisitos del Sistema

- Compilador de C
- Sistema operativo compatible con la biblioteca pthread

## Uso

El programa se ejecuta desde la línea de comandos con la siguiente sintaxis:

```bash
./program [NUM_FILOSOFOS] [TIEMPO_COMER] [TIEMPO_PENSAR] [TIEMPO_DORMIR] [NUM_COMIDAS_OPCIONAL]
