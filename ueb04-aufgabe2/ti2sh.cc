#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <iostream>
#include <memory>
#include <vector>  // Für die Konvertierung von argv

#include "shell.hh"
#include "sighnd.hh"

#include <unistd.h>  // Für fork(), execv()
#include <sys/types.h>  // Für pid_t
#include <sys/wait.h>  // Für waitpid() falls benötigt, aber hier über SignalHandler
#include <errno.h>  // Für errno und perror

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