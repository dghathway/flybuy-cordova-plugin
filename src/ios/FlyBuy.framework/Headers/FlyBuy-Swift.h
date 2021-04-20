// Generated by Apple Swift version 5.2.4 (swiftlang-1103.0.32.9 clang-1103.0.32.53)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <Foundation/Foundation.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import Foundation;
@import ObjectiveC;
#endif

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="FlyBuy",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif


SWIFT_CLASS("_TtC6FlyBuy10AppUpgrade")
@interface AppUpgrade : NSObject
@end


SWIFT_CLASS_NAMED("BeaconList")
@interface FlyBuyBeaconList : NSObject
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end



@class FlyBuyCustomerInfo;

SWIFT_CLASS_NAMED("ClaimOrderInfo")
@interface FlyBuyClaimOrderInfo : NSObject
- (nonnull instancetype)initWithCustomerCarColor:(NSString * _Nullable)customerCarColor customerCarType:(NSString * _Nullable)customerCarType customerLicensePlate:(NSString * _Nullable)customerLicensePlate customerName:(NSString * _Nullable)customerName customerPhone:(NSString * _Nullable)customerPhone pushToken:(NSString * _Nonnull)pushToken OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithCustomerInfo:(FlyBuyCustomerInfo * _Nonnull)customerInfo pushToken:(NSString * _Nonnull)pushToken pickupType:(NSString * _Nullable)pickupType OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("ConfigurationManager")
@interface FlyBuyConfigurationManager : NSObject
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

@class FlyBuyOrdersManager;
@class FlyBuyCustomerManager;
@class FlyBuySitesManager;
@class FlyBuyLogger;

SWIFT_CLASS_NAMED("Core")
@interface FlyBuyCore : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) FlyBuyOrdersManager * _Nonnull orders;)
+ (FlyBuyOrdersManager * _Nonnull)orders SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) FlyBuyCustomerManager * _Nonnull customer;)
+ (FlyBuyCustomerManager * _Nonnull)customer SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) FlyBuySitesManager * _Nonnull sites;)
+ (FlyBuySitesManager * _Nonnull)sites SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) FlyBuyConfigurationManager * _Nonnull config;)
+ (FlyBuyConfigurationManager * _Nonnull)config SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) FlyBuyLogger * _Nonnull logger;)
+ (FlyBuyLogger * _Nonnull)logger SWIFT_WARN_UNUSED_RESULT;
/// Configures FlyBuy with the given options
/// Example:
/// \code
/// FlyBuy.configure(["token": "TOKEN_HERE"])
///
/// \endcode
+ (void)configure:(NSDictionary<NSString *, id> * _Nonnull)opts;
/// handles a remote notification which may contain FlyBuy order data
/// \param data contains the <code>userInfo</code> data from a remote notification
///
+ (void)handleRemoteNotification:(NSDictionary * _Nonnull)data;
/// Updates the push token that FlyBuy uses to send push messages to the app.
+ (void)updatePushToken:(NSString * _Nonnull)newPushToken;
/// Updates the APNs device token that FlyBuy uses to send pushes to the app. This should only be used
/// when FlyBuy is configured to send pushes through APNs directly. If using a 3rd party service such as
/// Airship, OneSignal, etc, the correct method to call is <code>updatePushToken</code>.
+ (void)updateAPNPushToken:(NSData * _Nonnull)deviceToken;
@end



@class FlyBuyPickupWindow;

