//
//  DASLoggingTags.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 3/13/19.
//  Copyright © 2019 Daon. All rights reserved.
//

#ifndef LoggingTags_h
#define LoggingTags_h

// Default
static NSString * const KDASDefaultLoggingTag               = @"DAS";

// Contexts
static NSString * const KDASContextLoggingTag               = @"DAS-CTX";
static NSString * const KDASMultiAuthContextLoggingTag      = @"DAS-MULTI-CTX";

// Authenticators / Controllers
static NSString * const KDASVoiceLoggingTag                 = @"DAS-VOICE";
static NSString * const KDASFaceLoggingTag                  = @"DAS-FACE";
static NSString * const KDASPasscodeLoggingTag              = @"DAS-PASSCODE";
static NSString * const KDASADoSLoggingTag                  = @"DAS-ADOS";
static NSString * const KDASSRPLoggingTag                   = @"DAS-SRP";
static NSString * const KDASLocalAuthenticationLoggingTag   = @"DAS-LA";
static NSString * const KDASMetadataLoggingTag              = @"DAS-META";

// Multi-Authenticators
static NSString * const KDASMultiAuthLoggingTag             = @"DAS-MULTI-AUTH";

#endif /* LoggingTags_h */
