
 
#import <Foundation/Foundation.h>

#import <DaonCryptoSDK/DaonCryptoSDK.h>

#import <DaonFIDOSDK/IXUAFDelegate.h>
#import <DaonFIDOSDK/IXUAFDiscoveryData.h>
#import <DaonFIDOSDK/IXUAFTransaction.h>
#import <DaonFIDOSDK/IXUAFVersion.h>
#import <DaonFIDOSDK/IXUAFError.h>
#import <DaonFIDOSDK/IXUAFLocator.h>
#import <DaonFIDOSDK/IXUAFMessageReader.h>
#import <DaonFIDOSDK/IXUAFAccount.h>


extern NSNumber * IXUAFWarningDeviceSecurityDisabled;
extern NSNumber * IXUAFWarningDeviceDebug;
extern NSNumber * IXUAFWarningDeviceCompromised;
extern NSNumber * IXUAFWarningDeviceNoHardwareKeystore;
extern NSNumber * IXUAFWarningKeyMigrationFailed;
extern NSNumber * IXUAFWarningPendingRegistrationsRemoved;
extern NSNumber * IXUAFWarningDeviceSimulator;

@class IXUAFAuthenticatorRegistry;

/// Deprecated. Use the IXUAF API.

@interface DaonFIDO : NSObject

@property(nonatomic, weak) id<IXUAFDelegate> delegate;
@property (nonatomic, readonly) BOOL initialized;
@property (nonatomic, strong, readonly) NSArray * warnings;
@property (nonatomic, readonly) IXUAFAuthenticatorRegistry * registry;


/// Initialize the SDK. This must be called before the SDK is used.

- (IXUAFErrorCode) initialize;


/// Initialize the SDK. This must be called before the SDK is used.

- (IXUAFErrorCode) initializeWithParameters:(NSDictionary*)parameters NS_SWIFT_NAME(initialize(parameters:));


/// Set token received when registering for push notifications

+ (void) setPushNotificationServiceToken:(NSData*)token NS_SWIFT_NAME(setPushNotificationService(token:));


/// Perform UAF register operation
///
/// If the registrationResponseMessageString in the completion response is nil, then there was an error with the format of the server response.

- (void) register:(NSString*)uafMessage
       completion:(void (^)(NSString* response, NSError* error))completion NS_SWIFT_NAME(register(message:completion:));


/// Notify UAF client of the result of a UAF operation (registration or authentication)

- (void) notifyResult:(NSString *)uafMessage responseCode:(NSInteger)responseCode NS_SWIFT_NAME(notifyResult(message:code:));


/// Notify UAF client of the result of a UAF operation (registration or authentication)
///
/// The completion handler will return additional information about expired keys and if confirmation OTP is enabled, the OTP.

- (void) notifyResult:(NSString *)uafMessage
         responseCode:(NSInteger)responseCode
           parameters:(NSDictionary*)parameters
           completion:(void (^)(NSDictionary* response, NSError* error))completion NS_SWIFT_NAME(notifyResult(message:code:params:completion:));

- (void) notifyResult:(NSString *)uafMessage
         responseCode:(NSInteger)responseCode
      responseMessage:(NSString*)responseMessage
           parameters:(NSDictionary*)parameters
           completion:(void (^)(NSDictionary* response, NSError* error))completion;


/// Perform UAF authenticate operation
///
/// If the authenticationResponseMessage in the completion response is nil, then there was an error with the format of the server response.

- (void) authenticate:(NSString *)uafMessage
           completion:(void (^)(NSString* response, NSError* error))completion NS_SWIFT_NAME(authenticate(message:completion:));


/// Generate a One Time Password (OTP).

- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode
                        username:(NSString *)username
                           appId:(NSString *)appId
                      completion:(void (^)(NSDictionary<NSString*, NSString*>* response, NSError* error))completion;

- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode
                           appId:(NSString *)appId
                      completion:(void (^)(NSDictionary<NSString*, NSString*>* response, NSError* error))completion;



