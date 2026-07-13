
#import <Foundation/Foundation.h>

/// User account.
/// 
@interface IXUAFAccount : NSObject

@property (nonatomic, strong) NSString * userName;

- (id)initWithName:(NSString *)userName;


@end
