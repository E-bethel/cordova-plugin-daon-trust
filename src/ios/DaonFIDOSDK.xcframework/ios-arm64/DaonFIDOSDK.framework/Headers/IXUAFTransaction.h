
#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, IXUAFOfflineOTPMode)
{
    IXUAFOfflineOTPModeIdentify   = 0,  // User authenticates then the OTP is displayed.
    IXUAFOfflineOTPModeSign  = 1,       // User authenticates, enters transaction data / scans QR code, then the OTP is displayed.
};

typedef NS_ENUM (NSInteger, IXUAFTransactionContentType)
{
    IXUAFTransactionContentTypeUnknown  = 0,
    IXUAFTransactionContentTypePNG      = 1,
    IXUAFTransactionContentTypeText     = 2
};

/// FIDO UAF Transaction Confirmation
///
/// The IXUAFTransaction object is provided to the delegate, `operation:shouldDisplayTransaction` when a transaction confirmation needs to be displayed to the user.

@interface IXUAFTransaction : NSObject


- (id)initWithDictionary:(NSDictionary *)dictionary;


/// Accept or reject transaction.
///
/// - Parameter accept: Set to true to accept or false reject the transaction.
- (void) accept:(BOOL)accept;

/// Get content type.
///
/// - Returns: The content type, for example, `PNG` image or `TEXT`
///
- (IXUAFTransactionContentType) contentType;

/// Get PNG image or TEXT content.
///
/// #### Swift example
/// ```swift
///
/// if transaction != nil {
///     switch transaction!.contentType() {
///         case IXUAFTransactionContentType.PNG:
///             let decodedImageData = transaction!.content()
///             self.transactionImageView.image = UIImage(data: decodedImageData!)
///
///         case IXUAFTransactionContentType.text:
///             self.transactionTextView.text = String(data: transaction!.content(), encoding: String.Encoding.utf8)
///
///         default:
///            self.transactionTextView.text = "ERROR: Unknown Transaction Type."
///     }
/// } else {
///     self.transactionTextView.text = "ERROR: No Transaction."
/// }
/// ```
///
/// #### Objective-C example
/// ```objective-c
/// if (transaction) {
///     switch (transaction.contentType) {
///         case IXUAFTransactionContentTypePNG:
///             self.transactionImageView.image = [UIImage imageWithData:transaction.content];
///             break;
///
///         case IXUAFTransactionContentTypeText:
///             self.transactionTextView.text = [[NSString alloc] initWithData:transaction.content encoding:NSUTF8StringEncoding];
///             break;
///
///         default:
///             self.transactionTextView.text = @"ERROR: Unknown Transaction Type.";
///     }
/// } else {
///     self.transactionTextView.text = @"ERROR: No Transaction.";
/// }
/// ```
///
/// - Returns: The NSData object with the content.
- (NSData*) content;



@end
