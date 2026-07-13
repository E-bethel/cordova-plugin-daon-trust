//
//  IXUAFLicense
//  
//
//  Copyright (c) 2017 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>
#import <CommonCrypto/CommonDigest.h>

/// SDK license object.
///
/// The SDK requires a license that is bound to an application identifier. This license may in turn embed licenses that are required for specific authenticators. Contact Daon Support or Sales to request a license.
///
@interface IXUAFLicense : NSObject

@property (nonatomic, readonly) NSString * license;
@property (nonatomic, readonly) NSDictionary * extensions;

- (id) initWithContent:(NSString*)license;

- (bool) hasExpired;
- (bool) isVerified;
- (bool) supportsFeatureWithName:(NSString*)feature;

@end
