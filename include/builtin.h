#ifndef BUILTIN_H
#define BUILTIN_H

#include "utils.h"
#include "parser.h"

/**
 * Bu fonksiyon, girilen komutun yerleşik (builtin) olup olmadığını kontrol eder
 * ve uygunsa ilgili işlemi yapar.
 * Örneğin "quit" komutu buradan handle edilir.
 *
 * @param cmd Tek bir komut (Command yapısı).
 * @return 1 (builtin işlendi), 0 (builtin değil, harici komut).
 */
int handle_builtin(Command *cmd);

#endif
