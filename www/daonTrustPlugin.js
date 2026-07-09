var exec = require('cordova/exec');

exports.startOnboarding = function (options, success, error) {
  exec(success, error, 'DaonTrustPlugin', 'startOnboarding', [options || {}]);
};
