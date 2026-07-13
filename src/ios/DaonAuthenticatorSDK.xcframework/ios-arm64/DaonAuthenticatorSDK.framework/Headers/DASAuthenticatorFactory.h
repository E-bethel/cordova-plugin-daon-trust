//
//  DASAuthenticatorFactory.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/8/16.
//  Copyright © 2016-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

@protocol DASAuthenticator;
@protocol DASMultiAuthenticatorContext;
@protocol DASStorageProvider;

/// Provides a number of class factory methods for determining supported authenticator types, and creating instances of them.
@interface DASAuthenticatorFactory : NSObject

/// Provides an NSArray of all currently supported authenticator types.
/// - Returns: An NSArray containing NSNumber objects which hold a `DASAuthenticatorFactor` type.
+ (NSArray*) getSupportedAuthenticators;

/// Provides an NSArray of all currently supported authenticator types.
/// - Parameter extensions: An NSDictionary mapping extension keys to values (Both NSString) that may have impact on the availability of certain authenticators. E.g "com.daon.sdk.embedded.face".
/// - Returns: An NSArray containing NSNumber objects which hold a `DASAuthenticatorFactor` type.
+ (NSArray*) getSupportedAuthenticatorsWithExtensions:(NSDictionary*)extensions;

/// Instantiates a new `DASAuthenticator` object which supports a specific type of registration / authentication.
/// - Parameter factor: The requested factor (`DASAuthenticatorFactor`) type.
/// - Returns: A new `DASAuthenticator` object supporting the specified factor type.
+ (id<DASAuthenticator>) getAuthenticator:(DASAuthenticatorFactor)factor;

/// Instantiates a new `DASAuthenticator` object which supports a specific type of registration / authentication and signing algorithm.
/// - Parameters:
///   - factor: The requested factor (`DASAuthenticatorFactor`) type.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type to use when creating / accessing keys.
/// - Returns: A new `DASAuthenticator` object supporting the specified factor type.
+ (id<DASAuthenticator>) getAuthenticator:(DASAuthenticatorFactor)factor usingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Instantiates a new `DASMultiAuthenticator` object which supports registration / authentication of a group or groups of authenticators.
/// - Parameter policyType: The requested policy (`DASAuthenticatorPolicyType`) type.
/// - Returns: A new `DASMultiAuthenticator` object supporting the specified policy type.
+ (id<DASMultiAuthenticator>) getMultiAuthenticatorForPolicyType:(DASAuthenticatorPolicyType)policyType;

/// Instantiates a new `DASMultiAuthenticator` object which supports registration / authentication of a group or groups of authenticators with a specific signing algorithm.
/// - Parameters:
///   - policyType: The requested policy (`DASAuthenticatorPolicyType`) type.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type to use when creating / accessing keys.
/// - Returns: A new `DASMultiAuthenticator` object supporting the specified policy type.
+ (id<DASMultiAuthenticator>) getMultiAuthenticatorForPolicyType:(DASAuthenticatorPolicyType)policyType usingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Instantiates a new `DASAuthenticatorContext` object which provides a central hub for all information and services required for registration / authentication of an individual authenticator.
/// - Parameters:
///   - authenticator: The authenticator (`DASAuthenticator`) with which to create the context for.
///   - isRegistration: Whether or not we are registering or authenticating.
///   - isADoS: Whether or not to send data to a server for registration / authentication.
///   - requestExtensions: An NSDictionary mapping extension name to extension value (Both NSString).
///   - requestKeys: An NSArray containing the key names to use during registration or authentication.
///   - dismissUIOnCompletion: Whether or not to dismiss the authenticators view controller automatically once registration / authentication is complete.
///   - handler: A `DASCompletionHandlerWithData` object that will be called on success or failure of the registration / authentication.
/// - Returns: A new `DASAuthenticatorContext` object configured to support the selected authenticator.
+ (id<DASAuthenticatorContext>) getAuthenticatorContextForAuthenticator:(id<DASAuthenticator>)authenticator
                                                         isRegistration:(BOOL)isRegistration
                                                                 isADoS:(BOOL)isADoS
                                                      requestExtensions:(NSDictionary*)requestExtensions
                                                            requestKeys:(NSArray*)requestKeys
                                                  dismissUIOnCompletion:(BOOL)dismissUIOnCompletion
                                                      completionHandler:(DASCompletionHandlerWithData)handler;

