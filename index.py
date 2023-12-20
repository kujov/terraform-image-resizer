import os
import json
import boto3
from io import BytesIO
from PIL import Image

s3 = boto3.client('s3')
destination_bucket = os.environ['DESTINATION_BUCKET']

def lambda_handler(event, context):
    print("Processing image...")
    
    bucket = event['Records'][0]['s3']['bucket']['name']
    key = event['Records'][0]['s3']['object']['key']

    try:
        response = s3.get_object(Bucket=bucket, Key=key)
        original_image_data = response['Body'].read()

        resized_image_data = resize_image(original_image_data, 300, 200)  # Adjust width and height as needed

        s3.put_object(Bucket=destination_bucket, Key=f"resized/{key}", Body=resized_image_data)

        print("Image resized and uploaded successfully.")
        
        return {
            'statusCode': 200,
            'body': json.dumps('Image resized and uploaded successfully')
        }
    except Exception as e:
        print(f"Error: {e}")
        return {
            'statusCode': 500,
            'body': json.dumps('Error processing image')
        }

def resize_image(image_data, width, height):
    image = Image.open(BytesIO(image_data))
    resized_image = image.resize((width, height))
    
    output_buffer = BytesIO()
    resized_image.save(output_buffer, format="JPEG")
    
    return output_buffer.getvalue()
