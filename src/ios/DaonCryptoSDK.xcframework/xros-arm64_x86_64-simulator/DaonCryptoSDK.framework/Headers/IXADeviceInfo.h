//
//  IXADeviceInfo
//  DaonCryptoSDK
//
//  Created by Jonny Mortensen on 3/30/18.
//  Copyright © 2018 Jonny Mortensen. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS (NSUInteger, IXADeviceInfoState) {
    IXADeviceInfoStateEmulator  = 1,
    IXADeviceInfoStateDebug     = 2,
    IXADeviceInfoStateJailbreak = 4
};

@interface IXADeviceInfo : NSObject

+ (NSString*) platform;
+ (NSString*) model;

+ (BOOL) isBeingDebugged;
+ (BOOL) isEmulator;
+ (BOOL) isSecure;

+ (NSData*) state;

+ (BOOL) hasEnclave;

@end
