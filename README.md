# Modul 346 Bildverkleinerungs-Service

## Anleitung Vorinstallation Terraform

AWS CLI Installation:
```
sudo snap install aws-cli --classic
```
Alle benötigten Abhängigkeiten für Terraform:
```
sudo apt-get update && sudo apt-get install -y gnupg software-properties-common
```
```
wget -O- https://apt.releases.hashicorp.com/gpg | \
gpg --dearmor | \
sudo tee /usr/share/keyrings/hashicorp-archive-keyring.gpg
```
```
gpg --no-default-keyring \
--keyring /usr/share/keyrings/hashicorp-archive-keyring.gpg \
--fingerprint
```
```
echo "deb [signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] \
https://apt.releases.hashicorp.com $(lsb_release -cs) main" | \
sudo tee /etc/apt/sources.list.d/hashicorp.list
```
```
sudo apt update
```
Installation Terraform:
```
sudo apt-get install terraform
```
Offizielle Dokumentation: https://developer.hashicorp.com/terraform/tutorials/aws-get-started/install-cli

## Anleitung Ausführung des Skripts

```
./main
```
Das Menu sollte folgend aussehen:
```console
Welcome to the Infrastructure Management System
-------------------------------------------------
Please select an action by entering the command name:
  start  - Start the infrastructure
  stop   - Stop the infrastructure
  upload - Upload an image to the infrastructure
-------------------------------------------------
Enter your choice: 
```
Nun gibt es 3 Optionen:
- start:    Startet die Infrastruktur
- stop:     Stoppt die Infrastruktur
- upload:   Ladet ein Foto in den ersten Bucket hoch

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
Nämlich haben wir uns dazu entschieden ein Terraformskript für die Erzeugung unserer Buckets, sowie für das Skalieren und Abspeichern der Bilder in den verschiedenen Buckets.
Für Terraform haben wir uns entschieden, weil es einfacher organisiert ist und es auf Konfigurationen basiert.

## Umsetzung der Bildverkleinerung

