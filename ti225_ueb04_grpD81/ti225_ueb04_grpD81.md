---
title: Abgabe Übungsblatt 01
subtitle: Technische Informatik 2 Wintersemester 2025/26
author: Baris Basar, Cengizhan Evcil, Nicolai Held
group: D81
ctfteam: 403 FORBIDDEN
tutor: Tjark Moritz
bibliography: bibueb01.yaml
---

# Aufgabe 1

*a) Wie wird in ein Markdown-Dokument eine Grafik eingefügt?*

>Das markdow-template, welches von dieser Veranstalung zur Verfügung gestellt wurde, bietet in der Datei ti225_ueb01_grpH04.md ein Lösung unter 'Verschiedenes' eine genaue Anleitung: 
"Grafiken bindet man so ein (auf Groß- und Kleinschreibung achten!):
![Name der Grafik](ti2-2025.png){width=20%}." (ti225_ueb01_grpH04.md)
ZU beachten ist außederdem, dass die png- oder jpeg- Datei im gleichen Ordner wie die entsprechene .md-Datei vorhanden ist. 

*Diese Quelle halten wir für geeignet, da Sie direkt vom Aufgabensteller stammt und es daher fragwürdig wäre, wenn diese Antwort dann als falsch deklariert wird. Nicht zuletzt, da es sich hier um eine Quelle einer anerkannten akadamischen Institution handelt.*

*b) Welche Arten von Eingabe- und Ausgabeumlenkung gibt es in Unix?*

>Laut dem Chatbot Gemini von Google "gibt es 3 Hauptarten von Standard-Datenströmen für Ein- und Ausgabe: die Standardeingabe (stdin), die Standardausgabe (stdout) und die Standardfehlerausgabe (stderr). Die Umleitung ermöglicht es, diese standardmäßigen Verbindungen (z. B. Tastatur für stdin, Bildschirm für stdout/stderr) zu ändern und stattdessen Dateien oder andere Prozesse als Quelle oder Ziel zu verwenden." (Google Gemini, 30.10.2025)

*Hier denken wir, dass diese Quelle in Ordnung ist, da wir bei dieser technischen Frage dem ChatBot vertrauen in seiner Kompetenz diese Informationen vernünftig zu sammeln, wohlwissend, dass dieser genauso gut falsche Informationen an uns weitergeben kann. Aber, da es sich bei der Aufgabe hier um eine Übung für das Zitieren in 'markdown' handelt, haben wir gehofft, dass diese Quelle diesmal zu Übungszwecken in Ordnung ist.*

*c) Welches Betriebssystem wird gegenwärtig weltweit am häufigsten eingesetzt?*

>Laut dem ChatBot ChatGPT ist dies Android oder, wenn man sich nur auf Desktop- und Laptop-Computer beschränkt, dann ist es Windows. (ChatGPT, 30.10.2025)

*Diese Angaben halten wir für richtig, da sie sich mit unseren eigenen Erfahrungen decken. Dies ist natürlich kein Beweis, aber man kann SOLCHEN Statistiken besser glauben, wenn sie nicht mit der eigenen Wahrnehmung kollidieren. Muss sich aber den generellen Risiken jeder Statistik im klaren sein.* 







# Aufgabe 5

![Dateisystem mit Prozessen](PrzssBm1.png){width=100%}.

Die einzigen Prozesse die hier Veränderungen bewirken sind md (für das Erstellen eines neues Verzeichnisses) und date (erstellt/überschriebt eine neue Datei bla.py , dort wird das Date gespeichert). cd ändert nur wo wir uns gerade befinden, verändert aber nichts am Dateisystem, aber wo wir was verändern durch spätere Befehle. Daher ist zB. der Befehl von Ken für uns uninteressant (im Anschluss kommen keine Befehle). Es wird nur ein neues directory und eine File erstellt, daher hinter dem einen im Code / und hinter dem anderen nicht. (directory mit /.../ und file ohne, also einfach nur /...).

Schlussendlich sieht unser Baum also so aus:

![Loesung](PrzssBm2.png){width=100%}.

## Literaturverzeichnis


1. Universität Bremen "ti225_ueb01_grpH04.md" (2025)
2. Google Gemini Chatverlauf (s. Anhang) (30.10.2025)
3. OpenAI ChatGPT Chatverlauf (s. Anhang) (30.10.2025

# Anhang

Chatverlauf mit [Gemini] (https://gemini.google.com/) am 30.10.2025:

Frage: welche arten von eingabe und ausgabeumlenkung gibt es in unix

>In Unix gibt es drei Hauptarten von Standard-Datenströmen für Ein- und Ausgabe: die Standardeingabe (stdin), die Standardausgabe (stdout) und die Standardfehlerausgabe (stderr). Die Umleitung ermöglicht es, diese standardmäßigen Verbindungen (z. B. Tastatur für stdin, Bildschirm für stdout/stderr) zu ändern und stattdessen Dateien oder andere Prozesse als Quelle oder Ziel zu verwenden. Standardeingabe (\(stdin\)): Normalerweise die Tastatur. Sie kann auf eine Datei umgeleitet werden, um die Eingabe für ein Programm aus einer Datei zu lesen.Standardausgabe (\(stdout\)): Normalerweise der Bildschirm. Sie kann in eine Datei umgeleitet werden, um die normale Programmausgabe zu speichern, anstatt sie auf dem Bildschirm anzuzeigen.Standardfehlerausgabe (\(stderr\)): Normalerweise der Bildschirm. Sie wird verwendet, um Fehlermeldungen und Diagnoseinformationen auszugeben. Auch diese kann in eine Datei umgeleitet werden. Diese drei Ströme werden häufig in Kombination verwendet, um beispielsweise die gesamte Ausgabe (sowohl die normale als auch die Fehlerausgabe) in einer Datei zu speichern.



Chatverlauf mit [ChatGPT] (https://chat.openai.com/chat) am 30.10.2025:

Frage: welches betriebssystem wird gegenwärtig weltweit am häufigsten eingesetzt

>Weltweit ist derzeit das Betriebssystem Android am weitesten verbreitet — es kommt auf etwa 44–45 % aller Geräte zum Einsatz.Wenn man nur Desktop- und Laptop-Computer betrachtet, dominiert allerdings Microsoft Windows mit rund 70 % Marktanteil. 