SWIFT_CLASS_NAMED("CreateOrderInfo")
@interface FlyBuyCreateOrderInfo : NSObject
- (nonnull instancetype)initWithSiteID:(NSInteger)siteID partnerIdentifier:(NSString * _Nonnull)partnerIdentifier customerCarColor:(NSString * _Nullable)customerCarColor customerCarType:(NSString * _Nullable)customerCarType customerLicensePlate:(NSString * _Nullable)customerLicensePlate customerName:(NSString * _Nullable)customerName customerPhone:(NSString * _Nullable)customerPhone pushToken:(NSString * _Nullable)pushToken state:(NSString * _Nullable)state pickupWindow:(FlyBuyPickupWindow * _Nullable)pickupWindow OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithSiteID:(NSInteger)siteID partnerIdentifier:(NSString * _Nonnull)partnerIdentifier customerCarColor:(NSString * _Nullable)customerCarColor customerCarType:(NSString * _Nullable)customerCarType customerLicensePlate:(NSString * _Nullable)customerLicensePlate customerName:(NSString * _Nullable)customerName customerPhone:(NSString * _Nullable)customerPhone pushToken:(NSString * _Nullable)pushToken pickupWindow:(FlyBuyPickupWindow * _Nullable)pickupWindow OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("Customer")
@interface FlyBuyCustomer : NSObject
@property (nonatomic, readonly, copy) NSString * _Nonnull token;
@property (nonatomic, readonly, copy) NSString * _Nullable emailAddress;
@property (nonatomic, readonly, strong) FlyBuyCustomerInfo * _Nonnull info;
@property (nonatomic, readonly) BOOL registered;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("CustomerConsent")
@interface FlyBuyCustomerConsent : NSObject
@property (nonatomic, readonly) BOOL termsOfService;
@property (nonatomic, readonly) BOOL ageVerification;
- (nonnull instancetype)initWithTermsOfService:(BOOL)termsOfService ageVerification:(BOOL)ageVerification OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("CustomerInfo")
@interface FlyBuyCustomerInfo : NSObject
@property (nonatomic, readonly, copy) NSString * _Nonnull name;
@property (nonatomic, readonly, copy) NSString * _Nullable carType;
@property (nonatomic, readonly, copy) NSString * _Nullable carColor;
@property (nonatomic, readonly, copy) NSString * _Nullable licensePlate;
@property (nonatomic, readonly, copy) NSString * _Nullable phone;
- (nonnull instancetype)initWithName:(NSString * _Nonnull)name carType:(NSString * _Nullable)carType carColor:(NSString * _Nullable)carColor licensePlate:(NSString * _Nullable)licensePlate phone:(NSString * _Nullable)phone OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


/// Allows managing the customer: creating, storing, updating, signing-out
/// Example:
/// \code
/// // get the current FlyBuy customer
/// Core.customer.current
///
/// \endcode
SWIFT_CLASS_NAMED("CustomerManager")
@interface FlyBuyCustomerManager : NSObject
@property (nonatomic, readonly, strong) FlyBuyCustomer * _Nullable current;
/// create a FlyBuy customer
/// \param customerInfo contains the customer details
///
/// \param termsOfService user has accepted the terms of service
///
/// \param ageVerification user is of age to provide consent
///
/// \param callback Called with the new <code>Customer</code> or any error encountered. Optional.
///
- (void)create:(FlyBuyCustomerInfo * _Nonnull)customerInfo termsOfService:(BOOL)termsOfService ageVerification:(BOOL)ageVerification callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// create a FlyBuy customer
/// \param customerInfo contains the customer details
///
/// \param email email provided by the user
///
/// \param password password provided by the user
///
/// \param customerConsent contains the values of ‘termsOfService’ and ‘ageVerification’
///
/// \param callback Called with the new <code>Customer</code> or any error encountered. Optional.
///
- (void)create:(FlyBuyCustomerInfo * _Nonnull)customerInfo email:(NSString * _Nonnull)email password:(NSString * _Nonnull)password customerConsent:(FlyBuyCustomerConsent * _Nonnull)customerConsent callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// update a FlyBuy customer
/// \param customerInfo contains the customer details
///
/// \param callback Called with the updated <code>Customer</code> or any error encountered. Optional.
///
- (void)update:(FlyBuyCustomerInfo * _Nonnull)customerInfo callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// Login as a FlyBuy customer
/// \param emailAddress the account email
///
/// \param password the account password
///
/// \param callback Called with the  <code>Customer</code> or any error encountered. Optional.
///
- (void)loginWithEmailAddress:(NSString * _Nonnull)emailAddress password:(NSString * _Nonnull)password callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// Login as a FlyBuy customer with a token
/// \param token the account token
///
/// \param callback Called with the  <code>Customer</code> or any error encountered. Optional.
///
- (void)loginWithTokenWithToken:(NSString * _Nonnull)token callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// Convert the current customer (an anonymous account) to a registered account
/// \param emailAddress the account email
///
/// \param password the account password
///
/// \param callback Called with the  <code>Customer</code> or any error encountered. Optional.
///
- (void)signUpWithEmailAddress:(NSString * _Nonnull)emailAddress password:(NSString * _Nonnull)password callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// Request password reset for an email address
/// \param emailAddress the account email
///
/// \param callback Called with any error encountered. Optional.
///
- (void)requestNewPasswordWithEmailAddress:(NSString * _Nonnull)emailAddress callback:(void (^ _Nullable)(NSError * _Nullable))callback;
/// Perform password change for an email address
/// \param resetPasswordToken the token for the new password
///
/// \param password the account password
///
/// \param confirmation the account password confirmation
///
/// \param callback Called with the  <code>Customer</code> or any error encountered. Optional.
///
- (void)setNewPasswordWithResetPasswordToken:(NSString * _Nonnull)resetPasswordToken password:(NSString * _Nonnull)password confirmation:(NSString * _Nonnull)confirmation callback:(void (^ _Nullable)(FlyBuyCustomer * _Nullable, NSError * _Nullable))callback;
/// Signs out the FlyBuy user
- (void)logout;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC6FlyBuy11FlyBuyError")
@interface FlyBuyError : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("CustomerManagerError")
@interface FlyBuyCustomerManagerError : FlyBuyError
@end




