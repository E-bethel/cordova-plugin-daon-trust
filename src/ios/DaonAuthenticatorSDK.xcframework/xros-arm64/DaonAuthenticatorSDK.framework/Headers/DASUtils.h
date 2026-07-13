//
//  DASUtils.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/7/16.
//  Copyright © 2016-25 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

/// Provides a number of common utility methods that can be used across the SDK and in custom view controllers.
@interface DASUtils : NSObject

/*!
 @functiongroup Bundles
 */

/// Returns all of the bundles available to the application.
/// - Returns: An NSArray of all NSBundle objects contained within the application installation.
+ (NSArray<NSBundle*>*) allBundles;

/// Searches through all available bundles and returns the file path to the specified resource.
/// - Parameters:
///   - resource: The file name of the resource.
///   - resourceType: The file type of the resource.
/// - Returns: The file path to the requested resource.
+ (NSString*) getPathInAllBundlesForResource:(NSString*)resource ofType:(NSString*)resourceType;

/// Searches through all available bundles and returns the bundle that contains the specified resource.
/// - Parameters:
///   - resource: The file name of the resource.
///   - resourceType: The file type of the resource.
/// - Returns: The NSBundle that contains the requested resource.
+ (NSBundle*) bundleForResource:(NSString*)resource ofType:(NSString*)resourceType;

/*!
 @functiongroup Localisation
 */

/// Searches through all available bundles and returns the localisation for a specified key.
/// - Parameter key: The localisation key. See the DAS-Localizable.strings file for all potential keys and values.
/// - Returns: The localized NSString.
+ (NSString*) localise:(NSString*)key;

/*!
 @functiongroup Errors
 */

/// Returns the localized error message for a specific DASAuthenticatorError type.
/// - Parameter error: The DASAuthenticatorError error.
/// - Returns: An NSString with the localized error message for the DASAuthenticatorError type.
+ (NSString*) stringForError:(DASAuthenticatorError)error;

/// Creates a new NSError object for a DASAuthenticatorError error with the default localized error message.
/// - Parameter error: The DASAuthenticatorError error.
/// - Returns: An NSError with the DASAuthenticatorError error and localized message.
+ (NSError*) errorForError:(DASAuthenticatorError)error;

/// Creates a new NSError object for a DASAuthenticatorError error with a custom message.
/// - Parameters:
///   - error: The DASAuthenticatorError error.
///   - description: The string to use as the NSLocalizedDescriptionKey value.
/// - Returns: An NSError with the DASAuthenticatorError error and custom message.
+ (NSError*) errorForError:(DASAuthenticatorError)error description:(NSString*)description;

/// Creates a new NSError object for a DASAuthenticatorError error whose localisation includes a string format specifier.
/// - Parameters:
///   - error: The DASAuthenticatorError error.
///   - value: The integer to use in the error localisation.
/// - Returns: An NSError with the DASAuthenticatorError error and localized message.
+ (NSError*) errorForError:(DASAuthenticatorError)error integerArgument:(NSInteger)value;

/// Converts a Local Authentication error into a DASAuthenticatorError error.
/// - Parameter localAuthError: The Local Authentication error to convert.
/// - Returns: An NSError with the correct DASAuthenticatorError error and localized message. If no valid error is found, then the Local Authentication error is returned.
+ (NSError*) errorForLocalAuthError:(NSError*)localAuthError;

/// Pulls out an error's underlying error if available, or returns the passed in error.
/// - Parameter error: The error that potentially has an underlying error.
/// - Returns: If present, the NSError contained in the userInfo dictionary (under the NSUnderlyingErrorKey) for the passed in error. If not present it will return the passed in error.
+ (NSError*) underlyingErrorForError:(NSError*)error;

/// Determines whether or not a client error should be transmitted to the server for an ADoS authentication. Typically
/// this will be for errors the server has no way to know about such as timeouts.
/// - Parameter error: The error that occurred.
/// - Returns: YES if the error should be reported to the server.
+ (BOOL) reportADoSErrorToServer:(NSError*)error;

