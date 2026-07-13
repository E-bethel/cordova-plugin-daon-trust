//
//  IXABiometricsFactor.h
//  DaonAuthentication
//
//  Created by Jonny Mortensen on 10/27/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DaonCryptoSDK/IXTouchIDFactor.h>

@interface IXABiometricsFactor : IXTouchIDFactor

+ (IXABiometricsFactor*) factorWithKeyname:(NSString*)name;
+ (IXABiometricsFactor*) factorWithKeyname:(NSString*)name options:(NSUInteger)options;

/*!
 * @abstract Check if Face ID is available
 * @returns true if Face ID is available and enrolled.
 */
+ (BOOL) hasFaceID;

/*!
 * @abstract Check if Touch ID is available
 * @returns true if Touch ID is available and enrolled.
 */
+ (BOOL) hasTouchID;

@end