/// The expiration time of a current OTP

+ (NSInteger) oneTimePasswordExpiration;


/// Perform UAF deregister operation

- (void) deregister:(NSString *)uafMessage
         completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(deregister(message:completion:));


/// Discover the available UAF authenticators
- (void) discover:(void (^)(IXUAFDiscoveryData* response, NSError* error))completion NS_SWIFT_NAME(discover(completion:));


/// Check that a UAF request policy can be processed by at least one of the available UAF authenticators.

- (void) checkPolicy:(NSString *)uafRequest
          completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(checkPolicy(message:completion:));


/// Check that a UAF request policy can be processed by at least one of the available UAF authenticators for a given user.

- (void) checkPolicy:(NSString *)uafRequest
            username:(NSString *)username
          completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(checkPolicy(message:username:completion:));


/// Check for registered authenticators
/// Get a list of authenticators which match the given registration policy and lists those which are registered for the given user and app ID.

- (void) checkRegistrations:(NSString *)registrationPolicy
                   username:(NSString *)username
                      appId:(NSString *)appId
                 completion:(void (^)(NSArray<IXUAFAuthenticator*>* authenticators, NSError* error))completion
NS_SWIFT_NAME(checkRegistrations(policy:username:appId:completion:));

- (void) checkGroupRegistrations:(NSString *)registrationPolicy
                        username:(NSString *)username
                           appId:(NSString *)appId
                      completion:(void (^)(NSArray<NSArray<IXUAFAuthenticator*>*> * authenticators, NSError* error))completion
NS_SWIFT_NAME(checkGroupRegistrations(policy:username:appId:completion:));


/// Test whether an authenticator with a given aaid is locked.

- (BOOL) isLocked:(NSString *)aaid NS_SWIFT_NAME(isLocked(aaid:));


/// Enable or disable runtime logging.
/// - Parameter enabled: if true, logging will be enabled.

+ (void) setLoggingEnabled:(BOOL)enabled NS_SWIFT_NAME(setLogging(enabled:));


/// Enable or disable runtime logging at a given level.
/// - Parameter enabled: if true, logging will be enabled.
/// - Parameter level: IXALogLevelError, IXALogLevelInfo or IXALogLevelDebug.

+ (void) setLoggingEnabled:(BOOL)enabled level:(IXALogLevel)level NS_SWIFT_NAME(setLogging(enabled:level:));


/// Enable or disable runtime logging at a given level.
/// - Parameter enabled: if true, logging will be enabled.
/// - Parameter level: IXALogLevelError, IXALogLevelInfo or IXALogLevelDebug.
/// - Parameter persist: if true, the log will also be written to a file, daon-ixa.log in the apps document folder.

+ (void) setLoggingEnabled:(BOOL)enabled level:(IXALogLevel)level persist:(BOOL)persist NS_SWIFT_NAME(setLogging(enabled:level:persist:));


/// Remove all keys and enrolled data

- (void) reset;


/// Remove all keys, enrolled data and alls keys with a UUID name

- (void) resetAndRemoveUUIDKeys;


/// Get device status information, e.g. jailbroken, environment, etc.
+ (NSDictionary<NSString*, NSString*>*) status __deprecated;


/// Get SDK version.
+ (NSString*) version;


/// Get authenticator with AAID
- (IXUAFAuthenticator*) authenticatorWithAaid:(NSString*)aaid;


/// Set the facet ID.
///
/// Under normal SDK operation this method should never be called.
///
/// - Parameter facetId: The facet ID to set

+ (void) setFacetId:(NSString *)facetId NS_SWIFT_NAME(setFacet(withId:));


/// Get Facet ID
+ (NSString*) facetId;


/// Get device ID
+ (NSString*) deviceId;


/// Get list of available accounts
+ (NSArray<NSString*>*) accounts;


/// Delete account from device
/// - Parameter account: the account to delete

+ (void) deleteAccount:(NSString*)account;
@end
