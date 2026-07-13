//
//  DASStorageProvider.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 4/3/19.
//  Copyright © 2019-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>

// Forward Declarations
@class DASLockInfo;

// Blocks

/// Block that is used to notify a calling object that a data item has been stored.
/// - Parameter error: An error if the storage failed, otherwise nil.
typedef void (^DASStorageCompletionBlock) (NSError* error);

/// Block that is used to notify a calling object that a data item has been retrieved.
/// - Parameters:
///   - error: An error if the retrieval failed, otherwise nil.
///   - data: The retrieved data.
typedef void (^DASRetrievalCompletionBlock) (NSError* error, NSData* data);

// Constants
extern NSString * const KDASStorageKeyDaonExtensions;

/// Protocol for classes that wish to provide key management and storage capabilities.
@protocol DASStorageProvider <NSObject>

/// Determine if keys exist for a particular key name.
/// - Parameter keyName: The name of the keys to create.
/// - Returns: YES if the keys exist
- (BOOL) hasKey:(NSString*)keyName;

/// Create keys for a particular key name.
/// - Parameters:
///   - keyName: The name of the keys to create.
///   - authenticator: The `DASAuthenticator` type used when accessing the key.
/// - Returns: YES if the keys were created.
- (BOOL) createKeys:(NSString*)keyName authenticator:(id<DASAuthenticator>)authenticator;

/// Create keys for a particular key name.
/// - Parameters:
///   - keyName: The name of the keys to create.
///   - authenticator: The `DASAuthenticator` type used when accessing the key.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing the key.
/// - Returns: YES if the keys were created.
- (BOOL) createKeys:(NSString*)keyName authenticator:(id<DASAuthenticator>)authenticator algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Remove the keys created for a particular key name.
/// - Parameters:
///   - keyName: The name of the keys to delete.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing the key.
/// - Returns: YES if the keys were deleted.
- (BOOL) removeKeys:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Retrieve the public key that is being stored for a particular key name.
/// - Parameters:
///   - keyName: The key to retrieve the public key for.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing the key.
/// - Returns: An NSData object containing the public key.
- (NSData*) getPublicKey:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Determines if a Local Authentication device enrollment (Touch ID / Face ID) has changed.
/// - Parameters:
///   - keyName: The name of the signing key that was previously registered and will be checked.
///   - algorithm: The `DASAuthenticatorSigningAlgorithm` type used when accessing the key.
/// - Returns: YES if the device enrollment has changed (finger/face have been added or removed).
- (BOOL) hasEnrollmentChangedForKey:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/// Stores an NSString in the keychain or user defaults.
/// - Parameters:
///   - storageKeyString: The key under which to store the NSString.
///   - value: The NSString to store.
///   - inKeychain: If YES the NSString will be stored in the keychain otherwise it will be stored in user defaults.
- (void) setString:(NSString*)storageKeyString value:(NSString*)value inKeychain:(BOOL)inKeychain;

/// Retrieve an NSString that is stored in the keychain or user defaults.
/// - Parameters:
///   - storageKeyString: The key under which the NSString is stored.
///   - inKeychain: If YES the NSString will be retrieved from the keychain otherwise it will be retrieved from user defaults.
/// - Returns: The retrieved NSString
- (NSString*) getString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;

/// Check if an NSString that is stored in the keychain or user defaults.
/// - Parameters:
///   - storageKeyString: The key under which the NSString is stored.
///   - inKeychain: If YES the NSString will checked for in the keychain otherwise it will be checked in user defaults.
/// - Returns: YES if the NSString is stored.
- (BOOL) hasString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;

/// Remove an NSString from the keychain or user defaults.
/// - Parameters:
///   - storageKeyString: The key under which the NSString is stored.
///   - inKeychain: If YES the NSString will be removed from the keychain otherwise it will be removed from user defaults.
- (void) removeString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;

/// Stores an NSDictionary in the keychain
/// - Parameters:
///   - storageKeyString: The key under which to store the NSDictionary.
///   - value: The NSDictionary to store.
- (void) setDictionary:(NSString*)storageKeyString value:(NSDictionary*)value;

/// Retrieve an NSDictionary that is stored in the keychain.
/// - Parameter storageKeyString: The key under which the NSDictionary is stored.
/// - Returns: The retrieved NSDictionary
- (NSDictionary*) getDictionary:(NSString*)storageKeyString;

/// Remove an NSDictionary from the keychain.
/// - Parameter storageKeyString: The key under which the NSDictionary is stored.
- (void) removeDictionary:(NSString*)storageKeyString;

/// Stores an NSData in the keychain
/// - Parameters:
///   - storageKeyString: The key under which to store the NSData.
///   - value: The NSData to store.
- (void) setData:(NSString*)storageKeyString value:(NSData*)value;

