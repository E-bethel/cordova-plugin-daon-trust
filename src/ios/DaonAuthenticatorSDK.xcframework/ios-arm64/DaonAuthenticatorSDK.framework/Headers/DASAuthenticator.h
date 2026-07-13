//
//  DASAuthenticator.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/8/16.
//  Copyright © 2016-25 Daon. All rights reserved.
//

#ifndef DASAuthenticator_h
#define DASAuthenticator_h

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

// Enums

/// Categorizes the different signing algorithms available.
/// - Parameters:
///   - DASAuthenticatorSigningAlgorithmRSA: RSA.
///   - DASAuthenticatorSigningAlgorithmEC: EC. Default.
///   - DASAuthenticatorSigningAlgorithmECWithAccessibility: EC without requiring a device passcode to be set.
typedef NS_ENUM (NSInteger, DASAuthenticatorSigningAlgorithm)
{
    DASAuthenticatorSigningAlgorithmRSA = 0,
    DASAuthenticatorSigningAlgorithmEC  = 1,
    DASAuthenticatorSigningAlgorithmECWithAccessibility  = 2
};

/// Categorizes the different types of authenticator.
/// - Parameters:
///   - DASAuthenticatorFactorFace: Face collection via device camera. Face data is registered & authenticated on the device.
///   - DASAuthenticatorFactorFaceADoS: Face collection via device camera. Face data is registered & authenticated on the server.
///   - DASAuthenticatorFactorVoice: Voice collection via device microphone. Voice data is registered & authenticated on the device.
///   - DASAuthenticatorFactorVoiceADoS: Voice collection via device microphone. Voice data is registered & authenticated on the server.
///   - DASAuthenticatorFactorPassword: Passcode collection. Passcode data is registered & authenticated on the device.
///   - DASAuthenticatorFactorPasswordADoS: Passcode collection. Passcode data is registered & authenticated on the server.
///   - DASAuthenticatorFactorFingerprint: Touch ID registration & authentication.
///   - DASAuthenticatorFactorPattern: Not supported at this time.
///   - DASAuthenticatorFactorSilent: Device possession.
///   - DASAuthenticatorFactorSilentAccessibility: Device possession using DASAuthenticatorSigningAlgorithmECWithAccessibility algorithm.
///   - DASAuthenticatorFactorEye: Discontinued.
///   - DASAuthenticatorFactorPalm: Palm collection via device camera. Palm data is registered & authenticated on the device.
///   - DASAuthenticatorFactorOfflineOTP: Offline OTP.
///   - DASAuthenticatorFactorUnsupported: Default if no type is set.
///   - DASAuthenticatorFactorUnknown: No / unknown type.
typedef NS_ENUM (NSInteger, DASAuthenticatorFactor)
{
    DASAuthenticatorFactorFace                  = 0,
    DASAuthenticatorFactorFaceADoS              = 1,
    DASAuthenticatorFactorVoice                 = 2,
    DASAuthenticatorFactorVoiceADoS             = 3,
    DASAuthenticatorFactorPassword              = 4,
    DASAuthenticatorFactorPasswordADoS          = 5,
    DASAuthenticatorFactorFingerprint           = 6,
    DASAuthenticatorFactorPattern               = 7,    // Not supported.
    DASAuthenticatorFactorSilent                = 8,
    DASAuthenticatorFactorSilentAccessibility   = 9,
    DASAuthenticatorFactorEye                   = 10,   // Discontinued.
    DASAuthenticatorFactorPalm                  = 11,
    DASAuthenticatorFactorOfflineOTP            = 12,
    DASAuthenticatorFactorUnsupported           = 14,
    DASAuthenticatorFactorUnknown               = 15
};

/// Categorizes the different types of authenticator protection mechanisms.
/// - Parameters:
///   - DASAuthenticatorProtectionHardware: Hardware protection.
///   - DASAuthenticatorProtectionSoftware: Software protection.
typedef NS_ENUM (NSInteger, DASAuthenticatorProtection)
{
    DASAuthenticatorProtectionHardware  = 0,
    DASAuthenticatorProtectionSoftware  = 1,
    DASAuthenticatorProtectionUnknown   = 2
};

/// Categorizes the different types of authenticator authenticator lock state.
/// - Parameters:
///   - DASAuthenticatorLockStateUnlocked: Not Locked.
///   - DASAuthenticatorLockStateTemporary: Temporary Lock.
///   - DASAuthenticatorLockStatePermanent: Permanent Lock.
typedef NS_ENUM (NSInteger, DASAuthenticatorLockState)
{
    DASAuthenticatorLockStateUnlocked   = 0,
    DASAuthenticatorLockStateTemporary  = 1,
    DASAuthenticatorLockStatePermanent  = 2,
};

