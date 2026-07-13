/*!
 @header IXUAF
 Simplified FIDO interface.
 @copyright Daon. All rights reserved.
 @updated 2019-01-10
 */

#import <Foundation/Foundation.h>
#import <DaonCryptoSDK/DaonCryptoSDK.h>
#import <DaonFIDOSDK/IXUAFError.h>
#import <DaonFIDOSDK/IXUAFTransaction.h>
#import <DaonFIDOSDK/IXUAFDiscoveryData.h>
#import <DaonFIDOSDK/IXUAFDelegate.h>
#import <DaonFIDOSDK/IXUAFServiceDelegate.h>

static NSString * _Nonnull const kIXUAFServiceParameterUsername      = @"username";
static NSString * _Nonnull const kIXUAFServiceParameterApplication   = @"application";
static NSString * _Nonnull const kIXUAFServiceParameterDescription   = @"description";
static NSString * _Nonnull const kIXUAFServiceParameterIdentifier    = @"id";
static NSString * _Nonnull const kIXUAFServiceParameterInstanceID    = @"instanceId";
static NSString * _Nonnull const kIXUAFServiceParameterProvider      = @"provider";
static NSString * _Nonnull const kIXUAFServiceParameterServer        = @"device.gateway.url";
static NSString * _Nonnull const kIXUAFServiceParameterType          = @"push.type";
static NSString * _Nonnull const kIXUAFServiceParameterRequest       = @"request";

static NSString * _Nonnull const kIXUAFServiceParameterPolicyRegistration = @"param.policy.reg";
static NSString * _Nonnull const kIXUAFServiceParameterPolicyAuthentication = @"param.policy.auth";

static NSString * _Nonnull const kIXUAFServiceParameterAccountNameFirst = @"param.account.name.first";
static NSString * _Nonnull const kIXUAFServiceParameterAccountNameLast = @"param.account.name.last";
static NSString * _Nonnull const kIXUAFServiceParameterAccountPassword = @"param.account.password";
static NSString * _Nonnull const kIXUAFServiceParameterAccountRegistrationRequest = @"param.account.registration";

static NSString * _Nonnull const kIXUAFServiceParameterTransactionConfirmationType = @"param.transaction.confirmation.type";
static NSString * _Nonnull const kIXUAFServiceParameterTransactionConfirmationContent = @"param.transaction.confirmation.content";

static NSString * _Nonnull const kIXUAFTransactionConfirmationContentTypeText = @"text/plain";
static NSString * _Nonnull const kIXUAFTransactionConfirmationContentTypePNG = @"image/png";

static NSString * _Nonnull const kIXUAFServiceParameterSingleShot = @"param.singleshot";
static NSString * _Nonnull const kIXUAFServiceParameterOTP = @"param.otp";

static NSString * _Nonnull const kIXUAFApplicationSchemeDefault = @"default";  // iOS bundle id
static NSString * _Nonnull const kIXUAFApplicationSchemeUser    = @"user";     // User set
static NSString * _Nonnull const kIXUAFApplicationSchemeURL     = @"url";      // E.g. Published Locally

/// Daon FIDO UAF SDK interface. Provides an abstraction of FIDO UAF functionality. 
///  
/// ```swift
/// let fido = IXUAF(service: IXUAFRPSAService(url: server))
/// fido?.logging = true
/// fido?.delegate = self
///  
/// let params = ["com.daon.sdk.keys.access.biometry" : "true"]
///  
/// fido?.initialize(parameters: params) { (code, warnings) in
///    self.busy(on: false)
///  
///    if code == .licenseExpired {
///        self.show(title: "Initialize failed", message: "License expired")
///    } else if code == .licenseNotVerified {
///        self.show(title: "Initialize failed", message: "License not verified")
///    } else if code == .licenseNoAuthenticators {
///        self.show(title: "Initialize failed", message: "No licensed authenticators")
///    } else {
///        if code != .noError {
///            self.show(title: "Initialize", message: "\(code.rawValue)")
///        }
///    }
///  
///    for warning in warnings {
///        if warning == IXUAFWarningDeviceDebug {
///            self.updateInfo(message: "Application is running in debug mode")
///        } else if warning == IXUAFWarningDeviceSimulator {
///            self.updateInfo(message: "Application is running in a simulator")
///        } else if warning == IXUAFWarningDeviceSecurityDisabled {
///            self.updateInfo(message: "Device passcode/Touch ID/Face ID is not enabled")
///        } else if warning == IXUAFWarningDeviceCompromised {
///            self.updateInfo(message: "Device is jailbroken")
///        } else if warning == IXUAFWarningKeyMigrationFailed {
///            self.updateInfo(message: "Touch ID/Face ID. One or more keys failed to migrate and has been invalidated.")
///        }
///    }
/// }
/// ```