/// Instantiates a new `DASAuthenticatorContext` object specifically for accessing context functionality without a specific authenticator. isRegistration will default to true.
/// - Returns: A new `DASAuthenticatorContext` object.
+ (id<DASAuthenticatorContext>) getSimpleContext;

/// Instantiates a new `DASMultiAuthenticatorContext` object which provides a central hub for all information and services required for registration / authentication of an set of authenticators.
/// - Parameters:
///   - authenticators: The selected authenticators in an NSDictionary with a mapping of NSNumber objects holding a `DASAuthenticatorFactor` type to their associated `DASAuthenticator` object.
///   - policyType: The `DASAuthenticatorPolicyType` type which will prescribe the way in which the authenticators are presented to the user for selection.
///   - factorsAndKeys: An NSArray of authenticator groups, each group made up of an NSDictionary that maps `DASAuthenticatorFactor` types (in a NSNumber object) to an NSArray of keys (NSString objects).
///   - factorsAndExtensions: An NSDictionary that maps `DASAuthenticatorFactor` types (in a NSNumber object) to an NSDictionary mapping extension name to extension value (Both NSString).
///   - uiCustomizationDelegate: An `DASAuthenticatorDelegate` derived object that will be notified of authenticator events specific to UI customization.
///   - isRegistration: Whether or not we are registering or authenticating the set of authenticators.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing an authenticators key.
///   - filterNonUIAuthenticators: Whether or not to filter out Non-ui authenticators when performing an DASAuthenticatorPolicyTypeOR policy. Default is YES.
///   - completionHandler: A block object that will be called on success of the registration / authentication for a set of authenticators.
///   - failureHandler: A block object that will be called on failure of the registration / authentication for a set of authenticators.
/// - Returns: A new `DASMultiAuthenticatorContext` object configured to support the selected select of authenticators.
+ (id<DASMultiAuthenticatorContext>) getMultiAuthenticatorContextForAuthenticators:(NSDictionary*)authenticators
                                                                            policy:(DASAuthenticatorPolicyType)policyType
                                                                    factorsAndKeys:(NSArray<NSDictionary*>*)factorsAndKeys
                                                                 requestExtensions:(NSDictionary<NSNumber*, NSDictionary*>*)factorsAndExtensions
                                                           uiCustomizationDelegate:(id<DASAuthenticatorDelegate>)uiCustomizationDelegate
                                                                    isRegistration:(BOOL)isRegistration
                                                                  signingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm
                                                         filterNonUIAuthenticators:(BOOL)filterNonUIAuthenticators
                                                                      onCompletion:(void (^) (NSDictionary* extensions, NSDictionary* keys))completionHandler
                                                                         onFailure:(void (^) (id<DASAuthenticator> authenticator, DASAuthenticatorError error))failureHandler;

/// Instantiates a new `DASADoSControllerProtocol` derived object responsible for delivering ADoS data to a server.
/// - Parameters:
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
///   - authenticator: The `DASAuthenticator` authenticator to be used.
///   - extensions: The incoming request extensions.
///   - keys: The incoming request keys.
///   - startTime: The time at which the authenticator process started.
/// - Returns: A new object conforming to the `DASADoSControllerProtocol` protocol.
+ (id<DASADoSControllerProtocol>) getStandardADoSControllerWithContext:(id<DASAuthenticatorContext>)context
                                                         authenticator:(id<DASAuthenticator>)authenticator
                                                     requestExtensions:(NSDictionary*)extensions
                                                           requestKeys:(NSArray*)keys
                                                             startTime:(NSDate*)startTime;

