
#import <Foundation/Foundation.h>
#import <DaonFIDOSDK/IXUAFTransaction.h>
#import <DaonFIDOSDK/IXUAFVersion.h>

/// Utility class for decoding FIDO messages.
/// 
@interface IXUAFMessageReader : NSObject

/// Get Reader with message
+ (IXUAFMessageReader*_Nonnull) readerWithMessage:(NSString*_Nonnull)message;

///Get Reader with message
/// - Parameter validate: If true, check if the message is a valid FIDO message.
+ (IXUAFMessageReader*_Nonnull) readerWithMessage:(NSString*_Nonnull)message validate:(BOOL)validate;

/// Get Reader with dictionary
+ (IXUAFMessageReader*_Nonnull) readerWithDictionary:(NSDictionary*_Nonnull)message;

/// Create Reader with message
/// - Parameter validate: If true, check if the message is a valid FIDO message.
- (id _Nonnull ) initWithMessage:(NSString*_Nonnull)message validate:(BOOL)validate;

/// Create Reader with dictionary
- (id _Nonnull) initWithDictionary:(NSDictionary*_Nonnull)message;

/// Returns true if the message requires transaction confirmation
- (BOOL) requiresTransactionConfirmation;

/// Get transaction confirmation object
- (IXUAFTransaction*_Nullable) transaction;

/// true if this is a registration message
- (BOOL) isRegistration;

/// true if this is an authentication message
- (BOOL) isAuthentication;

/// true if this is a de-registration message
- (BOOL) isDeregistration;

/// Get Application ID if available
- (NSString*_Nullable) application;

/// Get version
- (IXUAFVersion*_Nonnull) version;

/// Get header extensions
- (NSDictionary*_Nonnull) extensions;

/// Get final challenge, eg. fcparam
- (NSDictionary<NSString*,id>*_Nullable) fcParams;

- (NSArray<NSArray<NSString*>*> *_Nonnull) accepted;

/// Get assertion extensions. A dictionary mapping AAIDs to extensions.
- (NSDictionary*_Nonnull) assertionExtensions;

/// Get OTP (if enabled on the policy)
- (NSString*_Nullable) otp;

/// Get assertions
///
/// Parse registration and authentication assertions.
///
/// - Returns: Array of NSNumber -> NSData (see FIDO spec for tag ids)

- (NSArray<NSDictionary<NSNumber*, NSData*>*>*_Nonnull) assertions;

/// Check trusted facets.
///
/// This method will potentially make a network call.
- (void) checkTrustedFacetsWithCompletion:(void (^_Nonnull)(BOOL trusted))completionHandler;

@end
