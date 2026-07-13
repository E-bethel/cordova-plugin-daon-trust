
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


typedef void (^Block)(CLLocation* location);

/// Location service
///
/// The IXUAFLocator class implements a location service which must be started and stopped by the app in order for the FIDO SDK to collect location information.
///
/// Once started, the service will continue to run until it is manually stopped or the timeout is triggered. If locate is called while the service is already running, the service continues to run.
///
@interface IXUAFLocator : NSObject <CLLocationManagerDelegate>
{
	CLLocationManager *locationmanager;
    CLLocation *currentLocation;
    id delegate;
    BOOL locating;

}

+ (IXUAFLocator*) sharedInstance;

/// Run locator for 30 seconds
- (void) locate;

/// Start locator.
///
/// - Parameter accuracy: The location accuracy.
/// - Parameter timeout: The location timeout in seconds.
- (void) locateWithAccuracy:(CLLocationAccuracy)accuracy timeout:(NSTimeInterval)timeout;

/// Stop locating.
///
- (void) cancelUpdatingLocation;

/// Get current location
///
/// This method should be called after a call to locate or locateWithAccuracy:timout.
///
/// - Returns: The current location
- (CLLocation*) location;

@end
