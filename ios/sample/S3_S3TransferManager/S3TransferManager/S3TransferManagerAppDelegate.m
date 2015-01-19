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

#import "S3TransferManagerAppDelegate.h"
#import "Constants.h"
#import <AWSS3/AmazonS3Client.h>

@implementation S3TransferManagerAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    s3Client = [[AmazonS3Client alloc] initWithAccessKey:ACCESS_KEY_ID
                                                     withSecretKey:SECRET_KEY];
    s3Client.endpoint = S3Endpoint;
 
    
    return YES;
}



@end