### Terraform
Terraform ermöglicht es Nutzern, eine Infrastruktur as a Code zu verfassen. Das ermöglicht dem Nutzer das Ausführen der Infrastruktur per Knopfdruck. Bei unserer Softwarelösung die wir für die Bildverkleinerung erstellt haben, nutzen wir ebenfalls Terraform, um die ganzen Skripts/Codes zu bündeln und möglichst einfach und kompakt auszuführen. (//Bild TF//)

### AWS - Lambda-Funktion
Die AWS - Lambda-Funktionen machen es für uns Nutzern möglich, Funktionen auszuführen ohne dafür den physischen Server dafür verwalten zu müssen. Bei uns wird die Lambda-Funktion verwendet, um die Bilder zu verkleinern und um das verkleinerte Bild in ein anderes Bucket zu verschieben. (//Bild Lambda-Funktion//)

### Test
Die Tests zu Ausführung unseres Skripts haben wir auf einer komplett neuen und leeren Ubuntu VM vorgenommen, wo keine vorinstallationen beinhaltet, welches unsere Tests beinflussen könnten. Auf dieser VM haben wir dann die Anleitung einmal durch gemacht, um zu überprüfen, ob es bei Aussenstehenden auch einwandfrei funktionieren würde.

### Testfall 1: Upload eines Bildes

**Ziel:** Überprüfen, ob das Hochladen eines Bildes in den ersten S3-Bucket erfolgreich ist.

**Schritte:**
1. Starten Sie das Skript.
2. Wählen Sie die Option "upload".
3. Wählen Sie ein Bild zum Hochladen aus.

**Erwartetes Ergebnis:** Das ausgewählte Bild wird erfolgreich in den ersten S3-Bucket hochgeladen.

**Tatsächliches Ergebnis:** Das ausgewählte Bild wurde erfolgreich in den ersten S3-Bucket hochgeladen.

**Fazit:** Der Testfall war erfolgreich.

### Testfall 2: Bildverkleinerung

**Ziel:** Überprüfen, ob das Skript ein hochgeladenes Bild erfolgreich verkleinert und in den zweiten S3-Bucket abspeichert.

**Schritte:**
1. Starten Sie das Skript.
2. Wählen Sie die Option "start", um die Bildverkleinerung zu starten.

**Erwartetes Ergebnis:** Das hochgeladene Bild wird erfolgreich verkleinert und in den zweiten S3-Bucket abgespeichert.

**Tatsächliches Ergebnis:** Das hochgeladene Bild wurde erfolgreich verkleinert und in den zweiten S3-Bucket abgespeichert.

**Fazit:** Der Testfall war erfolgreich.

### Testfall 3: Fehlgeschlagene Bildverkleinerung

**Ziel:** Überprüfen, wie das Skript mit einem ungültigen Bild umgeht und ob es eine angemessene Fehlermeldung gibt.

**Schritte:**
1. Starten Sie das Skript.
2. Wählen Sie die Option "start".
3. Versuchen Sie, ein ungültiges Bild (nicht unterstütztes Dateiformat) hochzuladen.

**Erwartetes Ergebnis:** Das Skript erkennt das ungültige Bild und gibt eine Fehlermeldung aus.

**Tatsächliches Ergebnis:** Das Skript erkennt das ungültige Bild und gibt eine Fehlermeldung aus.

**Fazit:** Der Testfall war erfolgreich.

### Hilfsmittel
Wir haben folgende Hilfmittel für die Entwicklung unseres Bildverkleinerungsprogramms verwendet:
- Visual Studio Code (VSC) | Bearbeitung des MarkDown-Files
- AWS CLI | Erstellung der Buckets, sowie Ausführung der Lambda-Funktionen
- GitHub | Speicherort unseres Repositorys und Ort der Versionskontrolle
- VMWare | Virtuelle Maschinen als Grundlage auf denen z.B. die AWS CLI läuft

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

## Reflexion von Kenin:

Zu Beginn hatte ich nur begrenztes Know-how im Umgang mit Terraform. Dennoch begeistere ich mich für Konfigurationsdateien, wie sie beispielsweise bei Docker Compose zum Einsatz kommen. Aus diesem Grund entschied ich mich für Terraform. Bei der Lambda-Funktion empfahl ich Williams die Verwendung von Python, da ich über umfangreiche Kenntnisse in dieser Sprache verfüge und ihm gegebenenfalls bei Problemen behilflich sein kann.

Ich stiess auf keine grösseren Probleme, da ich zuvor alle Details mit meinem Team besprochen und die Aufgaben aufgeteilt hatte. Um Stress und Fehler zu vermeiden, hielt ich mich strikt an den Zeitplan. Gleichzeitig suchte ich nach neuen Herausforderungen, um mein Wissen zu erweitern. In diesem Zusammenhang lernte ich die Python-Bibliothek Pillow sowie die S3-API näher kennen, was mein Verständnis für die Integration von Bildverarbeitung und Cloud-Speicher vertiefte.

Durch diese Erfahrungen habe ich nun eine solide Grundlage im Umgang mit Terraform erlernt und werde es in zukünftigen Projekten, die Infrastructure as Code (IaC) nutzen, sicherlich wieder einsetzen

Für zukünftige Projekte nehme ich mir vor, nach einer intensiven oder frustrierenden Arbeitssession eine Pause einzulegen oder eine Nacht darüber zu schlafen. Dies hat sich als effektiv erwiesen, um mit einem frischen Blick und erneuerter Energie an Herausforderungen heranzugehen. Zudem plane ich, regelmässige Reflexionen und die Dokumentation von Erkenntnissen in meinen Arbeitsablauf zu integrieren. Dies wird mir helfen, Muster in meinen Herausforderungen zu erkennen und meine Ansätze kontinuierlich zu verbessern. Weiterhin möchte ich den Austausch mit Kollegen durch regelmässige Peer-Reviews meiner Codes und Konfigurationen verstärken, um von unterschiedlichen Perspektiven und Erfahrungen zu profitieren.

## Reflexion von Williams
Vorgabe: positive Punkte, Verbesserungsvorschläge für ein nächstes Projekt, Reflexion ist Substanz (nicht nur oberflächlich)
In unserem Projekt lag mein Fokus auf der Entwicklung der Lambda-Funktion. Ursprünglich starteten wir mit JavaScript und versuchten, Node-Module zu integrieren, doch stellten fest, dass diese nicht mit unserer benötigten Engine kompatibel waren. Diese Erfahrung betonte die Wichtigkeit der Tool-Kompatibilität von Anfang an.

Ein entscheidender Wendepunkt war der Wechsel zu Python, nachdem feststand, dass die Buckets bereits einsatzbereit waren. Dies erwies sich als äusserst effizient, da Python tiefer ins System greifen konnte und keine umfangreichen speziellen Pakete wie Node-Module erforderte.
Die Verwendung von Terraform war ebenfalls positiv, obwohl die Einarbeitung anfangs herausfordernd war. Für zukünftige Projekte empfehle ich von Beginn an Python zu nutzen, sofern möglich, und die Tool-Kompatibilität sorgfältig zu überprüfen.
Insgesamt war dieses Projekt eine lehrreiche Erfahrung, die meine Flexibilität und Problemlösungsfähigkeiten stärkte. Mit den vorgeschlagenen Verbesserungen hoffe ich auf noch erfolgreichere zukünftige Projekte.

Während des Projekts konnte ich nicht nur meine Fähigkeiten in der Entwicklung der Lambda-Funktion verbessern, sondern auch wertvolles Wissen im Bereich Terraform und Cloud Computing sammeln. Der Übergang zu Python und die effiziente Verwendung von Terraform haben mir gezeigt, wie wichtig es ist, sich in diesen Technologien weiterzubilden. Insgesamt war dieses Projekt eine wertvolle Lerngelegenheit, die meine Expertise erweitert hat und mich besser auf zukünftige Herausforderungen im Bereich Cloud Computing und Infrastrukturmanagement vorbereitet hat.

Meine Verbesserungsvorschläge für das nächste Projekt, ist es sich von anfang an etwas besser zu erkundigen. Da ich vorallem viel Zeit verschwendet habe, bis ich gemerkt habe das die node modules nicht kompatibel sind mit der Engine selbst. Im Gesamten habe ich sonst, eigentlich das Projektmamagement sehr gut gefunden und würde es so wieder machen.
## Reflexion von Filip
Mein Schwerpunkt in diesem Projekt bestand darin mich mit dem Verfassen der Dokumentation auseinanderzusetzen, da wir zu dritt waren und somit mit der Flexibiliät der Aufgaben ein bisschen eingeschränkt waren, wer, wo ,was machen konnte. Dennoch konnte ich ebenfalls ein wenig Hilfe beim Planen und teils beim Entwicklen des Skripts leisten, was mir Freude bereitete.
Gerne hätte ich mich ein bisschen mehr mit der Materie von AWS und Python vertraut gemacht, aber der Punkt dass wir zu dritt waren hat mir ein bisschen gegen die Karten gespielt, was nicht heisst dass ich nicht trotzdessen einiges an hilfreichem Knowhow einholen konnte. 

Da ich mich intensiv mit der Dokumentation befasst habe, musste ich mich auch in die Skripts der Anderen einlesen und mich mit den darin enthaltenen Elementen vertraut machen, um es überhaupt verfassen zu können.
Ein grosser Schwerpunkt bestand bei mir darin die Elemente von Terraform zu verstehen, da ich garkeine Vorkenntnisse in diesem Teil der Informatik mitbringen konnte. Dennoch war es mir möglich durch die Hilfe von Kenin und Williams mich schnell darin einfinden und dies zu Dokumentieren.

Für das nächste Projekt hoffe ich, dass ich eine grössere Rolle im Bereich der Entwicklung eines Programms oder eines Skripts einnehmen kann, damit mich intensiver mit der Materie befassen kann und mir somit zusätzlich wichtiges Knowhow einholen kann.
Ein weiterer Punkt wäre den ich gerne anderst umsetzen würde ist der Aspekt, dass ich bei Dokumentationen nicht direkt losschreiben sollte, sondern mir zuerst einen groben Überblick über das grosse Ganze zu verschaffen, damit ich im Nachhinein weniger Änderungen vornehmen muss.

Mein kurzes Fazit zu diesem Projekt und diesem Modul ist, dass ich es sehr spannend und erstaunlich finde/fand, wie praktisch und vielseitig man IT-Komponenten der Cloud einsetzen kann, ohne dabei einen grossen Aufwand zu betreiben. Cloud findet immer mehr und mehr einen sicheren Platz in der IT und es ist sehr hilfreich sich bereits in der Ausbildung damit auseinander zu setzten und sich gewisse Vorkenntnisse diesbezüglich anzueignen.

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
