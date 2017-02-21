#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h> 


using namespace Aws::S3;
using namespace Aws::S3::Model;

static const char* KEY = "s3_cpp_sample_key";
static const char* BUCKET = "s3-cpp-sample-bucket";

static const char* ALLOCATION_TAG = "MYTESTS3Client";

int main()
{
    Aws::SDKOptions options;

	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;

    Aws::InitAPI(options);
	{
		Aws::Client::ClientConfiguration clientConfig;
		// clientConfig.scheme = Aws::Http::Scheme::HTTPS;
		clientConfig.scheme = Aws::Http::Scheme::HTTP;
		clientConfig.connectTimeoutMs = 30000;
		clientConfig.requestTimeoutMs = 600000;
		
		clientConfig.endpointOverride= "s3.test.com:3000";

		//http://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/using-service-client.html
		//http://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/credentials.html
		Aws::String access_key_id("hehehehe");
	    	Aws::String secret_key("hehehehe");
		auto client = Aws::MakeShared<S3Client>(ALLOCATION_TAG, Aws::Auth::AWSCredentials(access_key_id, secret_key), clientConfig);
		


		PutObjectRequest putObjectRequest;
		putObjectRequest.WithKey(KEY)
			   .WithBucket(BUCKET);

		//this can be any arbitrary stream (e.g. fstream, stringstream etc...)
		auto requestStream = Aws::MakeShared<Aws::StringStream>("s3-sample");
		*requestStream << "Hello World!";

		//set the stream that will be put to s3
		putObjectRequest.SetBody(requestStream);

		auto putObjectOutcome = client->PutObject(putObjectRequest);

		if(putObjectOutcome.IsSuccess())
		{
			std::cout << "Put object succeeded" << std::endl;
		}
		else
		{
			std::cout << "Error while putting Object " << putObjectOutcome.GetError().GetExceptionName() << 
				   " " << putObjectOutcome.GetError().GetMessage() << std::endl;
			return -1;
		}

		//now get the object back out of s3. The response stream can be overridden here if you want it to go directly to 
		// a file. In this case the default string buf is exactly what we want.
		GetObjectRequest getObjectRequest;
		getObjectRequest.WithBucket(BUCKET)
			.WithKey(KEY);


		auto getObjectOutcome = client->GetObject(getObjectRequest);
		if(getObjectOutcome.IsSuccess())
		{
			std::cout << "Successfully retrieved object from s3 with value: " << std::endl;
			std::cout << getObjectOutcome.GetResult().GetBody().rdbuf() << std::endl << std::endl;;  
		}
		else
		{
			std::cout << "Error while getting object " << getObjectOutcome.GetError().GetExceptionName() <<
				 " " << getObjectOutcome.GetError().GetMessage() << std::endl;
		}

		
	}
    Aws::ShutdownAPI(options);
    return 0;  
}
