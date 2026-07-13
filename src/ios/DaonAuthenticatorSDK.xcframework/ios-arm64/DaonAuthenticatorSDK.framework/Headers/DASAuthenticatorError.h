//
//  DASAuthenticatorError.h
//  DaonAuthenticatorSDK
//
//  Copyright © 2016-25 Daon. All rights reserved.
//

#ifndef DASAuthenticatorError_h
#define DASAuthenticatorError_h

/// Categorizes the different types of errors that can be produced from the Authenticator SDK.
/// For more details, see the localisations in DAS-Errors.strings.
typedef NS_ENUM (NSInteger, DASAuthenticatorError)
{
    DASAuthenticatorErrorNone                                       = -1,
    
    // Flow
    DASAuthenticatorErrorCancelled                                  = 0,
    DASAuthenticatorErrorADoSAbort                                  = 1,
    DASAuthenticatorErrorFallback                                   = 2,
    DASAuthenticatorErrorAbort                                      = DASAuthenticatorErrorADoSAbort,
    
    // Permissions
    DASAuthenticatorErrorNoCameraPermission                         = 50,
    DASAuthenticatorErrorNoMicrophonePermission                     = 51,
    DASAuthenticatorErrorNoBiometricsPermission                     = 52,
    
    // Authenticators
    DASAuthenticatorErrorAuthenticatorNotImplemented                        = 100,
    DASAuthenticatorErrorAuthenticatorNotSupported                          = 101,
    DASAuthenticatorErrorAuthenticatorNoHostViewController                  = 102,
    DASAuthenticatorErrorAuthenticatorTooManyAttemptsTempLocked             = 103,
    DASAuthenticatorErrorAuthenticatorTooManyAttemptsPermLocked             = 104,
    DASAuthenticatorErrorAuthenticatorMissingAuthToken                      = 105,
    DASAuthenticatorErrorAuthenticatorAuthTokenMismatch                     = 106,
    DASAuthenticatorErrorAuthenticatorInconsistentState                     = 107,
    DASAuthenticatorErrorCantStartMultiAuthenticator                        = 108,
    DASAuthenticatorErrorCantStartMultiAuthenticatorTempLock                = 109,
    DASAuthenticatorErrorCantStartMultiAuthenticatorPermLock                = 110,
    DASAuthenticatorErrorCantStartMultiAuthenticatorAllLocked               = 111,
    DASAuthenticatorErrorCantSwitchToAuthenticatorTempLocked                = 112,
    DASAuthenticatorErrorCantSwitchToAuthenticatorPermLocked                = 113,
    DASAuthenticatorErrorFailedToSign                                       = 114,
    DASAuthenticatorErrorCannotContinueRemainingAuthIsTempLocked            = 115,
    DASAuthenticatorErrorCannotContinueRemainingAuthIsPermLocked            = 116,
    DASAuthenticatorErrorFailedToWriteEnrollmentData                        = 117,
    DASAuthenticatorErrorFailedToReadEnrollmentData                         = 118,
    DASAuthenticatorErrorFailedToEncryptEnrollmentData                      = 119,
    DASAuthenticatorErrorFailedToDecryptEnrollmentData                      = 120,
    DASAuthenticatorErrorFailedToLoadLocalDataKey                           = 121,
    DASAuthenticatorErrorLocalAuthenticationEnrollmentHasChanged            = 122,
    DASAuthenticatorErrorCantStartMultiAuthenticatorOnlyNonUIAuthsAvailable = 123,
    DASAuthenticatorErrorCantStartMultiAuthenticatorNonUIInMCPolicy         = 124,
    DASAuthenticatorErrorNoBiometrics                                       = 125,
    DASAuthenticatorErrorCouldNotFindViewController                         = 126,
    DASAuthenticatorErrorCantStartMultiAuthenticatorNoPolicyViewController  = 127,
    
    // Password Collection
    DASAuthenticatorErrorPasswordFailedToVerify                     = 200,
    DASAuthenticatorErrorPasswordIsEmpty                            = 201,
    DASAuthenticatorErrorPasswordMismatch                           = 202,
    DASAuthenticatorErrorPasswordMultipleFailedAttempts             = 203,
    DASAuthenticatorErrorPasswordRequired                           = 204,
    DASAuthenticatorErrorPasswordAllowed                            = 205,
    DASAuthenticatorErrorPasswordDisallowed                         = 206,
    DASAuthenticatorErrorPasswordRequiredNumberOfDigits             = 207,
    DASAuthenticatorErrorPasswordRequiredNumberOfUppercaseLetters   = 208,
    DASAuthenticatorErrorPasswordRequiredNumberOfLowercaseLetters   = 209,
    DASAuthenticatorErrorPasswordRequiredNumberOfSymbols            = 210,
    DASAuthenticatorErrorPasswordRequiredVariety                    = 211,
    DASAuthenticatorErrorPasswordReenrollMismatch                   = 212,
    
    // Face Collection
    DASAuthenticatorErrorFaceRecognitionTimeout                     = 300,
    DASAuthenticatorErrorFaceRegistrationFailed                     = 301,
    DASAuthenticatorErrorFaceQualityCheckFailedReasonUnknown        = 302,
    DASAuthenticatorErrorFaceQualityCheckFailedFaceNotFound         = 303,
    DASAuthenticatorErrorFaceQualityCheckFailedFaceNotFrontal       = 304,
    DASAuthenticatorErrorFaceQualityCheckFailedEyesNotFound         = 305,
    DASAuthenticatorErrorFaceQualityCheckFailedEyesNotOpen          = 306,
    DASAuthenticatorErrorFaceQualityCheckFailedLightingNotUniform   = 307,
    DASAuthenticatorErrorFaceQualityCheckFailedFaceTooFarAway       = 308,
    DASAuthenticatorErrorFaceQualityCheckFailedHeadTilted           = 309,
    DASAuthenticatorErrorFaceQualityCheckFailedImageNotSharp        = 310,
    DASAuthenticatorErrorFaceQualityCheckFailedPoorImageExposure    = 311,
    DASAuthenticatorErrorFaceQualityCheckFailedGrayscaleDensity     = 312,
    DASAuthenticatorErrorFaceNotVisible                             = 313,
    DASAuthenticatorErrorFaceMultipleFailedAttempts                 = 314,
    DASAuthenticatorErrorFaceNoModelsFound                          = 315,
    DASAuthenticatorErrorFaceLicenseExpired                         = 316,
    DASAuthenticatorErrorFaceQualityCheckFailedDeviceNotUpright     = 317,
    DASAuthenticatorErrorFaceLicenseMissing                         = 318,
    DASAuthenticatorErrorFaceLicenseInvalid                         = 319,
    DASAuthenticatorErrorFaceLivenessAtRegistrationTimeout         = 320,
    DASAuthenticatorErrorFaceLostFaceContinuity                     = 321,
    DASAuthenticatorErrorFaceFailedToAuthenticate                   = 322,
    DASAuthenticatorErrorFaceRecognitionTimeoutNoFaceDetected       = 323,
    DASAuthenticatorErrorFaceLivenessAlertFaceNotDetected           = 324,
    DASAuthenticatorErrorFaceLivenessAlertFaceNotCentered           = 325,
    DASAuthenticatorErrorFaceLivenessAlertMotionTooFast             = 326,
    DASAuthenticatorErrorFaceLivenessAlertMotionSwingTooFast        = 327,
    DASAuthenticatorErrorFaceLivenessAlertMotionTooFar              = 328,
    DASAuthenticatorErrorFaceLivenessAlertFaceTooCloseToEdge        = 329,
    DASAuthenticatorErrorFaceLivenessAlertFaceTooNear               = 330,
    DASAuthenticatorErrorFaceLivenessAlertFaceTooFar                = 331,
    DASAuthenticatorErrorFaceLivenessCheckFailed                    = 332,
    DASAuthenticatorErrorFaceLivenessCheckSpoof                     = 333,
    DASAuthenticatorErrorFaceLivenessCheckEyesClosed                = 334,
    DASAuthenticatorErrorFaceLivenessAlertInsufficientFaceData      = 335,
    DASAuthenticatorErrorFaceLivenessAlertInsufficientFrameData     = 336,
    DASAuthenticatorErrorFaceLivenessAlertFrameMismatch             = 337,
    DASAuthenticatorErrorFaceLivenessAlertNoMovementDetected        = 338,
    DASAuthenticatorErrorFaceTemplateMatchingRegNotSupported        = 339,
    DASAuthenticatorErrorFaceTemplateNilOrEmpty                     = 340,
    DASAuthenticatorErrorFaceQualityCheckFailedFaceTooClose         = 341,
    DASAuthenticatorErrorFaceQualityCheckMaskDetected               = 342,
    DASAuthenticatorErrorFaceQualityCheckFailedPoorLighting         = 343,
    DASAuthenticatorErrorFaceLivenessResolutionTooLow               = 344,
    DASAuthenticatorErrorFaceIFPRequired                            = 345,
    
    // Voice Collection
    DASAuthenticatorErrorVoiceUnknownError                  = 700,
    DASAuthenticatorErrorVoiceCouldNotStartRecording        = 701,
    DASAuthenticatorErrorVoiceCouldNotSaveSample            = 702,
    DASAuthenticatorErrorVoiceNotRecording                  = 703,
    DASAuthenticatorErrorVoiceFailedTooSoft                 = 704,
    DASAuthenticatorErrorVoiceFailedTooNoisy                = 705,
    DASAuthenticatorErrorVoiceFailedTooSoftSpeechClarity    = 706,
    DASAuthenticatorErrorVoiceFailedUtteranceTooShort       = 707,
    DASAuthenticatorErrorVoiceFailedTooLoud                 = 708,
    DASAuthenticatorErrorVoiceFailedFileIsCorruptedOrEmpty  = 709,
    DASAuthenticatorErrorVoiceFailedWrongUtteranceDetected  = 710,
    DASAuthenticatorErrorVoiceFailedBackgroundModelMismatch = 711,
    DASAuthenticatorErrorVoiceCouldNotGenerateTemplate      = 712,
    DASAuthenticatorErrorVoiceCouldNotLoadTemplate          = 713,
    DASAuthenticatorErrorVoiceFailedToAuthenticate          = 714,
    DASAuthenticatorErrorVoiceMultipleFailedAttempts        = 715,
    DASAuthenticatorErrorVoiceTimeout                      = 716,
    DASAuthenticatorErrorVoiceMissingModelFiles             = 717,
    DASAuthenticatorErrorVoiceCouldNotEncodeSample          = 718,
    DASAuthenticatorErrorVoiceFailedUnsupportedFormat       = 719,
    
    // Touch ID
    DASAuthenticatorErrorFingerprintFailedToVerify          = 800,
    DASAuthenticatorErrorFingerprintMultipleFailedAttempts  = 801,
    
    // Face ID
    DASAuthenticatorErrorFaceIdFailedToVerify               = 900,
    DASAuthenticatorErrorFaceIdMultipleFailedAttempts       = 901,
    
    // Local Authentication
    DASAuthenticatorErrorLocalAuthRetryLimitExceeeded       = 1000,
    DASAuthenticatorErrorLocalAuthBiometryLockedOut         = 1001,
    DASAuthenticatorErrorLocalAuthBiometryNotAvailable      = 1002,
    DASAuthenticatorErrorLocalAuthPasscodeNotSet            = 1003,
    DASAuthenticatorErrorLocalAuthBiometryNotEnrolled       = 1004,
    DASAuthenticatorErrorLocalAuthCancelled                 = 1005, // Only reported back on Face ID as we do not get any other errors back from the OS.
    DASAuthenticatorErrorLocalAuthFailed                    = 1006,
    
    // ADoS (Client) Errors
    DASAuthenticatorErrorADoSInvalidPasscodeData            = 1100,
    DASAuthenticatorErrorADoSCouldNotGenerateValidator      = 1101,
    DASAuthenticatorErrorADoSCouldNotGenerateEvidence       = 1102,
    DASAuthenticatorErrorADoSCouldNotValidateServerResponse = 1103,
    DASAuthenticatorErrorADoSMissingServerParameters        = 1104,
    DASAuthenticatorErrorADoSTooManyAttemptsServerLocked    = 1105,
    DASAuthenticatorErrorADoSReenrollDataMissing            = 1106,
    
    // OTP Errors
    DASAuthenticatorErrorOTPFailedToGenerateKeys            = 1200,
    DASAuthenticatorErrorOTPMissingAuthenticationData       = 1201,
    DASAuthenticatorErrorOTPFailedToGenerateOTP             = 1202,
    DASAuthenticatorErrorOTPInvalidTransactionData          = 1203,
    DASAuthenticatorErrorOTPCannotAccessCamera              = 1204,
    
    // Palm Collection
    DASAuthenticatorErrorPalmFailedToStartDecoder           = 1300,
    DASAuthenticatorErrorPalmMissingLicense                 = 1301, // Not used
    DASAuthenticatorErrorPalmInvalidLicense                 = 1302,
    DASAuthenticatorErrorPalmMissingEnrollmentData          = 1303,
    DASAuthenticatorErrorPalmCouldNotSaveEnrollmentData     = 1304,
    DASAuthenticatorErrorPalmFailedToStartDecoderAgain      = 1305,
    DASAuthenticatorErrorPalmFailedToVerifyPalm             = 1306,
    DASAuthenticatorErrorPalmMultipleFailedAttempts         = 1307,
    DASAuthenticatorErrorPalmRecognitionTimeout             = 1308,
    DASAuthenticatorErrorPalmAuthenticationLivenessFailed   = 1309,
    DASAuthenticatorErrorPalmExpectedLeftPalmGotRightPalm   = 1310,
    DASAuthenticatorErrorPalmExpectedRightPalmGotLeftPalm   = 1311,
    DASAuthenticatorErrorPalmRecognitionTimeoutNoPalmDetected = 1312,
    
    // ADoS (Server) Errors
    // All *known* server errors are contained in the
    // DAS-Errors.strings file for customization.
    DASAuthenticatorErrorServerUnknownError             = 10000,
    DASAuthenticatorErrorServerRecapture                = 11501,
    DASAuthenticatorErrorServerTooManyAttempts          = 11600,
    DASAuthenticatorErrorServerUserLockout              = 11601,
    DASAuthenticatorErrorServerFaceTooManyAttempts      = 11602,
    DASAuthenticatorErrorServerVoiceTooManyAttempts     = 11603,
    DASAuthenticatorErrorServerPasscodeTooManyAttempts  = 11604

};

#endif /* DASAuthenticatorError_h */
