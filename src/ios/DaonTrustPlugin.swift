import Foundation
import DaonTrustSDK
import DaonTrustSDKDocumentProcessor
import DaonTrustSDKAppkeysProcessor
import DaonTrustSDKDeviceIntegrityProcessor

@objc(DaonTrustPlugin)
class DaonTrustPlugin: CDVPlugin, DaonEventDelegate {
    private var callbackId: String?
    private var sdk: TrustSDK?

    @objc(startOnboarding:)
    func startOnboarding(command: CDVInvokedUrlCommand) {
        callbackId = command.callbackId

        let options = command.argument(at: 0) as? [String: Any]
        let serverUrl = "" // TEMP DEBUG: force QR flow to test bare presentation
guard let viewController = self.viewController else { return }
NSLog("DAON DEBUG: presentedViewController = %@", String(describing: viewController.presentedViewController))
NSLog("DAON DEBUG: viewController.view.window = %@", String(describing: viewController.view.window))
NSLog("DAON DEBUG: viewController class = %@", String(describing: type(of: viewController)))        print("DAON DEBUG: viewController = \(viewController), isViewLoaded = \(viewController.isViewLoaded), window = \(String(describing: viewController.view.window))")
        let sdkInstance = TrustSDK(withViewController: viewController, delegate: self)
        self.sdk = sdkInstance

        do {
    let documentProcessor = try DocumentProcessor.Builder().build()
    NSLog("DAON DEBUG: documentProcessor built OK")
    sdkInstance.addDocumentProcessor(documentProcessor)
    NSLog("DAON DEBUG: documentProcessor added OK")

    let appkeysProcessor = try AppkeysProcessor.Builder()
        .enableDebugLogs(true)
        .enableLocationUsage(false)
        .enableSilentBiometricRegistration(false)
        .setBiometricRegistrationReason("Secure your account with biometrics")
        .setBiometricAuthenticationReason("Verify your identity")
        .build()
    NSLog("DAON DEBUG: appkeysProcessor built OK")
    sdkInstance.addAppkeysProcessor(appkeysProcessor)
    NSLog("DAON DEBUG: appkeysProcessor added OK")

    let deviceIntegrityProcessor = DeviceIntegrityProcessor()
    NSLog("DAON DEBUG: deviceIntegrityProcessor created OK")
    sdkInstance.addDeviceIntegrityProcessor(deviceIntegrityProcessor)
    NSLog("DAON DEBUG: deviceIntegrityProcessor added OK")

    let daonOptions = DaonOptions()
    if !serverUrl.isEmpty {
        daonOptions.serverUrl = serverUrl
    }
    NSLog("DAON DEBUG: about to call sdk.start, serverUrl empty = %@", "\(serverUrl.isEmpty)")

    sdkInstance.start(withDaonOptions: daonOptions)
    NSLog("DAON DEBUG: sdk.start returned (call completed, not necessarily flow completed)")
} catch {
    NSLog("DAON DEBUG: CAUGHT ERROR = %@", error.localizedDescription)
    sendEvent(type: "failure", message: error.localizedDescription, keepCallback: false)
}
    }

    func didReceive(successResponse daonEvent: DaonEvent) {
    NSLog("DAON DEBUG: successResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
    sendEvent(type: "success", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: true)
}

func didReceive(failedResponse daonEvent: DaonEvent) {
    NSLog("DAON DEBUG: failedResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
    sendEvent(type: "failure", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: false)
}

func didReceive(infoResponse daonEvent: DaonEvent) {
    NSLog("DAON DEBUG: infoResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
    sendEvent(type: "info", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: true)
}

    private func sendEvent(type: String, message: String, keepCallback: Bool) {
        guard let callbackId else { return }

        let payload: [String: Any] = [
            "type": type,
            "message": message
        ]

        let pluginResult = CDVPluginResult(status: .ok, messageAs: payload)
        pluginResult?.setKeepCallbackAs(keepCallback)
        self.commandDelegate.send(pluginResult, callbackId: callbackId)
    }
}