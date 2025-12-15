---
title: Abgabe Übungsblatt 05
subtitle: Technische Informatik 2 Wintersemester 2025/26
author: Baris Basar, Cengizhan Evcil, Nicolai Held
group: D81
ctfteam: 403 FORBIDDEN
tutor: Tjark Moritz
bibliography: bibueb01.yaml
---

# Aufgabe 1

# Aufgabe 2 

![Das ist die Flagge von "FIFO"](FIFO.png)

![Das ist die Flagge von "LFU"](LFU.png)

# Dokumentation: LFU 
**Zugriffsfolge:** 2, 6, 1, 5, 6, 1, 3, 5, 5, 3, 1, 3, 6, 4, 2, 6, 3, 6, 6, 4  
**Anzahl der Page Frames:** 4 (A, B, C, D)  

### 1. Exemplarische Erklärung von fünf repräsentativen Seitenzugriffen  

| Schritt | Zugriff | Hit/Miss | Seite wird geladen in Frame | Ersetzte Seite (Victim) | Warum wurde genau diese Seite ersetzt? |
|---------|---------|----------|-----------------------------|--------------------------|----------------------------------------|
| 1       | 2       | Miss     | A                           | —                        | Erster Zugriff – Frame A ist noch frei. Seite 2 wird mit Zähler 1 eingetragen. |
| 7       | 3       | Miss     | A                           | 2                        | Beide Seiten 2 und 5 haben nur 1 Zugriff. Seite 2 ist älter (seit Schritt 1 im Speicher, Seite 5 erst seit Schritt 4) → FIFO-Tie-Breaker → Seite 2 fliegt raus. |
| 14      | 4       | Miss     | B                           | 6                        | Alle vier Seiten haben exakt 3 Zugriffe → Gleichstand. Die älteste Seite im Speicher ist 6 (seit Schritt 2) → sie wird ersetzt. |
| 15      | 2       | Miss     | B                           | 4                        | Seite 4 wurde gerade erst im vorherigen Schritt geladen und hat nur 1 Zugriff → niedrigste Frequenz → eindeutig raus. |
| 20      | 4       | Miss     | C                           | 1                        | Drei Seiten (6, 1 und 5) haben jeweils 3 Zugriffe. Unter diesen dreien ist Seite 1 die älteste (seit Schritt 3 im Speicher) → FIFO-Tie-Breaker → Seite 1 wird ersetzt. |

**Endstand nach dem letzten Zugriff**  
- Frame A: 3  
- Frame B: 6  
- Frame C: 4  
- Frame D: 5  

### 2. Anzahl der Festplatten-Lesevorgänge (Page Faults)

| Algorithmus       | Anzahl Page Faults |
|-------------------|--------------------|
| FIFO              | 8                  |
| LRU               | 7                  |
| LFU (mit FIFO-Tie)| **9**              |

LFU schneidet in dieser Folge am schlechtesten ab, weil seltene, aber früh geladene Seiten lange im Speicher „kleben“ bleiben.


## Literaturverzeichnis

1. 
2. 