/// Instantiates a new `DASADoSControllerProtocol` derived object responsible for delivering ADoS SRP data to a server.
/// - Parameters:
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
///   - authenticator: The `DASAuthenticator` authenticator to be used.
///   - extensions: The incoming request extensions.
///   - keys: The incoming request keys.
///   - startTime: The time at which the authenticator process started.
/// - Returns: A new object conforming to the `DASADoSControllerProtocol` protocol.
+ (id<DASADoSControllerProtocol>) getSrpADoSControllerWithContext:(id<DASAuthenticatorContext>)context
                                                    authenticator:(id<DASAuthenticator>)authenticator
                                                requestExtensions:(NSDictionary*)extensions
                                                      requestKeys:(NSArray*)keys
                                                        startTime:(NSDate*)startTime;

/// Instantiates a new `DASFingerprintControllerProtocol` derived object responsible for providing access to Touch ID registration and authentication functionality.
/// - Parameter context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
/// - Returns: A new object conforming to the `DASFingerprintControllerProtocol` protocol.
+ (id<DASFingerprintControllerProtocol>) getFingerprintControllerWithContext:(id<DASAuthenticatorContext>)context;

/// Instantiates a new `DASFingerprintControllerProtocol` derived object responsible for providing access to Touch ID registration and authentication functionality. It provides a simpler path
/// to creating a custom UI for Touch ID as it encapsulates the logic surrounding calls to `incrementFailuresAndCheckForLockWithErrorCode:score:` and the "sdk.locking" extension so that your code does not need to.
/// - Parameters:
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
///   - sdkWillHandleLockEvents: Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
/// `performAuthenticationWithReason:completionHandler:`.
/// - Returns: A new object conforming to the `DASFingerprintControllerProtocol` protocol.
+ (id<DASFingerprintControllerProtocol>) getFingerprintControllerWrapperWithContext:(id<DASAuthenticatorContext>)context
                                                              sdkHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/// Instantiates a new `DASFaceIdControllerProtocol` derived object responsible for providing access to Face ID registration and authentication functionality.
/// - Parameter context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
/// - Returns: A new object conforming to the `DASFaceIdControllerProtocol` protocol.
+ (id<DASFaceIdControllerProtocol>) getFaceIdControllerWithContext:(id<DASAuthenticatorContext>)context;

/// Instantiates a new `DASFaceIdControllerProtocol` derived object responsible for providing access to Face ID registration and authentication functionality. It provides a simpler path
/// to creating a custom UI for Face ID as it encapsulates the logic surrounding calls to `incrementFailuresAndCheckForLockWithErrorCode:score:` and the "sdk.locking" extension so that your code does not need to.
/// - Parameters:
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
///   - sdkWillHandleLockEvents: Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
/// `performAuthenticationWithReason:completionHandler:`.
/// - Returns: A new object conforming to the `DASFaceIdControllerProtocol` protocol.
+ (id<DASFaceIdControllerProtocol>) getFaceIdControllerWrapperWithContext:(id<DASAuthenticatorContext>)context
                                                    sdkHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/// Instantiates a new `DASMetadataControllerProtocol` derived object responsible for providing access metadata scanning functionality.
/// - Parameters:
///   - delegate: An object implementing `DASMetadataControllerDelegate` that wishes to be notified of metadata scanning events from an `DASMetadataControllerProtocol` derived object.
///   - previewView: The UIView upon which the video preview will be drawn.
///   - metadataTypes: The list of metadata types that you wish to scan for.
/// - Returns: A new object conforming to the `DASMetadataControllerProtocol` protocol.
+ (id<DASMetadataControllerProtocol>) getMetadataControllerWithDelegate:(id<DASMetadataControllerDelegate>)delegate
                                                            previewView:(UIView*)previewView
                                                          metadataTypes:(NSArray<AVMetadataObjectType>*)metadataTypes;

/// Instantiates a new `DASStorageProvider` derived object responsible for providing key management and storage capabilities.
/// - Returns: A new object conforming to the `DASStorageProvider` protocol.
+ (id<DASStorageProvider>) getStorageProvider;

@end
