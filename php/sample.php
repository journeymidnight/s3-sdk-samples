<?php
namespace Aws\S3;
use Aws\S3\S3Client;
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

$client = S3Client::factory([
	'key' => 'V7IPYXNZNMP8FGFG647G', 
	'secret' => 'Fd4TUtoR4pmWojmrY7TZwLZiN5qWZxraZbo6FTFn',
	'region' => 'us-west-2',
	'endpoint' => 'http://los-cn-north-1.lecloudapis.com'
]);

$bucket = uniqid("php-sdk-sample-", true);
$name = $bucket;

echo "Creating bucket named {$bucket}\n";
$result = $client->createBucket(array('ACL' => 'public-read','Bucket' => $bucket));

echo "Putting object into bucket named {$bucket}\n";
$key = 'MyObjectKey';
$result = $client->putObject(array('Bucket' => $bucket, 'Key' => $key, 'Body' => 'Hello World!'));

// Access parts of the result object
echo $result['Expiration'] . "\n";
echo $result['ServerSideEncryption'] . "\n";
echo $result['ETag'] . "\n";
echo $result['VersionId'] . "\n";
echo $result['RequestId'] . "\n";

echo "\n-------------------------------------\n";
echo "List bucket and object\n";
echo "-------------------------------------\n";
$result = $client->listBuckets();
foreach ($result['Buckets'] as $bucket) {
    // Each Bucket value will contain a Name and CreationDate
    echo "{$bucket['Name']} - {$bucket['CreationDate']}\n";
    $iterator = $client->getIterator('ListObjects', array(
        'Bucket' => $bucket['Name']));

    foreach ($iterator as $object) {
        echo $object['Key'] . "\n";
    }
}

echo "\n-------------------------------------\n";
echo "Downloading that same object\n";
echo "-------------------------------------\n";
$result = $client->getObject(array('Bucket' => $name, 'Key' => $key));

echo "\n---BEGIN---\n";
print($result['Body']);
echo "\n---END---\n\n";

// Delete the objects in the bucket before attempting to delete the bucket
echo "Deleting bucket and object\n";
echo "-------------------------------------\n";
$result = $client->listBuckets();
foreach ($result['Buckets'] as $bucket) {
    $iterator = $client->getIterator('ListObjects', array(
        'Bucket' => $bucket['Name']));

    foreach ($iterator as $object) {
        echo "Deleting object key =  " . "{$object['Key']}\n";
	$client->deleteObject(array('Bucket' => $bucket['Name'], 'Key' => $object['Key']));
    }
    echo "Deleting bucket name = " . "{$bucket['Name']}\n";
    $client->deleteBucket(array('Bucket' => $bucket['Name']));
}
echo "-------------------------------------\n";
