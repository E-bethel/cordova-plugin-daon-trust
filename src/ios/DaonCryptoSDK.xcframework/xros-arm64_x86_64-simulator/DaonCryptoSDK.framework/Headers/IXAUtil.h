//
//  IXAUtil.h
//
//  Created by Jonny Mortensen on 10/11/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IXAUtil : NSObject

+ (BOOL) string:(NSString*)str matchesPattern:(NSString*)pattern;

+ (NSString*) hexWithData:(NSData*)data;

@end
