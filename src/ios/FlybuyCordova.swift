import FlyBuy
import CoreLocation

typealias PluginResultType = [AnyHashable : Any]

@objc(FlybuyCordova) class FlybuyCordova : CDVPlugin {
    
    var locationManager: CLLocationManager!
    private var eventsCallbackId: String? = nil {
        didSet {
            setRegisteredForNotifications(registered: (eventsCallbackId != nil))
        }
    }
    
    func getKey() -> String? {
        return self.commandDelegate.settings["flybuy_ios_api_key"] as? String
    }
    
    override func pluginInitialize() {
        assert(getKey() != nil)
        FlyBuy.Core.configure(["token": getKey() as Any])
        locationManager = CLLocationManager()
    }
    
    @objc(fetchOrders:)
    func fetchOrders(command: CDVInvokedUrlCommand) {
        FlyBuy.Core.orders.fetch() { self.handlePluginResult(result: $0, error: $1, command: command) }
    }

    @objc(getSitesByQuery:)
    func getSitesByQuery(command: CDVInvokedUrlCommand) {
        guard let queryTerm = command.argument(at: 0) as? String else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "No parameters passed to function")

            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        getSites(query: queryTerm, command: command)
    }
    
    @objc(getAllSites:)
    func getAllSites(command: CDVInvokedUrlCommand) {
        getSites(query: nil, command: command)
    }
    
    private func getSites(query: String?, command: CDVInvokedUrlCommand) {
        FlyBuy.Core.sites.fetchAll(query: query) { self.handlePluginResult(result: $0, error: $1, command: command) }
    }
    
    @objc(getConfig:)
    func getConfig(command: CDVInvokedUrlCommand) {
        
//        FlyBuy.config.fetch { (result, error) in  // Fix: need to update here
//            var pluginResult = CDVPluginResult()
//            if let configResult = result {
//                pluginResult = CDVPluginResult(status: .ok, messageAs: configResult)
//            } else if let unwrappedError = error {
//                pluginResult = CDVPluginResult(status: .error, messageAs: unwrappedError.localizedDescription)   // Hasn't been tested yet!
//            }
//
//            self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
//        }
    }
    
    @objc(createCustomer:)
    func createCustomer(command: CDVInvokedUrlCommand) {
        
        guard let customerData = command.argument(at: 0) as? NSDictionary else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "No parameters passed to function")
            
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        let customerInfo = CustomerInfo(name: customerData["name"] as! String,
                                        carType: customerData["carType"] as? String,
                                        carColor: customerData["carColor"] as? String,
                                        licensePlate: customerData["licensePlate"] as? String,
                                        phone: customerData["phone"] as? String)
        
        FlyBuy.Core.customer.create(customerInfo, termsOfService: true, ageVerification: true)  { self.handlePluginResult(result: $0, error: $1, command: command) }
    }
    
    @objc(getCurrentCustomer:)
    func getCurrentCustomer(command: CDVInvokedUrlCommand) {
        
        guard let customer = FlyBuy.Core.customer.current else {
            return self.commandDelegate!.send(CDVPluginResult(status: .ok), callbackId: command.callbackId)
        }
        return self.commandDelegate!.send(CDVPluginResult(result: customer), callbackId: command.callbackId)
    }
    
    @objc(updatePushToken:)
    func updatePushToken(command: CDVInvokedUrlCommand) {
        
        guard let token = command.argument(at: 0) as? String else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "No token passed to function")
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        print("\(#function): updating push token to \(token)")
        FlyBuy.Core.updatePushToken(token)
        return self.commandDelegate!.send(CDVPluginResult(status: .ok), callbackId: command.callbackId)
    }
    
    @objc(handleNotification:)
    func handleNotification(command: CDVInvokedUrlCommand) {
        
        guard let userInfo = command.argument(at: 0) as? [AnyHashable: Any] else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "No push info data to function")
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        FlyBuy.Core.handleRemoteNotification(userInfo)
        return self.commandDelegate!.send(CDVPluginResult(status: .ok), callbackId: command.callbackId)
    }
    
    @objc(createOrder:)
    func createOrder(command: CDVInvokedUrlCommand) {
        
        guard let siteId = command.argument(at: 0) as? Int,
            let partnerId = command.argument(at: 1) as? String,
            let customerInfo = command.argument(at: 2) as? NSDictionary
            else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "Incorrect parameter count or types passed to function")
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        let customer = CustomerInfo(fromInfo: customerInfo)
        
        var pickupWindow: PickupWindow?
        if let pickupWindowArg = command.argument(at: 3) as? NSDictionary,
            let startTimeString = pickupWindowArg["startTime"] as? String,
            let endTimeString = pickupWindowArg["endTime"] as? String {
            
            let dateFormatter = DateFormatter()
            dateFormatter.locale = .init(identifier: "en_US_POSIX")
            dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSZ"
            
            if let startDate = dateFormatter.date(from: startTimeString),
                let endDate = dateFormatter.date(from: endTimeString) {
                pickupWindow = PickupWindow(start: startDate, end: endDate)
            } else {
                print("Error parsing pickupwindow dates: startTimeString = \(startTimeString), endTimeString = \(endTimeString)")
            }
        }

        // `Order` is `Codable`... so we could use JSONEncoder here, but it adds escaping `\` characters to the output going up the chain, and disabling that requires a
        // newer version of iOS I wasn't prepared to jump to yet.
        FlyBuy.Core.orders.create(siteID: siteId, partnerIdentifier: partnerId, customerInfo: customer, pickupWindow: pickupWindow) { (order, error) in
            if let error = error {
                return self.handlePluginResult(result: order, error: error, command: command)
            } else if let order = order {
                FlyBuy.Core.orders.fetch() { (orders, error) in
                    if let fetchedOrder = orders?.first(where: { $0.id == order.id }) {
                        self.handlePluginResult(result: fetchedOrder, error: error, command: command)
                    } else {
                        self.handlePluginResult(result: order, error: error, command: command)
                    }
                    
                }
            } else {
                self.commandDelegate!.send(CDVPluginResult(status: .error, messageAs: "Error creating the order with Flybuy, no order or error returned"), callbackId: command.callbackId)
            }
        }
    }

    @objc(claimOrder:)
    func claimOrder(command: CDVInvokedUrlCommand) {

        guard let redemptionCode = command.argument(at: 0) as? String
            else {
            let pluginResult = CDVPluginResult(status: .error, messageAs: "Incorrect parameter count or types passed to function")
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        let claimFetchedOrder: ((Order) -> Void) = { order in
            // Re-use the existing customer info since there should always be some in any scenario where Flybuy receives the order from us or the Olo webhook (based on testing)
            let customerInfo = CustomerInfo(name: order.customerName ?? "Unknown",
                                            carType: order.customerCarType,
                                            carColor: order.customerCarColor,
                                            licensePlate: order.customerLicensePlate)
            
            let doClaim: (() -> Void) = {
                
                FlyBuy.Core.orders.claim(withRedemptionCode: redemptionCode, customerInfo: customerInfo, pickupType: order.pickupType) { (claimedOrder, error) in
                    // On instructions from Flybuy team, do another fetch after claiming to make sure it's up to date.
                    FlyBuy.Core.orders.fetch() { (orders, error) in
                        let foundOrder = orders?.first(where: { $0.id == order.id })
                        self.handlePluginResult(result: foundOrder, error: error, command: command) }
                }
            }
            
            // If we haven't established a customer with the SDK yet, we have to do that before claiming an order. Only do this if `currentCustomer` isn't initialized yet.
            if (FlyBuy.Core.customer.current == nil) {
                FlyBuy.Core.customer.create(customerInfo, termsOfService: true, ageVerification: true)  { (customer, error) in
                    doClaim()
                }
            } else {
                doClaim()
            }
        }
        
        // This logic is hairy because the Flybuy SDK is quite tempormental about redemption of a code when it's already been redeemed or fetched.
        // Step 1: Fetch all orders the Flybuy SDK currently knows about to see if we can do a match ourselves.
        FlyBuy.Core.orders.fetch() { (orders, error) in
            if let orders = orders, let foundOrder = orders.first(where: { $0.redemptionCode == redemptionCode }) {
                // If we found an order in the SDK fetch() cache, claim it.
                claimFetchedOrder(foundOrder)
            } else {
                // If we don't have it in our cache, fetch it by it's code to "get it into our cache"
                FlyBuy.Core.orders.fetch(withRedemptionCode: redemptionCode) { (order, error) in
                    if let error = error {
                        return self.handlePluginResult(result: order, error: error, command: command)
                    } else if let order = order {
                        // If Flybuy returned it, claim it.
                        claimFetchedOrder(order)
                    } else {
                        let pluginResult = CDVPluginResult(status: .error, messageAs: "No error or order returned by Flybuy for redemption code \(redemptionCode)")
                        return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
                    }
                }
            }
        }
    }
    
    @objc(getPermissionStatus:)
    func getPermissionStatus(command: CDVInvokedUrlCommand) {
        let status = CLLocationManager.authorizationStatus()
        
        var str = "UNKNOWN";
        switch (status) {
        case .denied:
            str = "DENIED";
            break;
        case .restricted:
            str = "DENIED";
            break;
        case .authorizedAlways:
            str = "GRANTED_BACKGROUND";
            break;
        case .authorizedWhenInUse:
            str = "GRANTED_FOREGROUND";
            break;
        case .notDetermined:
            str = "NOT_YET_ASKED"
            break;
        default:
            str = "UNKNOWN";
        }
        
        self.commandDelegate!.send(CDVPluginResult(status: .ok, messageAs: str), callbackId: command.callbackId)
    }
    
    @objc(requestPermissions:)
    func requestPermissions(command: CDVInvokedUrlCommand) {
        var isBackground = false
        if let bgNumber = command.argument(at: 0) as? Int {
            isBackground = bgNumber == 1
        }
        
        if isBackground {
            locationManager.requestAlwaysAuthorization()
        } else {
            locationManager.requestWhenInUseAuthorization()
        }
        
        self.commandDelegate!.send(CDVPluginResult(status: .ok), callbackId: command.callbackId)
    }
    
    /*
    - (void)requestPermissions:(CDVInvokedUrlCommand *)command {
        NSNumber *backgroundNumber = [command.arguments objectAtIndex:0];

        BOOL background = [backgroundNumber boolValue];

        if (background) {
            [locationManager requestAlwaysAuthorization];
        } else {
            [locationManager requestWhenInUseAuthorization];
        }

        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
 */
    
    @objc(event:)
    func event(command: CDVInvokedUrlCommand) {
        let sendErrorResult: ((String) -> Void) = { errorMsg in
            let pluginResult = CDVPluginResult(status: .error, messageAs: errorMsg)
            return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
        }
        
        guard let orderId = command.argument(at: 0) as? Int,
            let stateStr = command.argument(at: 1) as? String else {
                return sendErrorResult("Incorrect parameter count or types passed to function")
        }
        
        let states = stateStr.lowercased().split(separator: ".")
        if states.count != 2 {
            return sendErrorResult("State passed to function is not of the form <Entity>.<State>, i.e. customer.waiting")
        }
        
        let type = String(states[0])
        let state = String(states[1])
        
        print("\(#function): type=\(type), state=\(state)")
        
        switch type {
         case "customer":
             if (CustomerState(stateString: state)) {
                 FlyBuy.Core.orders.updateCustomerState(orderID: orderId, customerState: state) { self.handlePluginResult(result: $0, error: $1, command: command) }
             } else {
                 return sendErrorResult("Invalid customer state")
             }
         case "order":
             if (OrderState(stateString: state)) {
                 FlyBuy.Core.orders.updateOrderState(orderID: orderId, state: state) {
                    self.handlePluginResult(result: $0, error: $1, command: command) }
             } else {
                 return sendErrorResult("Invalid order state")
             }
        default:
            sendErrorResult("Unrecognized type/state: [\(type), \(state)]")
            break
        }
    }
    
    @objc(onEvents:)
    func onEvents(command: CDVInvokedUrlCommand) {
        eventsCallbackId = command.callbackId
    }
    
    @objc(offEvents:)
    func offEvents(command: CDVInvokedUrlCommand) {
        eventsCallbackId = nil
    }
    
    private func handleNotification(_ notification: Notification, eventName: String) {
        guard let callbackId = self.eventsCallbackId, let userInfo = notification.userInfo else { return }
        let data: [AnyHashable: Any] = userInfo.merging(["eventName": eventName]) { (current, _) in current }
        let result = CDVPluginResult(status: .ok, messageAs: data)
        self.commandDelegate.send(result, callbackId: callbackId)
    }
    
    private func setRegisteredForNotifications(registered: Bool) {
        if (registered) {
            NotificationCenter.default.addObserver(forName: .ordersUpdated, object: nil, queue: nil) { [weak self] (notification) in
                // Update multiple orders
                self?.handleNotification(notification, eventName: "OrdersUpdated")
            }
            NotificationCenter.default.addObserver(forName: .orderUpdated, object: nil, queue: nil) { [weak self] (notification) in
                // Update single order
                self?.handleNotification(notification, eventName: "OrderUpdated")
            }
            NotificationCenter.default.addObserver(forName: .ordersError, object: nil, queue: nil) { [weak self] (notification) in
                // Handle error
                self?.handleNotification(notification, eventName: "OrdersError")
            }
        } else {
            NotificationCenter.default.removeObserver(self, name: .ordersUpdated, object: nil)
            NotificationCenter.default.removeObserver(self, name: .orderUpdated, object: nil)
            NotificationCenter.default.removeObserver(self, name: .ordersError, object: nil)
        }
    }
    
    private func handlePluginResult(result: Array<DictionaryRepresentable>?, error: Error?, command: CDVInvokedUrlCommand) -> Void {
        var pluginResult = CDVPluginResult(status: .ok)
        if let result = result {
            let resultArray = result.map { $0.toDictionary() }
            pluginResult = CDVPluginResult(status: .ok, messageAs: resultArray)
        } else if let error = error {
            pluginResult = CDVPluginResult(status: .error, messageAs: error.localizedDescription)
        }
        return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
    }
    
    private func handlePluginResult<T: DictionaryRepresentable>(result: T?, error: Error?, command: CDVInvokedUrlCommand) -> Void {
        var pluginResult = CDVPluginResult(status: .ok)
        if let result = result {
            print(result)
            pluginResult = CDVPluginResult(result: result)
        } else if let error = error {
            pluginResult = CDVPluginResult(status: .error, messageAs: error.localizedDescription)
        }
        return self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
    }
}

