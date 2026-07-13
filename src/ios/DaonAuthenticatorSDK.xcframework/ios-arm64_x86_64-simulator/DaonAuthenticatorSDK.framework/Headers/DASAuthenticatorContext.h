//
//  DASAuthenticatorContext.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 3/9/17.
//  Copyright © 2017-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

#ifndef DASAuthenticatorContext_h
#define DASAuthenticatorContext_h

// Forward Declarations
@class DASAuthenticatorInfo;
@protocol DASMetadataControllerDelegate;
@protocol DASMetadataControllerProtocol;

// Blocks

/// Block that is used to notify a calling object that an operation has timed out.
typedef void (^DASTimeoutHandler) (void);

/// Block that is used to notify a calling object that an operation has completed.
/// - Parameter error: The error that occurred. A nil error should be treated as success.
typedef void (^DASCompletionHandler) (NSError *_Nullable error);

/// Block that is used to notify a calling object that an operation has completed and data collected from the user.
/// - Parameters:
///   - error: The error that occurred. A nil error should be treated as success.
///   - data: The collected data.
typedef void (^DASCompletionHandlerWithData) (NSError *_Nullable error, NSData *_Nullable data);

/// A protocol for classes that wish to provide controller functionality.
@protocol DASControllerProtocol <NSObject>

/// Terminates all current work where possible.
- (void) cancel;
@end

/// A protocol for classes that wish to ADoS data delivery functionality.
@protocol DASADoSControllerProtocol <DASControllerProtocol>

/// YES if reenrollment data is required along with authentication data.
@property (nonatomic, readonly) BOOL isReenrollRequired;

/// Converts an UIImage object into a UT8 encoded JSON object for delivery to the server.
/// - Parameter image: The UIImage to convert.
/// - Returns: The converted data.
- (NSData*_Nullable) dataForImage:(UIImage*_Nonnull)image;

/// Converts an UIImage object into a UT8 encoded JSON object for delivery to the server.
/// - Parameters:
///   - image: The UIImage to convert.
///   - quality: The jpg quality
///   - format: Either jpeg or png
/// - Returns: The converted data.
- (NSData*_Nullable) dataForImage:(UIImage*_Nonnull)image quality:(CGFloat)quality format:(NSString*_Nonnull)format;

/// Converts an UIImage object into a UT8 encoded JSON object for delivery to the server.
/// - Parameters:
///   - image: The UIImage to convert.
///   - quality: The jpg quality
///   - format: Either jpeg or png
/// - Returns: The converted data.
- (NSData*_Nullable) dataForPortraitImage:(UIImage*_Nonnull)image quality:(CGFloat)quality format:(NSString*_Nonnull)format;

/// Converts a Liveness template object into a UT8 encoded JSON object for delivery to the server.
/// - Parameter data: The template data to convert.
/// - Returns: The converted data.
- (NSData*_Nullable) dataForTemplate:(NSData*_Nonnull)data;

/// Converts a set of PCM audio samples into a UT8 encoded JSON object for delivery to the server.
/// - Parameter samples: The samples to convert.
/// - Returns: The converted data.
- (NSData*_Nullable) dataForVoiceSamples:(NSArray<NSData*>*_Nonnull)samples;

/// Converts a set of SRP attributes into a UT8 encoded JSON object for delivery to the server.
/// - Parameter srp: SRP data
/// - Returns: The converted data.
- (NSData*_Nullable) dataForPassword:(NSString*_Nonnull)srp;

/// Converts an NSArray of NSData objects into a UT8 encoded JSON object for delivery to the server.
/// - Parameter dataArray: The NSArray of NSData objects
/// - Returns: The converted data.
- (NSData*_Nullable) dataForDataArray:(NSArray<NSData*>*_Nonnull)dataArray;

/// Attempts to deliver the data to the server.
/// - Parameters:
///   - data: The data to be delivered to the server
///   - handler: A `DASCompletionHandler` object that will be called on success or failure of the delivery.
- (void) deliverData:(NSData*_Nonnull)data completionHandler:(DASCompletionHandler _Nonnull )handler;

@end

/// A protocol for classes that wish to provide local authentication functionality.
@protocol DASAppleBiometricsControllerProtocol <DASControllerProtocol>

/// Initiates a Local Authentication on the device using Touch ID or Face ID
/// - Parameters:
///   - reason: The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
///   - handler: A `DASCompletionHandler` object that will be called on success or failure.
- (void) performAuthenticationWithReason:(NSString*_Nonnull)reason completionHandler:(DASCompletionHandler _Nonnull)handler;

