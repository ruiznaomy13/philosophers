# Philosopher 🍝🍴

> This file is written in Spanish and English.
 
[ENGLISH]
This program simulates the classic Dining Philosophers problem in a round table using threads and mutex in C.

## Problem Description

In this representation, each philosopher is modeled as a thread, and each fork as a shared resource.
- A philosopher can only eat if they have two adjacent free forks 🍴
- After eating, the philosopher spends some time thinking before attempting to eat again ⏱
- If a philosopher doesn't eat within a specified time interval, they die ❌

## System Requirements

- C Compiler
- Operating system with pthread library support

## Usage

The program is run from the command line with the following syntax:

```bash
./program [NUM_PHILOSOPHERS] [TIME_TO_EAT] [TIME_TO_THINK] [TIME_TO_SLEEP] [NUM_MEALS_OPTIONAL]

**NUM_PHILOSOPHERS**: Number of philosophers at the table (also the number of forks).
**TIME_TO_EAT**: Time in milliseconds a philosopher can go without eating before dying.
**TIME_TO_THINK**: Time in milliseconds a philosopher spends thinking after eating.
**TIME_TO_SLEEP**: Time in milliseconds a philosopher spends sleeping after thinking.
**NUM_MEALS_OPTIONAL** (optional): Number of meals each philosopher will have before the program stops. If not provided, the program will run indefinitely.

[SPANISH]
Este programa simula el problema clásico de los filósofos comensales en una mesa redonda utilizando hilos y mutex en C.

## Descripción del Problema

En esta representación, cada filósofo está modelado como un hilo y cada tenedor como un recurso compartido.
- Un filósofo solo puede comer si tiene dos tenedores adyacentes libres 🍴
- Después de comer, el filósofo pasa un tiempo pensando antes de intentar comer nuevamente ⏱
- Si un filósofo no come en un intervalo de tiempo especificado, muere ❌

## Requisitos del Sistema

- Compilador de C
- Sistema operativo compatible con la biblioteca pthread

## Uso

El programa se ejecuta desde la línea de comandos con la siguiente sintaxis:

```bash
./program [NUM_FILOSOFOS] [TIEMPO_COMER] [TIEMPO_PENSAR] [TIEMPO_DORMIR] [NUM_COMIDAS_OPCIONAL]

**NUM_FILOSOFOS**: Número de filósofos en la mesa (también el número de tenedores).
**TIEMPO_COMER**: Tiempo en milisegundos que un filósofo puede pasar sin comer antes de morir.
**TIEMPO_PENSAR**: Tiempo en milisegundos que un filósofo pasa pensando después de comer.
**TIEMPO_DORMIR**: Tiempo en milisegundos que un filósofo pasa durmiendo después de pensar.
**NUM_COMIDAS_OPCIONAL** (opcional): Número de comidas que cada filósofo realizará antes de que el programa se detenga. Si no se proporciona, el programa se ejecutará indefinidamente.
