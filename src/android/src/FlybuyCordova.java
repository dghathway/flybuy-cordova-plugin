package com.wearehathway.cordova.flybuy;

import android.app.Activity;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonPrimitive;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;
import com.google.gson.reflect.TypeToken;
import com.radiusnetworks.flybuy.sdk.FlyBuyCore;
import com.radiusnetworks.flybuy.sdk.data.common.SdkError;
import com.radiusnetworks.flybuy.sdk.data.customer.CustomerInfo;
import com.radiusnetworks.flybuy.sdk.data.customer.CustomerState;
import com.radiusnetworks.flybuy.sdk.data.order.OrderState;
import com.radiusnetworks.flybuy.sdk.data.room.domain.Customer;
import com.radiusnetworks.flybuy.sdk.data.room.domain.Order;
import com.radiusnetworks.flybuy.sdk.data.room.domain.PickupWindow;
import com.radiusnetworks.flybuy.sdk.pickup.PickupManager;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.threeten.bp.Instant;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import androidx.lifecycle.Observer;
import timber.log.Timber;

/**
 * This class echoes a string called from JavaScript.
 */
public class FlybuyCordova extends CordovaPlugin {

  private static CallbackContext eventsCallbackContext;
  private FlyBuyEventObserver orderObserver = new FlyBuyEventObserver();

  private ArrayList<Integer> observedIds = new ArrayList<>();
  Gson gson;
  /*
   * For the purposes of Newk's, the main SDK functions we need to provide access
   * to are: FlyBuy.customer.create FlyBuy.customer.current FlyBuy.orders.create
   * FlyBuy.orders.event
   * 
   * Also, push notifications support. See
   * https://github.com/RadiusNetworks/flybuy-android/blob/master/doc/
   * notifications.md for more info
   */

  // See
  // https://cordova.apache.org/docs/en/latest/guide/platforms/android/plugin.html
  // for more details on the standard methods to implement
  @Override
  public boolean execute(String action, final JSONArray args, final CallbackContext callbackContext)
      throws JSONException {
    if (action.equals("onCreate"))
      onCreate(args, callbackContext);
    else if (action.equals("onActivityStarted"))
      onActivityStarted(callbackContext);
    else if (action.equals("onActivityStopped"))
      onActivityStopped(callbackContext);
    else if (action.equals("onLocationPermissionChanged"))
      onLocationPermissionChanged(callbackContext);
    else if (action.equals("fetchOrders"))
      fetchOrders(callbackContext);
    else if (action.equals("getAllSites"))
      getAllSites(null, callbackContext);
    else if (action.equals("getSitesByQuery"))
      getAllSites(args, callbackContext);
    else if (action.equals("getConfig"))
      getConfig(callbackContext);
    else if (action.equals("createCustomer"))
      createCustomer(args, callbackContext);
    else if (action.equals("updateCustomer"))
      updateCustomer(args, callbackContext);
    else if (action.equals("getCurrentCustomer"))
      getCurrentCustomer(callbackContext);
    else if (action.equals("createOrder"))
      createOrder(args, callbackContext);
    else if (action.equals("updatePushToken"))
      updatePushToken(args, callbackContext);
    else if (action.equals("getPermissionStatus"))
      getPermissionsStatus(args, callbackContext);
    else if (action.equals("requestPermissions"))
      requestPermissions(args, callbackContext);
    else if (action.equals("event"))
      event(args, callbackContext);
    else if (action.equals("onEvents"))
      onEvents(args, callbackContext);
    else if (action.equals("offEvents"))
      offEvents(args, callbackContext);
    else if (action.equals("claimOrder"))
      claimOrder(args, callbackContext);
    else if (action.equals("handleNotification"))
      handleNotification(args, callbackContext);
    else
      return false;

    return true;
  }

