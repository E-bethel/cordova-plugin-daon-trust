#import <Foundation/Foundation.h>

#import <DaonFIDOSDK/IXUAFAuthenticator.h>

static NSString * const kIXUAFErrorUserInfoAuthenticatorKey  = @"authenticator";

/// FIDO Error codes.
/// 
@interface IXUAFError : NSObject


typedef NS_ENUM(NSInteger, IXUAFServerErrorCode)
{
    // Client error codes from FIDO doco
    IXUAFServerErrorCodeNoError                      = 1200,
    /*
     1202    Accepted. Message accepted, but not completed at this time. The RP may need time to process the attestation, run risk scoring, etc. The server should not send an authenticationToken with a 1202 response
    1400    Bad Request. The server did not understand the message
    1401    Unauthorized. The userid must be authenticated to perform this operation, or this KeyID is not associated with this UserID.
    1403    Forbidden. The userid is not allowed to perform this operation. Client should not retry
    1404    Not Found.
    1408    Request Timeout.
    1480    Unknown AAID. The server was unable to locate authoritative metadata for the AAID.
    1481    Unknown KeyID. The server was unable to locate a registration for the given UserID and KeyID combination.
            This error indicates that there is an invalid registration on the user's device. It is recommended that FIDO UAF Client deletes the key from local device when this error is received.
            
    1490    Channel Binding Refused. The server refused to service the request due to a missing or mismatched channel binding(s).
    1491    Request Invalid. The server refused to service the request because the request message nonce was unknown, expired or the server has previously serviced a message with the same nonce and user ID.
    1492    Unacceptable Authenticator. The authenticator is not acceptable according to the server's policy, for example because the capability registry used by the server reported different capabilities than client-side discovery.
    1493    Revoked Authenticator. The authenticator is considered revoked by the server.
    1494    Unacceptable Key. The key used is unacceptable. Perhaps it is on a list of known weak keys or uses insecure parameter choices.
    1495    Unacceptable Algorithm. The server believes the authenticator to be capable of using a stronger mutually-agreeable algorithm than was presented in the request.
    1496    Unacceptable Attestation. The attestation(s) provided were not accepted by the server.
    1497    Unacceptable Client Capabilities. The server was unable or unwilling to use required capabilities provided supplementally to the authenticator by the client software.
    1500    Unacceptable Content. There was a problem with the contents of the message and the server was unwilling or unable to process it.
     */
    IXUAFServerErrorCodeInternalError               = 1500,
    IXUAFServerErrorCodeRetry                       = 1501, // ADOS retry
};

typedef NS_ENUM(NSInteger, IXUAFErrorCode) {
    // Client error codes from FIDO doco
    IXUAFErrorCodeNoError                             = 0x00,
    IXUAFErrorCodeWaitUserAction                      = 0x01,
    IXUAFErrorCodeInsecureTransport                   = 0x02,
    IXUAFErrorCodeUserCancelled                       = 0x03,
    IXUAFErrorCodeUnsupportedVersion                  = 0x04,
    IXUAFErrorCodeNoSuitableAuthenticator             = 0x05,
    IXUAFErrorCodeProtocolError                       = 0x06,
    IXUAFErrorCodeUntrustedFacetId                    = 0x07,
    IXUAFErrorCodeKeyDisappearedPermanently           = 0x09,
    IXUAFErrorCodeAuthenticatorAccessDenied           = 0x0c,
    IXUAFErrorCodeInvalidTransactionContent           = 0x0d,
    IXUAFErrorCodeUserNotResponsive                   = 0x0e,
    IXUAFErrorCodeInsufficientAuthenticatorResources  = 0x0f,
    IXUAFErrorCodeUserLockout                         = 0x10,
    IXUAFErrorCodeUserNotEnrolled                     = 0x11,
    IXUAFErrorCodeUnknown                             = 0xFF,
    
    // Proprietary error codes
    IXUAFErrorCodeSdkNotInitialised                   = 0xA0,
    IXUAFErrorCodeMissingDelegate                     = 0xA1,
    IXUAFErrorCodeDeviceSecurityDisabled              = 0xA2,
    IXUAFErrorCodeLicenseNotVerified                  = 0xA3,
    IXUAFErrorCodeLicenseExpired                      = 0xA4,
    IXUAFErrorCodeLicenseNoAuthenticators             = 0xA5,
    IXUAFErrorCodeDeviceDebug __deprecated            = 0xA6,
    IXUAFErrorCodeUserAlternativeAuthenticator        = 0xA7,
    IXUAFErrorCodeOfflineOneTimePassword              = 0xA8,
    IXUAFErrorCodeBiometricsInvalidated               = 0xA9,
    IXUAFErrorCodeDeviceCompromised __deprecated      = 0xAA,
    IXUAFErrorCodeDeviceNoHardwareKeystore            = 0xAB, // 171
    IXUAFErrorCodeKeyMigrationFailed                  = 0xAC,
    IXUAFErrorCodeAuthenticatorLocked                 = 0xAF,  // 175
    
    IXUAFErrorCodeExtensionsEncryption                 = 0xB0,
    IXUAFErrorCodeExtensionsNoEncryptionKeyID          = 0xB1,
    IXUAFErrorCodeExtensionsNoConfirmationOTPKey       = 0xB2,
};

typedef NS_ENUM(NSInteger, IXUAFWarningCode) {
    IXUAFWarningCodeDeviceSecurityDisabled              = 0xA2,
    IXUAFWarningCodeDeviceDebug __deprecated            = 0xA6,
    IXUAFWarningCodeDeviceCompromised __deprecated      = 0xAA,
    IXUAFWarningCodeDeviceNoHardwareKeystore            = 0xAB,
    IXUAFWarningCodeKeyMigrationFailed                  = 0xAC,
    IXUAFWarningCodeKeyPendingRegistrationsRemoved      = 0xAD,
    IXUAFWarningCodeDeviceSimulator __deprecated        = 0xAE
};

+ (NSError *) errorWithCode:(NSInteger)code authenticator:(IXUAFAuthenticator*)authenticator;
+ (NSError *) errorWithCode:(NSInteger)code;

+ (NSError *) errorWithCode:(NSInteger)code message:(NSString*)message;
+ (NSError *) errorWithCode:(NSInteger)code message:(NSString*)message authenticator:(IXUAFAuthenticator*)authenticator;

+ (NSError *) errorWithAuthenticatorCode:(NSInteger)code message:(NSString*)message authenticator:(IXUAFAuthenticator*)authenticator;

+ (NSError *) notInitalizedError;

+ (NSError *) protocolError;
+ (NSError *) protocolErrorWithAuthenticator:(IXUAFAuthenticator*)authenticator;


@end