@interface IXUAF : NSObject <IXUAFDelegate>

/// The configuration delegate.
@property(nonatomic, weak) id<IXUAFDelegate> _Nullable delegate;

/// True if the SDK is initialized.
@property (nonatomic, readonly) BOOL initialized;

/// The FIDO application id.
@property (nonatomic, strong)   NSString *_Nullable application;

/// Enable or disable logging. Default is disabled.
@property (nonatomic, assign)   BOOL logging;

/// Set token received when registering for push notifications
///
/// - Parameter token: The Apple Push Notifications token.
+ (void) setPushNotificationServiceToken:(NSData*_Nullable)token NS_SWIFT_NAME(setPushNotificationService(token:));

/// Get unique device ID
/// - Returns: A unique device ID
///
+ (NSString*_Nonnull) deviceId;

/// Set the facet ID.
///
/// Under normal SDK operation this method should never be called.
///
/// - Parameter facetId: The facet ID to set
///
+ (void) setFacet:(NSString *_Nonnull)facetId NS_SWIFT_NAME(setFacet(withId:));

/// Get Facet ID
+ (NSString*_Nonnull) facet;

/// Get SDK version.
+ (NSString*_Nonnull) version;

/// Get key information and validity
+ (NSDictionary<NSString*, NSDictionary*>*_Nonnull) keys;
+ (NSDictionary<NSString*, NSDictionary*>*_Nonnull) keysWithApplication:(NSString*_Nullable)appid NS_SWIFT_NAME(keys(application:));
+ (NSDictionary<NSString*, NSDictionary*>*_Nonnull) keysWithApplication:(NSString*_Nullable)appid
                                                               username:(NSString*_Nonnull)username NS_SWIFT_NAME(keys(application:username:));

/// Check if there are any valid keys
///  - Returns: Security Framework OSStatus code. errSecSuccess means no issues.
+ (OSStatus) checkKeys;

/// Get list of available accounts
+ (NSArray<NSString*>*_Nonnull) accounts;

- (instancetype _Nonnull) initWithService:(id<IXUAFServiceDelegate>_Nullable)service;

/// Initialise the SDK. This must be called before the SDK is used.
///
/// - Parameter parameters: The SDK exensions and other parameters.
/// - Parameter completion: The completion handler.
///
- (void) initializeWithParameters:(NSDictionary<NSString*, NSString*> *_Nullable)parameters
                       completion:(void (^_Nonnull)(IXUAFErrorCode code, NSArray<NSNumber*> *_Nonnull warnings))completion NS_SWIFT_NAME(initialize(parameters:completion:));


- (void) requestServiceAccessWithUsername:(NSString*_Nonnull)username
                               parameters:(NSDictionary *_Nullable)parameters
                               completion:(void (^_Nonnull)(NSString*_Nullable, NSError *_Nullable))completion NS_SWIFT_NAME(requestServiceAccess(username:parameters:completion:));

- (void) revokeServiceAccessWithParameters:(NSDictionary *_Nullable)parameters
                                completion:(void (^_Nonnull)(NSError *_Nullable))completion NS_SWIFT_NAME(revokeServiceAccess(parameters:completion:));

- (void) deleteUser:(NSString*_Nonnull)username
         parameters:(NSDictionary *_Nullable)parameters
         completion:(void (^_Nonnull)(NSError *_Nullable))completion NS_SWIFT_NAME(delete(username:parameters:completion:));


/// Remove all keys and enrolled data
- (void) reset;

/// Remove all keys, enrolled data and alls keys with a UUID name
- (void) resetAndRemoveUUIDKeys;

/// Get application scheme
- (NSString*_Nonnull) applicationScheme;