  @Override
  public void pluginInitialize() {
    String apiToken = preferences.getString("FLYBUY_ANDROID_API_KEY", null);
    FlyBuyCore.configure(cordova.getContext(), apiToken);
    PickupManager.Companion.getInstance(null).configure(cordova.getContext());
    PickupManager.Companion.getInstance(null).onLocationPermissionChanged();

    this.gson = new GsonBuilder().disableHtmlEscaping()
        .registerTypeAdapter(Instant.class, new JsonSerializer<Instant>() {
          public JsonElement serialize(Instant instant, Type type, JsonSerializationContext jsonSerializationContext) {
            return new JsonPrimitive(instant.toString());
          }
        }).create();
  }

  public void onCreate(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    final String apiKey = args.getString(0);
    final Activity activity = this.cordova.getActivity();
    Handler handler = new Handler(Looper.getMainLooper());
    handler.post(new Runnable() {
      public void run() {
        FlyBuyCore.configure(activity, apiKey);

        PickupManager.Companion.getInstance(null).configure(cordova.getContext());
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
      }
    });
  }

  public void onActivityStarted(final CallbackContext callbackContext) {
    Handler handler = new Handler(Looper.getMainLooper());
    handler.post(new Runnable() {
      public void run() {
        // FlyBuyCore.onActivityStopped();
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
      }
    });
  }

  public void onActivityStopped(final CallbackContext callbackContext) {
    removeObservers();
    FlybuyCordova.eventsCallbackContext = null;
    Handler handler = new Handler(Looper.getMainLooper());
    handler.post(new Runnable() {
      public void run() {
        // FlyBuyCore.onActivityStopped();
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
      }
    });
  }

  public void onLocationPermissionChanged(final CallbackContext callbackContext) {
    Handler handler = new Handler(Looper.getMainLooper());
    handler.post(new Runnable() {
      public void run() {
        // PickupManager.getInstance();
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
      }
    });
  }

  public void fetchOrders(final CallbackContext callbackContext) {
    FlyBuyCore.orders.fetch((orders, error) -> {
      sendResult(orders, error, callbackContext);
      return null;
    });
  }

  public void getAllSites(final JSONArray args, final CallbackContext callbackContext) {
    String query = "";
    if (args != null) {
      try {
        query = args.getString(0);
      } catch (JSONException ignored) {
      }
    }

    FlyBuyCore.sites.fetchAll(query, (sites, error) -> {
      sendResult(sites, error, callbackContext);
      return null;
    });
  }

  public void getConfig(final CallbackContext callbackContext) {
    FlyBuyCore.config.fetch(true, (data, error) -> {
      sendResult(data, error, callbackContext);
      return null;
    });
  }

