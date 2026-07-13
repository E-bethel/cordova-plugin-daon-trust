//
//  DASCaptureControllerProtocol.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 6/4/19.
//  Copyright © 2019-25 Daon. All rights reserved.
//

#ifndef DASCaptureControllerProtocol_h
#define DASCaptureControllerProtocol_h

/// A protocol for classes that wish implement their own handling of an authenticator register or authenticate event.
@protocol DASCaptureControllerProtocol

/// Used to notify a conforming object that capture should begin.
- (void) execute;

@end

#endif /* DASCaptureControllerProtocol_h */
