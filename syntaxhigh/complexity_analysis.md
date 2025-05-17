# Análisis de Complejidad

## Complejidad Temporal

### Función analyze:
- Divide el contenido en líneas: O(n) donde n es el tamaño del contenido
- Procesa cada línea: O(n * m) donde m es la complejidad de procesar una línea
- Complejidad total: O(n * m)

### Función process_line:
- Llama a readytoken para cada línea: O(m) donde m es la longitud de la línea

### Función readytoken:
- Para cada carácter o token en la línea, busca una coincidencia en los patrones
- En el peor caso (si cada carácter es procesado individualmente): O(m * p) donde p es el número de patrones
- Complejidad: O(m * p)

### Función searchtoken:
- Prueba cada patrón secuencialmente: O(p) donde p es el número de patrones
- Cada coincidencia de patrón (Regex.run) tiene una complejidad de O(k) donde k depende de la complejidad de la expresión regular
- Complejidad: O(p * k)

## Análisis de Complejidad Total

Combinando estos análisis, la complejidad temporal total del programa es:
O(n * m * p * k) donde:

- n: número de líneas en el archivo
- m: longitud promedio de una línea
- p: número de patrones (expresiones regulares)
- k: complejidad promedio de evaluación de una expresión regular

Simplificando, si consideramos el tamaño total del archivo como N = n * m, la complejidad sería:
O(N * p * k)

### Consideraciones Importantes:
- El número de patrones (p) es constante en este programa (12 patrones).
- La complejidad de las expresiones regulares (k) puede variar, pero también es relativamente constante para este conjunto específico.

Por lo tanto, prácticamente la complejidad se simplifica a:
O(N) - Complejidad lineal respecto al tamaño del archivo

## Complejidad Espacial

- Almacenamiento del contenido original: O(N)
- Almacenamiento de líneas: O(N)
- Acumulación de tokens HTML: O(N) con un factor constante mayor debido al marcado HTML

La complejidad espacial total es:
O(N) - Complejidad lineal respecto al tamaño del archivo 