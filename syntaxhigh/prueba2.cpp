#include <iostream>
#include <string>
#include <vector>

// Esta es una función de ejemplo
/* Este es un comentario
   multilínea */

class Persona {
private:
    std::string nombre;
    int edad;
    
public:
    Persona(std::string n, int e) : nombre(n), edad(e) {}
    
    void saludar() {
        std::cout << "Hola, mi nombre es " << nombre << " y tengo " << edad << " años." << std::endl;
    }
};

int sumar(int a, int b) {
    return a + b;
}

int main() {
    // Declaración de variables
    int numero = 42;
    float pi = 3.14159;
    char caracter = 'A';
    std::string texto = "Esto es una cadena de texto";
    
    // Uso de operadores
    int resultado = sumar(5, 7) * 2;
    
    if (resultado > 20) {
        std::cout << "El resultado es mayor que 20" << std::endl;
    } else {
        std::cout << "El resultado es menor o igual a 20" << std::endl;
    }
    
    // Creación de un objeto
    Persona persona("Juan", 30);
    persona.saludar();
    
    return 0;
}