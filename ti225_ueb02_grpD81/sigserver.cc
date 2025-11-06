#include <iostream>   // für std::cout
#include <cerrno>     // für errno
#include <cstring>    // für strerror
#include <signal.h>   // für Signale, sigaction
#include <unistd.h>   // für getpid() und pause()

/**
 * Signalhandler für den Empfang von Signalen mit zusätzlicher Senderinformation.
 *
 * @param signum Die Nummer des empfangenen Signals.
 * @param info   Zeiger auf siginfo_t, enthält Informationen über den Sender (PID, UID, etc.).
 * @param ctx    Zeiger auf ucontext_t (nicht genutzt in diesem Beispiel, kann nullptr sein).
 *
 * Diese Funktion wird aufgerufen, wenn ein Signal wie SIGCONT empfangen wird.
 * Sie gibt die Signalnummer sowie PID und UID des sendenden Prozesses aus.
 */
void signalHandler(int signum, siginfo_t* info, void* ctx) {
    std::cout << "Signal erhalten: " << signum << "\n";

    if (info != nullptr) {
        // PID und UID des Prozesses, der das Signal gesendet hat
        std::cout << "Sender-PID: " << info->si_pid << "\n";
        std::cout << "Sender-UID: " << info->si_uid << "\n";
    }

    std::cout << "Programm läuft weiter...\n\n";
}

int main() {
    // sigaction-Struktur initialisieren
    struct sigaction act{};
    act.sa_flags = SA_SIGINFO;         // wichtig: aktiviert siginfo_t für den Handler
    act.sa_sigaction = signalHandler;  // Funktionspointer auf den Signalhandler
    sigemptyset(&act.sa_mask);         // keine Signale während des Handlers blockieren

    // Handler für SIGCONT setzen
    if (sigaction(SIGCONT, &act, nullptr) == -1) {
        // Fehler beim Setzen des Handlers
        perror("sigaction");
        return 1;
    }

    std::cout << "sigserver gestartet. PID = " << getpid() << "\n";
    std::cout << "Warten auf SIGCONT...\n";

    // Endlosschleife: Programm wartet passiv auf Signale
    // pause() blockiert, bis ein Signal empfangen wird
    while (true) {
        pause();
    }

    return 0;
}