
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <DaonFIDOSDK/IXUAFAuthenticator.h>
#import <DaonFIDOSDK/IXUAFAccount.h>
#import <DaonFIDOSDK/IXUAFTransaction.h>
#import <DaonFIDOSDK/IXUAFOperation.h>

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticatorCollectorInfo.h>
#import <DaonAuthenticatorSDK/DASCaptureControllerProtocol.h>

/// SDK delegate for controlling registration and authentication behaviour, including UI customization.
/// 
/// The `IXUAFDelegate` delegate can be used to customize the behavior of the SDK. Optional methods of the protocol allow the delegate to manage authenticators, transactions, UI flow, and perform other actions.
///
/// ```swift tab="Swift"
/// let fido : IXUAF(service: MyService())
/// fido.delegate = self
/// ```
///
/// ```objective-c tab="Objective-C"
///
/// fido = [[IXUAF alloc] initWithService:[MyService new]];
/// fido.delegate = self;
/// ```
///
/// > Note: When using the `IXUAF` API, all delegate methods have a default implementation.

@protocol IXUAFDelegate <NSObject>

@optional


/// Called before registration or authentication with a list of allowed authenticators for the current request.
///
/// This delegate method is called when the SDK has determined all the available authenticators for a given operation and policy. Only un-registered authenticators will be returned for registration and only registered authenticators will be returned for authentication. This method is optional and if not implemented, the first authenticator will be used.
///
/// Authenticators are provided as an array of authenticator groups. A group is again an array of authenticators. If a group has more than one authenticator it corresponds to an 'AND' verification.
///
/// Return nil if you want to handle the authenticator selection yourself. Returning a list of authenticators will invoke the authenticator choice view controller. If the authenticator selection is handled within the app (for example, return nil), you will have to call the verifyWithAuthenticator method on the operation to start the verification process when an authenticator has been selected.
///
/// Authenticators can be removed from the list for additional filtering. Return the list of authenticators that should be available for authentication or registration.
///
/// - Parameter operation: The current operation.
/// - Parameter authenticators: The list of allowed authenticators.
/// - Returns: All or a subset of authenticators.

- (NSArray<NSArray<IXUAFAuthenticator*>*> * _Nullable ) operation:(id<IXUAFOperation> _Nonnull)operation willAllowAuthenticators:(NSArray<NSArray<IXUAFAuthenticator*>*> * _Nonnull)authenticators;


/// Called after authentication with a list of available accounts. Use the operation object to choose an account for signing.
///
/// This method is called when a registered authenticator has performed a successful verification, and there is more than one account (or key) associated with the authenticator. This method is optional and by default the first account will be selected for signing. Otherwise, you will have to call IXUAFOperation signWithAccount.
///
/// - Parameter operation: The current operation.
/// - Parameter accounts: The list of available accounts.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation canUseAccounts:(NSArray<IXUAFAccount*> * _Nonnull)accounts;


/// Called when an account was selected.
///
/// - Parameter operation: The current operation.
/// - Parameter account: The selected account.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation didSelectAccount:(IXUAFAccount* _Nonnull)account ;


/// Called after authentication if a transaction confirmation is required.
///
///This method is called in response to a FIDO transaction confirmation. The user will have to confirm the transaction details, which can be either a text or an image. To accept or confirm a transaction, call the IXUAFTransaction accept.
///
/// - Parameter operation: The current operation.
/// - Parameter transaction: The transaction object. See IXUAFTransaction.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation shouldDisplayTransaction:(IXUAFTransaction* _Nonnull)transaction ;


/// Called during registration or authentication if an operation requires additional validation. Tthis is only used for ADoS to submit the data to the server.
///
/// > Note: You do not need to implement this method when using the IXUAF API. If using the low-level DaonFIDO API, make sure to call notifyWithResult on the operation with the response from the server.
///
/// - Parameter operation: The current operation.
/// - Parameter message: The FIDO message.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation shouldVerifyMessage:(NSString* _Nonnull)message;


/// Signed fido message
///
/// Called during registration or authentication when response is ready for the server
///
/// - Parameter operation: The current operation.
/// - Parameter message: The FIDO message.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation 
    didSignMessage:(NSString* _Nullable)message;


/// Authentication attempt failed (non ADOS only)
///
/// Called when an authentication attempt fails.
///
/// - Parameter operation: The current operation.
/// - Parameter info: The attempt info.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation authenticationAttemptFailedWithInfo:(NSDictionary<NSString*, id>* _Nonnull)info;


