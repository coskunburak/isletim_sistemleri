#ifndef PARSER_H
#define PARSER_H

#include "utils.h"

// Her komut parçasını tutmak için bir yapı
typedef struct Command {
    char *argv[MAX_ARGS];    // Komut ve parametreleri
    char *inputFile;         // '<' ile belirtilen girdi dosyası
    char *outputFile;        // '>' ile belirtilen çıktı dosyası
    int  background;         // '&' ile arkaplan bilgisi
} Command;

/**
 * parse_input:
 * Kullanıcıdan alınan satırı (örneğin "ls -l > out.txt") parçalara ayırarak
 * bir dizi Command yapısına dönüştürür.
 *
 * Not: Boru (pipe) veya noktalı virgül (;) gibi operatörler de burada işlenebilir.
 *
 * @param line     Kullanıcının girdiği tam satır.
 * @param commands Dışarıya doldurulan Command dizisi (pointer).
 * @return         Komut sayısını (pipe veya ; ile bölünen) döndürür.
 */
int parse_input(char *line, Command *commands);

#endif