/// Initiates a Local Authentication on the device using Touch ID or Face ID
/// - Parameters:
///   - reason: The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
///   - handler: A `DASCompletionHandler` object that will be called on success or failure.
///   - fallbackTitle: Allows fallback button title customization. If set to empty string, the button will be hidden. A default title "Enter Password" is used when this property is left nil.
- (void) performAuthenticationWithReason:(NSString*_Nonnull)reason completionHandler:(DASCompletionHandler _Nonnull)handler fallback:(NSString*_Nullable)fallbackTitle;

/// Initiates a Local Authentication on the device using Touch ID or Face ID
/// - Parameters:
///   - reason: The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
///   - handler: A `DASCompletionHandler` object that will be called on success or failure.
///   - fallbackTitle: Allows fallback button title customization. If set to empty string, the button will be hidden. A default title "Enter Password" is used when this property is left nil.
///   - terminateOnFallback: If YES, the context will be automatically completed with a `DASAuthenticatorErrorFallback` error if fallback is selected and no error will be returned via the completionHandler (this is the default behaviour for the other overloads). If NO, the error will be returned via the completionHandler for the developer to handle.
- (void) performAuthenticationWithReason:(NSString*_Nonnull)reason
                       completionHandler:(DASCompletionHandler _Nonnull)handler
                                fallback:(NSString*_Nullable)fallbackTitle
                     terminateOnFallback:(BOOL)terminateOnFallback;

@end

/// A protocol for classes that wish to provide Touch ID functionality.
@protocol DASFingerprintControllerProtocol <DASAppleBiometricsControllerProtocol>
@end

/// A protocol for classes that wish to provide Face ID functionality.
@protocol DASFaceIdControllerProtocol <DASAppleBiometricsControllerProtocol>
@end

/// A protocol for classes that wish to implement their own concrete authenticator context.
/// The authenticator context is the central hub for all information and services which data collection view controllers may need to perform their tasks.
@protocol DASAuthenticatorContext <NSObject>
    
/// The location of a folder where view controllers can save temporary data.
/// The folder is generated at the following location: [NSTemporaryDirectory() stringByAppendingPathComponent:@"Authenticators"]
/// The folder is deleted at the beginning and end of capture.
@property (nonatomic, readonly) NSString * _Nullable tempDataDirectory;

/// YES if the context was instantiated in registration mode, NO for authentication mode.
@property (nonatomic, readonly) BOOL isRegistration;

/// YES if the context requires ADoS for registration and authentication.
@property (nonatomic, readonly) BOOL isADoSRequired;

/// YES if the context is in a success, failure, or cancellation state.
/// If isCaptureComplete is true, then any calls to complete or cancel methods will be ignored. To reset this flag, call `reset`.
@property (nonatomic, readonly) BOOL isCaptureComplete;

/// The current view controller being used for collection.
@property (nonatomic, weak) UIViewController * _Nullable activeViewController;

/// The current authenticator information.
@property (nonatomic, readonly) DASAuthenticatorInfo * _Nullable authenticatorInfo;

/// YES if the activeViewController should be automatically dismissed on capture completion.
@property (nonatomic) BOOL dismissViewControllerOnCompletion;

/// Dismisses the UI (if the client is not responsible) and terminates the capture process with the `DASAuthenticatorErrorCancelled` error.
- (void) cancelCapture;

/// Dismisses the UI (if the client is not responsible) and completes the capture process with success.
- (void) completeCapture;

/// Dismisses the UI (if the client is not responsible) and completes the capture process with success and some additional data.
/// - Parameter data: The additional data. Currently only used to provide the users input when performing Offline OTP.
- (void) completeCaptureWithTemporaryData:(NSData*_Nullable)data;

/// Dismisses the UI (if the client is not responsible) and completes the capture process with an `DASAuthenticatorError` error.
/// - Parameter error: The `DASAuthenticatorError` type that caused capture to fail.
- (void) completeCaptureWithError:(DASAuthenticatorError)error NS_SWIFT_NAME(completeCapture(error:));

/// Resets a completed (isCaptureComplete == true) context so that it can be used again.
/// This is typically only used when going backwards in a navigation stack to previously completed authenticators.
- (void) reset;

