//
//  DASMetadataControllerDelegate.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 2/13/19.
//  Copyright © 2019-25 Daon. All rights reserved.
//

#ifndef DASMetadataControllerDelegate_h
#define DASMetadataControllerDelegate_h

/// A protocol for classes that wish to be notified of metadata scanning events from an `DASMetadataControllerProtocol` derived object.
@protocol DASMetadataControllerDelegate <DASControllerProtocol>

/// Used to notify a conforming object that metadata scanning has started.
- (void) metadataControllerScanningStarted;

/// Used to notify a conforming object that metadata scanning completed successfully.
/// - Parameters:
///   - image: An image of the metadata object that was scanned.
///   - contents: The UT8 encoded contents of the metadata object that was scanned.
- (void) metadataControllerCompletedWithImage:(UIImage*)image contents:(NSData*)contents;

/// Used to notify a conforming object that metadata scanning failed with an error.
/// - Parameter error: The error that caused scanning to fail.
- (void) metadataControllerCompletedWithError:(NSError*)error;

@end

#endif /* DASMetadataControllerDelegate_h */

