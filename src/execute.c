#include "execute.h"
#include "builtin.h"
#include "signals.h"

/**
 * Tek bir komutu (Command *cmd) yürütür.
 * Giriş/Çıkış yönlendirmesi var mı kontrol eder.
 * Arka planda mı değil mi kontrol eder.
 * 
 * Bu fonksiyon foreground (ön plan) durumda komutun bitmesini bekler.
 * Arka plan ise beklemez.
 */
int execute_single_command(Command *cmd) {
    // Builtin kontrolü
    if (handle_builtin(cmd)) {
        // Yerleşik komut ise 0 döndürelim
        return 0;
    }

    // Fork
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork hatasi");
        return -1;
    }
    else if (pid == 0) {
        // Çocuk proses

        // Girdi yönlendirme
        if (cmd->inputFile) {
            int fd_in = open(cmd->inputFile, O_RDONLY);
            if (fd_in < 0) {
                fprintf(stderr, "%s giriş dosyası bulunamadı.\n", cmd->inputFile);
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Çıkış yönlendirme
        if (cmd->outputFile) {
            int fd_out = open(cmd->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Çıkış dosyası açılamadı");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        // Arka plan komutları için sinyal vs. ayarları
        // Örneğin bir arka plan işleminde ctrl+c yakalamak istenmez vs.
        // Bu projede basitçe default bırakabiliriz.

        // Komut çalıştır
        if (execvp(cmd->argv[0], cmd->argv) < 0) {
            perror("Komut çalıştırılamadı");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else {
        // Ebeveyn proses
        int status = 0;

        if (cmd->background == 1) {
            // Arka planda çalıştırılacak
            // Beklemeden prompt'a geri döneriz
            printf("\n"); // Prompt öncesi satır başı
            fflush(stdout);
            // Arka plan işlemi için pid kaydını bir veri yapısında tutabiliriz
            // Bu veri yapısı main tarafında global bir listede saklanıp
            // Sinyal veya waitpid ile beklenebilir.
            return 0;
        } else {
            // Ön planda, bekleyerek
            waitpid(pid, &status, 0);
            return WEXITSTATUS(status);
        }
    }
    return 0;
}

/**
 * Pipe veya ';' ile ayrılmış birden fazla komutu sırayla (veya pipe ile bağlı) çalıştır.
 * Basitlik adına önce sadece ';' sıralı komutlar mantığı verelim.
 * Pipe kullanımında bir dizi pipe fd'leri oluşturmak, her komutu fork etmeden önce
 * uygun dup2 yapısıyla bağlamak gerekiyor.
 */
void execute_commands(Command *commands, int numCommand) {
    // Bu örnekte pipe gerçekte parse tarafında tam ayrıştırılmadığı için
    // her komutu teker teker execute_single_command ile çalıştırıyoruz.

    // Noktalı virgül (;): soldan sağa sırayla çalışır, aralarında veri transferi yok.
    // Arka plan (&) ise execute_single_command içinde handle edildi.

    // Daha gelişmiş senaryoda, eğer commands[i] nin pipe'a bağlı olduğu bilinirse
    // pipe() çağrısı ile commands[i] stdout'unu pipe'a, commands[i+1] in stdin'ini
    // bu pipe'a bağlamamız gerekir. 
    // (Bu proje metninde pipe 20 puan değerinde. Aşağıda basit pipe örneği verildi.)

    // Basit senaryo: ';' ile ardışık
    for (int i = 0; i < numCommand; i++) {
        // Sadece execute_single_command çağırıyoruz
        execute_single_command(&commands[i]);
    }
}

/*
 * Pipe örneği (isteğe bağlı, parse çok basitleştirildiği için tam entegre edilmiyor):
 *
 * Örneğin "echo 12 | increment" gibi 2 komut:
 * 1. pipe() => fd[0] (read end), fd[1] (write end)
 * 2. fork() => child: stdout -> fd[1], close(fd[0]), exec(echo 12)
 * 3. fork() => child: stdin  -> fd[0], close(fd[1]), exec(increment)
 * 4. parent: close(fd[0]), close(fd[1]), wait() 2 child
 *
 * Yukarıdaki mantık main veya bu fonksiyonun içinde handle edilebilir.
 * Proje detayında bu yapıyı siz tamamlayabilirsiniz.
 */