/// Logs the error and locks the authenticator if there have been too many attempts.
/// The following is the default behavior when using this method:
/// On each call, an attempt counter is incremented. If the attempt counter reaches 5 (override with "lock.max.attempts" extension) then:
/// 1) The attempt counter is reset
/// 2) The suspension counter is incremented
/// 3) The authenticator is temporarily locked for suspension counter * suspension milliseconds (Default: 30000, Override: "lock.suspend.init").
/// 
/// If a successful attempt is made once the temporary lock expires, the attempt and suspension counters will both reset to 0.
/// 
/// if failures continue, and the suspension counter reaches 3 (override with "lock.max.unlocks" extension), the authenticator will be permanently locked.
/// 
/// For each attempt, `reportAttemptWithErrorCode:score:` will be called to log the error.
/// 
/// If either a temporary or permanent lock occurs, the Daon Authenticator SDK will display an error, then dismiss the capture UI.
/// NOTE
/// This function should not be called for ADoS authenticators as the server will be in control of locking those authenticators.
/// - Parameters:
///   - errorCode: The error code that was reported.
///   - score: An optional score for reporting back with the error to the server.
/// - Returns: YES if the authenticator is now locked, NO otherwise.
- (BOOL) incrementFailuresAndCheckForLockWithErrorCode:(NSInteger)errorCode score:(NSNumber*_Nullable)score;

/// Logs the error and locks the authenticator if there have been too many attempts. Caller will control the display of any lock error.
/// As `incrementFailuresAndCheckForLockWithErrorCode:score:` except the caller will control the display of any lock error. Includes a call to `reportAttemptWithErrorCode:score:`, allows custom UIs to handle locking error presentation themselves.
/// - Parameters:
///   - errorCode: The error code that was reported.
///   - score: An optional score for potential reporting back with the error to the server.
///   - responseHandler: A `DASCompletionHandler` object that will be called on completion of the lock checks. If passed nil, authenticator is not locked.
- (void) incrementFailuresAndCheckForLockWithErrorCode:(NSInteger)errorCode
                                                 score:(NSNumber*_Nullable)score
                                       responseHandler:(DASCompletionHandler _Nonnull )responseHandler NS_SWIFT_NAME(incrementFailures(error:score:completion:));

/// Logs the error and locks the authenticator if there have been too many attempts. Caller will control the display of any lock error.
/// As `incrementFailuresAndCheckForLockWithErrorCode:score:` except the caller will control the display of any lock error.
/// - Parameters:
///   - error: The error that was reported.
///   - delegate: A `DASAuthenticatorDelegate` object.
- (NSError*_Nullable) incrementFailuresAndCheckForLockWithError:(NSError*_Nonnull)error
                                              delegate:(id<DASAuthenticatorDelegate>_Nullable)delegate;

- (void) resetLock;

/// Determine if there have been enough failed attempts to display a warning to the user.
/// - Returns: YES if the number of attempts is currently 3, otherwise NO.
- (BOOL) haveEnoughFailedAttemptsForWarning;

/// Uses the `DASAuthenticatorDelegate` object to report back any errors for potential delivery to a server for logging.
/// - Parameters:
///   - errorCode: The error code that was reported.
///   - score: An optional score for potential reporting back with the error to the server.
/// - Returns: YES if the current authenticator action should be aborted.
- (BOOL) reportAttemptWithErrorCode:(NSInteger)errorCode score:(NSNumber*_Nullable)score;

/// Displays a lock error and terminates capture once the user presses OK.
/// - Parameter lockError: The error to display
- (void) showLockError:(NSError*_Nonnull)lockError;

/// Register a `DASControllerProtocol` derived object with the context so that cleanup can be perform at the completion of capture.
/// - Parameter controller: The controller to register.
- (void) registerController:(id<DASControllerProtocol>_Nonnull)controller;

/// Determines whether a `DASControllerProtocol` derived object has been registered with the context.
/// - Parameter controller: The controller to check.
/// - Returns: YES if the controller is registered.
- (BOOL) isControllerRegistered:(id<DASControllerProtocol>_Nonnull)controller;

/// Instantiates a new `DASADoSControllerProtocol` derived object responsible for delivering ADoS data to a server.
/// - Returns: A new object conforming to the `DASADoSControllerProtocol` protocol.
- (id<DASADoSControllerProtocol>_Nullable) createStandardADoSController;

/// Instantiates a new `DASADoSControllerProtocol` derived object responsible for delivering ADoS SRP data to a server.
/// - Returns: A new object conforming to the `DASADoSControllerProtocol` protocol.
- (id<DASADoSControllerProtocol>_Nullable) createSrpADoSController;

/// Instantiates a new `DASFingerprintControllerProtocol` derived object responsible for providing access to Touch ID registration and authentication functionality.
/// - Returns: A new object conforming to the `DASFingerprintControllerProtocol` protocol.
- (id<DASFingerprintControllerProtocol>_Nullable) createFingerprintController;

