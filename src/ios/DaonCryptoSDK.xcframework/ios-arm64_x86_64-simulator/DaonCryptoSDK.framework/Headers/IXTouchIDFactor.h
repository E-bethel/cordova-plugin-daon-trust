//
//  IXTouchIDFactor.h
//  DaonAuthentication
//
//  Created by Jonny Mortensen on 2/18/15.
//  Copyright (c) 2015-17 Daon. All rights reserved.
//
// Renamed to make internal. Use IXABiometricsFactor

#import <Foundation/Foundation.h>
#import <DaonCryptoSDK/IXAFactor.h>


@interface IXTouchIDFactor : IXAFactor

+ (IXTouchIDFactor*) factorWithKey:(NSString*)name;
+ (IXTouchIDFactor*) factorWithKey:(NSString*)name options:(NSUInteger)options;

- (id) initWithKey:(NSString*)key options:(NSUInteger)options;

- (NSError *) unlockAndWaitWithMessage:(NSString*)message;
+ (void) unlockWithMessage:(NSString*)message completion:(void (^)(BOOL, NSError *))completion;

@end
