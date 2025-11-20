---
title: Abgabe Übungsblatt 04
subtitle: Technische Informatik 2 Wintersemester 2025/26
author: Baris Basar, Cengizhan Evcil, Nicolai Held
group: D81
ctfteam: 403 FORBIDDEN
tutor: Tjark Moritz
bibliography: bibueb01.yaml
---

# Aufgabe 1

# Aufgabe 2

## 2a. Einleitung

Ziel dieser Aufgabe ist es, eine einfache Shell zu implementieren, die:

- Kommandos mit beliebig vielen Argumenten einlesen kann,
- diese Kommandos als neue Prozesse startet,
- Kommandos entweder im Vordergrund oder im Hintergrund ausführt,
- typische Fehlerfälle berücksichtigt,
- Signale korrekt verarbeitet (SIGCHLD).

Ein Teil des Codes wurde vorgegeben (Einlesen der Befehle, Signalhandler, Shell-Struktur). Die Aufgabe bestand darin, die tatsächliche Prozessausführung mittels `fork()` und `execv()` einzubauen.

## 2b. Aufbau & Funktionsweise der Shell

Die Shell läuft in einer Endlosschleife:

```bash
auto [path, cmd] = Shell::readCommand();
```

`readCommand()` liefert:

- **path** → vollständiger Pfad zum auszuführenden Programm

- **cmd** → Objekt mit:

- **argv** → Argumentliste (vector<string>)

- **background** → true, wenn Prozess im Hintergrund laufen soll (&)

Wird kein gültiges Kommando eingegeben, springt die Shell zum nächsten Durchlauf.

## 2c. Prozessverwaltung

Dies geschieht durch:

```bash
pid_t pid = fork();
```

Es gibt drei mögliche Fälle:

| Rückgabewert | Bedeutung |
| ----- | -------- |
| -1    | Fehler beim Erzeugen des Prozesses   |
| 0     | Wir befinden uns im Kindprozess   |
| >0    | Wir befinden uns im Elternprozess, Wert = PID des Kindes |

## 2d. Ausführen des Kommandos im Kindprozess

Der Kindprozess muss ein anderes Programm ersetzen. Dazu:

1. `vector<string>` wird in `char*[]` übersetzt → nötig für `execv()`

2. `execv(path, args)` wird aufgerufen

Bei Erfolg kehrt execv() niemals zurück.

## 2e. Verhalten des Elternprozesses

Vordergrundprozess → Shell blockiert, bis dieser Prozess beendet ist

Hintergrundprozess → Shell blockiert NICHT, Nutzer kann weiter tippen

Die Hintergrundprozesse werden vom vorhandenen `SignalHandler` über **SIGCHLD** eingefangen und aufgeräumt.

## 2f. Fehlerbehandlung

Die Shell behandelt:

Fehler beim `Fork`:
```cc
if (pid == -1) {
    perror("fork");
    continue;
}
```

Fehler beim `Exec`:

Falls `execv()` fehlschlägt:

- Falscher Programmpfad

- Keine Rechte

- Binärdatei beschädigt

- ...

Dann:

```cc
perror("execv");
exit(EXIT_FAILURE);
```

## 2g. Testfälle & Testergebnisse

1. `ls -l`

```bash
command: ls
arguments: -l
background: nein
 ```

2. `ls -l &`
```bash
command: ls
arguments: -l
background: ja
```

3. `sleep 10`
```bash
command: sleep
arguments: 10
background: nein
```

4. `sleep 10 &`
```bash
command: sleep
arguments: 10
background: ja
```

5. `echo foo`
```bash
command: echo
arguments: foo
background: nein
```

6. `echo foo &`
```bash
command: echo
arguments: foo
background: ja
```

7. `bla/fasel`
```bash
command: bla/fasel
arguments:
background: nein
bla/fasel: command not found
```

8. `sleep 100`
```bash
command: sleep
arguments: 100
background: nein
```

9. `mkdir test`

9.1. Erster Aufruf:
```bash
command: mkdir
arguments: test
background: nein
```

9.2. Zweiter Aufruf:
```bash
command: mkdir
arguments: test
background: nein
mkdir: test: File exists
```

10. `cd abc`
```bash
command: cd
arguments: abc
background: nein
No such file or directory
```

11. `date`
```bash
command: date
arguments:
background: nein
Thu Nov 20 21:37:47 CET 2025
````

12. `date &`
```bash
command: date
arguments:
background: ja
Thu Nov 20 21:37:50 CET 2025
```

13. `cat a.txt`
```bash
command: cat
arguments: a.txt
background: nein
cat: a.txt: No such file or directory
```

14. `cat a.txt &`
```bash
command: cat
arguments: a.txt
background: ja
cat: a.txt: No such file or directory
```

## Literaturverzeichnis

1. https://man7.org/linux/man-pages/
2. https://cplusplusreference.com

# Anhang