//
//  DASAuthenticatorCollectorInfo.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/26/18.
//  Copyright © 2018-25 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Provides information for a specific registration / authenticator collection event.
/// When providing your own view controllers for display, this will allow you to specify the view controller and whether or not you will be displaying it yourself.
@interface DASAuthenticatorCollectorInfo : NSObject

/// A reference to your custom view controller.
@property (nonatomic) UIViewController *collectionViewController;

/// Whether or not you will be displaying the view controller yourself.
/// NOTE: If you claim responsibility for presenting the view controller, you must also dismiss it yourself.
@property (nonatomic) BOOL clientIsResponsibleForPresentation;

/// Instantiates a new `DASAuthenticatorCollectorInfo` object with information for a specific registration / authenticator event.
/// - Parameters:
///   - viewController: A reference to your custom view controller.
///   - clientWillPresent: Whether or not you will be displaying the view controller yourself.
/// - Returns: A new `DASAuthenticatorCollectorInfo` object.
- (id) initWithViewController:(UIViewController*)viewController clientWillPresent:(BOOL)clientWillPresent;

@end
