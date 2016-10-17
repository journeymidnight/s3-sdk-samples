import boto3
import uuid
import time
from boto.s3.bucket import Bucket

s3 = boto3.resource(service_name = 's3', 
	region_name = None,
	api_version=None,
	use_ssl=False,
	verify=None,
	endpoint_url = 'http://los-cn-north-1.lecloudapis.com',
	aws_access_key_id=None, 
	aws_secret_access_key=None,
	aws_session_token=None, config=None)

print("===========================================");
print("Getting Started with Amazon S3");
print("===========================================\n");

name='my-first-s3-bucket-'+ str(uuid.uuid4())
bucket = s3.Bucket(name)
response = bucket.create(ACL = 'public-read')
print("Creating bucket " + bucket.name + "\n");

print("List bucket " + bucket.name + "\n");
try:
	print("=================================================================================================");
	print("bucketname".rjust(55)  + "\t\t" + "creation_date" + " \n");
	for b in s3.buckets.all():
		print "{name}\t\t{creation_date}\n".format( name = b.name,  creation_date = b.creation_date )

	print("=================================================================================================\n");
except:
	print("Deleting bucket " + bucket.name + "\n")
	for b in s3.buckets.all():
		print("Deleting bucket " + b.name + "\n")
		response = b.delete()

print("Uploading a new object to S3 from a file\n")
s3.Object(name, 'MyObjectKey').put(Body=open('/root/.aws/credentials', 'rb'))
#print object

print("\nDownloading an object\n")
time.sleep(1);

print("=================================================================================================");
print("Key".rjust(11) + "\t" + "etag".rjust(34) + "\t" + "size" + " \n");
for obj in bucket.objects.all():
	print "{key}\t{etag}\t{size}\t\n".format( key = obj.key, etag = obj.e_tag, size = obj.size)
print("=================================================================================================\n");

for b in s3.buckets.all():
	for obj in b.objects.all():
		print("Deleting an object key = " + obj.key + "\n")
		obj.delete();
	print("Deleting bucket " + b.name + "\n") 
	response = b.delete()