/// Instantiates a new `DASFingerprintControllerProtocol` derived object responsible for providing access to Touch ID registration and authentication functionality. It provides a simpler path
/// to creating a custom UI for Touch ID as it encapsulates the logic surrounding calls to `incrementFailuresAndCheckForLockWithErrorCode:score:` and the "sdk.locking" extension so that your code does not need to.
/// - Parameter sdkWillHandleLockEvents: Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
/// `performAuthenticationWithReason:completionHandler:`.
/// - Returns: A new object conforming to the `DASFingerprintControllerProtocol` protocol.
- (id<DASFingerprintControllerProtocol>_Nullable) createFingerprintControllerWrapperWithSDKHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/// Instantiates a new `DASFaceIdControllerProtocol` derived object responsible for providing access to Face ID registration and authentication functionality.
/// - Returns: A new object conforming to the `DASFaceIdControllerProtocol` protocol.
- (id<DASFaceIdControllerProtocol>_Nullable) createFaceIdController;

/// Instantiates a new `DASFaceIdControllerProtocol` derived object responsible for providing access to Face ID registration and authentication functionality. It provides a simpler path
/// to creating a custom UI for Face ID as it encapsulates the logic surrounding calls to `incrementFailuresAndCheckForLockWithErrorCode:score:` and the "sdk.locking" extension so that your code does not need to.
/// - Parameter sdkWillHandleLockEvents: Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
/// `performAuthenticationWithReason:completionHandler:`.
/// - Returns: A new object conforming to the `DASFaceIdControllerProtocol` protocol.
- (id<DASFaceIdControllerProtocol>_Nullable) createFaceIdControllerWrapperWithSDKHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/// Instantiates a new `DASMetadataControllerProtocol` derived object responsible for providing access metadata scanning functionality.
/// - Parameters:
///   - delegate: An object implementing `DASMetadataControllerDelegate` that wishes to be notified of metadata scanning events from an `DASMetadataControllerProtocol` derived object.
///   - previewView: The UIView upon which the video preview will be drawn.
///   - metadataTypes: The list of metadata types that you wish to scan for.
/// - Returns: A new object conforming to the `DASMetadataControllerProtocol` protocol.
- (id<DASMetadataControllerProtocol>_Nullable) createMetadataControllerWithDelegate:(id<DASMetadataControllerDelegate>_Nonnull)delegate
                                                                        previewView:(UIView*_Nullable)previewView
                                                                      metadataTypes:(NSArray<AVMetadataObjectType>*_Nullable)metadataTypes;

/// Reads a value from the incoming extensions as a float.
/// - Parameters:
///   - key: The extensions key to read.
///   - defaultValue: The default value to return if the key is not present in the extensions.
/// - Returns: A float value read from the incoming extensions, or defaultValue.
- (float) extensionsFloatForKey:(NSString*_Nonnull)key defaultValue:(float)defaultValue;

/// Reads a value from the incoming extensions as an NSInteger.
/// - Parameters:
///   - key: The extensions key to read.
///   - defaultValue: The default value to return if the key is not present in the extensions.
/// - Returns: A NSInteger value read from the incoming extensions, or defaultValue.
- (NSInteger) extensionsIntForKey:(NSString*_Nonnull)key defaultValue:(NSInteger)defaultValue;

/// Reads a value from the incoming extensions as an NSString.
/// - Parameter key: The extensions key to read.
/// - Returns: A NSString value read from the incoming extensions, or nil.
- (NSString*_Nullable) extensionsStringForKey:(NSString*_Nonnull)key;

/// Reads a value from the incoming extensions as a BOOL.
/// - Parameters:
///   - key: The extensions key to read.
///   - defaultValue: The default value to return if the key is not present in the extensions.
/// - Returns: A BOOL value read from the incoming extensions, or defaultValue.
- (BOOL) extensionsBoolForKey:(NSString*_Nonnull)key defaultValue:(BOOL)defaultValue;

/// Gets the current set of extensions that will be returned via the `DASAuthenticatorDelegate` when registration or authentication completes.
/// - Returns: An NSDictionary mapping extension keys to values (both NSString).
- (NSDictionary*_Nullable)responseExtensions;

/// Sets the extensions that will be returned via the `DASAuthenticatorDelegate` when registration or authentication completes.
/// - Parameter extensions: An NSDictionary mapping extension keys to values (both NSString).
- (void) setResponseExtensions:(NSDictionary*_Nonnull)extensions;

/// Instantiates a new NSError object which encapsulates an `DASAuthenticatorError` type.
/// - Parameter errorCode: The `DASAuthenticatorError` type that has occurred.
/// - Returns: A new NSError object for the `DASAuthenticatorError` type.
- (NSError*_Nullable) errorForCode:(DASAuthenticatorError)errorCode;

/// Loads the localisation for a specific key.
/// - Parameter key: The localisation key. See the DAS-Localizable.strings file for available keys and values.
/// - Returns: The localized string.
- (NSString*_Nullable) localise:(NSString*_Nonnull)key;
  
@end

#endif /* DASAuthenticatorContext_h */
