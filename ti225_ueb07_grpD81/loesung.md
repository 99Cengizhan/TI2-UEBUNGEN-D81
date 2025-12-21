# Lösung: Gerätecontroller mit Double-Buffering

## Aufgabenstellung

Ein Gerätecontroller mit folgenden Eigenschaften:
- **Maximale Datenrate:** 174.400 Bit/s
- **Pufferarchitektur:** Double-Buffering (2 Puffer)
- **Nachfüllzeit:** 130 μs (Zeit zum Aufwecken des Prozesses und Nachfüllen)
- **Low-Watermark (LWM):** Löst Interrupt aus, wenn erreicht

## Lösungsansatz

### Grundprinzip

1. Der Controller sendet Daten aus einem Puffer an das Gerät
2. Bei Erreichen der Low-Watermark wird ein Interrupt ausgelöst
3. Der Prozess wird aufgeweckt und füllt den anderen Puffer nach (130 μs)
4. Währenddessen sendet der Controller weiter aus dem aktuellen Puffer
5. Nach dem Leeren des Puffers wird auf den anderen Puffer umgeschaltet

### Kritischer Punkt

**Problem:** Wenn die Low-Watermark zu niedrig ist, wird der Puffer leer, bevor das Nachfüllen abgeschlossen ist. Dies führt zu einer Wartezeit ohne Datenübertragung.

**Berechnung der benötigten Bytes während Nachfüllen:**
```
Bytes_während_Nachfüllen = (174.400 Bit/s × 130 μs) / 8 = 2,834 Byte
```

### Formel für effektive Datenrate

**Fall 1: LWM < benötigte Bytes (Unterbrechung)**
```
Sendezeit = (Puffergröße × 8 Bit) / 174.400 Bit/s
Verfügbare_Sendezeit_bei_LWM = (LWM × 8 Bit) / 174.400 Bit/s
Wartezeit = 130 μs - Verfügbare_Sendezeit_bei_LWM
Zykluszeit = Sendezeit + Wartezeit
Effektive_Datenrate = (Puffergröße × 8 Bit) / Zykluszeit
```

**Fall 2: LWM ≥ benötigte Bytes (keine Unterbrechung)**
```
Zykluszeit = Sendezeit
Effektive_Datenrate = 174.400 Bit/s (volle Rate)
```

## Berechnungen

### Fall 1: Puffergröße 3 Byte, LWM 0 Byte

```
Bits: 3 × 8 = 24 Bit
Sendezeit: 24 Bit / 174.400 Bit/s = 137,61 μs
Bei LWM=0: Puffer ist leer, volle 130 μs Wartezeit
Zykluszeit: 137,61 μs + 130 μs = 267,61 μs
Effektive Rate: 24 Bit / 267,61 μs = 89.681 Bit/s
```

**Antwort: 89681 Bit/s**

---

### Fall 2: Puffergröße 70 Byte, LWM 0 Byte

```
Bits: 70 × 8 = 560 Bit
Sendezeit: 560 Bit / 174.400 Bit/s = 3.211,01 μs
Bei LWM=0: Puffer ist leer, volle 130 μs Wartezeit
Zykluszeit: 3.211,01 μs + 130 μs = 3.341,01 μs
Effektive Rate: 560 Bit / 3.341,01 μs = 167.614 Bit/s
```

**Antwort: 167614 Bit/s**

---

### Fall 3: Puffergröße 350 Byte, LWM 1 Byte

```
Bits: 350 × 8 = 2.800 Bit
Sendezeit: 2.800 Bit / 174.400 Bit/s = 16.055,05 μs

Während Nachfüllen (130 μs) werden 2,834 Byte gesendet
Verfügbare Bytes bei LWM: 1 Byte < 2,834 Byte → Unterbrechung!

Verfügbare Sendezeit: (1 × 8 Bit) / 174.400 Bit/s = 45,87 μs
Wartezeit: 130 μs - 45,87 μs = 84,13 μs
Zykluszeit: 16.055,05 μs + 84,13 μs = 16.139,17 μs
Effektive Rate: 2.800 Bit / 16.139,17 μs = 173.491 Bit/s
```

**Antwort: 173491 Bit/s**

---

### Fall 4: Puffergröße 670 Byte, LWM 5 Byte

```
Bits: 670 × 8 = 5.360 Bit
Sendezeit: 5.360 Bit / 174.400 Bit/s = 30.733,94 μs

Während Nachfüllen (130 μs) werden 2,834 Byte gesendet
Verfügbare Bytes bei LWM: 5 Byte > 2,834 Byte → Keine Unterbrechung!

Wartezeit: 0 μs
Zykluszeit: 30.733,94 μs
Effektive Rate: 5.360 Bit / 30.733,94 μs = 174.400 Bit/s
```

**Antwort: 174400 Bit/s**

---

### Fall 5: Minimale Low-Watermark für volle Datenrate

Um die volle Datenrate zu erreichen, darf keine Unterbrechung entstehen.

```
Benötigte Bytes während Nachfüllen: 2,834 Byte
Minimale LWM (aufgerundet): ⌈2,834⌉ = 3 Byte
```

**Antwort: 3 Byte**

---

## Zusammenfassung der Antworten

| Fall | Puffergröße | LWM | Effektive Datenrate |
|------|-------------|-----|---------------------|
| 1    | 3 Byte      | 0 B | **89.681 Bit/s**    |
| 2    | 70 Byte     | 0 B | **167.614 Bit/s**   |
| 3    | 350 Byte    | 1 B | **173.491 Bit/s**   |
| 4    | 670 Byte    | 5 B | **174.400 Bit/s**   |
| 5    | Minimale LWM für volle Rate | **3 Byte** |

## Erkenntnisse

1. **Kleine Puffer mit LWM=0** führen zu erheblichen Effizienzverlusten
2. **Größere Puffer** verbessern die Effizienz, da der relative Anteil der Wartezeit sinkt
3. **Optimale LWM** ermöglicht unterbrechungsfreies Senden bei 100% Effizienz
4. Die kritische Grenze liegt bei **3 Byte LWM**, da in 130 μs genau 2,834 Byte gesendet werden