  public void claimOrder(final JSONArray args, final CallbackContext callbackContext) {
    try {
      String redemptionCode = args.getString(0);

      // Fetch all orders and search for the one with the passed in redemption code.
      FlyBuyCore.orders.fetch((orders, fetchOrdersError) -> {

        Order foundOrder = null;
        if (orders != null) {
          for (Order order : orders) {
            if (redemptionCode.equals(order.getRedemptionCode())) {
              foundOrder = order;
            }
          }
        }

        if (foundOrder != null) { // If order is found attempt to claim it.
          claimFetchedOrder(foundOrder, callbackContext);
        } else { // Order not found. Fetch it by redemption code
          FlyBuyCore.orders.fetch(redemptionCode, (fetchedOrder, sdkError) -> {
            if (sdkError != null) { // Return error
              sendResult(fetchedOrder, sdkError, callbackContext);
            } else { // Now claim the order
              claimFetchedOrder(fetchedOrder, callbackContext);
            }
            return null;
          });
        }
        return null;
      });

    } catch (JSONException exception) {
      Timber.e(exception, "Error claiming order with redemption code");
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, exception.getMessage()));
    }
  }

  private void claimFetchedOrder(Order order, CallbackContext callbackContext) {

    if (order == null || TextUtils.isEmpty(order.getRedemptionCode())) {
      Timber.e("Error claiming order with redemption code");
      callbackContext
          .sendPluginResult(new PluginResult(PluginResult.Status.ERROR, "Error claiming order with redemption code"));
      return;
    }

    CustomerInfo customerInfo = new CustomerInfo(order.getCustomer().getName(), order.getCustomer().getPhone(),
        order.getCustomer().getCarType(), order.getCustomer().getCarColor(), order.getCustomer().getLicensePlate());

    // If we haven't established a customer with the SDK yet, we have to do that
    // before claiming an order.
    // Only do this if `currentCustomer` isn't initialized yet.
    if (FlyBuyCore.customer.getCurrent() == null) {
      FlyBuyCore.customer.create(customerInfo, true, true, null, null, (customerInfoResult, sdkError) -> {
        if (sdkError != null) {
          sendResult(customerInfoResult, sdkError, callbackContext);
        } else {
          doClaim(order, customerInfo, callbackContext);
        }
        return null;
      });
    } else {
      doClaim(order, customerInfo, callbackContext);
    }
  }

  public void doClaim(Order order, CustomerInfo customerInfo, CallbackContext callbackContext) {
    if (order == null || TextUtils.isEmpty(order.getRedemptionCode())) {
      Timber.e("Error claiming order with redemption code");
      callbackContext
          .sendPluginResult(new PluginResult(PluginResult.Status.ERROR, "Error claiming order with redemption code"));
      return;
    }

    FlyBuyCore.orders.claim(order.getRedemptionCode(), customerInfo, order.getPickupType(),
        (claimedOrder, claimedError) -> {
          sendResult(claimedOrder, claimedError, callbackContext);
          return null;
        });
  }

  public void createCustomer(final JSONArray args, final CallbackContext callbackContext) {

    final CustomerInfo customerInfo;
    // Build customer object from json
    try {
      JSONObject customerJSON = args.getJSONObject(0);

      customerInfo = new CustomerInfo(customerJSON.getString("name"), customerJSON.getString("phone"),
          customerJSON.getString("carType"), customerJSON.getString("carColor"),
          customerJSON.getString("licensePlate"));

    } catch (JSONException exception) {
      Timber.e(exception, "Error parsing customer JSON");
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, exception.getMessage()));
      return;
    }

    cordova.getThreadPool().execute(new Runnable() {
      @Override
      public void run() {
        // Create the customer in flybuy
        FlyBuyCore.customer.create(customerInfo, true, true, null, null, (customerInfoResult, sdkError) -> {
          sendResult(customerInfoResult, sdkError, callbackContext);
          return null;
        });
      }
    });
  }

  private void createOrder(JSONArray args, CallbackContext callbackContext) throws JSONException {
    CustomerInfo customerInfo = null;
    int siteId = 0;
    String partnerId = null;
    PickupWindow pickupWindow = null;

    try {
      siteId = args.getInt(0);
      partnerId = args.getString(1);
      JSONObject customerJSON = args.getJSONObject(2);
      JSONObject pickupWindowJSON = args.optJSONObject(3);

      customerInfo = new CustomerInfo(customerJSON.getString("name"), customerJSON.getString("phone"),
          customerJSON.getString("carType"), customerJSON.getString("carColor"),
          customerJSON.getString("licensePlate"));

      if (pickupWindowJSON != null) {
        Instant startInstant, endInstant;
        if (pickupWindowJSON.has("startTime")) {
          startInstant = Instant.parse(pickupWindowJSON.getString("startTime"));

          if (pickupWindowJSON.has("endTime")) {
            endInstant = Instant.parse(pickupWindowJSON.getString("endTime"));
          } else {
            endInstant = startInstant;
          }
          pickupWindow = new PickupWindow(startInstant, endInstant);
        }
      }

    } catch (JSONException ex) {
      Timber.e(ex);
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, ex.getMessage()));
    }

    FlyBuyCore.orders.create(siteId, partnerId, customerInfo, pickupWindow, null, null, (createdOrder, error) -> {

      PickupManager.Companion.getInstance(null).onLocationPermissionChanged();

      FlyBuyCore.orders.fetch((orders, fetchOrdersError) -> {
        Order resultOrder = createdOrder;
        if (orders != null) {
          for (Order fetchedOrder : orders) {
            if (fetchedOrder.getId() == createdOrder.getId()) {
              resultOrder = fetchedOrder;
            }
          }
        }
        sendResult(resultOrder, fetchOrdersError, callbackContext);
        return null;
      });
      return null;
    });
  }

  private void updatePushToken(final JSONArray args, final CallbackContext callbackContext) {
    String token;
    try {
      token = args.getString(0);
    } catch (JSONException jsonException) {
      Timber.e(jsonException);
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, jsonException.getMessage()));
      return;
    }

    FlyBuyCore.onNewPushToken(token);
  }

  private void getCurrentCustomer(CallbackContext callbackContext) {
    cordova.getThreadPool().execute(new Runnable() {
      @Override
      public void run() {
        Customer currentCustomer = FlyBuyCore.customer.getCurrent();
        sendResult(currentCustomer, null, callbackContext);
      }
    });
  }

  public void updateCustomer(final JSONArray args, final CallbackContext callbackContext) {
    final CustomerInfo customerInfo;
    try {
      JSONObject customerJSON = args.getJSONObject(0);

      customerInfo = new CustomerInfo(customerJSON.getString("name"), customerJSON.getString("phone"),
          customerJSON.getString("carType"), customerJSON.getString("carColor"),
          customerJSON.getString("licensePlate"));

    } catch (JSONException exception) {
      Timber.e(exception, "Error parsing customer JSON");
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, exception.getMessage()));
      return;
    }
    cordova.getThreadPool().execute(new Runnable() {
      @Override
      public void run() {
        FlyBuyCore.customer.update(customerInfo, (customer, sdkError) -> {
          sendResult(customer, sdkError, callbackContext);
          return null;
        });
      }
    });
  }

  public void getPermissionsStatus(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    String str;
    boolean foreground = cordova.hasPermission("android.permission.ACCESS_FINE_LOCATION");
    if (Build.VERSION.SDK_INT >= 29) {
      if (foreground) {
        boolean background = cordova.hasPermission("android.permission.ACCESS_BACKGROUND_LOCATION");
        str = background ? "GRANTED_BACKGROUND" : "GRANTED_FOREGROUND";
      } else {
        str = "DENIED";
      }
    } else {
      str = foreground ? "GRANTED_BACKGROUND" : "DENIED";
    }

    callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, str));
  }

  public void requestPermissions(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    final boolean background = args.getBoolean(0);

    if (background && Build.VERSION.SDK_INT >= 29) {
      cordova.requestPermissions(this, 0,
          new String[] { "android.permission.ACCESS_FINE_LOCATION", "android.permission.ACCESS_BACKGROUND_LOCATION" });
    } else {
      cordova.requestPermissions(this, 0, new String[] { "android.permission.ACCESS_FINE_LOCATION" });
    }

    callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
  }

  public void handleNotification(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    try {
      JSONObject pushData = args.getJSONObject(0);
      Type dataType = new TypeToken<Map<String, String>>() {
      }.getType();

      Map<String, String> data = gson.fromJson(pushData.toString(), dataType);

      FlyBuyCore.onMessageReceived(data, sdkError -> {
        if (sdkError != null) {
          Timber.e(sdkError.userError());
        }
        return null;
      });
    } catch (JSONException ex) {
      Timber.e(ex);
    }
  }

  public void onEvents(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    FlybuyCordova.eventsCallbackContext = callbackContext;

    int orderId;
    try {
      orderId = args.getInt(0);
    } catch (JSONException ex) {
      Timber.e(ex);
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, ex.getMessage()));
      return;
    }

    cordova.getActivity().runOnUiThread(() -> {
      if (!observedIds.contains(orderId)) {
        FlyBuyCore.orders.getOrder(orderId).observeForever(orderObserver);
        observedIds.add(orderId);
      }
    });
  }

  public void offEvents(final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    FlybuyCordova.eventsCallbackContext = null;
    removeObservers();
  }

  private void removeObservers() {
    for (Integer id : observedIds) {
      FlyBuyCore.orders.getOrder(id).removeObserver(orderObserver);
    }
    observedIds.clear();
  }

  public class FlyBuyEventObserver implements Observer<Order> {
    @Override
    public void onChanged(Order order) {
      if (FlybuyCordova.eventsCallbackContext != null) {
        sendResult(order, null, FlybuyCordova.eventsCallbackContext, true);
      }
    }
  }

  private void event(JSONArray args, CallbackContext callbackContext) {
    int orderId;
    String stateStr = null;

    try {
      orderId = args.getInt(0);
      stateStr = args.getString(1);
    } catch (JSONException ex) {
      Timber.e(ex);
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, ex.getMessage()));
      return;
    }

    String[] strings = stateStr.toLowerCase().split("\\.");
    if (strings.length != 2) {
      callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR,
          "State passed to function is not of the form <Entity>.<State>, i.e. customer.waiting"));
    }
    switch (strings[0]) {
      case "customer":
        String customerState = CustomerState.CREATED;
        if (strings.length > 1) {
          customerState = getCustomerState(strings[1]);
        }

        FlyBuyCore.orders.updateCustomerState(orderId, customerState, (order, error) -> {
          sendResult(order, error, callbackContext);
          return null;
        });
        break;
      case "order":
        String orderState = OrderState.CREATED;
        if (strings.length > 1) {
          orderState = getOrderState(strings[1]);
        }

        FlyBuyCore.orders.updateState(orderId, orderState, (order, error) -> {
          sendResult(order, error, callbackContext);
          return null;
        });
        break;
    }
  }

  private String getOrderState(String stateStr) {

    if (TextUtils.isEmpty(stateStr)) {
      return "Unknown";
    }

    switch (stateStr) {
      case "created":
        return OrderState.CREATED;
      case "ready":
        return OrderState.READY;
      case "delayed":
        return OrderState.DELAYED;
      case "cancelled":
        return OrderState.CANCELLED;
      case "completed":
        return OrderState.COMPLETED;
      case "gone":
        return OrderState.GONE;
    }
    return "Unknown";
  }

  private String getCustomerState(String stateStr) {
    if (TextUtils.isEmpty(stateStr)) {
      return CustomerState.CREATED;
    }

    switch (stateStr) {
      case "created":
        return CustomerState.CREATED;
      case "en_route":
        return CustomerState.EN_ROUTE;
      case "waiting":
        return CustomerState.WAITING;
      case "nearby":
        return CustomerState.NEARBY;
      case "arrived":
        return CustomerState.ARRIVED;
      case "completed":
        return CustomerState.COMPLETED;
    }
    return "Unknown";
  }

  private void sendResult(Object result, SdkError error, CallbackContext callbackContext) {
    sendResult(result, error, callbackContext, false);
  }

  private void sendResult(Object result, SdkError error, CallbackContext callbackContext, boolean keepCallback) {
    PluginResult pluginResult;
    if (error == null) {
      try {
        String jsonStr = gson.toJson(result);
        if (result == null) {
          pluginResult = new PluginResult(PluginResult.Status.OK, new JSONObject());
        } else if (result instanceof List<?>) {
          pluginResult = new PluginResult(PluginResult.Status.OK, new JSONArray(jsonStr));
        } else {
          pluginResult = new PluginResult(PluginResult.Status.OK, new JSONObject(jsonStr));
        }
      } catch (JSONException e) {
        Timber.e(e);
        pluginResult = new PluginResult(PluginResult.Status.ERROR, e.getMessage());
      }
    } else {
      Timber.e(error.getType().toString());
      pluginResult = new PluginResult(PluginResult.Status.ERROR, gson.toJson(error));
    }

    pluginResult.setKeepCallback(keepCallback);
    callbackContext.sendPluginResult(pluginResult);
  }
}
