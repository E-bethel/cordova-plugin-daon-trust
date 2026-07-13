//
//  DASExtensions.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/8/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#ifndef DASExtensions_h
#define DASExtensions_h

/////////////////////////////////////////////////////
// Extension KEYS coming IN to the SDK
/////////////////////////////////////////////////////

// Common - General
static NSString * const KDASExtensionKeysAccessibility                      = @"keys.accessibility";
static NSString * const KDASExtensionAuthenticatorReenroll                  = @"reenroll";
static NSString * const KDASExtensionAuthenticatorCancelOnBackground        = @"background.cancel";
static NSString * const KDASExtensionAuthenticatorPrecedence                = @"com.daon.sdk.authenticator.precedence";
static NSString * const KDASExtensionAuthenticatorOperation                 = @"authenticator.operation";
static NSString * const KDASExtensionAuthenticatorOperationRegister         = @"reg";
static NSString * const KDASExtensionAuthenticatorOperationAuthenticate     = @"auth";
static NSString * const KDASExtensionFilterNonUIAuthenticators              = @"com.daon.sdk.filter.non.ui.authenticators";
static NSString * const KDASExtensionSigningTimeout                         = @"sign.timeout";

// Common - Locking
static NSString * const KDASExtensionAuthenticatorLockMaxAttempts           = @"lock.max.attempts"; // Attempts before suspension
static NSString * const KDASExtensionAuthenticatorLockMaxUnlocks            = @"lock.max.unlocks";  // Unlocks before permanent lock
static NSString * const KDASExtensionAuthenticatorLockInitialSuspendTime    = @"lock.suspend.init"; // Initial Suspension period in milliseconds
static NSString * const KDASExtensionAuthenticatorLockSuspendTimeIncrement  = @"lock.suspend.inc";  // Suspension increment between unlocks
static NSString * const KDASExtensionAuthenticatorUnlock                    = @"unlock";

static NSString * const KDASExtensionAuthenticatorADoSLockMaxAttempts       = @"maxAttempts";

// Passcode
static NSString * const KDASExtensionPasscodeLengthMin                      = @"length.min";
static NSString * const KDASExtensionPasscodeLengthMax                      = @"length.max";
static NSString * const KDASExtensionPasscodeType                           = @"type";
static NSString * const KDASExtensionPasscodeWeakCodes                      = @"weakcodes";   // Not Implemented

// Pattern
static NSString * const KDASExtensionPatternLengthMin                       = @"length.min";  // Not Implemented
static NSString * const KDASExtensionPatternLengthMax                       = @"length.max";  // Not Implemented
static NSString * const KDASExtensionPatternType                            = @"type";        // Not Implemented
static NSString * const KDASExtensionPatternWeakCodes                       = @"weakcodes";   // Not Implemented
static NSString * const KDASExtensionPatternInvalid                         = @"invalid";     // Not Implemented

// Face
static NSString * const KDASExtensionFaceRecognitionThreshold               = @"recognition.threshold";
static NSString * const KDASExtensionFaceRecognitionShowFace                = @"recognition.show.face";
static NSString * const KDASExtensionFaceRecognitionTimeout                 = @"recognition.timeout";
static NSString * const KDASExtensionFaceLivenessThreshold                  = @"liveness.threshold";
static NSString * const KDASExtensionFaceLivenessAtEnrollmentContinuity     = @"liveness.enroll.continuity";
static NSString * const KDASExtensionFaceLivenessContinuityStrict           = @"liveness.continuity.strict";
static NSString * const KDASExtensionFaceLivenessServerResolution           = @"liveness.server.resolution";
static NSString * const KDASExtensionFaceQualityThreshold                   = @"quality.threshold";
static NSString * const KDASExtensionFaceQualityThresholdRange              = @"quality.threshold.range";
static NSString * const KDASExtensionFaceLicense                            = @"license";
static NSString * const KDASExtensionFaceLicenseOrganisation                = @"license.organization";
static NSString * const KDASExtensionFaceSaveEnrollmentDataDEPRECATED       = @"save.enrollment"; // Not consistent with Android, use KDASExtensionFaceV3SaveEnrollmentData instead.
static NSString * const KDASExtensionFaceSaveEnrollmentData                 = @"save.enrollment.data";
static NSString * const KDASExtensionFaceEnrollmentQualityCounterEnabled    = @"enrollment.quality.counter.enabled";
static NSString * const KDASExtensionFaceEnrollmentQualityCounterMax        = @"enrollment.quality.counter.max";
static NSString * const KDASExtensionFaceActiveLivenessType                 = @"liveness.active.type";
static NSString * const KDASExtensionFacePassiveLivenessType                = @"liveness.passive.type";
static NSString * const KDASExtensionFaceRequiresEyesOpen                   = @"require.eyes.open"; 
static NSString * const KDASExtensionFaceRequiresEyesOpenFavorPerformance   = @"require.eyes.open.favor.performance";
static NSString * const KDASExtensionFaceLivenessSecurityLevel              = @"liveness.security.level";


