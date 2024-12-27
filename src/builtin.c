/**
    Burak Coskun
    Furkan Demirelli
    Eren Ozan Özmen
 */

#include "builtin.h"

int handle_builtin(Command *cmd) {
    if (cmd->argv[0] == NULL) {
        return 1; // Boş komut
    }

    if (strcmp(cmd->argv[0], "quit") == 0) {
        // quit komutu
        // Arka planda çalışan süreçler varsa onların bitmesini bekleyeceğiz.
        // Bu bekleme mantığını main veya başka fonksiyonda da yapabiliriz.
        // Burada basitçe bir bayrak set edilebilir.
        printf("Shell kapanıyor...\n");
        exit(0);
        // return 1;
    }

    // Diğer built-in komutlar (örneğin cd, vs.) eklenebilir

    return 0; // builtin olmadığı anlamına gelir
}
