/**
    Burak Coskun
    Furkan Demirelli
    Eren Ozan Özmen
 */

#include "signals.h"

static void sigchld_handler(int signo) {
    // Bir çocuk proses sonlandığında bu handler tetiklenir
    int saved_errno = errno;
    pid_t pid;
    int status;

    // Non-blocking şekilde tüm biten çocukları yakala
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Arka plan süreci bittiğinde sonuç yazdır
        if (WIFEXITED(status)) {
            int retval = WEXITSTATUS(status);
            printf("[%d] retval: %d\n", pid, retval);
            fflush(stdout);
        }
    }
    errno = saved_errno;
}

void register_signals() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &sa, NULL) < 0) {
        perror("sigaction hatasi");
        exit(1);
    }
}
