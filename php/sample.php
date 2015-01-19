<?php
/*
 * Copyright 2013. Amazon Web Services, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

// Include the SDK using the Composer autoloader
require 'vendor/autoload.php';


/*
 If you instantiate a new client for Amazon Simple Storage Service (S3) with
 no parameters or configuration, the AWS SDK for PHP will look for access keys
 in the AWS_ACCESS_KEY_ID and AWS_SECRET_KEY environment variables.

 For more information about this interface to Amazon S3, see:
 http://docs.aws.amazon.com/aws-sdk-php-2/guide/latest/service-s3.html#creating-a-client
*/
$client = new AmazonS3(array(
        'key' => '9EEIWGS705M4ZJ3N7FEM',
        'secret' => '8humW3nOraybmbIjY6s15IVned87gz/nUrgxYlEX',
));

$client->set_hostname('s3.lecloud.com');
$client->allow_hostname_override(false);
$client->enable_path_style();
/* use http protocol */
$client->disable_ssl();

/* use https protocol
 * curl will check if CA is verified.
$client->disable_ssl_verification();
 */


$bucket = uniqid("php-sdk-sample-", true);
echo "Creating bucket named {$bucket}\n";
$result = $client->createBucket($bucket, AmazonS3::REGION_US_W1);


$key = 'hello_world.txt';
echo "Creating a new object with key {$key}\n";
$result = $client->create_object($bucket, $key, array(
    'body'   => "Hello World!"
));

$client->set_object_acl($bucket, $key, AmazonS3::ACL_PUBLIC);



echo "Downloading that same object:\n";
$result = $client->get_object($bucket, $key)->body;

echo "\n---BEGIN---\n";
print($result);
echo "\n---END---\n\n";


echo "Deleting object\n";
$client->delete_object($bucket, $key);


$result = $client->deleteBucket($bucket,1);
