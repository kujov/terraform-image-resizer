'''
Datum: 22.12.2023
Autor: Williams Pesic, Kenin Kujovic
Quellen: https://devdocs.io/python~3.9/
'''

import os
import json
import boto3
from io import BytesIO
from PIL import Image

# Initialisierung von AWS S3-Client und Angabe des Ziel-S3-Buckets
s3 = boto3.client('s3')
destination_bucket = os.environ['DESTINATION_BUCKET']

def lambda_handler(event, context):
    print("Verarbeitung des Bildes...")

    # Extrahieren von Informationen über das hochgeladene S3-Objekt aus dem Lambda-Event
    bucket = event['Records'][0]['s3']['bucket']['name']
    key = event['Records'][0]['s3']['object']['key']

    try:
        # Herunterladen des Originalbilds aus dem Quell-S3-Bucket
        response = s3.get_object(Bucket=bucket, Key=key)
        original_image_data = response['Body'].read()

        # Ändern der Größe des Bildes auf die angegebenen Abmessungen (Breite und Höhe)
        resized_image_data = resize_image(original_image_data, 300, 200)  # Bitte die gewünschten Werte anpassen

        # Hochladen des verkleinerten Bildes in den Ziel-S3-Bucket
        s3.put_object(Bucket=destination_bucket, Key=f"resized/{key}", Body=resized_image_data)

        print("Bild wurde erfolgreich verkleinert und hochgeladen.")

        return {
            'statusCode': 200,
            'body': json.dumps('Bild wurde erfolgreich verkleinert und hochgeladen.')
        }
    except Exception as e:
        print(f"Fehler: {e}")
        return {
            'statusCode': 500,
            'body': json.dumps('Fehler bei der Bildverarbeitung')
        }

def resize_image(image_data, width, height):
    # Öffnen des Bildes aus den Bytes und Ändern der Größe
    image = Image.open(BytesIO(image_data))
    resized_image = image.resize((width, height))

    # Speichern des verkleinerten Bildes in einem Bytes-Puffer im JPEG-Format
    output_buffer = BytesIO()
    resized_image.save(output_buffer, format="JPEG")

    return output_buffer.getvalue()
