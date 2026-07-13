import Foundation
import AVFoundation
import DaonTrustSDK
import DaonTrustSDKDocumentProcessor
import DaonTrustSDKAppkeysProcessor
import DaonTrustSDKDeviceIntegrityProcessor

@objc(DaonTrustPlugin)
class DaonTrustPlugin: CDVPlugin, DaonEventDelegate {
    private var callbackId: String?
    private var sdk: TrustSDK?
    private var daonWindow: UIWindow?

    override func pluginInitialize() {
        super.pluginInitialize()
        NSLog("DAON DEBUG: pluginInitialize called — SDK will be created on demand")
    }

    @objc(startOnboarding:)
    func startOnboarding(command: CDVInvokedUrlCommand) {
        callbackId = command.callbackId

        let options = command.argument(at: 0) as? [String: Any]
        let serverUrl = (options?["serverUrl"] as? String)?.trimmingCharacters(in: .whitespacesAndNewlines) ?? ""
        NSLog("DAON DEBUG: serverUrl received = %@", serverUrl)

        // 1. Create a new UIWindow that will float above the Cordova webview
        let windowScene = viewController.view.window?.windowScene
        let newWindow = UIWindow(windowScene: windowScene!)
        newWindow.windowLevel = .normal + 1
        newWindow.backgroundColor = .clear

        // 2. Build a plain container view controller inside a navigation controller
        let containerVC = UIViewController()
        containerVC.view.backgroundColor = .white
        let navController = UINavigationController(rootViewController: containerVC)
        navController.setNavigationBarHidden(true, animated: false)
        navController.modalPresentationStyle = .fullScreen

        newWindow.rootViewController = navController
        newWindow.makeKeyAndVisible()
        self.daonWindow = newWindow

        // 3. Create the SDK with the container view controller (NOT Cordova's)
        let sdkInstance = TrustSDK(withViewController: containerVC, delegate: self)
        self.sdk = sdkInstance

        do {
            let documentProcessor = try DocumentProcessor.Builder().build()
            sdkInstance.addDocumentProcessor(documentProcessor)
            NSLog("DAON DEBUG: documentProcessor built OK")

            let appkeysProcessor = try AppkeysProcessor.Builder()
                .enableDebugLogs(true)
                .enableLocationUsage(false)
                .enableSilentBiometricRegistration(false)
                .setBiometricRegistrationReason("Secure your account with biometrics")
                .setBiometricAuthenticationReason("Verify your identity")
                .build()
            sdkInstance.addAppkeysProcessor(appkeysProcessor)
            NSLog("DAON DEBUG: appkeysProcessor built OK")

            let deviceIntegrityProcessor = DeviceIntegrityProcessor()
            sdkInstance.addDeviceIntegrityProcessor(deviceIntegrityProcessor)

            let daonOptions = DaonOptions()
            daonOptions.initializationTimeout = 60
            if !serverUrl.isEmpty {
                daonOptions.serverUrl = serverUrl
            }

            NSLog("DAON DEBUG: about to call sdk.start on dedicated UIWindow")
            sdkInstance.start(withDaonOptions: daonOptions)
            NSLog("DAON DEBUG: sdk.start returned")
        } catch {
            NSLog("DAON DEBUG: CAUGHT ERROR = %@", error.localizedDescription)
            self.sendEvent(type: "failure", message: error.localizedDescription, keepCallback: false)
            self.dismissDaonWindow()
        }
    }

    // MARK: - DaonEventDelegate

    func didReceive(successResponse daonEvent: DaonEvent) {
        NSLog("DAON DEBUG: successResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
        sendEvent(type: "success", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: true)
        dismissDaonWindow()
    }

    func didReceive(failedResponse daonEvent: DaonEvent) {
        NSLog("DAON DEBUG: failedResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
        sendEvent(type: "failure", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: false)
        dismissDaonWindow()
    }

    func didReceive(infoResponse daonEvent: DaonEvent) {
        NSLog("DAON DEBUG: infoResponse code=%d desc=%@", daonEvent.code.rawValue, daonEvent.localizedDescription ?? "nil")
        sendEvent(type: "info", message: daonEvent.localizedDescription ?? String(daonEvent.code.rawValue), keepCallback: true)
    }

    // MARK: - Helpers

    private func sendEvent(type: String, message: String, keepCallback: Bool) {
        guard let callbackId else { return }
        let payload: [String: Any] = ["type": type, "message": message]
        let pluginResult = CDVPluginResult(status: .ok, messageAs: payload)
        pluginResult?.setKeepCallbackAs(keepCallback)
        self.commandDelegate.send(pluginResult, callbackId: callbackId)
    }

    private func dismissDaonWindow() {
        DispatchQueue.main.async {
            self.daonWindow?.isHidden = true
            self.daonWindow = nil
            // Restore the original Cordova window as key
            self.viewController.view.window?.makeKeyAndVisible()
            NSLog("DAON DEBUG: Daon window dismissed")
        }
    }
}