SWIFT_CLASS("_TtC6FlyBuy14FlyBuyAPIError")
@interface FlyBuyAPIError : FlyBuyError
@end



SWIFT_CLASS("_TtC6FlyBuy26FlyBuyErrorInvalidResponse")
@interface FlyBuyErrorInvalidResponse : FlyBuyError
@end


SWIFT_CLASS("_TtC6FlyBuy21FlyBuyErrorInvalidURL")
@interface FlyBuyErrorInvalidURL : FlyBuyError
@end


SWIFT_CLASS_NAMED("Geofence")
@interface FlyBuyGeofence : NSObject
@property (nonatomic, readonly, copy) NSString * _Nonnull latitude;
@property (nonatomic, readonly, copy) NSString * _Nonnull longitude;
@property (nonatomic, readonly) double radiusMeters;
@end

typedef SWIFT_ENUM(NSInteger, LocationAuthStatus, open) {
  LocationAuthStatusNotDetermined = 0,
  LocationAuthStatusRestricted = 1,
  LocationAuthStatusDenied = 2,
  LocationAuthStatusAuthorizedAlways = 3,
  LocationAuthStatusAuthorizedWhenInUse = 4,
};

typedef SWIFT_ENUM(NSInteger, LogLevel, open) {
  LogLevelVerbose = 0,
  LogLevelDebug = 1,
  LogLevelInfo = 2,
  LogLevelWarning = 3,
  LogLevelError = 4,
  LogLevelNone = 5,
};


SWIFT_CLASS_NAMED("Logger")
@interface FlyBuyLogger : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end






SWIFT_CLASS_NAMED("LoginInfo")
@interface FlyBuyLoginInfo : NSObject
@property (nonatomic, readonly, copy) NSString * _Nonnull emailAddress;
@property (nonatomic, readonly, copy) NSString * _Nonnull password;
- (nonnull instancetype)initWithEmailAddress:(NSString * _Nonnull)emailAddress password:(NSString * _Nonnull)password OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@class CLLocation;
@class NSNumber;

