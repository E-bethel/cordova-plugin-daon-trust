//
//  IXAKeychain
//
//  Copyright © 2016-18 Daon. All rights reserved.
//
#import <Foundation/Foundation.h>

@interface IXAKeychain : NSObject

/*!
 @brief set key.
 @description To use access groups, add the following to the applications plist:
 <key> DaonKeychainAccessGroup </key>
 <string>$(AppIdentifierPrefix)mykeychaingroup</string>

 Xcode will replace >$(AppIdentifierPrefix) with the Bundle Seed ID, e.g. X35FV693K3.mykeychaingroup
 
 Create the Apps entitlements by adding mykeychaingroup under Capabilities: Keychain Sharing in Xcode.
 
 @param key The key name
 @param value The value
 */
+ (BOOL) setKey:(NSString*)key value:(NSString*)value;
+ (BOOL) setKey:(NSString*)key data:(NSData*)value;
+ (NSString*) stringForKey:(NSString*)key;
+ (NSData*) dataForKey:(NSString*)key;
+ (BOOL) deleteKey:(NSString*)key;
+ (BOOL) clear;
+ (NSArray*) findKeysWithString:(NSString*)string error:(NSError**)error;
+ (NSArray*) allKeys;
@end
