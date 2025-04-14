# Chess
 Chess game

Requires Winlib and Gaklib.

![Unbenannt](https://github.com/user-attachments/assets/14b65d7b-a8c3-4542-936c-08a9834bb109)

Ein einfaches Schachspiel. Im Feld Tiefe kann die Suchtiefe für den nächsten 
Zug vorgegeben werden. Beim Wert 0, wird die Stellung überhaupt nicht bewertet
sondern stattdessen per Zufall ein möglicher Zug ausgesucht. Je größer der Wert
desto tiefer wird der nächste Zug analysiert, was natürlich etwas länger 
dauert.

Diese Testversion speichert nach jedem Zug eine Datei im Tempverzeichnis mit 
dem Namensmuster chess[n].txt. Die letzte Stellung wird immer in chess.txt 
gespeichert und beim Starten geladen.

Wenn Du einen Fehler findest, kannst Du mir die letzten chess[n].txt schicken,
damit ich den Fehler analysieren kann.