/// Retrieve an NSData that is stored in the keychain.
/// - Parameter storageKeyString: The key under which the NSData is stored.
/// - Returns: The retrieved NSData
- (NSData*) getData:(NSString*)storageKeyString;

/// Remove an NSDictionary from the keychain.
/// - Parameter storageKeyString: The key under which the NSDictionary is stored.
- (void) removeData:(NSString*)storageKeyString;

/// Retrieves the `LockInfo` for a specific authenticator.
/// - Parameter authenticatorId: The ID of the authenticator whose `LockInfo` will be retrieved.
/// - Returns: The `LockInfo` for the specified authenticator
- (DASLockInfo*) lockInfoForAuthenticator:(NSString*)authenticatorId;

/// Updates the `LockInfo` for a specific authenticator.
/// - Parameters:
///   - lockInfo: The updated `LockInfo` object
///   - authenticatorId: The ID of the authenticator whose `LockInfo` will be updated.
- (void) updateLockInfo:(DASLockInfo*)lockInfo forAuthenticator:(NSString*)authenticatorId;

/// Unlocks a specific authenticator.
/// - Parameters:
///   - authenticatorId: The ID of the authenticator which will be unlocked.
///   - randomId: A random string that will be stored with the unlock request. The random string is stored with the authenticators state. When a subsequent unlock request is made, the new string will be compared against the previous string. If they do not match, then the unlock will proceed.
/// - Returns: YES if the authenticator was unlocked.
- (BOOL) unlock:(NSString*)authenticatorId randomId:(NSString*)randomId;

/// Retrieves the `DASAuthenticatorLockState` for a specific authenticator.
/// - Parameter authenticatorId: The ID of the authenticator whose lock information will be retrieved.
/// - Returns: The `DASAuthenticatorLockState`.
- (DASAuthenticatorLockState) lockStateForAuthenticator:(NSString*)authenticatorId;

/// Delete the stored lock information (`LockInfo`) for a specific authenticator.
/// - Parameter authenticatorId: The ID of the authenticator whose lock information will be deleted.
- (void) deleteLockInfoForAuthenticator:(NSString*)authenticatorId;

/// Prepares the authenticator for re-enrollment.
/// - Parameters:
///   - authenticatorId: The ID of the authenticator which will be prepared for re-enrollment.
///   - randomId: A random string that will be stored with the reenroll request.
/// - Returns: YES if the authenticator can re-enroll
- (BOOL) reenroll:(NSString*)authenticatorId randomId:(NSString*)randomId;

/// Generates a random data id for use in naming an encrypted data file.
/// - Parameter authenticatorId: The ID of the authenticator whose data will potentially be stored in the encrypted data file.
/// - Returns: The random data id for use in naming an encrypted data file.
- (NSString*) getDataIdForAuthenticator:(NSString*)authenticatorId;

/// Determines if an encrypted data file with a specified ID exists.
/// - Parameter dataId: A unique ID which identifies the encrypted data file.
/// - Returns: YES if the encrypted data file exists.
- (BOOL) isDataAvailable:(NSString*)dataId;

/// Stores a NSData object in an encrypted data file with a specified ID.
/// - Parameters:
///   - data: The data to store.
///   - dataId: A unique ID which identifies the encrypted data file.
///   - backgroundOption: If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when creating the encryption keys.
///   - completionBlock: A `DASStorageCompletionBlock` block that will be used to notify the caller that the data was stored, or failed during the attempt.
- (void) storeData:(NSData*)data withId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption completionBlock:(DASStorageCompletionBlock)completionBlock;

/// Asynchronously Retrieves the contents of encrypted data file with a specified ID.
/// - Parameters:
///   - dataId: A unique ID which identifies the encrypted data file.
///   - backgroundOption: If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when accessing the encryption keys.
///   - completionBlock: A `DASRetrievalCompletionBlock` block that will be used to notify the caller that the data was retrieved, or failed during the attempt.
- (void) retrieveDataWithId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption completionBlock:(DASRetrievalCompletionBlock)completionBlock;

/// Synchronously Retrieves the contents of encrypted data file with a specified ID.
/// - Parameters:
///   - dataId: A unique ID which identifies the encrypted data file.
///   - backgroundOption: If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when accessing the encryption keys.
///   - error: The pointer to an NSError object that will be set if an error occurred.
/// - Returns: The retrieved data or nil if an error occurred.
- (NSData*) retrieveDataWithId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption error:(NSError**)error;

/// Deletes the encrypted data file with a specified ID.
/// - Parameter dataId: A unique ID which identifies the encrypted data file.
- (void) deleteDataWithId:(NSString*)dataId;

/// Removes all stored settings (From NSUserDefaults) and deletes all encrypted data files from the file system.
- (void) reset;

@end