extension CDVPluginResult {
    convenience init<T: DictionaryRepresentable>(result: T) {
        self.init(status: .ok, messageAs: result.toDictionary())
    }
    
    convenience init(result: Array<DictionaryRepresentable>) {
        self.init(status: .ok, messageAs: result.map { $0.toDictionary() })
    }
}

protocol DictionaryRepresentable {
    func toDictionary() -> PluginResultType
}

class ArgumentError: Error {}

// Fix: CustomerState and OrderState are not in Scope error, 
// https://www.radiusnetworks.com/developers/flybuy/#/sdk-2.0/ios-migration-guide?id=convert-to-state-strings
func CustomerState(stateString: String) -> Bool {
    return ["created", "enroute", "en_route", "nearby", "arrived", "waiting", "completed"].index(of: stateString.lowercased()) != -1
 }

func OrderState(stateString: String) -> Bool {
    return ["created", "ready", "delayed", "cancelled", "completed", "gone"].index(of: stateString.lowercased()) != -1
    
 }


extension CustomerInfo: DictionaryRepresentable {
    convenience init(fromInfo: NSDictionary) {
        self.init(name: fromInfo["name"] as! String,
                  carType: fromInfo["carType"] as? String,
                  carColor: fromInfo["carColor"] as? String,
                  licensePlate: fromInfo["licensePlate"] as? String,
                  phone: fromInfo["phone"] as? String)
    }
    
