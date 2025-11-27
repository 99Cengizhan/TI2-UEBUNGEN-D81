---
title: Abgabe Übungsblatt 05
subtitle: Technische Informatik 2 Wintersemester 2025/26
author: Baris Basar, Cengizhan Evcil, Nicolai Held
group: D81
ctfteam: 403 FORBIDDEN
tutor: Tjark Moritz
bibliography: bibueb01.yaml
---

# Aufgabe 1 & CTF-Challenge „gdb“ – Lösungsdokumentation

![Das ist die Flagge von "gdb"](gdbFlag.png)

### Überblick

Auf dem bereitgestellten System befand sich eine ausführbare Datei
`programm`, die eine Passwortabfrage implementiert. Die Aufgabe bestand
darin, mithilfe des Debuggers **gdb** die Passwortüberprüfung zu
umgehen, ohne das echte Passwort zu kennen.

Ziel war es, den Programmablauf an einer geeigneten Stelle so zu
manipulieren, dass die Passwortprüfung immer als erfolgreich erkannt
wird.

------------------------------------------------------------------------

## 1. Analyse des Programms

Nach dem Starten von gdb wurde die `main`-Funktion disassembliert:

``` gdb
(gdb) set disassembly-flavor intel
(gdb) disas main
```

Im Disassembly findet sich folgender kritischer Abschnitt:

``` asm
0x00000000004055c8 <+283>: call 0x405299 <read_password(...)>
0x00000000004055d7 <+298>: call 0x405063 <checkPassword(...)>
0x00000000004055dc <+303>: test al,al
0x00000000004055de <+305>: je 0x405676 <main+457>
```

Wichtig:

-   Die Funktion `checkPassword()` gibt ihr Ergebnis im Register **AL**
    zurück
    -   `1` → Passwort korrekt\
    -   `0` → Passwort falsch
-   Direkt danach erfolgt die Überprüfung über `test al, al`
-   Bei falschem Passwort wird per `je` in den Fehlerzweig gesprungen.

### Ziel

Das Register **AL so manipulieren**, dass es immer den Wert `1`
enthält.\
Dadurch wird das Passwort als korrekt akzeptiert.

------------------------------------------------------------------------

## 2. Setzen eines Breakpoints an der Entscheidungsstelle

Der passende Punkt ist die Instruktion:

    0x4055dc

Hier wird der Rückgabewert geprüft, bevor der Sprung ausgeführt wird.

``` gdb
(gdb) break *0x4055dc
```

### Begründung

-   Breakpoint liegt **nach** dem Funktionsaufruf von `checkPassword()`
-   Breakpoint liegt **vor** der Verzweigung (`je`)
-   An dieser Stelle kann man den Rückgabewert (`al`) sicher
    manipulieren
-   Die gesamte Passwortlogik bleibt unangetastet -- nur die
    Entscheidung wird beeinflusst

------------------------------------------------------------------------

## 3. Automatische Manipulation durch Breakpoint-Commands

Nach Setzen des Breakpoints wurden gdb-interne Befehle definiert, die
beim Erreichen des Breakpoints automatisch ausgeführt werden:

``` gdb
(gdb) commands
> silent
> set $al = 1
> continue
>end
```

### Erklärung der Commands

  -----------------------------------------------------------------------
  Befehl                                     Bedeutung
  ------------------------------------------ ----------------------------
  `silent`                                   Unterdrückt Ausgaben beim
                                             Breakpoint-Hit

  `set $al = 1`                              Setzt Rückgabewert von
                                             `checkPassword()` auf
                                             „korrektes Passwort"

  `continue`                                 Programm läuft ohne
                                             Unterbrechung weiter
  -----------------------------------------------------------------------

Damit wird jeder Passwortversuch automatisch als korrekt erkannt.

------------------------------------------------------------------------

## 4. Ausführen des Programms

Nun wird das Programm einfach gestartet:

``` gdb
(gdb) run
```

Nach Eingabe eines beliebigen Passworts setzt gdb automatisch `al = 1`,
und das Programm zeigt die Flag an:

    flag{1f679cfd-5e4e-4022-b0f3-cb2b0a611f0d}

Das Passwort selbst wird somit vollständig umgangen.

------------------------------------------------------------------------

## 5. Ergebnis

Durch das geschickte Setzen eines Breakpoints und Manipulation des
Registers `al` konnte die Passwortabfrage erfolgreich umgangen werden.\
Dies ist eine saubere, reproduzierbare Methode, die exakt an der
Entscheidungsstelle des Programms eingreift und den Kontrollfluss in
gewünschter Weise beeinflusst.



## Literaturverzeichnis

1. https://sourceware.org/gdb/current/onlinedocs/gdb.html/