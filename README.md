# Taller 02 - SIMD (CE-4302)
**Autores:** Sebastian Quesada y Luis Delgado
---

##  Descripción del Proyecto

Este taller implementa y compara dos versiones de un algoritmo de conversión de texto (mayúsculas ↔ minúsculas) con el objetivo de analizar las diferencias de rendimiento entre una versión **serial** y una versión **SIMD (vectorizada)** utilizando **instrucciones AVX2**.

Además, se incluye un **generador de cadenas aleatorias** y un **script de benchmarking** en Python que permite medir, registrar y graficar los resultados.

El proyecto fue desarrollado y probado en una máquina virtual Linux (Ubuntu 24.04) utilizando herramientas como `g++`, `make`, `perf` y `matplotlib`.

---
##  Requisitos del Entorno

- Ubuntu 24.04 o similar 
- Compilador `g++` con soporte C++17 
- Soporte SIMD (AVX2) 

Se debe correr:
sudo apt update
sudo apt install -y build-essential python3 python3-pip linux-tools-generic
pip install --break-system-packages matplotlib numpy pandas


## Compilación del Proyecto

Abrir la terminal y ubicarse en la carpeta del proyecto:

cd ~/taller_SIMD


Limpiar compilaciones previas:

make clean


Compilar todos los programas:

make


Esto generará los ejecutables:

bin/generator
bin/case_serial
bin/case_simd


##  Ejecución del Programa
1) Generador de Texto Aleatorio
./bin/generator <longitud> <porcentaje_letras> <alineacion>

Ejemplo:
./bin/generator 100000 80 32

Parámetros:
100000 → longitud del texto
80 → porcentaje de caracteres alfabéticos
32 → alineación (múltiplo de bytes)


2) Conversión Serial
./bin/case_serial <texto> <modo>

Ejemplo:
./bin/case_serial "HolaMundo" upper

Modos:
upper → convierte a mayúsculas
lower → convierte a minúsculas

Salida esperada:
Resultado: HOLAMUNDO
Tiempo de ejecución: 0.0023 ms

3) Conversión SIMD (AVX2)
./bin/case_simd <texto> <modo>

Ejemplo:
./bin/case_simd "HolaMundo" lower


4) Benchmark Automático
El script benchmark.py ejecuta ambas versiones (serial y SIMD) sobre textos de distintos tamaños y genera resultados comparativos.

python3 src/benchmark.py



