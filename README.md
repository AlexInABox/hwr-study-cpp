# HWR Studium "C++" - Semester 4

### Eine Sammlung von Unterrichtsmaterialien und Lösungen für meinen Hochschulkurs zur Programmiersprache C++.

---

### Spielübersicht

In diesem Spiel ist es dein Ziel, alle Werbe- und Virus-Popups so schnell wie möglich zu schließen. Die Popups erscheinen in regelmäßigen Abständen, und die Anzahl der Popups nimmt langsam zu, wodurch das Spiel immer schwieriger wird.

Wenn zu viele Popups auf dem Bildschirm sind, verlierst du das Spiel. Dein Highscore wird in einer Textdatei neben der ausführbaren Datei gespeichert und bleibt zwischen den Spielsitzungen erhalten – ziemlich praktisch!

Alle Assets sind in das Programm eingebettet, indem jedes dieser Assets in eine hexadezimale Darstellung umgewandelt und in `.hpp`-Dateien integriert wird.

---

### Build-Anweisungen

#### macOS (ARM)

1. **Abhängigkeiten installieren:**  
   Stelle sicher, dass `clang` und `cmake` installiert sind.

2. **Kompilieren:**
   ```
   cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -B build
   cmake --build build
   ```

#### Linux (z. B. Debian 13)

1. **Abhängigkeiten installieren:**  
   Auf Debian-basierte Systeme wie Ubuntu oder Debian 13 benötigst du `g++` und `cmake`. Zum Beispiel:
   ```
   sudo apt update
   sudo apt install g++ cmake
   ```

2. **Kompilieren:**
   ```
   cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B build
   cmake --build build
   ```

#### Windows

1. **Abhängigkeiten installieren:**  
   Du kannst Visual Studio oder MinGW verwenden. Viel Erfolg!

2. **Kompilieren:**  
   Keine klaren Anweisungen, aber du packst das schon!

---

### Drittanbieter-Bibliotheken

Für die Handhabung von Grafiken, Fensterverwaltung und Ereignissen wird **SFML 3.0.0** verwendet.

Weitere Informationen zu SFML findest du auf der [offiziellen SFML-Website](https://www.sfml-dev.org/).

---

### Zusätzliche Ressourcen

- [Wie man ein Element aus einem Vector in C++ entfernt](https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/)
- **KI-gestützte Code-Formatierungstools** zur automatischen Formatierung und Verbesserung von Code.

---

### Lizenz

[![GPLv3 Lizenz](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

---

![Logo](https://upload.wikimedia.org/wikipedia/de/thumb/9/90/Hochschule_für_Wirtschaft_und_Recht_Berlin_logo.svg/500px-Hochschule_für_Wirtschaft_und_Recht_Berlin_logo.svg.png)
