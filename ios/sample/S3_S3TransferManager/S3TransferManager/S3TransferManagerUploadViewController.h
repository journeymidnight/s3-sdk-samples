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

#import <UIKit/UIKit.h>

#import <AWSRuntime/AWSRuntime.h>
#import <AWSS3/AWSS3.h>

@interface S3TransferManagerUploadViewController : UIViewController <UINavigationControllerDelegate, AmazonServiceRequestDelegate>

 

- (IBAction)uploadSmallFile:(id)sender;
- (IBAction)uploadBigFile:(id)sender;
- (IBAction)pauseUploads:(id)sender;
- (IBAction)resumeUploads:(id)sender;
- (IBAction)cancelSmallUpload:(id)sender;
- (IBAction)cancelBigUpload:(id)sender;
- (IBAction)cancelAllTransfers:(id)sender;
- (NSString *)generateTempFile: (NSString *)filename : (long long)approximateFileSize;

@property (weak, nonatomic) IBOutlet UITextField *putObjectTextField;
@property (weak, nonatomic) IBOutlet UITextField *multipartObjectTextField;

@end
