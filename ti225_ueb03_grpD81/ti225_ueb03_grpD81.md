---
title: Abgabe Übungsblatt 03
subtitle: Technische Informatik 2 Wintersemester 2025/26
author: Baris Basar, Cengizhan Evcil, Nicolai Held
group: D81
ctfteam: 403 FORBIDDEN
tutor: Tjark Moritz
bibliography: bibueb01.yaml
---

# Aufgabe 1

### a) Modul-Analyse mit nm (Funktion main)
Vorgehensweise: Die Objektdateien wurden mit dem Tool nm inspiziert, um die Symboltabelle zu prüfen. Symbole, die mit T (Text segment) markiert sind, sind in der jeweiligen Datei definiert.

Ergebnis:

| Modul | Relevanter Ausschnitt aus nm |
| -------- | -------- |
| stat.o     | 0000000000000000 T main    |
| mage.o     | (Enthält keine Definition von main)    |

![Kommando: nm stat.o](nm_stat.png)

### b) Analyse der Linker-Fehler (undefined reference)

Analyse: Die Fehlermeldungen entstehen, weil eine Funktion, die von mage.o benötigt wird, im Linkvorgang nicht gefunden wird. Die nm-Analyse von mage.o zeigte die folgende undefinierte Referenz (U):

$$\text{U \_Z4initR15Initialisierung}$$

Ursache: Dem Linker fehlt die Implementierung (Definition) der C++-Funktion:

$$\text{void init(Initialisierung \&)}$$

Dieses Modul muss separat erstellt und hinzugefügt werden.

![Kommando: nm mage.o](nm_mage.png)

### c) Erstellung des Moduls values.cc

Ableitung des Namens: Die Symboltabelle von mage.o zeigte Klassenmethoden, die auf den Namen Caliban hindeuten (z.B. _ZN7CalibanC1Ev, _ZN7Caliban4statEv).

Implementation in values.cc:

Basierend auf den Definitionen in defs.hh (Makros HP, MANA, ATTACK, DEFENSE) und dem abgeleiteten Namen "Caliban" wurde die Initialisierungsfunktion implementiert:

```c++
#include "defs.hh" 

void init(Initialisierung& data) {
    // Initialisierung der numerischen Felder mit den Werten aus defs.hh.
    data.hp = HP;
    data.mana = MANA;
    data.attack = ATTACK;
    data.defense = DEFENSE;
    
    // Setzen des Namens basierend auf der Symboltabelle
    data.name = "Caliban"; 
}
```

### d) Kompilieren, Linken und Ausführen des Programms

Ausgeführte Kommandos:

1. Kompilieren des neuen Moduls:
```bash
g++ -c values.cc -o values.o
```

2. Linken aller Module:
```bash
g++ mage.o stat.o values.o -o mage
```

3. Ausführen des Programms:
```bash
./mage
```

### Programmausgabe und Flagge:

![Gefundene Flagge](flagge.png)

### Gefundene Flagge:

$$\text{flag{21290e22-9689-45e1-bf20-421230aaada5}}$$

# Aufgabe 2

## Literaturverzeichnis

1)
2)
3)

# Anhang