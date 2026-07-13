
#import <Foundation/Foundation.h>
#import <DaonFIDOSDK/IXUAFVersion.h>
#import <DaonFIDOSDK/IXUAFAuthenticator.h>

/// FIDO authenticator discovery data.
/// 
@interface IXUAFDiscoveryData : NSObject

@property (nonatomic, strong) NSArray<IXUAFVersion *> *supportedUafVersions;
@property (nonatomic, strong) NSString *clientVendor;
@property (nonatomic, strong) IXUAFVersion *clientVersion;
@property (nonatomic, strong) NSArray<IXUAFAuthenticator*> *availableAuthenticators;

- (id)initWithSupportedUafVersions:(NSArray<IXUAFVersion *> *)supportedUafVersions
                      clientVendor:(NSString *)clientVendor
                    clientVersions:(IXUAFVersion *)clientVersion
                    authenticators:(NSArray<IXUAFAuthenticator*> *)availableAuthenticators;
@end
