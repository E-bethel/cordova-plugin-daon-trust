/*!
 @header IXUAFOperation
 FIDO operation. The IXUAFOperation object is provided by the IXUAFDelegate methods.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

#import <DaonFIDOSDK/IXUAFAuthenticator.h>
#import <DaonFIDOSDK/IXUAFAccount.h>
#import <DaonFIDOSDK/IXUAFVersion.h>

/// The currently active FIDO operation.
///
/// If you are handling the authenticator selection yourself, for example, returning nil from the `operation:willAllowAuthenticators` delegate method,
/// you have to tell the SDK which authenticator to use by calling `verifyWithAuthenticator`.
///
/// if there are multiple accounts, you have to tell the SDK which account to use for siginig with `signWithAccount`.

@protocol IXUAFOperation <NSObject>

/// Message type
/// - Returns: The message type: "Reg" or "Auth"
- (NSString*) type;

/// Message version
/// - Returns: The FIDO message version.
- (IXUAFVersion*) version;

/// Start verification with authenticator
///
/// - Parameter authenticator: The authenticator or list of authenticators for AND
///
- (void) verifyWithAuthenticator:(NSArray<IXUAFAuthenticator*> *) authenticator;

@optional
/// Sign message
///
/// If more than one account is available, call this method when an account has been selected.
/// 
/// - Parameter account: The account.
///
- (void) signWithAccount:(IXUAFAccount*)account;

/// Notify the SDK with result
///
/// Call this method after getting a response back from the server, to make sure the SDK is in sync.
///
/// - Parameter result: The result, either a fido message or error message.
/// - Parameter responseCode: The response code.
///
- (void) notifyWithResult:(NSString*)result code:(NSInteger)responseCode;

@end