static NSString * const KDASExtensionFaceImageQuality            = @"image.quality";  // 0.9f (default)
static NSString * const KDASExtensionFaceImageFormat             = @"image.format"; // jpeg (default) | png
static NSString * const KDASExtensionFaceIFPRequired             = @"requireInjectionDetectionPayload";
static NSString * const KDASExtensionFaceIFPEnabled              = @"liveness.ifp";

// Liveness Hold phase duration in milliseconds
static NSString * const KDASExtensionFaceLivenessStartDelay               = @"liveness.start.delay";


static NSString * const KDASExtensionFaceLivenessTemplate                 = @"liveness.template";
static NSString * const KDASExtensionFaceLivenessTemplateQuality          = @"liveness.template.quality";
static NSString * const KDASExtensionFaceLivenessTimeout                  = @"liveness.timeout";

// Voice
static NSString * const KDASExtensionVoiceRecognitionThreshold              = @"recognition.threshold";
static NSString * const KDASExtensionVoiceRecognitionTimeout                = @"recognition.timeout";
static NSString * const KDASExtensionVoiceQualityCheckEnabled               = @"quality.check.enabled";
static NSString * const KDASExtensionVoiceTextValidationEnabled             = @"text.validation.enabled";
static NSString * const KDASExtensionVoiceMaxLoudnessThreshold              = @"max.loudness.threshold";
static NSString * const KDASExtensionVoiceMinVoiceActivityLevelThreshold    = @"min.voice.activity.level.threshold";
static NSString * const KDASExtensionVoiceMinDurationThreshold              = @"min.duration.threshold";
static NSString * const KDASExtensionVoiceMinSignalLevelThreshold           = @"min.signal.level.threshold";
static NSString * const KDASExtensionVoiceMinTextValidationScoreThreshold   = @"min.text.validation.score.threshold";
static NSString * const KDASExtensionVoiceMaxTextValidationAlignThreshold   = @"max.text.validation.align.threshold";
static NSString * const KDASExtensionVoiceEnrollmentQualityCounterEnabled   = @"enrollment.quality.counter.enabled";
static NSString * const KDASExtensionVoiceEnrollmentQualityCounterMax       = @"enrollment.quality.counter.max";
static NSString * const KDASExtensionVoiceSubmitOnTimeout                   = @"submit.on.timeout";

// Local Authentication
static NSString * const KDASExtensionFaceIdEnabled                          = @"com.daon.sdk.embedded.face";
static NSString * const KDASExtensionDisableADoSFaceOnFaceIdDevice          = @"com.daon.sdk.disable.ados.face.on.faceid.device";
static NSString * const KDASExtensionLocalAuthEmbeddedUIEnabled             = @"embedded.ui.enabled";
static NSString * const KDASExtensionLocalAuthEmbeddedUIReason              = @"embedded.ui.reason"; // Touch ID Only
static NSString * const KDASExtensionLocalAuthenticationEnrollmentCurrent   = @"enrollment.current.only";
static NSString * const KDASExtensionLocalAuthenticationEnrollmentSilent    = @"silent";
static NSString * const KDASExtensionLocalAuthenticationLocking             = @"sdk.locking";
static NSString * const KDASExtensionLocalAuthenticationKeychainAccess      = @"keys.access.biometry";
// Palm
static NSString * const KDASExtensionPalmLicenseKey                         = @"license.key";
static NSString * const KDASExtensionPalmUseFrontCamera                     = @"useFrontCamera";
static NSString * const KDASExtensionPalmRecognitionTimeout                 = @"recognition.timeout";
static NSString * const KDASExtensionPalmAuthenticationLivenessEnabled      = @"liveness.verify";
static NSString * const KDASExtensionPalmRegistrationSidednessEnforced      = @"sidedness.enforced";