/*!
 @functiongroup Images
 */

/// Searches through all available bundles and returns the first image with a specified name.
/// - Parameter imageName: The name of the image to find.
/// - Returns: The loaded image.
+ (UIImage*) loadImageNamed:(NSString*)imageName;

/// Base64 decode an image string.
/// - Parameter encodedImage: The image Base64 encoded to a string.
/// - Returns: The decoded UIImage.
+ (UIImage*) base64DecodeImage:(NSString*)encodedImage;

/// Rotates an image to a specific orientation.
/// - Parameters:
///   - image: The image to rotate.
///   - orientation: The requested image orientation.
/// - Returns: The rotated image.
+ (UIImage*) rotateImage:(UIImage*)image toOrientation:(UIImageOrientation)orientation;

/// Resizes an image to a specific size.
/// - Parameters:
///   - image: The image to resize.
///   - newSize: The requested image size.
/// - Returns: The resized image.
+ (UIImage*) resizeImage:(UIImage*)image toSize:(CGSize)newSize;

/*!
@functiongroup Video
*/

#if !TARGET_OS_VISION
/// Determines the current AVCaptureVideoOrientation for new video setup based on the status bar orientation.
/// - Returns: The current AVCaptureVideoOrientation.
+ (AVCaptureVideoOrientation) videoOrientation __deprecated;
#endif

#if !TARGET_OS_VISION
/// Determines the current orientation angle for new video setup based on the status bar orientation.
/// - Returns: The current orientation angle.
+ (CGFloat) videoRotationAngle __deprecated;;
#endif

/*!
 @functiongroup Device Information
 */

/// Determines if the current device is running iOS 9 and above.
/// - Returns: YES if the iOS version is >= 9.
+ (BOOL) isIos9AndAbove;

/// Determines if the current device is running iOS 11 and above.
/// - Returns: YES if the iOS version is >= 11.
+ (BOOL) isIos11AndAbove;

/// Determines the current device's platform version.
/// - Returns: The platform version, e.g. "iPhone10,3"
+ (NSString*) devicePlatform;

/// Determines if the current device supports the secure enclave.
/// - Returns: YES if the secure enclave is available.
+ (BOOL) deviceSupportsSecureEnclave;

/// Determines if Touch ID is supported by the current device.
/// - Returns: YES if biometrics are available.
+ (BOOL) isTouchIDSupported;

/// Determines if Touch ID is currently enabled.
/// - Returns: YES if biometrics are available and the current LAContext biometryType is LABiometryTypeTouchID or iOS version is < 11.
+ (BOOL) isTouchIDEnabled;

/// Determines if Face ID is supported by the current device.
/// - Returns: YES if Face ID is currently enabled or supported by the device.
+ (BOOL) isFaceIDSupported;

/// Determines if Face ID is currently enabled.
/// - Returns: YES if the current LAContext biometryType is LABiometryTypeFaceID.
+ (BOOL) isFaceIDEnabled;

/// Determines if dark mode has been enabled on the device.
/// - Returns: YES if dark mode is enabled.
+ (BOOL) isDarkModeEnabled;

/*!
 @functiongroup View Controllers
 */

/// Attempts to determine the current visible UIViewController, which can then be used for presenting authenticator UIViewController.
/// - Returns: The UIViewController that the SDK believes authenticator UIViewController's should be presented from.
+ (UIViewController*) determineHostViewController;

/// Overrides determineHostViewController to explicitly declare the host UIViewController.
/// - Parameter viewController: The UIViewController to set as the host.
+ (void) setHostViewController:(UIViewController*)viewController;

