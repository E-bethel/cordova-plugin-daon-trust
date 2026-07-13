//
//  IXAOneTimePassword.h
//
//  Created by Jonny Mortensen on 2/12/18.
//  Copyright © 2018 Jonny Mortensen. All rights reserved.
//

#import <Foundation/Foundation.h>


static NSString * const kOTPAlgorithmSHA256 = @"OOTPSha256";
static NSString * const kOTPAlgorithmSHA384 = @"OOTPSha384";
static NSString * const kOTPAlgorithmSHA512 = @"OOTPSha512";

@interface IXAOneTimePassword : NSObject

/**
 * Constructs a new time-based one-time password generator with the given time-step, password length, and HMAC
 * algorithm.
 *
 * @param step the magnitude of the time-step in seconds
 * @param length the length, in decimal digits, of the one-time passwords to be generated; must be between
 * 6 and 8, inclusive
 * @param algorithm the name of the algorithm.
 */
- (id) initWithLength:(NSUInteger)length step:(NSTimeInterval)step algorithm:(NSString*)algorithm;

/**
 * Constructs a new time-based one-time password generator with the given time-step, password length, and HMAC
 * algorithm.
 *
 * @param step the magnitude of the time-step in seconds
 * @param length the length, in decimal digits, of the one-time passwords to be generated; must be between
 * 6 and 8, inclusive
 * @param algorithm the name of the algorithm.
 * @param minimumTimeToLive the minimum ttl period
 */
- (id) initWithLength:(NSUInteger)length step:(NSTimeInterval)step algorithm:(NSString*)algorithm minimumTimeToLive:(NSTimeInterval)minimumTimeToLive ;

// Create key pair and return public key
- (NSString*) generateKeys;

- (void) deleteKeys;

// Get public key
- (NSString*) publicKey;

// Return OTP by passing servers public key, transaction data and status byte
- (NSString*) oneTimePasswordWithPublicKey:(NSData*)serverPublicKey data:(NSData*)data state:(NSData*)state;

// Return OTP async
- (void) oneTimePasswordWithPublicKey:(NSData*)serverPublicKey data:(NSData*)data state:(NSData*)state completion:(void (^)(NSString* otp))completion;

+ (NSInteger) timeToLiveWithStep:(NSTimeInterval)step;
- (NSString*) timeToLive;

@end
