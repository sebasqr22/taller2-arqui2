#include <iostream>
#include <vector>
#include <random>
#include <cstring>
#include <iomanip>

// genera una cadena aleatoria
std::string generar_cadena(size_t longitud, double porcentaje_letras, size_t alineacion) {
    std::string texto(longitud, ' ');

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::uniform_int_distribution<> letras('a', 'z');
    std::uniform_int_distribution<> simbolos(33, 126);

    for (size_t i = 0; i < longitud; ++i) {
        if (dist(gen) < porcentaje_letras / 100.0)
            texto[i] = static_cast<char>(letras(gen));
        else
            texto[i] = static_cast<char>(simbolos(gen));
    }

    // relleno de espacios
    size_t resto = texto.size() % alineacion;
    if (resto != 0) {
        texto.append(alineacion - resto, ' ');
    }

    return texto;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <longitud> <porcentaje_letras> <alineacion>\n";
        return 1;
    }

    size_t longitud = std::stoul(argv[1]);
    double porcentaje = std::stod(argv[2]);
    size_t alineacion = std::stoul(argv[3]);

    std::string cadena = generar_cadena(longitud, porcentaje, alineacion);

    std::cout << "Cadena generada (longitud " << cadena.size() << "):\n";
    std::cout << cadena << "\n";

    return 0;
}



