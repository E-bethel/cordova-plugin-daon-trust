//
//  DASAuthenticatorBase.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/9/16.
//  Copyright © 2016-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

// Forward Declarations
@protocol DASAuthenticatorContext;
@protocol DASAuthenticatorDelegate;
@protocol DASCaptureControllerProtocol;
@protocol DASStorageProvider;
@class DASAuthenticatorCollectorInfo;
@class DASDefaultContext;

/// Categorizes the different UI actions that an authenticator can perform.
typedef NS_ENUM (NSUInteger, DASAuthenticatorUIAction)
{
    /// Default.
    DASAuthenticatorUIActionNone           = 0,
    /// Registration is in progress.
    DASAuthenticatorUIActionRegister       = 1,
    /// Authentication is in progress.
    DASAuthenticatorUIActionAuthenticate   = 2
};

/// A base class for all classes wishing to provide `DASAuthenticator` behavior.
@interface DASAuthenticatorBase : NSObject <DASAuthenticator>
{
    @protected
        /// The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
        id<DASAuthenticatorContext> context;

        /// The current action that is taking place.
        DASAuthenticatorUIAction currentUIAction;
    
        /// The `DASAuthenticatorDelegate` derived object that will be notified of authenticator events.
        id<DASAuthenticatorDelegate> currentDelegate;
    
        /// The `DASCaptureControllerProtocol` derived object that is currently executing custom client capture code.
        id<DASCaptureControllerProtocol> currentCaptureController;
    
        /// A `DASStorageProvider` derived object responsible for providing key management and storage capabilities.
        id<DASStorageProvider> storageProvider;

        /// The key name (`NSString`) that was provided to the `register:extensions:delegate:` method.
        NSString *currentKey;
    
        /// The key names (`NSString`) that were provided to the `authenticate:extensions:delegate:` method.
        NSArray *currentKeys;
    
        /// The time at which the current registration or authentication started.
        NSDate *currentStartTime;
    
        /// The `DASAuthenticatorSigningAlgorithm` type that was provided at instantiation.
        DASAuthenticatorSigningAlgorithm signingAlgorithm;
    
        /// Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
        BOOL invalidated;
    
        /// Whether or not the authenticator already had registration data available when `register:extensions:delegate:` was called. This will be the case when FIDO is being used with multiple accounts.
        BOOL hadDataBeforeRegister;
}

/// Instantiates a new `DASAuthenticatorBase` object.
/// - Parameter algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing the authenticators key.
/// - Returns: A new `DASAuthenticatorBase` object.
- (id) initWithAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Loads the authenticator icon.
/// - Parameter name: The name of the icon.
/// - Returns: A `UIImage` for the named image, or a default one.
- (UIImage*) loadIconWithName:(NSString*)name;

/// Removes all encrypted data files associated with this authenticator.
- (void) clearEnrolledData;

/// Determines if there are encrypted data files associated with this authenticator.
/// - Returns: `YES` if data is stored, otherwise `NO`.
- (BOOL) isDataStored;

/// Instantiates a new `DASAuthenticatorCollectorInfo` object with information for a specific registration / authenticator event.
///
/// The @link createCollectionUIWithContext:delegate: @/link method will pass through the following steps in order to determine which UIViewController should be stored in the new @link DASAuthenticatorCollectorInfo @/link object:
/// 1) Calls @link onViewControllerForFactor:context: @/link to see if the client has implemented the method and has provided a custom UIViewController.
/// 2) If #1 is nil, calls the newer @link onCollectionViewControllerForFactor:context: @/link method to see if the client has implemented the method and has provided a custom UIViewController and whether they will be responsible for presentation.
/// 3) If #2 is nil, checks to see if the client has provided a modified version of our default UIViewController for the current authenticator.
/// 4) If #3 is nil, uses our default UIViewController for the current authenticator.
///
/// - Parameters:
///   - context: The `DASAuthenticatorContext` object with which a custom view controller can register or authenticate.
///   - delegate: The `DASAuthenticatorDelegate` derived object that will be notified of authenticator events.
/// - Returns: A new `DASAuthenticatorCollectorInfo` object.
- (DASAuthenticatorCollectorInfo*) createCollectionUIWithContext:(id<DASAuthenticatorContext>)context delegate:(id<DASAuthenticatorDelegate>)delegate;

/// Attempts to present the UIViewController for the current authenticator.
/// - Discussion: Calls `createCollectionUIWithContext:delegate:` to create the `DASAuthenticatorCollectorInfo` object then either presents the contained UIViewController as the root of a UINavigationController or lets the client display it themselves.
- (void) attemptUIPresentation;

/// Empty method which should be implemented by all sub-classes to create the `DASAuthenticatorContext` for the concrete authenticator and begin presentation using `attemptUIPresentationt:`.
/// - Parameters:
///   - forRegistration: `YES` if the user is expected to register, `NO` if the user is expected to authenticate.
///   - extensions: An `NSDictionary` mapping extension keys to values (Both `NSString`).
///   - keys: An `NSDictionary` mapping `DASAuthenticatorFactor` types (in `NSNumber` objects) to an `NSArray` containing the names of all keys required.
- (void) presentCollectionUIWithRegistration:(BOOL)forRegistration extensions:(NSDictionary*)extensions keys:(NSArray*)keys;

/// Builds the response extensions and provides them to either `onRegisterComplete:extensions:keys:` or `onAuthenticateComplete:keys:` to complete the current registration or authentication.
- (void) onCollectionCompletion;

/// Completes the current registration or authentication with an error by calling `onFailed:code:message:`.
/// - Parameter errorObject: The `NSError` that caused the failure. If error code is `DASAuthenticatorErrorCancelled` and registration is in progress, any newly registered keys will be cleaned up (unregistered).
- (void) onCollectionFailureWithErrorObject:(NSError*)errorObject;
    
@end
