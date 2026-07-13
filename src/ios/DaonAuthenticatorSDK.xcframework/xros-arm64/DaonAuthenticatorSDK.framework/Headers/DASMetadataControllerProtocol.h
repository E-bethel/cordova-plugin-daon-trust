//
//  DASMetadataControllerProtocol.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 2/13/19.
//  Copyright © 2019-25 Daon. All rights reserved.
//

#ifndef DASMetadataControllerProtocol_h
#define DASMetadataControllerProtocol_h

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>

/// A protocol for classes that wish to provide metadata scanning functionality.
@protocol DASMetadataControllerProtocol <DASControllerProtocol>

/// Instructs the controller to configure the camera and begin scanning for the specific AVMetadataObjectType types.
/// As soon as a relevant object is detected, it will be returned via the delegate (`DASMetadataControllerDelegate`)
/// `metadataControllerCompletedWithImage:contents:` method.
- (void) start;

@end

#endif /* DASMetadataControllerProtocol_h */
