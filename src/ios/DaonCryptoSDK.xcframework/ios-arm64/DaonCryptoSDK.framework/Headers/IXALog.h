//
//  IXALog
//  DaonCryptoSDK
//
//  Created by Neil Johnston on 03/12/19.
//  Copyright © 2019 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, IXALogLevel)
{
    IXALogLevelError  = 0,
    IXALogLevelInfo   = 1,
    IXALogLevelDebug  = 2
};

/**
 * Log utility methods
 */
@interface IXALog : NSObject

+ (BOOL) isLoggingEnabled;

/**
 * Enable or disable logging
 * - parameter enabled: Whether or not to enable logging
 */
+ (void) setLoggingEnabled:(BOOL)enabled level:(IXALogLevel)level;
+ (void) setWriteToFileEnabled:(BOOL)enabled;

/**
 * Verbose log the message using the default tag
 * - parameter message:
 */
+ (void) logInfo:(NSString*)message;

/**
 * Debug log the message using the default tag
 * - parameter message:
 */
+ (void) logDebug:(NSString*)message;

/**
 * Error log the message using the default tag
 * - parameter message:
 */
+ (void) logError:(NSString*)message;

/**
 * Verbose log the message using a custom tag
 * - parameter message:
 */
+ (void) logInfoWithTag:(NSString*)tag message:(NSString*)message;

/**
 * Debug log the message using a custom tag
 * - parameter message:
 */
+ (void) logDebugWithTag:(NSString*)tag message:(NSString*)message;

/**
 * Error log the message using a custom tag
 * - parameter message:
 */
+ (void) logErrorWithTag:(NSString*)tag message:(NSString*)message;

/**
 * Returns a string containing the stack trace of the given {@link Throwable}
 * - parameter error: throwable error
 * - returns: stack trace string
 */
+ (NSString*) stackTrace:(NSError*)error;

@end
