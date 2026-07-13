
#import <Foundation/Foundation.h>

/// FIDO UAF version object.
///
@interface IXUAFVersion : NSObject

@property (nonatomic, assign) NSInteger major;
@property (nonatomic, assign) NSInteger minor;


- (id)initWithMajor:(NSInteger)major minor:(NSInteger)minor;

- (NSString*) stringValue;

- (NSDictionary*) dictionary;
@end
