# Benutzeranleitung Bildverkleinerung Kenin, Williams, Filip
## Erläuterung des Projekt
Wir durften uns zwischen drei verschiedenen Projekten entschieden, welche wir umsetzen wollen. <br>
Wir haben uns für das Bildverkleinerungsprojekt entschieden.<br>
In diesem Projekt geht es darum, dass wir zwei AWS S3 Buckets erstellen müssen. Innerhalb des ersten Buckets wird gewöhnlich das Bild eingefügt.<br>
Nun soll es anhand eines Skripts automatischen das Bild verkleinern und in den zweiten Bucket abspeichern. <br>

## Aufgabenaufteilung
Zu Beginn haben wir uns mit dem Aufteilen der Aufgaben. Die Aufgaben unterscheiden sich nur zu Beginn, da wir schlussendlich alle an der Entwicklung des Skripts beschäftigt sind.
- Kenin: Einrichten der Architektur auf AWS, Entwicklung des Skripts
- Williams:  Erstellung und Einbindung des Skripts, Entwicklung des Skripts
- Filip: Erstellung und Umsetzung der Dokumentation, Entwicklung des Skripts

## Schwierigkeiten
**Dependencies auf Lambda:** Um die **Pillow** Library zu verwenden haben wir Layers verwendet. 
```
layers = [
    "arn:aws:lambda:us-east-1:113088814899:layer:Klayers-python37-Pillow:11",
  ]
  ```
(Achtung: diese sind Standortabhängig!)
Quelle Layers: https://github.com/keithrozario/Klayers/blob/master/deployments/python3.7/arns/us-east-1.csv <br> <br>
**Einstieg Terraform:** Vorab benötigte Terraform ein gewisses Know-How. Dies hat mich(Kenin) am Anfang ein wenig Zeit gekostet. Ich bevorzuge Terraform da ich generell denke "Config" files sind viel übersichtlicher und sorgen für Ordnung.



Quellen:
- https://medium.com/@neonforge/how-to-generate-unique-s3-bucket-names-in-terraform-devops-pro-tips-4d14c38d597f