/// Get authenticator with AAID
///  - Parameter aaid: The AAID
///  - Returns: An IXUAFAuthenticator object.
- (IXUAFAuthenticator*_Nullable) authenticatorWithAaid:(NSString*_Nonnull)aaid;

/// Force unlock client authenticator
///  - Parameter aaid: The AAID
///  - Parameter key: An optional keyid
///  - Returns: True if the authenticator was unlocked.
- (BOOL) unlock:(NSString*_Nonnull)aaid key:(NSString*_Nullable)keyid;


/// Discover available UAF authenticators.
/// - Parameter handler: The handler returns the list of authenticators or an error.
- (void) discoverWithCompletionHandler:(void (^_Nonnull)(IXUAFDiscoveryData *_Nullable response, NSError *_Nullable error))handler;

/// Perform UAF register operation.
/// - Parameter handler: The handler returns the response or an error.
- (void) registerWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/// Perform UAF register operation.
/// - Parameter parameters: Additional parameters passed during registration.
/// - Parameter handler: The handler returns the response or an error.
- (void) registerWithParameters:(NSDictionary*_Nullable)parameters
                        handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(parameters:handler:)) __deprecated_msg("This method has been deprecated, please use register(username:parameters:handler:)");

/// Perform UAF register operation.
///
///```swift
/// fido?.register(username: username) { [self] (res, error) in
///     if let e = error {
///         show(error: e);
///     } else {
///         if let response = res {
///             show(title: "Success", message: "Registered: \(response)");
///         } else {
///             show(title: "Success", message: "Registered");
///         }
///     }
/// }
///```
/// - Parameter username: The username.
/// - Parameter handler: The handler returns the response or an error.
- (void) registerWithUsername:(NSString*_Nullable)username
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(username:handler:));

/// Perform UAF register operation.
/// - Parameter username: The username.
/// - Parameter parameters: Additional parameters passed during registration.
/// - Parameter handler: The handler returns the response or an error.

- (void) registerWithUsername:(NSString*_Nullable)username
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(username:parameters:handler:));

/// Perform UAF authenticate operation.
/// - Parameter handler: The handler returns the response or an error.
- (void) authenticateWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/// Perform UAF authenticate operation.
///
/// - Parameter parameters: Additional parameters passed during authentication
/// - Parameter handler: The handler returns the response or an error.
- (void) authenticateWithParameters:(NSDictionary*_Nullable)parameters
                            handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(parameters:handler:));

/// Perform UAF step-up authenticate operation.
///
///```swift
///fido?.authenticate(username:username, description: "step-up") { [self] (res, error) in
///        if let e = error {
///            show(error: e);
///        } else {
///            if let response = res {
///                show(title: "Success", message: "Authenticated: \(response)");
///            } else {
///                show(title: "Success", message: "Authenticated");
///            }
///        }
///    }
///```
///
/// - Parameter username: The username.
/// - Parameter description: A short description
/// - Parameter handler: The handler returns the response or an error.
///
- (void) authenticateWithUsername:(NSString*_Nullable)username
                      description:(NSString*_Nullable)description
                          handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(username:description:handler:));

/// Perform UAF step-up authenticate operation.
///
/// - Parameter username: The username.
/// - Parameter description: A short description.
/// - Parameter parameters: Additional parameters passed during authentication.
/// - Parameter handler: The handler returns the response or an error.
///
- (void) authenticateWithUsername:(NSString*_Nullable)username
                      description:(NSString*_Nullable)description
                       parameters:(NSDictionary*_Nullable)parameters
                          handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(username:description:parameters:handler:));

/// Perform UAF authenticate operation in response to a push notification.
///
/// - Parameter notification: The push notification dictionary.
/// - Parameter username: The username.
/// - Parameter parameters: Additional parameters passed during authentication.
/// - Parameter handler: The handler returns the response or an error.

- (void) authenticateWithNotification:(NSDictionary*_Nonnull)notification
                             username:(NSString*_Nullable)username
                           parameters:(NSDictionary*_Nullable)parameters
                              handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(notification:username:parameters:handler:));

