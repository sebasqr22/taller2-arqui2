#include <immintrin.h>   // intrinsics AVX2
#include <iostream>
#include <string>
#include <chrono>
#include <cstring>

// pasa de minusculas a mayusculas usando AVX2
void case_converter_SIMD(char* text, size_t len, bool to_upper) {
    const __m256i diff = _mm256_set1_epi8(0x20); // diferencia 'a'-'A' = 0x20
    const __m256i lower_a = _mm256_set1_epi8('a');
    const __m256i lower_z = _mm256_set1_epi8('z');
    const __m256i upper_a = _mm256_set1_epi8('A');
    const __m256i upper_z = _mm256_set1_epi8('Z');

    size_t i = 0;
    for (; i + 32 <= len; i += 32) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(text + i));

        if (to_upper) {
            __m256i mask_lower = _mm256_and_si256(
                _mm256_cmpgt_epi8(chunk, _mm256_sub_epi8(lower_z, _mm256_set1_epi8(1))),
                _mm256_cmpgt_epi8(_mm256_add_epi8(chunk, _mm256_set1_epi8(1)), lower_a)
            );
            chunk = _mm256_sub_epi8(chunk, _mm256_and_si256(mask_lower, diff));
        } else {
            __m256i mask_upper = _mm256_and_si256(
                _mm256_cmpgt_epi8(chunk, _mm256_sub_epi8(upper_z, _mm256_set1_epi8(1))),
                _mm256_cmpgt_epi8(_mm256_add_epi8(chunk, _mm256_set1_epi8(1)), upper_a)
            );
            chunk = _mm256_add_epi8(chunk, _mm256_and_si256(mask_upper, diff));
        }

        _mm256_storeu_si256(reinterpret_cast<__m256i*>(text + i), chunk);
    }
    for (; i < len; ++i) {
        if (to_upper && text[i] >= 'a' && text[i] <= 'z')
            text[i] -= 0x20;
        else if (!to_upper && text[i] >= 'A' && text[i] <= 'Z')
            text[i] += 0x20;
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
    case_converter_SIMD(texto.data(), texto.size(), to_upper);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;

    std::cout << "Resultado: " << texto << "\n";
    std::cout << "Tiempo de ejecución SIMD: " << dur.count() << " ms\n";

    return 0;
}
