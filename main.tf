terraform {
  required_providers {
    aws = {
      source = "hashicorp/aws"
      version = "4.64.0"
    }
  }
}

provider "aws" {}

resource "aws_s3_bucket" "imageresizerbeforeninethousand" {
  bucket = "imageresizerbeforeninethousand"
}

resource "aws_s3_bucket" "imageresizerafterninethousand" {
  bucket = "imageresizerafterninethousand"
}

