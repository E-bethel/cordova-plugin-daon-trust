//
//  DASAuthenticatorInfo.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 5/2/17.
//  Copyright © 2017-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>

/// Provides readonly information about a specific authenticator.
@interface DASAuthenticatorInfo : NSObject

/// The `DASAuthenticatorFactor` type supported by the authenticator.
@property (nonatomic, readonly) DASAuthenticatorFactor authenticatorFactor;

/// The name of the authenticator.
@property (nonatomic, readonly) NSString *authenticatorName;

/// The more detailed description of the authenticator.
@property (nonatomic, readonly) NSString *authenticatorDescription;

/// The authenticators icon.
@property (nonatomic, readonly) UIImage *authenticatorIcon;

/// The current `DASAuthenticatorLockState` type of the authenticator.
@property (nonatomic, readonly) DASAuthenticatorLockState authenticatorLockState;

/// The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970). Defaults to -1 if authenticatorLockState is not DASAuthenticatorLockStateTemporary.
@property (nonatomic, readonly) long long authenticatorLockedUntil;

/// The `DASAuthenticatorSigningAlgorithm` type used to create / access the authenticators keys.
@property (nonatomic, readonly) DASAuthenticatorSigningAlgorithm authenticatorSigningAlgorithm;

/// A static internal id used only within the Daon Authenticator SDK.
@property (nonatomic, readonly) NSString *authenticatorId;

/// The version of the authenticator.
@property (nonatomic, readonly) NSInteger authenticatorVersion;

/// An NSDictionary mapping extension keys to values (Both strings), that were passed into the authenticator.
@property (nonatomic, readonly) NSDictionary *authenticatorExtensions;

/// Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
@property (nonatomic, readonly) BOOL authenticatorInvalidated;

/// Instantiates a new `DASAuthenticatorInfo` object with information about a specific authenticator.
/// - Parameters:
///   - factor: The `DASAuthenticatorFactor` type supported by the authenticator.
///   - name: The name of the authenticator.
///   - description: The more detailed description of the authenticator.
///   - icon: The authenticators icon.
///   - lockState: The current `DASAuthenticatorLockState` type of the authenticator.
///   - lockUntil: The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970).
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used to create / access the authenticators keys.
///   - ident: A static internal id used only within the Daon Authenticator SDK.
///   - version: A version of the authenticator.
///   - exts: An NSDictionary mapping extension keys to values (Both strings), that were passed into the authenticator.
///   - invalidated: Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
/// - Returns: A new `DASAuthenticatorInfo` object.
- (id) initWithFactor:(DASAuthenticatorFactor)factor
                 name:(NSString*)name
          description:(NSString*)description
                 icon:(UIImage*)icon
            lockState:(DASAuthenticatorLockState)lockState
          lockedUntil:(long long)lockUntil
            algorithm:(DASAuthenticatorSigningAlgorithm)algorithm
                   id:(NSString*)ident
              version:(NSInteger)version
           extensions:(NSDictionary*)exts
          invalidated:(BOOL)invalidated;

@end
