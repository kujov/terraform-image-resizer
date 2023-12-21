# Benutzeranleitung Bildverkleinerung Kenin, Williams, Filip

Optinal:
```
sudo apt-get update && sudo apt-get install -y gnupg software-properties-common
sudo apt update
```
Terraform installieren:
```
sudo apt-get install terraform
```
Installation verifizieren:
```
terraform -help
```
Ofizielle Dokumentation: https://developer.hashicorp.com/terraform/tutorials/aws-get-started/install-cli

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

## Planung
Wir haben zuerst ein erstes Konzept für das Projekt erstellt.
Nämlich haben wir uns dazu entschieden ein Terraformscript für die Erzeugung unserer Buckets, sowie für das Skalieren und Abspeichern der Bilder in den verschiedenen Buckets.
Für Terraform haben wir uns entschieden, weil es einfacher organisiert ist und es auf Konfigurationen basiert.

## Umsetzung unseres Scripts
### Bildverkleinerung

### Terraform

### AWS - Lambda-Funktion

### Test

### Hilfsmittel

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

## Reflexion von Kenin
Vorgabe: positive Punkte, Verbesserungsvorschläge für ein nächstes Projekt, Reflexion ist Substanz (nicht nur oberflächlich)
## Reflexion von Williams
Vorgabe: positive Punkte, Verbesserungsvorschläge für ein nächstes Projekt, Reflexion ist Substanz (nicht nur oberflächlich)
## Reflexion von Filip
Vorgabe: positive Punkte, Verbesserungsvorschläge für ein nächstes Projekt, Reflexion ist Substanz (nicht nur oberflächlich)

Quellen:
- https://medium.com/@neonforge/how-to-generate-unique-s3-bucket-names-in-terraform-devops-pro-tips-4d14c38d597f
- https://docs.aws.amazon.com/lambda/latest/dg/chapter-layers.html
- https://spacelift.io/blog/how-to-use-terraform-variables
- https://stackoverflow.com/questions/53605776/how-to-enforce-terraform-destroy
- https://stackoverflow.com/questions/57288992/terraform-how-to-create-iam-role-for-aws-lambda-and-deploy-both
- https://stackoverflow.com/questions/65984400/how-to-delete-non-empty-s3-bucket-with-terraform
- https://www.geeksforgeeks.org/python-pil-image-resize-method/
- https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-examples.html
- https://hackernoon.com/how-to-use-aws-s3-with-python
- https://registry.terraform.io/providers/hashicorp/random/latest/docs/resources/string
