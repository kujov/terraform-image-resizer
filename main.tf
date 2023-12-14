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
}
