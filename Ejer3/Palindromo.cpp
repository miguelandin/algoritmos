#include <iostream>
#include <string>

bool esPalindromo(std::string palabra);

int main()
{
    std::string palabra;
    std::cin >> palabra;
    std::cout << esPalindromo(palabra);

    return 0;
}

bool esPalindromo(std::string palabra) //t(1) = 1, t(n) = t(n-2) + 1 -> 1/4 (4 + (-1)^n - (-1)^(2 n) + 2 n) = O(n)
{ // S(1) = 1, S(0) = 1, S(n) = S(n - 2) + n -> S(n) = 1/8 (2 n (n + 3) + 3 (-1)^n - (-1)^(2 n) (2 n + 3) + 8) = O(n²)
    int n = palabra.length(); // cogemos la longitud de la palabra

    if (n <= 1) // caso base la palabra no tiene caracter que comparar
        return true; // entonces se llegó a que es verdader
    else {
        if (palabra[0] != palabra[n - 1]) // si lo lados opuestos no son iguales
            return false;
        else { // se crea una palabra con un caracter menos en los lados
            std::string subPalabra = palabra.substr(1, n - 2);
            return esPalindromo(subPalabra); // se llama de nuevo
        }
    }
}