/// Presents a given UIViewController as the root of a host UIViewController.
/// - Parameters:
///   - viewController: The UIViewController to present.
///   - hostViewController: The UIViewController from which to present the UINavigationController.
+ (void) presentNavigationControllerWithRoot:(UIViewController*)viewController fromHost:(UIViewController*)hostViewController;

/*!
 @functiongroup Tokens
 */

/// Generates a token.
/// - Returns: The generated token.
+ (NSString*) generateAuthToken;

/*!
 @functiongroup Extensions
 */

/// Generates the standard set of response extensions.
/// - Parameters:
///   - startDate: The time that registration / authentication began.
///   - currentExtensions: The request extensions.
///   - authenticator: The authenticator that was used.
///   - addAuthToken: Whether or not to include an auth token.
///   - addLockInfo: Whether to include the current authenticator state information.
///   - error: The error information to include.
/// - Returns: An NSDictionary mapping extension keys to values (Both NSString).
+ (NSMutableDictionary*) buildReturnExtensionsWithStartTime:(NSDate*)startDate
                                          currentExtensions:(NSDictionary*)currentExtensions
                                              authenticator:(id<DASAuthenticator>)authenticator
                                               addAuthToken:(BOOL)addAuthToken
                                                addLockInfo:(BOOL)addLockInfo
                                               addErrorInfo:(NSError*)error;

/// Determines the correct response extension value for a DASAuthenticatorProtection type.
/// - Parameter protection: The DASAuthenticatorProtection type.
/// - Returns: An NSString containing the value string depending on the protection type.
+ (NSString*) extensionForKeyStoreType:(DASAuthenticatorProtection)protection;

/// Determines the correct response extension value for a DASAuthenticatorDataStore type.
/// - Parameter dataStore: The DASAuthenticatorDataStore type.
/// - Returns: An NSString containing the value string depending on the dataStore type.
+ (NSString*) extensionForDataStoreType:(DASAuthenticatorDataStore)dataStore;

/// Determines the correct response extension value for a DASAuthenticatorLockState type.
/// - Parameter lockState: The DASAuthenticatorLockState type.
/// - Returns: An NSString containing the value string depending on the lockState type.
+ (NSString*) extensionForLockState:(DASAuthenticatorLockState)lockState;

/*!
 @functiongroup Factors
 */

/// Determines whether a particular DASAuthenticatorFactor type supports ADoS.
/// - Parameter factor: The DASAuthenticatorFactor type to check.
/// - Returns: YES if ADoS is supported.
+ (BOOL) isADoSFactor:(DASAuthenticatorFactor)factor;

/// Determines whether a particular DASAuthenticatorFactor type requires Local Authentication (Touch ID or Face ID).
/// - Parameters:
///   - factor: The DASAuthenticatorFactor type to check.
///   - version: The version of the authenticator that supports the given factor.
/// - Returns: YES if Local Authentication is supported.
+ (BOOL) isLocalAuthenticatorFactor:(DASAuthenticatorFactor)factor version:(NSInteger)version;

/*!
 @functiongroup App-Extension Safe Methods (Work when "Require Only App-Extension-Safe API" flag is used)
 */

/// Sets whether the idle timer is disabled for the app.
/// - Parameter disabled: A Boolean value that controls whether the idle timer is disabled for the app.
+ (void) setIdleTimerDisabled:(BOOL)disabled;

#if !TARGET_OS_VISION
/// Gets the current orientation of the app's status bar.
/// - Returns: The current orientation of the app's status bar.
+ (UIInterfaceOrientation) statusBarOrientation;
#endif

/*!
 @functiongroup UI Constraints
 */

/// Adds constraints to a view which enforces that a child view is the same size as it's container view.
/// - Parameters:
///   - view: The view the constraint will be added to.
///   - containerView: The view that has the size we want.
///   - childView: The child view that needs to be made the same size as containerView.
+ (void) addConstrainEqualConstraintToView:(UIView*)view containerView:(UIView*)containerView childView:(UIView*)childView;

@end
