# Syntax Highlighter in Elixir for C++

In this task I made a program call (`syntaxhigh.exs`) in elixir who receive a `.cpp` file with a normal C++ code, then it analize and with regular expression it could take every single token from c++ in the file:

- Keywords
- Comments
- Strings
- Libraries 
- Numbers 
- Identifiers
- Functions 
- Punctuations
- Whitespace 
- Operators

The target is to make a `.html` file (`output.html`) where you can see every different token in a specific color. 

## Files Required

The files you need to run this are: 
- `syntaxhigh.exs`
- `prueba2.cpp`
- `prueba3.cpp`
- `Store_proyect.cpp` 
- `output.html` 

The 3 `.cpp` files are for testing.

# Complexity Analysis of Syntax Highlighter in Elixir

## Main Functions and their Complexity

# Análisis de Complejidad

## Complejidad (O)

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

# Possible Optimizations

## Performance Improvements

1. **Regex Pattern Ordering**
   - Sort regex patterns by frequency of appearance to improve average time
   - Most common patterns should be checked first

2. **Efficient Tokenization**
   - Implement more efficient tokenization techniques
   - Avoid testing all patterns for each position
   - Use pattern matching optimization strategies

3. **Finite State Machine Implementation**
   - Implement a parser based on finite state machines
   - This would reduce complexity
   - More efficient than regex pattern matching for certain cases

## Benefits

- Reduced processing time
- Lower memory usage
- More efficient token recognition
- Better scalability for larger files

# Ethical Implications

The ethical implications of this type of technology in society are that this can be a great help for someone who is trying to make a similar project but in another language, in addition to the fact that this also facilitates the understanding of how a programming language works in terms of knowing how to identify all its elements and at the same time makes it so that by just looking at a code you can much more easily identify what the person who wrote it meant to say.




