// keys.cpp
#include "keys.h"

const char* awsKeyID = "[FILLMEIN]"; // REPLACE with your access key id
const char* awsSecKey = "[FILLMEIN]"; // REPLACE with your secret access key


// Init and connect Edison wifi to local wlan
char* ssid = "[FILLMEIN]"; //  your network SSID (name)
char* pass = "[FILLMEIN]";    // your network password (use for WPA, or use as key for WEP)

// Common AWS constants
const char* AWS_REGION = "us-west-2";  // us-west-2 etc
const char* AWS_ENDPOINT = "amazonaws.com";

/* Constants for connecting to Amazon SNS. */
const char* TARGET_ARN = "[FILLMEIN]";  // replace each ':' with '%3A'


/* Contants describing DynamoDB table and values being used. */
const char* HASH_KEY_NAME = "device_id";
const char* HASH_KEY_VALUE = "[FILLMEIN]"; // REPLACE with your team or particpant name e.g Team38
const char* RANGE_KEY_NAME = "time";
const char* RANGE_KEY_VALUE = "1";
const char* TABLE_NAME = "[FILLMEIN]"; //REPLACE with your DDB Table name e.g. hackday-2014-team38
const char* ATTRIBUTE_NAME = "device";
const char* ATTRIBUTE_VALUE = "mediatek";

/* Constants describing Kinesis stream */
const char* streamName = "[FILLMEIN]"; //REPLACE with your stream name e.g. hackday-2014-team38-TeamStream-1K5DAIU8GCRXY
const char* partitionKey = "partitionKey";
