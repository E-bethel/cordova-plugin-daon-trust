

#ifndef IXUAFConstants_h
#define IXUAFConstants_h

static const long ATTACHMENT_HINT_INTERNAL = 1;
static const short TRANSACTION_CONFIRMATION_DISPLAY_ANY = 0x0001;
static NSString * const PNG_IMAGE_MIME_TYPE = @"image/png";

// User verification types
static const long USER_VERIFY_PRESENCE              = 0x01;
static const long USER_VERIFY_FINGERPRINT           = 0x02;
static const long USER_VERIFY_PASSCODE              = 0x04;
static const long USER_VERIFY_VOICEPRINT            = 0x08;
static const long USER_VERIFY_FACEPRINT             = 0x10;
static const long USER_VERIFY_LOCATION              = 0x20;
static const long USER_VERIFY_EYEPRINT              = 0x40;
static const long USER_VERIFY_PATTERN               = 0x80;
static const long USER_VERIFY_HANDPRINT             = 0x100;
static const long USER_VERIFY_NONE                  = 0x200;
static const long USER_VERIFY_ALL                   = 0x400;

// Key protection types
static const short KEY_PROTECTION_SOFTWARE       = 0x0001;
static const short KEY_PROTECTION_HARDWARE       = 0x0002;
static const short KEY_PROTECTION_TEE            = 0x0004;
static const short KEY_PROTECTION_SECURE_ELEMENT = 0x0008;
static const short KEY_PROTECTION_REMOTE_HANDLE  = 0x0010;

// Matcher protection types
static const short MATCHER_PROTECTION_SOFTWARE = 0x0001;
static const short MATCHER_PROTECTION_TEE      = 0x0002;
static const short MATCHER_PROTECTION_ON_CHIP  = 0x0004;

// Signature algorithms
static const short ALG_SIGN_SECP256R1_ECDSA_SHA256_RAW = 0x0001;
static const short ALG_SIGN_SECP256R1_ECDSA_SHA256_DER = 0x0002;
static const short ALG_SIGN_RSASSA_PSS_SHA256_RAW      = 0x0003;
static const short ALG_SIGN_RSASSA_PSS_SHA256_DER      = 0x0004;
static const short ALG_SIGN_SECP256K1_ECDSA_SHA256_RAW = 0x0005;
static const short ALG_SIGN_SECP256K1_ECDSA_SHA256_DER = 0x0006;
static const short ALG_SIGN_SM2_SM3_RAW                = 0x0007;
static const short ALG_SIGN_RSA_EMSA_PKCS1_SHA256_RAW  = 0x0008;
static const short ALG_SIGN_RSA_EMSA_PKCS1_SHA256_DER  = 0x0009;

// Public key encodings
static const short ALG_KEY_ECC_X962_RAW = 0x0100;
static const short ALG_KEY_ECC_X962_DER = 0x0101;
static const short ALG_KEY_RSA_2048_RAW = 0x0102;
static const short ALG_KEY_RSA_2048_DER = 0x0103;

// Status codes
static const short UAF_STATUS_CODE_OK = 1200;

static const short ADOS_STATUS_CODE_FAILED = 1501;
static const short ADOS_ERROR_USER_BLOCKED = 1601;
static const short ADOS_ERROR_ATTEMPTS_FACE = 1602;
static const short ADOS_ERROR_ATTEMPTS_VOICE = 1603;
static const short ADOS_ERROR_ATTEMPTS_PASSCODE = 1604;


// Transaction types
static NSString * const TRANSACTION_CONTENT_TYPE_TEXT = @"text/plain";
static NSString * const TRANSACTION_CONTENT_TYPE_PNG_IMAGE = @"image/png";

#endif 
