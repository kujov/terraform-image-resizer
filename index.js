const AWS = require('aws-sdk');
const s3 = new AWS.S3();

const destinationBucket = process.env.DESTINATION_BUCKET;

exports.handler = async (event) => {
    console.log("Processing image...");

    const bucket = event.Records[0].s3.bucket.name;
    const key = decodeURIComponent(event.Records[0].s3.object.key.replace(/\+/g, ' '));

    try {
        const data = await s3.getObject({ Bucket: bucket, Key: key }).promise();

        await s3.putObject({ Bucket: destinationBucket, Key: `original/${key}`, Body: data.Body }).promise();

        console.log("Image uploaded successfully.");

        return { statusCode: 200, body: 'Image uploaded successfully' };
    } catch (err) {
        console.error(err);
        return { statusCode: 500, body: 'Error processing image' };
    }
};
