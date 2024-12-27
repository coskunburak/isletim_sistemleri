#ifndef EXECUTE_H
#define EXECUTE_H

#include "utils.h"
#include "parser.h"

/**
 * Verilen tek bir komutu (Command yapısı) yürütür.
 * 
 * @param cmd Yürütülecek komut
 * @return Çocuk sürecin çıkış değeri
 */
int execute_single_command(Command *cmd);

/**
 * Girdi olarak gelen komut dizisini (örneğin pipe, ; vb. ile ayrılmış) sırayla veya
 * pipe ile bağlı olarak çalıştırır.
 *
 * @param commands   Komut dizisi
 * @param numCommand Komut sayısı
 */
void execute_commands(Command *commands, int numCommand);

#endif
