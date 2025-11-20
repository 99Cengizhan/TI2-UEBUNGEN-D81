/**
 * @file ti2sh.cc
 * @brief Hauptprogramm für eine einfache Unix-Shell (TI2-Shell)
 * 
 * Diese Datei implementiert eine minimalistische Unix-Shell, die Befehle
 * vom Benutzer entgegennimmt, diese in eigenen Prozessen ausführt und
 * sowohl Vordergrund- als auch Hintergrundprozesse unterstützt.
 * 
 * Kernfunktionalität:
 * - Lesen und Parsen von Benutzereingaben
 * - Prozesserzeugung mittels fork()
 * - Programmausführung mittels execv()
 * - Verwaltung von Vordergrund- und Hintergrundprozessen
 * - Signalbehandlung für beendete Kindprozesse
 * 
 * @author TI2-Gruppe D81
 * @date November 2025
 */

/* Standard-C-Bibliotheken */
#include <cstddef>     // Für size_t
#include <cstdio>      // Für perror()
#include <cstdlib>     // Für exit(), EXIT_FAILURE
#include <cstring>     // Für Stringoperationen
#include <string>      // Für std::string

/* C++-Bibliotheken */
#include <iostream>    // Für Ein-/Ausgabe
#include <memory>      // Für std::unique_ptr
#include <vector>      // Für std::vector, Konvertierung von argv

/* Projektspezifische Header */
#include "shell.hh"    // Shell-Klasse für Kommandoverarbeitung
#include "sighnd.hh"   // SignalHandler-Klasse für SIGCHLD-Behandlung

/* POSIX-Systemaufrufe */
#include <unistd.h>    // Für fork(), execv()
#include <sys/types.h> // Für pid_t (Prozess-ID Typ)
#include <sys/wait.h>  // Für waitpid() (hier durch SignalHandler abstrahiert)
#include <errno.h>     // Für errno und perror() Fehlerbehandlung

using namespace std;
using namespace ti2;

int main() {
  /* Registrieren des Signalhandlers */
  SignalHandler::install();

  while (true) {
    auto [path, cmd] = Shell::readCommand();

    if (!cmd)
      continue;

    /* Hier die Ausführung des Kommandos implementieren */

    // Fork einen neuen Prozess erzeugen
    pid_t pid = fork();

    if (pid == -1) {
      // Fehler beim Fork: Ausgabe und fortfahren
      perror("fork");
      continue;
    } else if (pid == 0) {
      // Kindprozess: execv ausführen

      // Konvertiere vector<string> argv zu char* const argv[] für execv
      vector<char*> args(cmd->argv.size() + 1);  // +1 für NULL-Terminator
      for (size_t i = 0; i < cmd->argv.size(); ++i) {
        args[i] = const_cast<char*>(cmd->argv[i].c_str());  // c_str() gibt const char*
      }
      args[cmd->argv.size()] = nullptr;  // Ende des Arrays

      // execv aufrufen mit dem Pfad und den Argumenten
      execv(path.c_str(), args.data());

      // Wenn execv zurückkehrt, ist ein Fehler aufgetreten
      perror("execv");
      exit(EXIT_FAILURE);  // Kindprozess beenden
    } else {
      // Elternprozess: Wenn nicht im Hintergrund, blockieren bis Kind fertig
      if (!cmd->background) {
        SignalHandler::block(pid);
      }
      // Für Hintergrundprozesse: Kein Warten, der SignalHandler handhabt SIGCHLD
    }
  }

  return 0;
}