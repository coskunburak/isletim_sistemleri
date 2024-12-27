/**
    Burak Coskun
    Furkan Demirelli
    Eren Ozan Özmen
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

// Gerekli kütüphaneler ve makrolar

#define MAX_CMD_LEN 1024   // Tek satırda girilebilecek maksimum karakter
#define MAX_ARGS    64     // Parçalanabilecek maksimum argüman sayısı
#define DELIM       " \t\r\n\a" // Argüman ayracı boşluk/tap/yeni satır

#endif
