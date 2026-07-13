
#import <Foundation/Foundation.h>

static NSString * const kNoApplicationID  = @"";

/// Utility class for creating FIDO registration and authentication request messages. 
///
/// This can be used for Offline message creation or single shot authentication.

@interface IXUAFMessageWriter : NSObject

/// Create a FIDO registration OR request
///
/// - Parameter aaids: An array of aaid's.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Parameter username: The username.
/// - Returns: A FIDO registration message,
+ (NSString*) registrationRequestWithOrPolicy:(NSArray*)aaids application:(NSString*)appid username:(NSString*)username;

/// Create a FIDO registration AND request
/// - Parameter aaids: An array of aaid's.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Parameter username: The username
/// - Returns: A FIDO registration message,
+ (NSString*) registrationRequestWithAndPolicy:(NSArray*)aaids application:(NSString*)appid username:(NSString*)username;

/// Create a FIDO registration with an Open Policy.
///
/// - Parameter appid: The application id. If null the facet id is used.
/// - Parameter username: The username
/// - Returns: A FIDO registration message,
+ (NSString*) registrationRequestWithApplication:(NSString*)appid username:(NSString*)username;

/// Create a FIDO authentication OR request
///
/// - Parameter aaids: An array of aaid's.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Returns: A FIDO authentication message,
+ (NSString*) authenticationRequestWithOrPolicy:(NSArray*)aaids application:(NSString*)appid;

/// Create a FIDO authentication AND request
///
/// - Parameter aaids: An array of aaid's.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Returns: A FIDO authentication message,
+ (NSString*) authenticationRequestWithAndPolicy:(NSArray*)aaids application:(NSString*)appid;

/// Create a FIDO authentication request with policy
///
/// Create a FIDO authentication with a FIDO accepted policy object, e.g [[{"aaid":["53EC#C002"]}],[{"aaid":["D409#0301"]}],[{"aaid":["53EC#C002"]},{"aaid":["D409#0601"]}]]
///
/// - Parameter policy: The accepted array.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Returns: A FIDO authentication message,
+ (NSString*) authenticationRequestWithPolicy:(NSArray*)policy application:(NSString*)appid;

/// Create a FIDO authentication request with an Open Policy
///
/// - Parameter appid:The application id. If null the facet id is used.
/// - Returns: A FIDO authentication message,
+ (NSString*) authenticationRequestWithApplication:(NSString*)appid;

/// Update an existing FIDO request
///
/// - Parameter request: The fido request message
/// - Parameter username: The username.
/// - Returns: A FIDO registration or authentication message,
+ (NSString*) updateRequest:(NSString*)request username:(NSString*)username;

/// Update an existing FIDO request
///
/// - Parameter request: The fido request message
/// - Parameter accepted: The accepted policy.
/// - Parameter username: The username.
/// - Returns: A FIDO registration or authentication message,
+ (NSString*) updateRequest:(NSString*)request accepted:(NSArray*)accepted username:(NSString*)username;

/// Update an existing FIDO request.
///
/// - Parameter request: The fido request message
/// - Parameter extensions: The extensions
/// - Returns: A FIDO registration or authentication message,
+ (NSString*) updateRequest:(NSString*)request extensions:(NSDictionary*)extensions;

/// Create a FIDO deregistration request
///
/// - Parameter aaid: The aaid.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Returns: A FIDO de-registration message,
+ (NSString*) deregistrationRequestWithAaid:(NSString*)aaid application:(NSString*)appid;

/// Create a FIDO deregistration request
///
/// - Parameter aaid: The aaid.
/// - Parameter username: The username.
/// - Parameter appid: The application id. If null the facet id is used.
/// - Returns: A user specific FIDO de-registration message,
+ (NSString*) deregistrationRequestWithAaid:(NSString*)aaid username:(NSString*)username application:(NSString*)appid;

@end
