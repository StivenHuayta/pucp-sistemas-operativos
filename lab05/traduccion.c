#define _POSIX_C_SOURCE 200809L
/* traduccion.c — Guía previa del laboratorio 5, ejemplo 1
 * Compilar: gcc -std=c17 -Wall -Wextra -g traduccion.c -o traduccion
 * Uso: ./traduccion <dirección lógica en decimal> ...
 */
#include <stdio.h>
#include <stdlib.h>
#define BITS_DESPLAZ 12                       /* páginas de 4 KiB = 2^12 bytes */
#define TAM_PAGINA   (1u << BITS_DESPLAZ)
#define N_PAGINAS    8
#define AUSENTE      (-1)
/* Tabla de páginas del proceso: marco que ocupa cada página, o AUSENTE. */
static const int tabla[N_PAGINAS] = { 5, 2, AUSENTE, 7, 9, AUSENTE, 0, 3 };
int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        unsigned dir = (unsigned)strtoul(argv[i], NULL, 10);
        unsigned pagina = dir >> BITS_DESPLAZ;          /* dir / 4096 */
        unsigned desplaz = dir & (TAM_PAGINA - 1u);     /* dir % 4096 */
        printf("dirección lógica %u = 0x%X: página %u, desplazamiento %u\n",
               dir, dir, pagina, desplaz);
        if (pagina >= N_PAGINAS) {
            printf("  la página %u no existe en este proceso\n", pagina);
        } else if (tabla[pagina] == AUSENTE) {
            printf("  bit presente = 0: fallo de página\n");
        } else {
            unsigned fisica = ((unsigned)tabla[pagina] << BITS_DESPLAZ) | desplaz;
            printf("  marco %d: dirección física %u = 0x%X\n",
                   tabla[pagina], fisica, fisica);
        }
    }
    return 0;
}