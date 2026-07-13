
#ifndef IXUAFServiceDelegate_h
#define IXUAFServiceDelegate_h

#import <Foundation/Foundation.h>

///
/// SDK delegate for server communications.
/// 
/// The SDK provides default implementations for communicating with an RPSA or direct communication with the IdentityX server. However, an application can implement its own communication service by implementing the IXUAFServiceDelegate interface.
///
/// This is an interface that encapsulates the necessary interactions with a server during FIDO operations:
///
/// - Creating a FIDO registration, authentication or deregistration request
/// - Updating a FIDO registration or authentication with a FIDO response
/// - Requesting a FIDO registration policy
/// - Submitting failed authentication attempt data

@protocol IXUAFServiceDelegate <NSObject>

/// Get a FIDO registration message, e.g. from a server.
///
/// The registration call, registerWithCompletionHandler, will call this method when a registration message is needed.
///
/// The delegate communicates with the server to create a new FIDO registration request message. The IXUAF API registration call will call this method when a registration message is needed.

/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter params: The request parameters, username, etc.
/// - Parameter handler: The handler should return the FIDO message and/or any errors.
///
- (void) serviceRequestRegistrationWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                          handler:(nonnull void (^)(NSString* _Nullable message, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestRegistration(parameters:handler:));

/// Send FIDO registration message to the server.
///
/// The registration call, registerWithCompletionHandler, will call this method when the user has registered an authenticator and a registration message has been created.
///
/// The  delegate communicates with the server to register the authenticator and receives the server processing results back. The SDK is notified of the server result and the completion handler will be executed. The IXUAF API registration will call this method when the user has registered an authenticator and a registration message has been created.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username  |
/// | kIXUAFServiceParameterApplication   | string | FIDO application id |
/// | kIXUAFServiceParameterRequest       | string | FIDO request |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.

/// - Parameter uafMessage: The FIDO registration message
/// - Parameter params: Request parameters, e.g username, request, etc. in case of a step-up authentication, etc.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceRegisterWithMessage:(NSString* _Nonnull)uafMessage
                         parameters:(NSDictionary<NSString*, id>* _Nullable)params
                            handler:(nonnull void (^)(NSString* _Nullable response, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRegister(message:parameters:handler:));

/// Get a FIDO authentication message, e.g. from a server.
///
/// The authentication API will call this method when an authentication message is needed.
///
/// The delegate communicates with the server and receives a FIDO authentication request back. If the relying party knows the identity of the user then this will be a step-up authentication, otherwise it will be a standard authentication. The authentication API will call this method when an authentication message is needed.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username for step-up |
/// | kIXUAFServiceParameterApplication   | string | FIDO application id |
/// | kIXUAFServiceParameterDescription   | string | Authentication description |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter params: The request parameters, e.g. username.
/// - Parameter handler: The handler should return the FIDO message and/or any errors.
///
- (void) serviceRequestAuthenticationWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                            handler:(nonnull void (^)(NSString* _Nullable message, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestAuthentication(parameters:handler:));

/// Send FIDO authentication message to the server.
///
/// The authentication API will call this method when the user has authenticated and an authentication message has been created.
///
/// The delegate communicates with the server to authenticate the message. The SDK is notified of the server result and the completion handler will be executed. The IXUAF API authentication will call this method when the user has been authenticated and an authentication message has been created.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username for step-up |
/// | kIXUAFServiceParameterApplication   | string | FIDO application id |
/// | kIXUAFServiceParameterDescription   | string | Authentication description |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter uafMessage: The FIDO authentication message
/// - Parameter params: Request parameters, e.g username, request, etc. in case of a step-up authentication, etc.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceAuthenticateWithMessage:(NSString* _Nonnull)uafMessage
                             parameters:(NSDictionary<NSString*, id>* _Nullable)params
                                handler:(nonnull void (^)(NSString* _Nullable response, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceAuthenticate(message:parameters:handler:));

/// Send FIDO message to the server.
///
/// The  is called by the API to submit ADoS data to the server. When registering and authenticating with ADoS authenticators, the app is
/// responsible for sending the user authentication data to the server.
///
/// - Parameter uafMessage: The FIDO registration/authentication message
/// - Parameter username: The optional user name. May be provided in case of a step-up authentication.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceUpdateWithMessage:(NSString* _Nonnull)uafMessage
                         username:(NSString*_Nullable)username
                          handler:(nonnull void (^)(NSString* _Nullable response, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceUpdate(message:username:handler:));

/// Get a FIDO de-registration message, e.g. from a server.
///
/// The de-registration calls will call this method when a de-registration message is needed.
///
/// The delegate should get a FIDO de-registration message for the
/// given AAID. The de-registration calls will call this method when a de-registration message is needed.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username |
/// | kIXUAFServiceParameterApplication   | string | FIDO application id |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter aaid:The AAID to deregister.
/// - Parameter params: Request parameters, e.g username, FIDO application id, etc.
/// - Parameter handler: The handler should return the FIDO message and/or any errors.
///
- (void) serviceRequestDeregistrationWithAaid:(NSString* _Nonnull)aaid
                                   parameters:(NSDictionary<NSString*, id>* _Nullable)params
                                      handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestDeregistration(aaid:parameters:handler:));


/// Send authentication attempt data to the server.
///
/// The API will call this method after a failed attempt. This is not called for an ADOS authenticator, since the server already have the necessary information.
///
/// - Parameter info: The attempt information provided by the SDK.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceUpdateWithAttempt:(NSDictionary<NSString*, id>* _Nonnull)info
                          handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceUpdate(attempt:handler:));


@optional

/// Get the FIDO registration policy, e.g. from a server.
///
///The checkRegistrations call will call this method when needed.
///
/// - Parameter params: Request parameters, e.g username, FIDO application id, etc.
/// - Parameter handler: The handler should return the FIDO policy and/or any errors.
///
- (void) serviceRequestRegistrationPolicyWithParameters:(NSDictionary<NSString*, NSString*>* _Nullable)params
                                                handler:(nonnull void (^)(NSString* _Nullable policy, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestRegistrationPolicy(parameters:handler:)) __deprecated;

- (void) serviceInitializeWithParameters:(NSDictionary<NSString*, NSString*>* _Nullable)params
                                 handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceInitialize(parameters:handler:));

/// Invoked when calling IXUAF API requestServiceAccess. When using the default RPSA communication, this delegate will create the account or log in the user if a password is used.
///
/// The delegate is invoked when calling IXUAF API `requestServiceAccess`. When using the default RPSA communication, this delegate will create the account or log in the user if a password is used.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter params: Request parameters.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceRequestAccessWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                    handler:(nonnull void (^)(NSString* _Nullable message, NSDictionary<NSString*, id>* _Nullable data, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestAccess(parameters:handler:));

/// Invoked when calling IXUAF API revokeServiceAccess.
///
/// The delegate is invoked when calling IXUAF API `revokeServiceAccess`. When using the default RPSA communication, this delegate will delete the session.
///
/// - Parameter params: Request parameters.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceRevokeAccessWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                   handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRevokeAccess(parameters:handler:));

/// Invoked when calling IXUAF API delete(user)
///
/// The delegate is invoked when calling IXUAF API `delete(user)`.
///
/// | **Parameter** | **Type** | **Value** |
/// | - | - | - |
/// | kIXUAFServiceParameterUsername      | string | Username |
///
/// In addition to the SDK parameters, any custom parameters provided will be passed to the delegate methods and returned by the SDK.
///
/// - Parameter params: Request parameters.
/// - Parameter handler: The handler should return the FIDO response message and/or any errors.
///
- (void) serviceDeleteUserWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                   handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceDeleteUser(parameters:handler:));

@end


#endif /* IXUAFServiceDelegate_h */
