package cordova.plugin.daontrust;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import androidx.activity.ComponentActivity;

import com.daon.nfcmanager.TrustNFCManager;
import com.daon.trustsdk.DaonTrustSDK;
import com.daon.trustsdk.events.DaonEvent;
import com.daon.trustsdk.events.DaonEventListener;
import com.daon.trustsdk.model.DaonOptions;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class DaonTrustPlugin extends CordovaPlugin {
    private static final String TAG = "DaonTrustPlugin";
    private CallbackContext callbackContext;
    private DaonTrustSDK sdk;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        ComponentActivity activity = (ComponentActivity) cordova.getActivity();

        sdk = new DaonTrustSDK(activity, new DaonEventListener() {
            @Override
            public void onSuccess(String description) {
                sendEvent("success", description, true);
            }

            @Override
            public void onFail(DaonEvent daonEvent) {
                String message = daonEvent != null ? daonEvent.toString() : "Onboarding failed";
                sendEvent("failure", message, false);
            }

            @Override
            public void onInfo(DaonEvent daonEvent) {
                String message = daonEvent != null ? daonEvent.toString() : "Onboarding info";
                sendEvent("info", message, true);
            }
        });

        activity.getLifecycle().addObserver(sdk);

        try {
            TrustNFCManager trustNFCManager = new TrustNFCManager.Builder().build();
            sdk.addTrustNFCManager(trustNFCManager);
        } catch (Exception ex) {
            Log.e(TAG, "Failed to add NFC manager", ex);
        }
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if ("startOnboarding".equals(action)) {
            this.callbackContext = callbackContext;
            final JSONObject options = args.optJSONObject(0);
            final String serverUrl = options != null ? options.optString("serverUrl", "") : "";

            Handler mainHandler = new Handler(Looper.getMainLooper());
            mainHandler.post(new Runnable() {
                @Override
                public void run() {
                    try {
                        DaonOptions daonOptions = new DaonOptions();
                        daonOptions.setInitializationTimeout(60_000L);
                        if (serverUrl != null && !serverUrl.trim().isEmpty()) {
                            daonOptions.setServerUrl(serverUrl);
                        }

                        sdk.start(daonOptions);
                    } catch (Exception ex) {
                        Log.e(TAG, "Failed to start onboarding", ex);
                        sendEvent("failure", ex.getMessage(), false);
                    }
                }
            });
            return true;
        }
        return false;
    }

    private void sendEvent(String type, String message, boolean keepCallback) {
        if (callbackContext == null) {
            return;
        }
        try {
            JSONObject payload = new JSONObject();
            payload.put("type", type);
            payload.put("message", message);
            org.apache.cordova.PluginResult result = new org.apache.cordova.PluginResult(org.apache.cordova.PluginResult.Status.OK, payload);
            result.setKeepCallback(keepCallback);
            callbackContext.sendPluginResult(result);
        } catch (JSONException ex) {
            Log.e(TAG, "Unable to encode event payload", ex);
        }
    }
}