SWIFT_CLASS_NAMED("Order")
@interface FlyBuyOrder : NSObject
@property (nonatomic, readonly) NSInteger id;
@property (nonatomic, readonly) NSInteger siteID;
@property (nonatomic, copy) NSString * _Nonnull state;
@property (nonatomic, copy) NSString * _Nonnull customerState;
@property (nonatomic, readonly, copy) NSString * _Nullable partnerIdentifier;
@property (nonatomic, readonly, copy) NSString * _Nullable redemptionCode;
@property (nonatomic, readonly, copy) NSDate * _Nullable redeemedAt;
@property (nonatomic, readonly, copy) NSString * _Nullable displayName;
@property (nonatomic, readonly, strong) FlyBuyPickupWindow * _Nullable pickupWindow;
@property (nonatomic, copy) NSString * _Nullable pickupType;
@property (nonatomic, copy) NSDate * _Nullable etaAt;
@property (nonatomic, copy) NSDate * _Nullable completedAt;
@property (nonatomic, copy) NSDate * _Nullable createdAt;
@property (nonatomic, copy) NSDate * _Nullable updatedAt;
@property (nonatomic, copy) NSString * _Nullable customerRating;
@property (nonatomic, copy) NSString * _Nullable customerComment;
@property (nonatomic, readonly, copy) NSString * _Nullable siteName;
@property (nonatomic, readonly, copy) NSString * _Nullable sitePhone;
@property (nonatomic, readonly, copy) NSString * _Nullable siteStreetAddress;
@property (nonatomic, readonly, copy) NSString * _Nullable siteFullAddress;
@property (nonatomic, readonly, copy) NSString * _Nullable siteLocality;
@property (nonatomic, readonly, copy) NSString * _Nullable siteRegion;
@property (nonatomic, readonly, copy) NSString * _Nullable siteCountry;
@property (nonatomic, readonly, copy) NSString * _Nullable sitePostalCode;
@property (nonatomic, readonly, copy) NSString * _Nullable siteLongitude;
@property (nonatomic, readonly, copy) NSString * _Nullable siteLatitude;
@property (nonatomic, readonly, copy) NSString * _Nullable siteInstructions;
@property (nonatomic, readonly, copy) NSString * _Nullable siteDescription;
@property (nonatomic, readonly, copy) NSString * _Nullable siteCoverPhotoURL;
@property (nonatomic, readonly, copy) NSString * _Nullable sitePartnerIdentifier;
@property (nonatomic, readonly, copy) NSString * _Nullable projectAccentColor;
@property (nonatomic, readonly, copy) NSString * _Nullable projectAccentTextColor;
@property (nonatomic, readonly, copy) NSString * _Nullable projectLogoURL;
@property (nonatomic, readonly, copy) NSString * _Nullable customerName;
@property (nonatomic, readonly, copy) NSString * _Nullable customerCarType;
@property (nonatomic, readonly, copy) NSString * _Nullable customerCarColor;
@property (nonatomic, readonly, copy) NSString * _Nullable customerLicensePlate;
@property (nonatomic, readonly) BOOL projectMobileFlowAlwaysShowVehicleInfoFields;
@property (nonatomic, readonly) BOOL projectMobileFlowCustomerNameEditingEnabled;
@property (nonatomic, readonly) BOOL projectMobileFlowPickupTypeSelectionEnabled;
@property (nonatomic, readonly) BOOL projectMobileFlowRequireVehicleInfoIfVisible;
@property (nonatomic, readonly, copy) NSString * _Nullable curbsideLocalizedString;
@property (nonatomic, readonly, copy) NSString * _Nullable pickupLocalizedString;
@property (nonatomic, copy) NSString * _Nullable pushToken;
- (CLLocation * _Nullable)siteLocation SWIFT_WARN_UNUSED_RESULT;
- (NSNumber * _Nullable)siteDistanceFrom:(CLLocation * _Nonnull)location SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic, readonly, strong) NSNumber * _Nullable customerID;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end








SWIFT_CLASS_NAMED("OrderEvent")
@interface FlyBuyOrderEvent : NSObject
- (nonnull instancetype)initWithOrderID:(NSInteger)orderID customerState:(NSString * _Nonnull)customerState etaSeconds:(NSNumber * _Nullable)etaSeconds OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithOrderID:(NSInteger)orderID state:(NSString * _Nonnull)state OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithOrderID:(NSInteger)orderID locationAuthStatus:(enum LocationAuthStatus)locationAuthStatus OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithOrderID:(NSInteger)orderID customerRating:(NSInteger)customerRating customerComments:(NSString * _Nullable)customerComments OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


