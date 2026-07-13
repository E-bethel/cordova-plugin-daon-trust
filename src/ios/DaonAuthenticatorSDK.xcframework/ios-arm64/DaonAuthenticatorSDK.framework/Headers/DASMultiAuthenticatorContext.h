//
//  DASMultiAuthenticatorContext.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 4/28/17.
//  Copyright © 2017-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

#ifndef DASMultiAuthenticatorContext_h
#define DASMultiAuthenticatorContext_h

// Forward Declarations
@class DASAuthenticatorInfo;

// Blocks

/// Block that is used to notify a calling object that registration or authentication has completed successfully.
/// - Parameter factor: The `DASAuthenticatorFactor` type that was completed.
typedef void (^DASMultiAuthenticatorContextCompletionHandler) (DASAuthenticatorFactor factor);

/// Block that is used to notify a calling object that registration or authentication has failed.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type that failed.
///   - error: The `DASAuthenticatorError` type that caused registration or authentication to fail.
typedef void (^DASMultiAuthenticatorContextFailureHandler) (DASAuthenticatorFactor factor, DASAuthenticatorError error);

/// A protocol for classes that wish to implement their own concrete Multi-Authenticator context.
/// 
/// The Multi-Authenticator context is the central hub for all information and services relating to registration and authenticator of a group or groups of authenticators.
@protocol DASMultiAuthenticatorContext <NSObject>

/// The current view controller being used for collection.
@property (nonatomic) UIViewController *activeViewController;

/// The current factor (`DASAuthenticatorFactor`) being collected.
/// 
/// Typically this is called from the current Multi-Authenticator view controller to alert the context when the user has switched between different authenticators.
@property (nonatomic) DASAuthenticatorFactor activeFactor;

/// The ordered priority of authenticators, as configured using the "com.daon.sdk.authenticator.precedence" extension. Each element being an NSNumber object containing a value from the `DASAuthenticatorFactor` enum.
@property (nonatomic, readonly) NSArray *authenticatorPrecedence;

/// YES if the context is in a success, failure, or cancellation state.
@property (nonatomic, readonly) BOOL isCaptureComplete;

/// Dismisses the UI (if the client is not responsible) and terminates the capture process with the `DASAuthenticatorErrorCancelled` error.
- (void) cancelCapture;

/// Dismisses the UI (if the client is not responsible) and completes the capture process with success.
- (void) completeCapture;

/// Dismisses the UI (if the client is not responsible) and completes the capture process with a `DASAuthenticatorError` error.
/// - Parameter error: The `DASAuthenticatorError` type that caused capture to fail.
- (void) completeCaptureWithError:(DASAuthenticatorError)error;

/// Provides access to the set of authenticator groups that the context was instantiated with.
/// 
/// For the `DASAuthenticatorPolicyTypeAND` and `DASAuthenticatorPolicyTypeOR` policy types, the top level of the NSArray should only contain one item. 
/// For the `DASAuthenticatorPolicyTypeMultipleChoice` policy type there will be multiple items (authenticator groups) as specified by your server policy.
/// - Returns: An NSArray where each element represents an authenticator group as an NSArray of `DASAuthenticatorInfo` objects.
- (NSArray<NSArray<DASAuthenticatorInfo*>*>*) requestedAuthenticatorGroups;

/// Instantiates a ready for presentation UIViewController for a specific factor. Completion and failure handlers provide event handling.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type to instantiate a view controller for.
///   - completionHandler: The block that will be executed once data completion for the authenticator completes successfully.
///   - failureHandler: The block that will be executed once data completion for the authenticator completes with an error.
/// - Returns: A new UIViewController instance ready for presentation.
- (UIViewController*) authenticatorViewControllerForFactor:(DASAuthenticatorFactor)factor
                                         completionHandler:(DASMultiAuthenticatorContextCompletionHandler)completionHandler
                                            failureHandler:(DASMultiAuthenticatorContextFailureHandler)failureHandler;

/// Instantiates a `DASAuthenticatorContext` object for registration/authentication of a specific factor. Completion and failure handlers provide event handling.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type to instantiate a `DASAuthenticatorContext` object for.
///   - completionHandler: The block that will be executed once data completion for the context completes successfully.
///   - failureHandler: The block that will be executed once data completion for the context completes with an error.
/// - Returns: A new `DASAuthenticatorContext` object instance ready for use.
- (id<DASAuthenticatorContext>) authenticatorContextForFactor:(DASAuthenticatorFactor)factor
                                            completionHandler:(DASMultiAuthenticatorContextCompletionHandler)completionHandler
                                               failureHandler:(DASMultiAuthenticatorContextFailureHandler)failureHandler;

/// Returns whether or not the Multi-Authenticator contains at least one Authenticator that has been invalidated (had its keys removed).
/// 
/// Invalidation currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
/// - Returns: Whether or not the Multi-Authenticator contains at least one Authenticator that has been invalidated.
- (BOOL) hasInvalidatedFactors;

/// Resets a completed (isCaptureComplete == true) individual factors context so that it can be used again.
/// 
/// This is typically only used when going backwards in a navigation stack to previously completed authenticators.
- (void) resetActiveFactorContext;

/// Instantiates a new NSError object which encapsulates a `DASAuthenticatorError` type.
/// - Parameter errorCode: The `DASAuthenticatorError` type that has occurred.
/// - Returns: A new NSError object for the `DASAuthenticatorError` type.
- (NSError*) errorForCode:(DASAuthenticatorError)errorCode;

/// Loads the localisation for a specific key.
/// - Parameter key: The localisation key. See the DAS-Localizable.strings file for available keys and values.
/// - Returns: The localised string.
- (NSString*) localise:(NSString*)key;

@end

#endif /* DASMultiAuthenticatorContext_h */
