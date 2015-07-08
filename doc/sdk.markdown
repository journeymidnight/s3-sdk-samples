
SDK目前只支持从lecloud上传下载文件

从CDN下载可以自行拼出URL,用wget,浏览器等从CDN下载

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
    self.uploadFileOperation=[s3TM uploadFile:filename bucket: BucketName key:@”myfile1_tag”];
    //指定ACL
    #define kS3CannedAclPrivate             @"private"
    #define kS3CannedAclPublicRead         @"public-read"
    #define kS3CannedAclPublicReadWrite   @"public-read-write"
    #define kS3CannedAclAuthRead           @"authenticated-read"
    #define kS3CannedAclBucketOwnerRead   @"bucket-owner-read"
    #define kS3CannedAclBucketOwnerFullControl  @"bucket-owner-full-control"
    self.uploadSmallFileOperation.putRequest.cannedACL = [[S3CannedACL alloc] initWithStringValue:kS3CannedAclPublicRead];
     
##Download文件

	[s3TM downloadFile:saveFileName bucket: BucketName key: @”myfile1_tag”];

## cdn 下载

任何http client都可以下载, 只要ACL配置为Public

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}

##sample文件

	见样例文件S3_S3TransferManager.zip


# Android

##必须的sdk jar文件

    aws-android-sdk-x.x.x-core.jar
    aws-android-sdk-x.x.x-s3.jar
   
##参数配置
    
	public static final String ACCESS_KEY_ID = "ACCESSKEY";
    public static final String SECRET_KEY = "SECRETKEY";
    public static final String BUCKET_NAME = "my-first-s3-bucket";
    public static final String S3_ENDPOINT ="http://s3.lecloud.com";


##初始化AmazonS3Client

    sS3Client = new AmazonS3Client(
        new BasicAWSCredentials(ACCESS_KEY_ID,SECRET_KEY));
    sS3Client.setEndpoint(S3_ENDPOINT);

##Upload 文件

    //创建 bucket，并指定acl
    // acl参数列表
    //Private("private"),
    //PublicRead("public-read"),
    //PublicReadWrite("public-read-write"),
    //AuthenticatedRead("authenticated-read"),
    //LogDeliveryWrite("log-delivery-write"),
    //BucketOwnerRead("bucket-owner-read"),
    //BucketOwnerFullControl("bucket-owner-full-control");

    sS3Client.createBucket(new CreateBucketRequest(BUCKET_NAME).withCannedAcl(CannedAccessControlList.PublicRead));
    //文件上传
    sS3Client.putObject(BUCKET_NAME,“filename”, new File(“/sdcard/filename”));

##Download文件

    String downloadPath = Environment.getExternalStorageDirectory().getPath() + "/download_cache";
    GetObjectRequest request = new GetObjectRequest(
        Constants.BUCKET_NAME, "imageFilename");

    File dnFile=new File(downloadPath + "/imagefile.img");
    sS3Client.getObject(request,dnFile);

## cdn 下载

任何http client都可以下载, 只要ACL配置为Public

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}
 
##sample文件

	见样例文件s3-test.zip


# PHP

##SDK安装

参考http://docs.aws.amazon.com/AWSSDKforPHP/, 可以通过github clone, PEAR, Composer多种方式安装

##初始化参数

	$client = new AmazonS3(array(
	        'key' => 'ACCESSKEY',
	        'secret' => 'SECRETKEY',
	));

	$client->set_hostname('s3.lecloud.com');
	$client->allow_hostname_override(false);
	$client->enable_path_style();
	/* use http protocol */
	$client->disable_ssl();

##上传object

	$result = $client->create_object($bucket, $key, array(
	'body'   => "Hello World!"
	));
	/* set to public ,let letv CDN to access the object */
	$client->set_object_acl($bucket, $key, AmazonS3::ACL_PUBLIC);


## cdn 下载

任何http client都可以下载, 只要ACL配置为Public

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}

##sample文件

	sample.php


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
	multipart_chunk_size_mb = 15

替换其中accesskey和secretkey


## 上传

	./s3cmd mb s3://testbucket
	./s3cmd put -P {filename} s3://testbucket

-P选项表示支持cdn分发

## cdn 下载

任何HTTP client都可以下载

	wget http://s3-cdn.lecloud.com/{bucketname}/{objectname}
	


# Windows S3 工具

CloudBerry S3 Explorer PRO，该工具支持多线程上传，缺点是需要付费，价格为39.99$，提供15天的免费试用，可以先感受一下，目前来看此工具用户界面最为友好，功能最为齐全。另外CloudBerry还提供一个免费版，但是它不支持5GB以上的大文件。另外有一个叫cyberduck的工具，免费且支持大文件，但用户界面不太友好，另外对文件夹上传支持非常有限，需要您自己先创建好文件夹，再进行文件的上传，不过稍感欣慰的是它能够支持一次上传多个文件。另外需要注意的一点时，由于CloudBerry S3 Explorer PRO对上传文件切成小块上传，当下载时它会自己进行拼接，因而使用CloudBerry S3 Explorer PRO上传的文件只能通过CloudBerry S3 Explorer PRO下载，其他客户端会出现很多5MB的chunk文件，并且其他客户端不具备拼接的能力.


## CloudBerry使用方法:

0. [cloudBerry下载地址](http://www.cloudberrylab.com)

1. 进入Tools->Options,选择S3 Multipart Upload,把三个勾都打上
   
![](sdk-img/1.jpg)

2. 进入File->S3 Compatible-> S3 Compatible

![](sdk-img/2.jpg)

3. 通过点击New Account创建账户：

![](sdk-img/3.jpg)


4. 之后是填写账户信息：

	Service point为服务器IP地址，提供的服务器IP为：s3.lecloud.com
	Access key和Secret key类似于用户名和密码.
	Use SSL 不用勾选

![](sdk-img/4.jpg)


## cyberduck配置方法：

[cyberduck下载地址](http://cyberduck.io/)