/// Allows fetching the list of orders, creating a new order, or creating
/// order events.
/// Example:
/// \code
/// // fetch orders from FlyBuy
/// Core.orders.fetch()
///
/// \endcode
SWIFT_CLASS_NAMED("OrdersManager")
@interface FlyBuyOrdersManager : NSObject
/// contains a list of all the orders
@property (nonatomic, readonly, copy) NSArray<FlyBuyOrder *> * _Nonnull all;
/// contains a list of all currently open orders
@property (nonatomic, readonly, copy) NSArray<FlyBuyOrder *> * _Nonnull open;
/// contains a list of all closed orders
@property (nonatomic, readonly, copy) NSArray<FlyBuyOrder *> * _Nonnull closed;
/// contains the order states values
@property (nonatomic, copy) NSArray<NSString *> * _Nonnull orderStates;
/// contains the customer states values
@property (nonatomic, copy) NSArray<NSString *> * _Nonnull customerStates;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
/// fetches the list of orders from the FlyBuy web API
/// \param callback will get called on completion with the array of orders or any errors encountered. Optional.
///
- (void)fetchWithCallback:(void (^ _Nullable)(NSArray<FlyBuyOrder *> * _Nullable, NSError * _Nullable))callback;
/// fetches an order using a redemption code
/// \param redemptionCode the redemption code for the order
///
/// \param callback will get called on completion with the array of orders or any errors encountered. Optional.
///
- (void)fetchWithRedemptionCode:(NSString * _Nonnull)redemptionCode callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// Claims an order using a redemption code and pickup type
/// \param redemptionCode the redemption code for the order
///
/// \param customerInfo the customer details for the order
///
/// \param pickupType the pickup type string value for the order. Optional.
///
/// \param callback will get called on completion with the order and any errors encountered. Optional.
///
- (void)claimWithRedemptionCode:(NSString * _Nonnull)redemptionCode customerInfo:(FlyBuyCustomerInfo * _Nonnull)customerInfo pickupType:(NSString * _Nullable)pickupType callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// creates an order using the FlyBuy web API
/// \param siteID site identifier
///
/// \param partnerIdentifier partner identifier for the order
///
/// \param customerInfo customer information
///
/// \param pickupWindow pickup window for the order. Optional.
///
/// \param state initial order state
///
/// \param callback called once either an order is created or an error is encountered. Optional.
///
- (void)createWithSiteID:(NSInteger)siteID partnerIdentifier:(NSString * _Nonnull)partnerIdentifier customerInfo:(FlyBuyCustomerInfo * _Nonnull)customerInfo pickupWindow:(FlyBuyPickupWindow * _Nullable)pickupWindow state:(NSString * _Nonnull)state callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// creates an order using the FlyBuy web API
/// \param siteID site identifier
///
/// \param partnerIdentifier partner identifier for the order
///
/// \param customerInfo customer information
///
/// \param pickupWindow pickup window for the order. Optional.
///
/// \param callback called once either an order is created or an error is encountered. Optional.
///
- (void)createWithSiteID:(NSInteger)siteID partnerIdentifier:(NSString * _Nonnull)partnerIdentifier customerInfo:(FlyBuyCustomerInfo * _Nonnull)customerInfo pickupWindow:(FlyBuyPickupWindow * _Nullable)pickupWindow callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// creates an order event that sets the customer state
/// \param orderID specifies which order ID this event relates to
///
/// \param customerState contains the customer state which should be set on the order
///
/// \param callback Gets called at completion with the order or any error encountered. Optional.
///
- (void)updateCustomerStateWithOrderID:(NSInteger)orderID customerState:(NSString * _Nonnull)customerState callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// creates an order event that sets the order state
/// \param orderID specifies which order ID this event relates to
///
/// \param state contains the order state which should be set on the order
///
/// \param callback Gets called at completion with the order or any error encountered. Optional.
///
- (void)updateOrderStateWithOrderID:(NSInteger)orderID state:(NSString * _Nonnull)state callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
/// creates an order event that sets the customer state
/// \param orderID specifies which order ID this event relates to
///
/// \param rating the rating number
///
/// \param comments the comment string. Optional.
///
/// \param callback Gets called at completion with the order or any error encountered. Optional.
///
- (void)rateOrderWithOrderID:(NSInteger)orderID rating:(NSInteger)rating comments:(NSString * _Nullable)comments callback:(void (^ _Nullable)(FlyBuyOrder * _Nullable, NSError * _Nullable))callback;
@end






SWIFT_CLASS_NAMED("OrdersManagerError")
@interface FlyBuyOrdersManagerError : FlyBuyError
@end