    func toDictionary() -> PluginResultType {
        var result: PluginResultType = [:]
        result["name"] = self.name
        result["carType"] = self.carType
        result["carColor"] = self.carColor
        result["licensePlate"] = self.licensePlate
        result["phone"] = self.phone
        return result
    }
}

extension Customer: DictionaryRepresentable {
    func toDictionary() -> PluginResultType {
        var result: PluginResultType = [:]
        result["apiToken"] = self.token
        result["emailAddress"] = self.emailAddress
        
        let info = self.info.toDictionary()
        result.merge(info) { (lhs, rhs) -> Any in
            return lhs
        }
        result["registered"] = self.registered
        return result
    }
}

extension Site: DictionaryRepresentable {
    static func toDictionary(_ site: Site) -> PluginResultType {
        return site.toDictionary()
    }
    
    func toDictionary() -> PluginResultType {
        var result: PluginResultType = [:]
        result["id"] = self.id
        result["partnerIdentifier"] = self.partnerIdentifier
        result["name"] = self.name
        result["phone"] = self.phone
        result["streetAddress"] = self.streetAddress
        result["fullAddress"] = self.fullAddress
        result["locality"] = self.locality
        result["region"] = self.region
        result["country"] = self.country
        result["postalCode"] = self.postalCode
        result["longitude"] = self.longitude
        result["latitude"] = self.latitude
        result["instructions"] = self.instructions
        result["descriptionText"] = self.descriptionText
        result["coverPhotoURL"] = self.coverPhotoURL
        result["projectAccentColor"] = self.projectAccentColor
        result["projectAccentTextColor"] = self.projectAccentTextColor
        result["projectLogoURL"] = self.projectLogoURL
        return result
    }
}


