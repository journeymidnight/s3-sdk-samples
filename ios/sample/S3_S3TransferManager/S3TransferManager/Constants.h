/*
 * Copyright 2010-2013 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#define AWS_MULTI_FRAMEWORK
#import <Foundation/Foundation.h>
#import <AWSS3/AmazonS3Client.h>
#import <AWSS3/AWSS3.h>


FOUNDATION_EXPORT  NSString *const S3Endpoint;
FOUNDATION_EXPORT  NSString *const ACCESS_KEY_ID;
FOUNDATION_EXPORT  NSString *const SECRET_KEY;
FOUNDATION_EXPORT  NSString *const BucketName;      

FOUNDATION_EXPORT  AmazonS3Client *s3Client;
FOUNDATION_EXPORT  S3TransferManager *s3TM;
// Constants used to represent your AWS Credentials.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This sample App is for demonstration purposes only.
// It is not secure to embed your credentials into source code.
// DO NOT EMBED YOUR CREDENTIALS IN PRODUCTION APPS.
// We offer two solutions for getting credentials to your mobile App.
// Please read the following article to learn about Token Vending Machine:
// * http://aws.amazon.com/articles/Mobile/4611615499399490
// Or consider using web identity federation:
// * http://aws.amazon.com/articles/Mobile/4617974389850313
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!






#define CREDENTIALS_ERROR_TITLE    @"Missing Credentials"
#define CREDENTIALS_ERROR_MESSAGE  @"AWS Credentials not configured correctly.  Please review the README file."

#define kRequestTagForSmallFile         @"tag-tm-small-file-0"
#define kRequestTagForBigFile           @"tag-tm-big-file-0"
#define kKeyForBigFile                  @"tm-large-file-0"
#define kKeyForSmallFile                @"tm-small-file-0"

#define kSmallFileSize 1024*1024*4.8 //4.8 megs 临时测试文件
#define kBigFileSize 1024*1024*10  //10 megs 临时测试文件

@interface Constants : NSObject

/*
 * Creating bucket
 */
+ (NSString *)transferManagerBucket;

@end