/// Authentication attempt failed (all authenticators
///
/// Called when an authentication attempt fails.
///
/// - Parameter operation: The current operation.
/// - Parameter info: The attempt info. Max attempts and remaining attempts before being locked.

- (void) operation:(id<IXUAFOperation> _Nonnull)operation attemptFailedWithInfo:(NSDictionary<NSString*, id>* _Nonnull)info;


/// Allow multiple choice authentication
///
/// Enable multiple choice authentication. This requires a specific set of policies.

- (BOOL) shouldAllowMultipleChoiceAuthentication;


// UI Customization



/// Called when an authenticator for a given User Verification needs a view controller.
///
/// This method allows you to provide your own authenticator view controller to display for user verification.
///
/// The available verification methods are as follows:
///
/// | **Method**                | **Screen**        |
/// | - | - |
/// | USER\_VERIFY\_FINGERPRINT | Fingerprint       |
/// | USER\_VERIFY\_PASSCODE    | PIN / Passcode    |
/// | USER\_VERIFY\_VOICEPRINT  | Voice             |
/// | USER\_VERIFY\_FACEPRINT   | Face / Face ID    |
///
/// - Parameter operation: The current operation.
/// - Parameter method: The FIDO User Verification method/type.
/// - Parameter context: The authenticator context.
/// - Returns: A view controller for a User Verification type
///
- (DASAuthenticatorCollectorInfo* _Nullable)  operation:(id<IXUAFOperation> _Nonnull)operation
   shouldUseCollectionViewControllerForUserVerification:(NSInteger)method
                                                context:(_Nonnull id<DASAuthenticatorContext>)context;



/// Called when a containing AND/OR view controller is needed.
///
/// This method allows you to provide your own multi authenticator view controller for display.
///
/// The available multi authenticator policy types are as follows:
///
/// | Type           | Description                                                         |
/// | - | - |
/// | AND            | A view controller that supports AND verification.                   |
/// | OR             | A view controller that supports OR verification, for example, tabs. |
/// | MultipleChoice | A view controller that adjusts based on the user selection.         |
///
/// - Parameter operation: The current operation.
/// - Parameter type: The policy type, e.g. AND/OR.
/// - Parameter context: The authenticator context.
/// - Returns: A view controller for an authenticator type.
///
- (DASMultiAuthenticatorCollectorInfo* _Nullable) operation:(id<IXUAFOperation> _Nonnull)operation
                shouldUseViewControllerForAuthenticatorType:(DASAuthenticatorPolicyType)type
                                                    context:(_Nonnull id<DASMultiAuthenticatorContext>)context;


/// Called when an authenticator for a given User Verification needs a capture controller.
///
/// Used to notify a conforming object that data collection is about to begin for a specific verification method, and that if they wish they can provide their own capture controller to take over the process of data capture.
///
/// The available verification methods are as follows:
///
/// | **Method**                | **Screen**        |
/// | - | - |
/// | USER\_VERIFY\_FINGERPRINT | Fingerprint       |
/// | USER\_VERIFY\_PASSCODE    | PIN / Passcode    |
/// | USER\_VERIFY\_VOICEPRINT  | Voice             |
/// | USER\_VERIFY\_FACEPRINT   | Face / Face ID    |
///
/// - Parameter operation: The current operation.
/// - Parameter method: The FIDO User Verification method/type.
/// - Parameter context: The authenticator context.
/// - Returns: A capture controller for a User Verification type.
///
- (id<DASCaptureControllerProtocol> _Nullable)  operation:(id<IXUAFOperation> _Nonnull)operation
            shouldUseCaptureControllerForUserVerification:(NSInteger)method
                                                  context:(_Nonnull id<DASAuthenticatorContext>)context;


/// Called when a containing AND/OR capture controller is needed.
/// 
/// Used to notify a conforming object that data collection is about to begin for a specific grouped policy type, and that if they wish they can provide their own capture controller to take over the process of data capture..
///
/// - Parameter operation: The current operation.
/// - Parameter type: The policy type, e.g. AND/OR.
/// - Parameter context: The authenticator context.
/// - Returns: A capture controller for a policy type.
///
- (id<DASCaptureControllerProtocol> _Nullable) operation:(id<IXUAFOperation> _Nonnull)operation
                     shouldUseCaptureControllerForPolicy:(DASAuthenticatorPolicyType)type
                                                 context:(_Nonnull id<DASMultiAuthenticatorContext>)context;

@end
