
SDK目前只支持从lecloud上传下载文件,不支持从cdn下载
从cdn下载可以自行拼出URL,从CDN下载

# Python

## python SDK 上传

安装python-boto库文件

	tar zxvf python-s3-sdk-sample.tar.gz
	cd python-s3-sdk-sample	

修改S3Sample.py中的accesskey和secretkey
	
	edit S3Sample.py

运行测试文件
	
	python S3Sample.py

要注意在上传中有

	key.set_canned_acl('public-read')

权限的object才支持cdn分发,否则是用户私有的object


## cdn 下载

任何http client都可以下载

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}

## 更多

请参考python-boto文档:http://boto.readthedocs.org/
	
# Java

## 上传

安装JDK,ant

	tar zxvf java-s3-sdk-samples.tar.gz
	cd java-s3-sdk-samples/

修改S3Sample.java中的accesskey和secretkey
	
	edit S3Sample.java

运行测试文件
	
	ant


## cdn 下载

任何HTTP client都可以下载

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}

## 更多

参考Amazon官方文档, 目前lecloud支持aws-java-sdk-1.4.7


# IOS

##必须的sdk framework文件：
   
	AWSRuntime.framework
	AWSS3.framework

##参数配置

	NSString *const S3Endpoint = @"http://s3.lecloud.com";
	NSString *const ACCESS_KEY_ID = @"ACCESSKEY";
	NSString *const SECRET_KEY =@"SECRETKEY";
	NSString *const BucketName= @"my-first-s3-bucket";


##初始化AmazonS3Client
	
	AmazonS3Client *s3Client  = [[AmazonS3Client alloc] 
                                   initWithAccessKey:ACCESS_KEY_ID
                                   withSecretKey:SECRET_KEY];
	s3Client.endpoint = S3Endpoint;
	S3TransferManager *s3TM= [S3TransferManager new];
	s3TM.s3 = s3Client;

##Upload 文件：

	// 创建 bucket
	S3CreateBucketRequest *createBucketRequest = 
	        [[S3CreateBucketRequest alloc] 
	          initWithName: BucketName;
	//指定ACL
	#define kS3CannedAclPrivate             @"private"
	#define kS3CannedAclPublicRead         @"public-read"
	#define kS3CannedAclPublicReadWrite   @"public-read-write"
	#define kS3CannedAclAuthRead           @"authenticated-read"
	#define kS3CannedAclBucketOwnerRead   @"bucket-owner-read"
	#define kS3CannedAclBucketOwnerFullControl  @"bucket-owner-full-control"
	  createBucketRequest.cannedACL=kS3CannedAclPublicRead;
	  
	 @try {
	       S3CreateBucketResponse *createBucketResponse = [s3Client createBucket:createBucketRequest];
	                if(createBucketResponse.error != nil)
	                {
	                    NSLog(@"Error: %@", createBucketResponse.error);
	                }
	            }@catch(AmazonServiceException *exception){
	                if(![@"BucketAlreadyOwnedByYou" isEqualToString: exception.errorCode]){
	                    NSLog(@"Unable to create bucket: %@", exception.error);
	                }
	            }
	//文件上传
	[s3TM uploadFile:filename bucket: BucketName key:@”myfile1_tag”];

##Download文件

	[s3TM downloadFile:saveFileName bucket: BucketName key: @”myfile1_tag”];

##sample文件

	见样例文件S3_S3TransferManager.zip

# 命令行工具

下载最新s3cmd工具 http://s3tools.org/s3cmd

编辑~/.s3cfg文件

	[default]
	access_key = {access_key}
	secret_key = {secret_key}
	default_mime_type = binary/octet-stream
	enable_multipart = True
	encoding = UTF-8
	encrypt = False
	host_base = s3.lecloud.com
	host_bucket = %(bucket)s.s3.lecloud.com
	use_https = False
	put_continue = True
	multipart_chunk_size_mb = 8

替换其中accesskey和secretkey


## 上传

	./s3cmd mb s3://testbucket
	./s3cmd put -P {filename} s3://testbucket

-P选项表示支持cdn分发

## cdn 下载

任何HTTP client都可以下载

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}