/// Categorizes the type of data store in which the enrolled data was stored.
/// - Parameters:
///   - DASAuthenticatorDataStoreOS: The data store used is managed by the OS.
///   - DASAuthenticatorDataStoreSoftware: N/A for iOS.
///   - DASAuthenticatorDataStoreNone: No data is stored.
typedef NS_ENUM (NSInteger, DASAuthenticatorDataStore)
{
    DASAuthenticatorDataStoreOS         = 0,
    DASAuthenticatorDataStoreSoftware   = 1,
    DASAuthenticatorDataStoreNone       = 2,
};

// Forward Declarations
@protocol DASAuthenticatorDelegate;

/// A protocol for classes that wish to implement Authenticator (Registration / Authentication) behaviour.
@protocol DASAuthenticator <NSObject>

/// A static internal id used only within the Daon Authenticator SDK.
/// - Returns: An NSString containing the authenticators ID.
- (NSString*) getID;

/// A short name for the authenticator.
/// - Returns: An NSString containing the authenticators name.
- (NSString*) getName;

/// A longer description of the authenticator.
/// - Returns: An NSString containing the authenticators description.
- (NSString*) getDescription;

/// The version of the authenticator.
/// - Returns: An NSInteger containing the authenticators version.
- (NSInteger) getVersionCode;

/// The version of the authenticator as a string.
/// - Returns: An NSString containing the authenticators version.
- (NSString*) getVersionName;

/// The default icon for the authenticator.
/// - Returns: An UIImage containing the authenticators icon.
- (UIImage*) getIcon;

/// The `DASAuthenticatorFactor` type supported by the authenticator.
/// - Returns: The `DASAuthenticatorFactor` type.
- (DASAuthenticatorFactor) getFactorType;

/// The `DASAuthenticatorProtection` type supported by the authenticator.
/// - Returns: The `DASAuthenticatorProtection` type.
- (DASAuthenticatorProtection) getMatcherProtection;

/// The current set of extensions for the authenticator, this includes all request extensions plus any response extensions that have been added.
/// - Returns: An NSDictionary mapping extension keys to values (Both NSString).
- (NSDictionary*) getExtensions;

/// Updates the current set of extensions for the authenticator.
/// - Parameter extensions: An NSDictionary mapping extension keys to values (Both NSString).
- (void) setExtensions:(NSDictionary*)extensions;

/// The `DASAuthenticatorDataStore` type supported by the authenticator.
/// - Returns: The `DASAuthenticatorDataStore` type.
- (DASAuthenticatorDataStore) getDataStoreType;

/// The `DASAuthenticatorDelegate` derived object that will be notified of authenticator events.
/// - Returns: The `DASAuthenticatorDelegate` derived object.
- (id<DASAuthenticatorDelegate>) getClientDelegate;

/// Sets the `DASAuthenticatorDelegate` derived object that will be notified of authenticator events.
/// - Parameter delegate: The `DASAuthenticatorDelegate` derived object.
- (void) setClientDelegate:(id<DASAuthenticatorDelegate>)delegate;

/// The `DASAuthenticatorSigningAlgorithm` type supported by the authenticator.
/// - Returns: The `DASAuthenticatorSigningAlgorithm` type.
- (DASAuthenticatorSigningAlgorithm) getSigningAlgorithm;

/// Sets the `DASAuthenticatorSigningAlgorithm` type supported by the authenticator.
/// - Parameter algorithm: The `DASAuthenticatorSigningAlgorithm` type.
- (void) setSigningAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Whether or not the authenticator type has a user interface.
/// - Returns: YES if the authenticator type has a user interface.
- (BOOL) hasUICollection;

/// Whether or not the authenticator is supported for the current device.
/// - Returns: YES if the authenticator type is supported.
- (BOOL) isSupported;

/// Determines whether or not the authenticator has a given key registered.
/// - Parameter keyName: The key to check.
/// - Returns: YES if key is registered.
- (BOOL) isRegistered:(NSString*)keyName;

/// The `DASAuthenticatorLockState` type currently set for the authenticator.
/// - Returns: The `DASAuthenticatorLockState` type.
- (DASAuthenticatorLockState) lockState;

