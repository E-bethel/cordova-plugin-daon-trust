//
//  SecureKeys.h
//
//  Created by Jonny Mortensen on 7/16/14.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


#define newCFDictionary CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks)

typedef NS_ENUM (NSUInteger, Algorithm) {
    AlgorithmRSA,
    AlgorithmEC
};


@interface IXASecureKeys : NSObject
{
    NSString * _publicKeyName;
    NSString * _privateKeyName;
    
    uint _size;
    
    NSString * _name;
    CFStringRef _keyType;
    
    NSString * _group;
}

@property (nonatomic, readonly, assign) BOOL isNewKey;

- (id) initWithName:(NSString*)name algorithm:(Algorithm)algorithm;
- (BOOL) createKeysWithAccessControl:(SecAccessControlCreateFlags)flags;
- (BOOL) createKeysWithAccessControl:(SecAccessControlCreateFlags)flags accessibility:(CFTypeRef)accessibility;
- (BOOL) createKeysWithAccessibility:(CFTypeRef)accessibility enclave:(BOOL)useEnclave;

- (BOOL) removeKeys;

- (NSData*) privateKeyData;
- (NSData*) publicKeyData;
- (NSData*) encodedPublicKey;

- (SecKeyRef) privateKey;
- (SecKeyRef) publicKey;

- (NSData*) sign:(NSData*)data status:(OSStatus*)status;
- (NSData*) sign:(NSData*)data reason:(NSString*)reason status:(OSStatus*)status;

- (BOOL) verify:(NSData *)data signature:(NSData *)sig;

- (NSString*) signatureAlgorithm;
- (NSString*) keyAlgorithm;
- (NSString*) name;

+ (BOOL) hasKeyWithName:(NSString*)name status:(OSStatus*)status;
- (BOOL) rename:(NSString*)newname;

+ (void) removeAllKeys;

- (BOOL) hasAccessControl;
- (BOOL) isStoredInSecureEnclave;
- (BOOL) isSecureEnclaveSupported;

- (CFStringRef) accessibility;

- (NSData*) encryptData:(NSData*)content;
- (NSData*) decryptData:(NSData*)content; 

- (BOOL) updateKeyAccessibility:(CFTypeRef)accessibility flags:(SecAccessControlCreateFlags)flags;
- (BOOL) updatePrivateKeyAttributes:(CFDictionaryRef)attributes;

@end