// ADoS authentication request extensions from server
static NSString * const KADoSMode                                           = @"ados.mode";
static NSString * const KADoSModeHint                                       = @"ados.mode.hint";

// ADoS capture response extensions from server
static NSString * const KADoSAuthenticationStatusCode                       = @"authStatusCode";    // Currently unused
static NSString * const KADoSAuthenticationRetriesRemaining                 = @"retriesRemaining";

// ADoS SRP
// Multiple extensions allowed, e.g. allowedRegEx.1. Error messages may
// be associated with regex match failures via extensions, e.g. disallowedRegEx.1.message

// *** Preferred class: This used to be set in the plist, but breaks framework signing ***
// com.daon.sdk.<factor>.preferred = <plist item index>

static NSString * const KDASExtensionSRPPatternRegexAllowed                 = @"allowedRegEx";       // Acceptable passcode patterns.
static NSString * const KDASExtensionSRPPatternRegexRequired                = @"requiredRegEx";      // Required passcode patterns.
static NSString * const KDASExtensionSRPPatternRegexDisallowed              = @"disallowedRegEx";    // Disallowed passcode patterns.
static NSString * const KDASExtensionSRPPatternErrorMessage                 = @"message";            // Currently unused

static NSString * const KDASExtensionSRPPatternRequiredDigitCount           = @"requiredDigitCount";
static NSString * const KDASExtensionSRPPatternRequiredUppercaseCount       = @"requiredUpperCaseCount";
static NSString * const KDASExtensionSRPPatternRequiredLowercaseCount       = @"requiredLowerCaseCount";
static NSString * const KDASExtensionSRPPatternRequiredSymbolCount          = @"requiredSymbolCount";
static NSString * const KDASExtensionSRPPatternRequiredVarietyCount         = @"requiredVarietyCount";
static NSString * const KDASExtensionSRPPatternDenyConsecutive              = @"denyConsecutive";   // Currently unused

static NSString * const KDASExtensionSRPParam_I                             = @"I";
static NSString * const KDASExtensionSRPParam_s                             = @"s";
static NSString * const KDASExtensionSRPParam_N                             = @"N";
static NSString * const KDASExtensionSRPParam_g                             = @"g";
static NSString * const KDASExtensionSRPParam_H                             = @"H";
static NSString * const KDASExtensionSRPParam_v                             = @"v";
static NSString * const KDASExtensionSRPParam_B                             = @"B";
static NSString * const KDASExtensionSRPParam_M2                            = @"M2";

// OTP
static NSString * const KDASExtensionOTPMode                                = @"otp.mode";
static NSString * const KDASExtensionOTPKeyChain                            = @"ootpKeyChain";          // OTP Key cert chain
static NSString * const KDASExtensionOTPAlgorithm                           = @"ootpAlgorithm";         // HMAC 256
static NSString * const KDASExtensionOTPTimeStep                            = @"ootpTimeStep";          // In seconds, default 30
static NSString * const KDASExtensionOTPLength                              = @"ootpLength";            // 6-8


/////////////////////////////////////////////////////
// Extension KEYS going OUT of the SDK
/////////////////////////////////////////////////////

// Common
static NSString * const KDASExtensionInfoDuration                           = @"info.time";
static NSString * const KDASExtensionInfoAttempts                           = @"info.attempts";
static NSString * const KDASExtensionInfoState                              = @"state";
static NSString * const KDASExtensionInfoLockDuration                       = @"lockedUntil";
static NSString * const KDASExtensionErrorCode                              = @"error.code";
static NSString * const KDASExtensionErrorMessage                           = @"error.message";
static NSString * const KDASExtensionAuthToken                              = @"token";
static NSString * const KDASExtensionInfoKeyStoreType                       = @"keyStoreType";
static NSString * const KDASExtensionInfoDataStoreType                      = @"dataStoreType";

