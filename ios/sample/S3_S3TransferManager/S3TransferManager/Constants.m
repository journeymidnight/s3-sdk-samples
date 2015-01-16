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

#import "Constants.h"
#import <AWSS3/AmazonS3Client.h>
#import <AWSS3/AWSS3.h>

@implementation Constants

AmazonS3Client *s3Client=nil;
S3TransferManager *s3TM;
//参数配置
NSString *const S3Endpoint = @"http://s3.lecloud.com";
NSString *const ACCESS_KEY_ID = @"ACCESSKEY";
NSString *const SECRET_KEY =@"SECRETKEY";
NSString *const BucketName= @"my-first-s3-bucket-";


+ (NSString *)transferManagerBucket
{
    return [[NSString stringWithFormat:@"%@-%@", BucketName, ACCESS_KEY_ID] lowercaseString];
}

@end
