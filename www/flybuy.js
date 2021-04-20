var cordova = require('cordova');

// Cordova Format: exec(<successFunction>, <failFunction>, <service>, <action>, [<args>]);
// Simplify to remove <service> and <failFunction>
const exec = (action, args, callback, errCallback) => {
    cordova.exec(
        callback,
        errCallback,
        'FlybuyCordova',
        action,
        args
    );
};

var flybuyExport = {};

flybuyExport.onCreate = function (appKey, cb, err) {
    exec('onCreate', [appKey], cb, err);
}

flybuyExport.onActivityStarted = function () {
    exec('onActivityStarted');
}

flybuyExport.onActivityStopped = function () {
    exec('onActivityStopped');
}

flybuyExport.onLocationPermissionChanged = function () {
    exec('onLocationPermissionChanged');
}

flybuyExport.fetchOrders = function (callback, err) {
    exec('fetchOrders', null, callback, err);
}

flybuyExport.getAllSites = function (callback, err) {
    exec('getAllSites', null, callback, err);
}

flybuyExport.getSitesByQuery = function (value, callback, err) {
    exec('getSitesByQuery', [value], callback, err);
}

flybuyExport.getConfig = function (callback, err) {
    exec('getConfig', null, callback, err);
}

flybuyExport.createCustomer = function(customer, callback, err) {
    exec('createCustomer', [customer], callback, err)
}

flybuyExport.getCurrentCustomer = function(callback, err) {
    exec('getCurrentCustomer', null, callback, err);
}

flybuyExport.updatePushToken = function(pushToken) {
    exec('updatePushToken', [pushToken]);
}

flybuyExport.handleNotification = function(userInfo) {
    exec('handleNotification', [userInfo]);
}

/**
 * Creates an order within FlyBuy
 * this should actually just take an object instead of 4 params and split it out in the args array so we can interface it better in angular
 * @param {String} siteId The Flybuy site ID of the location where the order was placed.
 * @param {String} partnerId The partner-specified identifier of the order
 * @param {Object} customerInfo The customer's information, which should conform to a `CustomerInfo` object as outlined in the FlyBuy SDK documentation
 * @param {callback} callback Returns once the order has been created. Will return an object with order information if successful.
 * @param {Object} pickupWindow An optional pickup window object. Should be an object with `startTime` and `endTime` properties that are Javascript `Date` objects.
 */
flybuyExport.createOrder = function(siteId, partnerId, customerInfo, pickupWindow, callback, errCallback) {
    exec(
        'createOrder',
        [siteId, partnerId, customerInfo, pickupWindow],
        callback,
        errCallback
    );
}

flybuyExport.claimOrder = function(redemptionCode, callback, err) {
    exec('claimOrder', [redemptionCode], callback, err)
}

flybuyExport.getPermissionStatus = function(callback, err) {
    exec('getPermissionStatus', null, callback, err)
}

flybuyExport.requestPermissions = function(isForBackgroundTracking, callback, err) {
    exec('requestPermissions', [isForBackgroundTracking], callback, err)
}

/**
 * Calls the Flybuy `event` function in the SDK.
 * @param {Number} orderId The order ID to set the update event for.
 * @param {String} state A string of the format `entityType.eventType`, where `entityType` can be either `customer` or `order`, and the 
 * `eventType` maps to the values contained in the corresponding enums documented in the [Flybuy SDK documentation](https://github.com/RadiusNetworks/flybuy-ios/blob/master/doc/data_models.md#customer-state-enum-values)
 * @param {*} callback Returns when the operation is complete, but returns no value
 */
flybuyExport.updateState = function(orderId, state, callback, err) {
    exec('event', [orderId, state], callback, err)
}

flybuyExport.onEvents = function(callback) {
    exec('onEvents', null, (data) => {
        callback(data);
    });
}

flybuyExport.offEvents = function() {
    exec('offEvents');
}

module.exports = flybuyExport;