// Face
static NSString * const KDASExtensionInfoFaceRecognitionScore               = @"face.recognition.score";
static NSString * const KDASExtensionInfoFaceRecognitionDuration            = @"face.recognition.time";
static NSString * const KDASExtensionInfoFaceLivenessDuration               = @"face.liveness.time";
static NSString * const KDASExtensionInfoFaceLivenessScore                  = @"face.liveness.score.ext";
static NSString * const KDASExtensionInfoFaceImage                          = @"face.image";

// Voice
static NSString * const KDASExtensionInfoVoiceRecognitionScore              = @"voice.recognition.score";
static NSString * const KDASExtensionInfoVoiceRecognitionTime               = @"voice.recognition.time";

// OTP
static NSString * const KDASExtensionOTPData                                = @"otp.data";
static NSString * const KDASExtensionOTPToken                               = @"otp.token";
static NSString * const KDASExtensionOTPTokenTTL                            = @"otp.ttl";
static NSString * const KDASExtensionOTPPubKey                              = @"otp.ecdhPubKey";
static NSString * const KDASExtensionOTPPubKeyFormat                        = @"otp.ecdhPubKeyFormat";

/////////////////////////////////////////////////////
// VALUES that can be assigned to extension KEYS
/////////////////////////////////////////////////////

// Keyboard Types
static NSString * const KDASExtensionKeyboardTypeAlphaNumeric               = @"ALPHANUMERIC";
static NSString * const KDASExtensionKeyboardTypeNumeric                    = @"NUMERIC"; // Currently unused, If "ALPHANUMERIC" is not provided, "NUMERIC" is assumed.

// Boolean Values
static NSString * const KDASExtensionValueTrue                              = @"true";
static NSString * const KDASExtensionValueFalse                             = @"false";

// Key Store Types
static NSString * const KDASExtensionKeyStoreTypeHardware                   = @"HardwareOS";
static NSString * const KDASExtensionKeyStoreTypeSoftware                   = @"Software";

// Data Store Types
static NSString * const KDASExtensionDataStoreTypeOS                        = @"OS";
static NSString * const KDASExtensionDataStoreTypeSoftware                  = @"Software";
static NSString * const KDASExtensionDataStoreTypeNone                      = @"None";

// Locked states
static NSString * const KDASExtensionLockStateUnlocked                      = @"AVAIL";
static NSString * const KDASExtensionLockStateTemporary                     = @"TEMP_BLOCK";
static NSString * const KDASExtensionLockStatePermanent                     = @"PERM_BLOCK";

// ADoS mode values
static NSString * const KADoSModeEnrol                                      = @"enrol";
static NSString * const KADoSModeVerify                                     = @"verify";
static NSString * const KADoSModeVerifyAndReenroll                          = @"verifyAndReenrol";

// ADoS lock values
static NSString * const KADoSLockPermanent                                  = @"PERMANENT";         // Currently unused
static NSString * const KADoSLockTemporary                                  = @"TEMPORARY";         // Currently unused
static NSString * const KADoSCaptureDataSchemeID                            = @"capture.schemeId";  // Currently unused
static NSString * const KADoSCaptureDataIV                                  = @"capture.iv";        // Currently unused
static NSString * const KADoSCaptureData                                    = @"capture.data";      // Currently unused
static NSString * const KADoSCaptureDataEncryptionKey                       = @"capture.cdek";      // Currently unused

// Active liveness types
static NSString * const KActiveLivenessTypeNone                             = @"none";
static NSString * const KActiveLivenessTypeBlink                            = @"blink";


// Passive liveness types
static NSString * const KPassiveLivenessTypeNone                            = @"none";
static NSString * const KPassiveLivenessTypeClient                          = @"client";
static NSString * const KPassiveLivenessTypeServer                          = @"server";

// OTP
static NSString * const KOTPModeSign                                        = @"1";

#endif /* DASExtensions_h */
