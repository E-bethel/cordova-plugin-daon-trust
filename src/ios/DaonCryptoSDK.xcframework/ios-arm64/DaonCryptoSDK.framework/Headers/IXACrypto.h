//
//  IXACrypto
//
//  Created by Jonny Mortensen on 3/1/17.
//  Copyright © 2017-18 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>



@interface IXACrypto : NSObject

+ (NSData*) secretKeyFromPassword:(NSString*)password salt:(NSData*)salt;
+ (NSData*) secretKeyFromPassword:(NSString*)password salt:(NSData*)salt rounds:(uint)rounds;

+ (NSData*) nonceWithLength:(NSUInteger)length;

// Get 256 bit AES key
+ (NSData*) symmetricKey;

+ (NSData *) encrypt:(NSData*)data withKey:(NSData*)key;
+ (NSData *) decrypt:(NSData*)data withKey:(NSData*)key;

+ (NSData*) wrapSymmetricKey:(NSData *)symmetricKey withKey:(SecKeyRef)publicKey;
+ (NSData*) unwrapSymmetricKey:(NSData *)wrappedSymmetricKey withKey:(SecKeyRef)privateKey;

+ (NSData*) SHA1:(NSData*)data;
+ (NSData*) SHA256:(NSData*)data;
+ (NSData*) SHA384:(NSData*)data;
+ (NSData*) SHA512:(NSData*)data;

+ (SecKeyRef) dataEncryptionKeyCopyWithCertificate:(NSString*)certchain rootCertificate:(NSString*)rootchain san:(NSString*)san;

+ (NSData*) encryptionKeyDataWithCertificate:(NSString*)certchain;
+ (NSData*) dataWithPublicKey:(SecKeyRef)publicKeyRef;

+ (void) encryptionKeyDataWithCertificate:(NSString*)certchain completion:(void (^)(NSData* data))completion;
@end
