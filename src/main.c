/**
    Burak Coskun
    Furkan Demirelli
    Eren Ozan Özmen
 */

#include "utils.h"
#include "parser.h"
#include "execute.h"
#include "signals.h"
#include "builtin.h"

int main() {
    char line[MAX_CMD_LEN];
    Command commands[64];  // Aynı satırda en fazla 64 alt-komut (pipe veya ;) varsayalım.

    // Arka plan işlemleri yakalamak için sinyalleri kaydet
    register_signals();

    while (1) {
        // Prompt
        printf("> ");
        fflush(stdout);

        // Kullanıcı girişi
        if (fgets(line, MAX_CMD_LEN, stdin) == NULL) {
            // Kullanıcı CTRL+D yaparsa
            printf("\n");
            break;
        }

        // Boş satır mı?
        if (strcmp(line, "\n") == 0) {
            continue;
        }

        // Komutu parse et
        int cmdCount = parse_input(line, commands);

        // Herhangi bir komut girilmediyse devam
        if (cmdCount == 0) {
            continue;
        }

        // Komut(lar)ı yürüt
        execute_commands(commands, cmdCount);

        // Döngü başına tekrar prompt yazdırmak,
        // ya da execute_commands içinde foreground bitince prompt yazdırmak vs. 
        // Bu projede en basit şekilde döngü sonunda prompt'a dönüyoruz.
    }

    // Kabuk sonlandığında arka plan işlemleri bekleyelim (opsiyonel).
    // Yönergede "arka planda çalışan varsa, quit gelince bekle" diyor.
    // Bizim shell'de "quit" komutu handle_builtin içinde exit(0) ile sonlandırıyor.
    // O yüzden while(1) den break'le çıkma senaryosunda da
    // arka plan varsa beklemeyi ekleyebilirsiniz.

    return 0;
}
