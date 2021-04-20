# Usage notes:

* The latest version of the FlyBuy SDK does not jive well with version 28 and lower of the Android SDK. You will get an error indicating that `foregroundServiceType not found` or something like that. Unfortunately, cordova-android 8.0 can only use version 28 by default, so you have to do the following to get the code to compile with version 29:
    * The easiest thing to do is to set an environment variable before adding the Android platform with the Ionic/Cordova tool:
    ```
    export ORG_GRADLE_PROJECT_cdvCompileSdkVersion=29
    ionic cordova platform add android
    ```
    * There are other options you can read about [here](https://cordova.apache.org/docs/en/latest/guide/platforms/android/#configuring-gradle), but #1 and #2 require you use environment variables or command parameters, and #3 and #4 require that you make changes to gradle files after creating the platform, which is troublesome for automated build systems, so we will primariily rely on the environment variable for now.

