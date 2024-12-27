/**
    Burak Coskun
    Furkan Demirelli
    Eren Ozan Özmen
 */

#include "parser.h"

/**
 * Satırdaki pipe veya noktalı virgül karakterlerini bölüp,
 * her bölümü ayrı Command yapısı olarak algılarız.
 */
static int split_by_delimiters(char *line, char **subcommands, const char *delimiters) {
    int count = 0;
    char *token = strtok(line, delimiters);
    while (token != NULL) {
        subcommands[count++] = token;
        token = strtok(NULL, delimiters);
    }
    subcommands[count] = NULL;
    return count;
}

int parse_input(char *line, Command *commands) {
    // Örnek olarak öncelikle ';' ayrımı yapalım. Ardından pipe ayrımı yapabiliriz.
    // Bu örnekte sadece ; ve | (ikisini de) parse ettiğimizi varsayalım.
    // Basitlik için, ilk adımda ; ile ayırıyor, ikinci adımda | ile ayırıyor da yapabilirsiniz.
    // Pek çok farklı yaklaşım var, burada sadece örnek bir mantık veriyoruz.

    // Komutları 2 temel delim ile ayırabiliriz: ";" ve "|"
    // Ama en basit senaryoda, userInput "ls -l ; sleep 2 ; echo 13" gibi bir girdi olabilir.
    // Örneğin, bu parsing yapısında her ";" ve "|" ayırma sonunda
    // commands array'inde birer komut obje haline getireceğiz.

    // 1. subcommands (en fazla pipe veya noktalı virgül sayısı kadar)
    char *subcommands[64];
    memset(subcommands, 0, sizeof(subcommands));

    // Örneğin tüm noktalı virgülleri pipe'lar ile aynı kefeye koyup
    // tek delim klavuzu ";|" ile ayırıyoruz:
    int numSub = split_by_delimiters(line, subcommands, ";|");

    int cmdCount = 0;
    for (int i = 0; i < numSub; i++) {
        // Her subcommand için Command yapısını sıfırla
        memset(&commands[cmdCount], 0, sizeof(Command));

        // Şimdi subcommand içindeki kelimeleri argümanlara ayıralım
        // ve < > & gibi şeyleri yakalayalım.
        char *arg = strtok(subcommands[i], DELIM);
        int argIndex = 0;

        while (arg != NULL) {
            if (strcmp(arg, "<") == 0) {
                // Bir sonraki token inputFile olur
                arg = strtok(NULL, DELIM);
                commands[cmdCount].inputFile = arg;
            } else if (strcmp(arg, ">") == 0) {
                // Bir sonraki token outputFile olur
                arg = strtok(NULL, DELIM);
                commands[cmdCount].outputFile = arg;
            } else if (strcmp(arg, "&") == 0) {
                // Arka planda çalıştırma
                commands[cmdCount].background = 1;
            } else {
                // Normal argüman
                commands[cmdCount].argv[argIndex++] = arg;
            }
            arg = strtok(NULL, DELIM);
        }
        // Komutun sonuna NULL koyarak exec için hazırlıyoruz.
        commands[cmdCount].argv[argIndex] = NULL;
        cmdCount++;
    }
    return cmdCount;
}