/// The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970).
/// - Returns: Time in milliseconds or -1 if lockState is not `DASAuthenticatorLockStateTemporary`.
- (long long) lockEndTime;

/// Unlocks the authenticator.
/// The random string is stored with the authenticators state. When a subsequent unlock request is made, the new string will be compared against the previous string. If they do not match, then the unlock will proceed.
/// - Parameter randomId: A random string that will be stored with the unlock request.
/// - Returns: YES if the authenticator was unlocked.
- (BOOL) unlock:(NSString*)randomId;

/// Prepares the authenticator for re-enrollment.
/// The random string is stored with the authenticators state. When a subsequent re-enroll request is made, the new string will be compared against the previous string. If they do not match, then the re-enroll can proceed.
/// - Parameter randomId: A random string that will be stored with the reenroll request.
/// - Returns: YES if the authenticator can re-enroll.
- (BOOL) reenroll:(NSString*)randomId;

/// Determines whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
/// - Returns: YES if the authenticator has been invalidated.
- (BOOL) isInvalidated;

/// Update the authenticators state to show that it has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
- (void) invalidate;

/// Retrieve the public key that is being stored for a particular key name.
/// - Parameter keyName: The key to retrieve the public key for.
/// - Returns: An NSData object containing the public key.
- (NSData*) getPublicKey:(NSString*)keyName;

/// Determine the public key format that is current is used.
/// The supported format is based on the current `DASAuthenticatorSigningAlgorithm` type:
/// 1) `DASAuthenticatorSigningAlgorithmRSA`: "X.509"
/// 2) `DASAuthenticatorSigningAlgorithmEC`: "X9.62"
/// 3) `DASAuthenticatorSigningAlgorithmECWithAccessibility`: X9.62
/// - Returns: An NSString object containing the public key format.
- (NSString*) getPublicKeyFormat;

/// Determine the public key type that is current is used.
/// The supported type is based on the current `DASAuthenticatorSigningAlgorithm` type:
/// 1) `DASAuthenticatorSigningAlgorithmRSA`: "RSA"
/// 2) `DASAuthenticatorSigningAlgorithmEC`: "EC"
/// 3) `DASAuthenticatorSigningAlgorithmECWithAccessibility`: "EC"
/// - Returns: An NSString object containing the public key type.
- (NSString*) getPublicKeyType;

/// The `DASAuthenticatorProtection` type supported by the authenticator.
/// - Returns: The `DASAuthenticatorProtection` type.
- (DASAuthenticatorProtection) getKeyProtection;

/// The signing algorithm currently used by the authenticator.
/// The current algorithm is based on the current `DASAuthenticatorSigningAlgorithm` type:
/// 1) `DASAuthenticatorSigningAlgorithmRSA`: "SHA256withRSA"
/// 2) `DASAuthenticatorSigningAlgorithmEC`: "SHA256withECDSA"
/// 3) `DASAuthenticatorSigningAlgorithmECWithAccessibility`: "SHA256withECDSA"
/// - Returns: An NSString object containing the current signing algorithm.
- (NSString*) getAlgorithm;

/// Initiates the process to register an authenticator.
/// - Parameters:
///   - keyName: The name of the signing key that will be completed once registration completes.
///   - extensions: An NSDictionary mapping extension keys to values (Both NSString) that will be used during the registration process.
///   - delegate: The `DASAuthenticatorDelegate` derived object that will be notified of authenticator registration events.
- (void) register:(NSString*)keyName extensions:(NSDictionary*)extensions delegate:(id<DASAuthenticatorDelegate>)delegate;

/// Initiates the process to deregister an authenticator.
/// - Parameters:
///   - keyName: The name of the signing key that was previously registered and should be removed.
///   - removeAllData: Whether or not to remove the local encrypted data once the signing key has been removed.
/// - Returns: YES if the authenticator was deregistered.
- (BOOL) deregister:(NSString*)keyName removeAllData:(BOOL)removeAllData;

/// Initiates the process to authenticate an authenticator.
/// - Parameters:
///   - keys: An NSArray containing all key names that have previously been registered.
///   - extensions: An NSDictionary mapping extension keys to values (Both NSString) that will be used during the authentication process.
///   - delegate: The `DASAuthenticatorDelegate` derived object that will be notified of authenticator authentication events.
- (void) authenticate:(NSArray*)keys extensions:(NSDictionary*)extensions delegate:(id<DASAuthenticatorDelegate>)delegate;

@end

#endif /* DASAuthenticator_h */