/// Perform UAF deregister operation.
/// - Parameter aaid: The AAID.
/// - Parameter username: The username if available
/// - Parameter parameters: Additional parameters passed during deregistration.
/// - Parameter handler: The handler returns nil if the operation was a success.
///
- (void) deregisterWithAaid:(NSString*_Nonnull)aaid
                   username:(NSString*_Nullable)username
                 parameters:(NSDictionary*_Nullable)parameters
                    handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(aaid:username:parameters:handler:));

/// Perform UAF deregister operation.
/// - Parameter aaid: The AAID.
/// - Parameter username: The username if available
/// - Parameter handler: The handler returns nil if the operation was a success.

- (void) deregisterWithAaid:(NSString*_Nonnull)aaid
                   username:(NSString*_Nullable)username
                    handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(aaid:username:handler:));

/// Perform UAF deregister operation.
/// - Parameter message: The FIDO deregistration message.
/// - Parameter handler: The handler returns nil if the operation was a success.
///
- (void) deregisterWithMessage:(NSString*_Nonnull)message
                       handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(message:handler:));

/// Perform UAF deregister operation.
///
/// The handler is called for each deregistered authenticator with an AAID and/or error. The call is complete when the AAID is nil.
///
/// - Parameter parameters: Additional parameters passed during deregistration.
/// - Parameter handler: The handler is called with an AAID and/or error. The call is complete when the AAID is nil.
- (void) deregisterWithUsername:(NSString*_Nonnull)username
                     parameters:(NSDictionary*_Nullable)parameters
                        handler:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(deregister(username:parameters:handler:));

/// Perform UAF deregister operation.
///
/// The handler is called for each deregistered authenticator with an AAID and/or error. The call is complete when the AAID is nil.
///
/// - Parameter handler: The handler is called with an AAID and/or error. The call is complete when the AAID is nil.

- (void) deregisterWithUsername:(NSString*_Nonnull)username
                        handler:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(deregister(username:handler:));

/// Check for registered authenticators.
///
/// Get a list of authenticators which match the given registration policy and lists those which are registered for the given user and app ID.
/// - Parameter username: The username.
/// - Parameter parameters: Additional parameters
/// - Parameter handler: The handler returns the list of authenticators or an error.
///
- (void) checkRegistrationsWithUsername:(NSString*_Nonnull)username
                             parameters:(NSDictionary*_Nullable)parameters
                                handler:(void (^_Nonnull)(NSArray<IXUAFAuthenticator *> * _Nullable authenticators, NSError * _Nullable error)) handler NS_SWIFT_NAME(checkRegistrations(username:parameters:handler:)) __deprecated;

/// Check that a UAF message can be processed by at least one of the available UAF authenticators.
/// - Parameter message: The FIDO message.
/// - Parameter handler: The handler returns nil if the operation was a success.
 
- (void) checkMessage:(NSString *_Nonnull)message handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/// Check that a UAF message can be processed by at least one of the available UAF authenticators.
/// - Parameter message: The FIDO message.
/// - Parameter username: The username
/// - Parameter handler: The handler returns nil if the operation was a success.

- (void) checkMessage:(NSString *_Nonnull)message username:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/// Generate a One Time Password (OTP).
/// - Parameter mode: The mode IXUAFOfflineOTPModeIdentify or IXUAFOfflineOTPModeSign.
/// - Parameter handler: The handler returns the response or an error.

- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode handler:(void (^_Nonnull)(NSDictionary<NSString*, NSString*> *_Nullable response, NSError *_Nullable error))handler;

/// Check if authenticator is registered
/// - Parameter aaid: The authenticator AAID.
/// - Parameter username: The username.
/// - Returns: True if the authenticator with the given aaid is registered for the user.
///
- (BOOL) registeredWithAuthenticator:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;
    
// Single Shot

/// Register with FIDO message, e.g. can be used for single-shot registration.
/// - Parameter message: The FIDO message.
/// - Parameter parameters: Additional parameters passed during registration.
/// - Parameter handler: The handler returns the response or an error.
///
- (void) registerWithMessage:(NSString*_Nonnull)message
                  parameters:(NSDictionary*_Nullable)parameters
                     handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(message:parameters:handler:));

/// Authenticate with FIDO message, e.g. can be used for single-shot authentication.
/// - Parameter message: The FIDO message.
/// - Parameter parameters: Additional parameters passed during authentication.
/// - Parameter handler: The handler returns the response or an error.
///
- (void) authenticateWithMessage:(NSString*_Nonnull)message
                      parameters:(NSDictionary*_Nullable)parameters
                         handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(message:parameters:handler:));

