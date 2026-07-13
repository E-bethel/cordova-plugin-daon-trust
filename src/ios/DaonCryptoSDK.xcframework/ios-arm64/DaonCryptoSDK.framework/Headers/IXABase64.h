//
//  Base64.h
//
//  Created by Jonny Mortensen on 5/9/11.
//  Copyright 2011-18 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface IXABase64 : NSObject

+ (NSData*) decode:(NSString*)string;
+ (NSString*) encode:(NSData*)data;

/**
 * Encode a byte array to a base-64 URL safe encoding string with no wrapping and no padding. This is the format required for
 * base 64 fields in UAF messages.
 * - parameter bytes: byte array to convert
 * - returns: base-64 URL safe encoding of the byte array
 */
+ (NSString*) encodeBase64URLData:(NSData*)bytes;

/**
 * Decode a base-64 URL safe string to a byte array
 * - parameter string: Base-64 URL safe string
 * - returns: byte array
 */
+ (NSData*) decodeBase64URLString:(NSString*)string;

+ (NSString*) base64PadString:(NSString*)stringToPad;
@end
