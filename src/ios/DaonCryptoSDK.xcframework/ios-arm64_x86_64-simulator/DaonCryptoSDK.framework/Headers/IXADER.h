//
//  IXADER.h
//  DaonAuthentication
//
//  Created by Jonny Mortensen on 7/27/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString * const kOIDSubjectAlternativeName = @"2.5.29.17";
static NSString * const kOIDKeySubjectAlternativeName = @"551D11";

@interface IXADER : NSObject

+ (NSDictionary*) parseWithData:(NSData*)data;

@end