extension Order: DictionaryRepresentable {
    func toDictionary() -> PluginResultType {
        let dateFormatter = ISO8601DateFormatter()
        var result: PluginResultType = [:]
        result["id"] = self.id
        result["state"] = String(describing: self.state).lowercased()
        result["customerState"] = String(describing: self.customerState).lowercased()
        result["partnerIdentifier"] = self.partnerIdentifier
        result["pickupWindow"] = self.pickupWindow?.toDictionary()
        result["pickupType"] = self.pickupType
        if let date = self.etaAt {
            result["etaAt"] = dateFormatter.string(from: date)
        }
        if let date = self.redeemedAt {
            result["redeemedAt"] = dateFormatter.string(from: date)
        }
        result["customerRating"] = self.customerRating
        result["customerComment"] = self.customerComment
        result["siteID"] = self.siteID
        result["siteName"] = self.siteName
        result["sitePhone"] = self.sitePhone
        result["siteFullAddress"] = self.siteFullAddress
        result["siteLongitude"] = self.siteLongitude
        result["siteLatitude"] = self.siteLatitude
        result["siteInstructions"] = self.siteInstructions
        result["siteDescription"] = self.siteDescription
        result["siteCoverPhotoURL"] = self.siteCoverPhotoURL
        result["customerName"] = self.customerName
        result["customerCarType"] = self.customerCarType
        result["customerCarColor"] = self.customerCarColor
        result["customerLicensePlate"] = self.customerLicensePlate
        return result
    }
}

extension PickupWindow: DictionaryRepresentable {
    func toDictionary() -> PluginResultType {
        let dateFormatter = DateFormatter()
        dateFormatter.locale = .init(identifier: "en_US_POSIX")
        dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSZ"
        return [
            "start": dateFormatter.string(from: self.start),
            "end": dateFormatter.string(from: self.end)
        ]
    }
}
