terraform {
  required_providers {
    aws = {
      source = "hashicorp/aws"
      version = ">= 4.64.0"
    }
    //Random provider used for randstring generation
    random = {
      source = "hashicorp/random"
      version = ">= 3.0.0"
    }
  }
}

provider "aws" {}

data "aws_caller_identity" "current" {}

//Random id for name clash risk reduction
resource "random_id" "generated" {
  byte_length = 8
}

//Image original size bucket
resource "aws_s3_bucket" "imageResizerBefore" {
  bucket = "imageresizerbefore-${random_id.generated.hex}"
}

//Image resized size bucket
resource "aws_s3_bucket" "imageResizerAfter" {
  bucket = "imageresizerafter-${random_id.generated.hex}"
}

//Aws Lambda function
resource "aws_lambda_function" "image_resizer_lambda_ninethousand" {
  function_name = "imageresizerlambda-${random_id.generated.hex}"
  filename      = "index.zip"
  handler       = "index.handler"
  runtime       = "nodejs16.x"
  role          = "arn:aws:iam::${data.aws_caller_identity.current.account_id}:role/LabRole"
  //Env variables for saving resized image
  environment {
    variables = {
      DESTINATION_BUCKET = aws_s3_bucket.imageResizerAfter.bucket
    }
  }
}

resource "aws_lambda_permission" "allow_s3" {
  statement_id  = "AllowExecutionFromS3"
  action        = "lambda:InvokeFunction"
  function_name = aws_lambda_function.image_resizer_lambda_ninethousand.function_name
  principal     = "s3.amazonaws.com"
  source_arn    = aws_s3_bucket.imageResizerBefore.arn
}

/S3 trigger for lambda func
resource "aws_s3_bucket_notification" "s3_notification" {
  bucket = aws_s3_bucket.imageResizerBefore.bucket

  lambda_function {
    lambda_function_arn = aws_lambda_function.image_resizer_lambda_ninethousand.arn
    events             = ["s3:ObjectCreated:*"]
  }

  depends_on = [aws_lambda_permission.allow_s3]
}

