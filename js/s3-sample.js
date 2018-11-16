var AWS = require('aws-sdk');


//connect s3

AWS.config.endpoint = 'http://s3.test.com';
AWS.config.region = 's3.test.com';
AWS.config.accessKeyId = 'hehehehe';
AWS.config.secretAccessKey = 'hehehehe';
var s3 = new AWS.S3({apiVersion: '2006-03-01'});



function listbucket() {
    return new Promise(function(resolve, reject) {
        s3.listBuckets(function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);
                resolve()
            }
        });
    });
}

function createbucket(bucketname) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucketname,
        };
        s3.createBucket(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function putObject(body, bucket, key) {
    return new Promise(function(resolve, reject) {
        let params = {
            Body: body,
            Bucket: bucket,
            Key: key
        };
        s3.putObject(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function getObject(bucket, key) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucket,
            Key: key
        };
        s3.getObject(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log("get object content:");
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function deleteObject(bucket, key) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucket,
            Key: key
        };
        s3.deleteObject(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function listObjects(bucket) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucket,
        };
        s3.listObjects(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log("list objects:")
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function setBucketAcl(bucket, key) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucket,
            Key: key
        };
        s3.deleteObject(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function setObjectAcl(bucket, key) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucket,
            Key: key
        };
        s3.deleteObject(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject();
            }
            else {
                console.log(data);// successful response
                resolve();
            }
        })
    });
}

function deletebucket(bucketname) {
    return new Promise(function(resolve, reject) {
        let params = {
            Bucket: bucketname,
        };
        s3.deleteBucket(params, function(err, data) {
            if (err) {
                console.log(err, err.stack); // an error occurred
                reject(err);
            }
            else {
                console.log(data);// successful response
                resolve(params);
            }
        })
    });
}

const makeRequest = async () => {
    await createbucket("test")
    await listbucket()
    await putObject("context", "test", "testfile")
    await listObjects("test")
    await getObject("test", "testfile")
    await deleteObject("test", "testfile")
    await deletebucket("test")
    return listbucket()
}

makeRequest()
    .catch(err => {
        console.log(err);
        // output
        // Error: oops at callAPromise.then.then.then.then.then (index.js:8:13)
    })
//delete buckets


