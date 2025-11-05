#include <iostream>
#include <string>
#include <cctype>
#include <chrono>

// convierte una cadena in place segun el modo
void case_converter_serial(std::string &text, bool to_upper) {
    for (char &c : text) {
        if (to_upper && c >= 'a' && c <= 'z') {
            c = c - ('a' - 'A');
        } else if (!to_upper && c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <texto> <modo>\n";
        std::cerr << "modo = upper | lower\n";
        return 1;
    }

    std::string texto = argv[1];
    std::string modo = argv[2];

    bool to_upper = (modo == "upper");

    auto start = std::chrono::high_resolution_clock::now();
    case_converter_serial(texto, to_upper);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;

    std::cout << "Resultado: " << texto << "\n";
    std::cout << "Tiempo de ejecución: " << dur.count() << " ms\n";

    return 0;
}
