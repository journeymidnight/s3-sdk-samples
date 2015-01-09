import boto
import boto.s3.connection
import sys
import uuid
import time
from boto.s3.key import Key

access_key = 'ACCESSKEY'
secret_key = 'SECRETKEY'

conn = boto.connect_s3(
        aws_access_key_id = access_key,
        aws_secret_access_key = secret_key,
        host = 's3.lecloud.com',
        is_secure=False,   
        calling_format = boto.s3.connection.OrdinaryCallingFormat()
        )

bucket = conn.create_bucket('my-first-s3-bucket-' +  str(uuid.uuid4()))
key = bucket.new_key('MyObjectKey')
print("===========================================");
print("Getting Started with Amazon S3");
print("===========================================\n");

print("Creating bucket " + bucket.name + "\n");

for b in bucket.list():
        print "{name}\t{size}\t{modified}\n".format( name = b.name, size = b.size, modified = b.last_modified)

print("Uploading a new object to S3 from a file\n")
key.set_contents_from_string('Hello World!')
key.set_canned_acl('public-read')


print("Downloading an object\n")

time.sleep(1);
s3object = bucket.get_key('MyObjectKey')
print s3object

print("Deleting object\n")
bucket.delete_key('MyObjectKey')

print("Deleting bucket\n")
conn.delete_bucket(bucket.name)
