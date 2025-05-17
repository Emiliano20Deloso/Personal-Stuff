#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Esto es un comentario de una línea
/* Esto es un comentario
   de múltiples líneas */

// Definición de constantes
#define PI 3.14159265358979323846
#define MAX_STUDENTS 100

// Declaración de una clase
class Persona {
private:
    std::string nombre;
    int edad;
    double altura;
    char genero;

public:
    // Constructor
    Persona(std::string n, int e, double a = 1.70, char g = 'M') : 
        nombre(n), edad(e), altura(a), genero(g) {}
    
    // Métodos
    void saludar() {
        std::cout << "Hola, me llamo " << nombre << " y tengo " << edad << " años." << std::endl;
    }
    
    int obtenerAñosHastaJubilacion() {
        return (edad < 65) ? 65 - edad : 0;
    }
    
    ~Persona() {
        // Destructor
        std::cout << "Adiós, " << nombre << std::endl;
    }
};

// Función que calcula el factorial de un número
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Función que usa operadores y diferentes tipos de números
double calcularExpresion(double x, float y) {
    double resultado = 0.0;
    resultado = (x * 5.75) + (y / 2) - (3e-2 * std::pow(x, 2));
    
    if (resultado > 100) {
        return resultado * 0.9;  // Aplicar descuento del 10%
    } else if (resultado >= 50 && resultado <= 100) {
        return resultado;
    } else {
        return resultado * 1.05;  // Aplicar recargo del 5%
    }
}

// Función principal
int main() {
    // Declaración de variables
    int numeros[5] = {10, 20, 30, 40, 50};
    std::vector<std::string> nombres;
    bool continuar = true;
    char opcion = 'S';
    
    // Uso de operadores
    int a = 5, b = 7;
    int suma = a + b;
    int resta = a - b;
    int multiplicacion = a * b;
    int division = b / a;
    int modulo = b % a;
    bool comparacion = (a == b) || (a < b) && !(a > 10);
    
    // Incrementos y decrementos
    a++;
    --b;
    
    // Operadores de asignación
    int c = 10;
    c += 5;  // c = c + 5
    c *= 2;  // c = c * 2
    
    // Uso de strings y caracteres
    std::string mensaje = "¡Este es un mensaje de prueba!";
    char caracter = 'X';
    
    std::cout << "Mensaje: " << mensaje << std::endl;
    std::cout << "Carácter: " << caracter << std::endl;
    
    // Uso de la clase Persona
    Persona persona1("Ana", 25, 1.65, 'F');
    Persona persona2("Carlos", 42);
    
    persona1.saludar();
    
    int añosParaJubilacion = persona2.obtenerAñosHastaJubilacion();
    std::cout << "Años hasta jubilación: " << añosParaJubilacion << std::endl;
    
    // Cálculo del factorial
    int numero = 6;
    std::cout << "El factorial de " << numero << " es " << factorial(numero) << std::endl;
    
    // Uso de condicionales
    double valorX = 12.5;
    float valorY = 7.25f;
    double resultadoExp = calcularExpresion(valorX, valorY);
    
    std::cout << "El resultado de la expresión es: " << resultadoExp << std::endl;
    
    if (resultadoExp > 50) {
        std::cout << "El resultado es mayor que 50" << std::endl;
    } else {
        std::cout << "El resultado es menor o igual a 50" << std::endl;
    }
    
    // Uso de bucles
    std::cout << "Contador con for: ";
    for (int i = 0; i < 5; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Contador con while: ";
    int j = 0;
    while (j < 5) {
        std::cout << j << " ";
        j++;
    }
    std::cout << std::endl;
    
    // Uso de switch
    int dia = 3;
    switch (dia) {
        case 1:
            std::cout << "Lunes" << std::endl;
            break;
        case 2:
            std::cout << "Martes" << std::endl;
            break;
        case 3:
            std::cout << "Miércoles" << std::endl;
            break;
        default:
            std::cout << "Otro día" << std::endl;
    }
    
    return 0;
}