// Headless

/// Check if an AAID is registered.
///
/// - Parameters:
/// - aaid: The authenticator AAID.
/// - username: The username or account name.
/// - Returns: True if the authenticator with the given aaid is registered for the user.
///
- (BOOL) isRegisteredAaid:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;

/// No UI registration.
///
/// This interface simplifies integration with JavaScript frameworks, like React Native, etc. The interface is limited to passcode and device biometrics and provides no additional UI.
/// The data, e.g. password, and aaid is passed to the register or authenticate method. It is up to the application to collect the data.
///
/// - Parameters:
///   - aaid: The authenticator AAID.
///   - username: The username or account name.
///   - data: The data, e.g. password. It is up to the application to collect the data.
///   - parameters: Additional parameters passed during registration.
///   - handler: The handler returns the response or an error.
- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
                     data:(id _Nullable)data
               parameters:(NSDictionary*_Nullable)parameters
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(aaid:username:data:parameters:handler:));

/// No UI device biometrics registration.
///
/// This interface simplifies integration with JavaScript frameworks, like React Native, etc. The interface is limited to device biometrics and provides no additional UI.
///
/// - Parameters:
///   - aaid: The authenticator AAID.
///   - username: The username or account name.
///   - parameters: Additional parameters passed during registration.
///   - handler: The handler returns the response or an error.
- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
               parameters:(NSDictionary*_Nullable)parameters
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(aaid:username:parameters:handler:));

/// No UI device biometrics authentication.
///
/// This interface simplifies integration with JavaScript frameworks, like React Native, etc. The interface is limited to device biometrics and provides no additional UI.
///
/// - Parameters:
///   - aaid: The authenticator AAID.
///   - username: The username or account name.
///   - description: A short description or reason..
///   - parameters: Additional parameters passed during authentication.
///   - handler: The handler returns the response or an error.
- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                  description:(NSString*_Nullable)description
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(aaid:username:description:parameters:handler:));

/// No UI authentication.
///
/// This interface simplifies integration with JavaScript frameworks, like React Native, etc. The interface is limited to passcode and device biometrics and provides no additional UI.
/// The data, e.g. password, and aaid is passed to the register or authenticate method. It is up to the application to collect the data.
///
/// - Parameters:
///   - aaid: The authenticator AAID.
///   - username: The username or account name.
///   - data: The data, e.g. password. It is up to the application to collect the data.
///   - description: A short description or reason.
///   - parameters: Additional parameters passed during authentication.
///   - handler: The handler returns the response or an error.
- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                         data:(id _Nullable)data
                  description:(NSString*_Nullable)description
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(aaid:username:data:description:parameters:handler:));


// UAF messages


/// Interface for passing raw protocol message without a Service API comms interface. 
///
/// The API takes a fido registration request and returns a fido response message.
///
/// - Parameters:
///   - uafMessage: The FIDO UAF registration message.
///   - completion: The handler returns the FIDO UAF response or an error.
- (void) registrationResponseWithMessage:(NSString*_Nonnull)uafMessage
                              completion:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))completion NS_SWIFT_NAME(registrationResponse(message:completion:));

/// Interface for passing raw protocol message without a Service API comms interface.
///
/// The API takes a fido authentication request and returns a fido response message.
///
/// - Parameters:
///   - uafMessage: The FIDO UAF authentication message.
///   - completion: The handler returns the FIDO UAF response or an error.
- (void) authenticationResponseWithMessage:(NSString *_Nonnull)uafMessage
                                completion:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))completion NS_SWIFT_NAME(authenticationResponse(message:completion:));

/// Interface for passing raw protocol message without a Service API comms interface.
///
/// The API takes a fido registration or authentication response message.
///
/// - Parameters:
///   - uafMessage: The FIDO UAF response message.
///   - responseCode: An error code or UAF_STATUS_CODE_OK (1200) if no error.
- (void) notifyWithMessage:(NSString *_Nonnull)uafMessage
                      code:(NSInteger)responseCode NS_SWIFT_NAME(notify(message:code:));

@end

