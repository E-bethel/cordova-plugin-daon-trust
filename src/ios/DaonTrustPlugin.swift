import Foundation
import Cordova
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
        let serverUrl = (options?[
            "serverUrl"] as? String)?.trimmingCharacters(in: .whitespacesAndNewlines) ?? ""

        guard let viewController = self.viewController else { return }

        let sdkInstance = TrustSDK(withViewController: viewController, delegate: self)
        self.sdk = sdkInstance

        do {
            let documentProcessor = try DocumentProcessor.Builder().build()
            sdkInstance.addDocumentProcessor(documentProcessor)

            let appkeysProcessor = try AppkeysProcessor.Builder()
                .enableDebugLogs(false)
                .enableLocationUsage(false)
                .enableSilentBiometricRegistration(false)
                .setBiometricRegistrationReason("Secure your account with biometrics")
                .setBiometricAuthenticationReason("Verify your identity")
                .build()
            sdkInstance.addAppkeysProcessor(appkeysProcessor)

            let deviceIntegrityProcessor = DeviceIntegrityProcessor()
            sdkInstance.addDeviceIntegrityProcessor(deviceIntegrityProcessor)

            let daonOptions = DaonOptions()
            if !serverUrl.isEmpty {
                daonOptions.serverUrl = serverUrl
            }

            sdkInstance.start(withDaonOptions: daonOptions)
        } catch {
            sendEvent(type: "failure", message: error.localizedDescription, keepCallback: false)
        }
    }

    func didReceive(successResponse daonEvent: DaonEvent) {
        sendEvent(type: "success", message: daonEvent.localizedDescription ?? daonEvent.code.rawValue, keepCallback: true)
    }

    func didReceive(failedResponse daonEvent: DaonEvent) {
        sendEvent(type: "failure", message: daonEvent.localizedDescription ?? daonEvent.code.rawValue, keepCallback: false)
    }

    func didReceive(infoResponse daonEvent: DaonEvent) {
        sendEvent(type: "info", message: daonEvent.localizedDescription ?? daonEvent.code.rawValue, keepCallback: true)
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
