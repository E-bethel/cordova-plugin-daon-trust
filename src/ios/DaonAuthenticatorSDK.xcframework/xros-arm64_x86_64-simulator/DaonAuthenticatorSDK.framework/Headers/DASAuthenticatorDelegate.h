//
//  DASAuthenticatorDelegate.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/11/16.
//  Copyright © 2016-25 Daon. All rights reserved.
//

#ifndef DASAuthenticatorDelegate_h
#define DASAuthenticatorDelegate_h

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

// Forward Declarations
@protocol DASAuthenticatorContext;
@protocol DASCaptureControllerProtocol;
@protocol DASMultiAuthenticatorContext;
@class DASAuthenticatorCollectorInfo;
@class DASMultiAuthenticatorCollectorInfo;

// Blocks

/// Block that is used to notify a calling object that ADoS submission has completed.
/// - Parameters:
///   - error: An error that came back from the server, or from the transmission process. If a nil is returned then it should be treated as success.
///   - data: Any additional data returned from the server, such as SRP parameters.
typedef void (^ADoSCompletionHandler) (NSError * _Nullable error, NSDictionary * _Nullable data);

/// A protocol for classes that wish to be notified of DASAuthenticator events.
@protocol DASAuthenticatorDelegate <NSObject>

/// Used to notify a conforming object that a register operation has completed successfully.
/// - Parameters:
///   - authenticator: The active `DASAuthenticator` object when register completed.
///   - extensions: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into register as well as any completion extensions.
///   - keys: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to an NSArray containing the names of all keys just registered.
- (void) onRegisterComplete:(nonnull id<DASAuthenticator>)authenticator
                 extensions:(nonnull NSDictionary*)extensions
                       keys:(nonnull NSDictionary*)keys;

/// Used to notify a conforming object that an authenticate operation has completed successfully.
/// - Parameters:
///   - extensions: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into authenticate as well as any completion extensions.
///   - keys: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to an NSArray containing the names of all keys just authenticated.
- (void) onAuthenticateComplete:(nonnull NSDictionary*)extensions
                           keys:(nonnull NSDictionary*)keys;

/// Used to notify a conforming object that the current operation has failed and capture has been terminated.
/// - Parameters:
///   - authenticator: The active `DASAuthenticator` object when the operation failed.
///   - code: The error code that was raised.
///   - message: The message associated with the error that was raised.
- (void) onFailed:(nullable id<DASAuthenticator>)authenticator
             code:(NSInteger)code
          message:(nonnull NSString*)message;

/// Used to notify a conforming object that the current authentication operation has failed but the user will be allowed to retry.
/// - Parameters:
///   - authenticator: The active authenticator when the operation failed.
///   - info: An NSDictionary containing additional information related to the failure (lockStatus, errorCode, attempt, attemptsRemaining).
/// - Returns: YES if the authenticator should abort due to too many errors.
- (BOOL) onAttemptFailed:(nonnull id<DASAuthenticator>)authenticator
                    info:(nonnull NSDictionary*)info;

/// Used to notify a conforming object that ADoS data has been collected and should be delivered to the server for processing.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type for which data has been collected.
///   - data: The collected data, encoded and compressed for transmission.
///   - extensions: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into the current operation as well as any completion extensions.
///   - keys: An NSDictionary mapping `DASAuthenticatorFactor` types (in NSNumber objects) to an NSArray containing the names of all keys just registered.
///   - handler: A `ADoSCompletionHandler` block object that will be called once ADoS processing is complete.
- (void) onDataCollectionCompleteForFactor:(DASAuthenticatorFactor)factor
                             collectedData:(nullable NSArray<NSData*>*)data
                                extensions:(nonnull NSDictionary*)extensions
                                      keys:(nonnull NSDictionary*)keys
                         onAnalysisComplete:(nullable ADoSCompletionHandler )handler;

@optional

/// Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own UI.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type for which data will be collected.
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
/// - Returns: A custom UIViewController, or nil if the default view controller provided by the SDK should be used.
- (nullable UIViewController*) onViewControllerForFactor:(DASAuthenticatorFactor)factor context:(nonnull id<DASAuthenticatorContext>)context;

/// Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own UI.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type for which data will be collected.
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
/// - Returns: A `DASAuthenticatorCollectorInfo` object containing a reference to the custom UIViewController and whether or not the caller will be responsible for presentation of it. If nil is returned, the default view controller provided by the SDK will be used.
- (nullable DASAuthenticatorCollectorInfo*) onCollectionViewControllerForFactor:(DASAuthenticatorFactor)factor context:(nonnull id<DASAuthenticatorContext>)context;

/// Used to notify a conforming object that data collection is about to begin for a specific grouped policy type, and that if they wish they can provide their own UI.
/// - Parameters:
///   - policyType: The `DASAuthenticatorPolicyType` type which will prescribe the way in which the authenticators are presented to the user for selection.
///   - context: The `DASMultiAuthenticatorContext` object with which a custom view controller can determine which authenticators to display and how to authenticate them.
/// - Returns: A `DASMultiAuthenticatorCollectorInfo` object containing a reference to the custom UIViewController and whether or not the caller will be responsible for presentation of it. If nil is returned, the default view controller provided by the SDK will be used.
- (nullable DASMultiAuthenticatorCollectorInfo*) onCollectionViewControllerForPolicyType:(DASAuthenticatorPolicyType)policyType context:(nonnull id<DASMultiAuthenticatorContext>)context;

/// Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own capture controller.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type for which data will be collected.
///   - context: The `DASAuthenticatorContext` object with which a capture controller can register or authenticate.
/// - Returns: A `DASCaptureControllerProtocol` object whose execute method will be called to begin collection.
- (nullable id<DASCaptureControllerProtocol>) onCaptureControllerForFactor:(DASAuthenticatorFactor)factor
                                                                   context:(nonnull id<DASAuthenticatorContext>)context;

/// Used to notify a conforming object that data collection is about to begin for a specific grouped policy type, and that if they wish they can provide their own capture controller.
/// - Parameters:
///   - policy: The `DASAuthenticatorPolicyType` type which dictates how selection should occur.
///   - context: The `DASMultiAuthenticatorContext` object with which a capture controller can create single authenticator `DASAuthenticatorContext` objects.
/// - Returns: A `DASCaptureControllerProtocol` object whose execute method will be called to begin collection.
- (nullable id<DASCaptureControllerProtocol>) onCaptureControllerForPolicy:(DASAuthenticatorPolicyType)policy
                                                                   context:(nonnull id<DASMultiAuthenticatorContext>)context;

@end

#endif /* DASAuthenticatorDelegate_h */