SWIFT_CLASS_NAMED("Pagination")
@interface FlyBuyPagination : NSObject
@property (nonatomic, readonly) NSInteger currentPage;
@property (nonatomic, readonly) NSInteger totalPages;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("PickupWindow")
@interface FlyBuyPickupWindow : NSObject
@property (nonatomic, readonly, copy) NSDate * _Nonnull start;
@property (nonatomic, readonly, copy) NSDate * _Nonnull end;
- (nonnull instancetype)initWithStart:(NSDate * _Nonnull)start end:(NSDate * _Nonnull)end OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init:(NSDate * _Nonnull)date;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("RequestPasswordReset")
@interface FlyBuyRequestPasswordReset : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("SetNewPassword")
@interface FlyBuySetNewPassword : NSObject
- (nonnull instancetype)initWithResetPasswordToken:(NSString * _Nonnull)resetPasswordToken password:(NSString * _Nonnull)password confirmation:(NSString * _Nonnull)confirmation OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("SignUpInfo")
@interface FlyBuySignUpInfo : NSObject
@property (nonatomic, readonly, copy) NSString * _Nonnull emailAddress;
@property (nonatomic, readonly, copy) NSString * _Nonnull password;
@property (nonatomic, readonly, copy) NSString * _Nonnull passwordConfirmation;
- (nonnull instancetype)initWithEmailAddress:(NSString * _Nonnull)emailAddress password:(NSString * _Nonnull)password passwordConfirmation:(NSString * _Nonnull)passwordConfirmation OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS_NAMED("Site")
@interface FlyBuySite : NSObject
@property (nonatomic, readonly) NSInteger id;
@property (nonatomic, readonly, copy) NSString * _Nullable partnerIdentifier;
@property (nonatomic, readonly, copy) NSString * _Nullable name;
@property (nonatomic, readonly, copy) NSString * _Nullable phone;
@property (nonatomic, readonly, copy) NSString * _Nullable streetAddress;
@property (nonatomic, readonly, copy) NSString * _Nullable fullAddress;
@property (nonatomic, readonly, copy) NSString * _Nullable locality;
@property (nonatomic, readonly, copy) NSString * _Nullable region;
@property (nonatomic, readonly, copy) NSString * _Nullable country;
@property (nonatomic, readonly, copy) NSString * _Nullable postalCode;
@property (nonatomic, readonly, copy) NSString * _Nullable longitude;
@property (nonatomic, readonly, copy) NSString * _Nullable latitude;
@property (nonatomic, readonly, copy) NSString * _Nullable instructions;
@property (nonatomic, readonly, copy) NSString * _Nullable descriptionText;
@property (nonatomic, readonly, copy) NSString * _Nullable coverPhotoURL;
@property (nonatomic, readonly, copy) NSString * _Nullable projectAccentColor;
@property (nonatomic, readonly, copy) NSString * _Nullable projectAccentTextColor;
@property (nonatomic, readonly, copy) NSString * _Nullable projectLogoURL;
@property (nonatomic, readonly, strong) FlyBuyGeofence * _Nullable geofence;
- (CLLocation * _Nullable)location SWIFT_WARN_UNUSED_RESULT;
- (NSNumber * _Nullable)distanceFrom:(CLLocation * _Nonnull)loc SWIFT_WARN_UNUSED_RESULT;
@end

@class CLCircularRegion;

/// Allows fetching the list of sites
/// Example:
/// \code
/// // fetch sites from FlyBuy
/// FlyBuy.sites.fetch()
///
/// \endcode
SWIFT_CLASS_NAMED("SitesManager")
@interface FlyBuySitesManager : NSObject
@property (nonatomic, readonly, copy) NSArray<FlyBuySite *> * _Nullable all;
/// fetches the list of sites from the FlyBuy web API
/// \param query the query string. Optional.
///
/// \param page the desired page number. Optional.
///
/// \param callback will get called on completion with the array of sites or any errors encountered. Optional.
///
- (void)fetchWithQuery:(NSString * _Nullable)query page:(NSInteger)page callback:(void (^ _Nullable)(NSArray<FlyBuySite *> * _Nullable, FlyBuyPagination * _Nullable, NSError * _Nullable))callback;
/// fetches the list of sites from the FlyBuy web API
/// \param region a CLCircularRegion for the search region.
///
/// \param page the desired page number. Optional.
///
/// \param callback will get called on completion with the array of sites or any errors encountered. Optional.
///
- (void)fetchWithRegion:(CLCircularRegion * _Nonnull)region page:(NSInteger)page callback:(void (^ _Nullable)(NSArray<FlyBuySite *> * _Nullable, NSError * _Nullable))callback;
/// fetches the list of sites from the FlyBuy web API
/// \param region a CLCircularRegion for the search region.
///
/// \param page the desired page number.
///
/// \param per the amount of sites returned per page.
///
/// \param callback will get called on completion with the array of sites or any errors encountered. Optional.
///
- (void)fetchWithRegion:(CLCircularRegion * _Nonnull)region page:(NSInteger)page per:(NSInteger)per callback:(void (^ _Nullable)(NSArray<FlyBuySite *> * _Nullable, NSError * _Nullable))callback;
/// fetches the list of sites from the FlyBuy web API
/// \param query the query string. Optional.
///
/// \param callback will get called on completion with the array of sites and any errors encountered. Optional.
///
- (void)fetchAllWithQuery:(NSString * _Nullable)query callback:(void (^ _Nullable)(NSArray<FlyBuySite *> * _Nullable, NSError * _Nullable))callback;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end




SWIFT_CLASS_NAMED("UpdateOrderInfo")
@interface FlyBuyUpdateOrderInfo : NSObject
- (nonnull instancetype)initWithPushToken:(NSString * _Nonnull)pushToken OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end





#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
