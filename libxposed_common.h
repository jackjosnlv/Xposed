#ifndef LIBXPOSED_COMMON_H_
#define LIBXPOSED_COMMON_H_

#include "xposed_shared.h"

#ifndef NATIVE_METHOD
#define NATIVE_METHOD(className, functionName, signature) \
  { #functionName, signature, reinterpret_cast<void*>(className ## _ ## functionName) }
#endif
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

namespace xposed {

#define CLASS_XPOSED_BRIDGE  "com/rdc/zposed/ZposedBridge"
#define CLASS_XRESOURCES     "android/content/res/XResources"
#define CLASS_MIUI_RESOURCES "android/content/res/MiuiResources"
#define CLASS_ZYGOTE_SERVICE "com/rdc/zposed/services/ZygoteService"
#define CLASS_FILE_RESULT    "com/rdc/zposed/services/FileResult"


/////////////////////////////////////////////////////////////////
// Provided by common part, used by runtime-specific implementation
/////////////////////////////////////////////////////////////////
extern jclass classZposedBridge;
extern jmethodID methodZposedBridgeHandleHookedMethod;

extern int readIntConfig(const char* fileName, int defaultValue);
extern void onVmCreatedCommon(JNIEnv* env);


/////////////////////////////////////////////////////////////////
// To be provided by runtime-specific implementation
/////////////////////////////////////////////////////////////////
extern "C" bool xposedInitLib(xposed::XposedShared* shared);
extern bool onVmCreated(JNIEnv* env);
extern void prepareSubclassReplacement(JNIEnv* env, jclass clazz);
extern void logExceptionStackTrace();

extern jint    ZposedBridge_getRuntime(JNIEnv* env, jclass clazz);
extern void    ZposedBridge_hookMethodNative(JNIEnv* env, jclass clazz, jobject reflectedMethodIndirect,
                                             jobject declaredClassIndirect, jint slot, jobject additionalInfoIndirect);
extern void    ZposedBridge_setObjectClassNative(JNIEnv* env, jclass clazz, jobject objIndirect, jclass clzIndirect);
extern jobject ZposedBridge_cloneToSubclassNative(JNIEnv* env, jclass clazz, jobject objIndirect, jclass clzIndirect);
extern void    ZposedBridge_dumpObjectNative(JNIEnv* env, jclass clazz, jobject objIndirect);
extern void    ZposedBridge_removeFinalFlagNative(JNIEnv* env, jclass clazz, jclass javaClazz);

#if PLATFORM_SDK_VERSION >= 21
extern jobject ZposedBridge_invokeOriginalMethodNative(JNIEnv* env, jclass, jobject javaMethod, jint, jobjectArray,
                                                       jclass, jobject javaReceiver, jobjectArray javaArgs);
extern void    ZposedBridge_closeFilesBeforeForkNative(JNIEnv* env, jclass clazz);
extern void    ZposedBridge_reopenFilesAfterForkNative(JNIEnv* env, jclass clazz);
#endif
#if PLATFORM_SDK_VERSION >= 24
extern void    ZposedBridge_invalidateCallersNative(JNIEnv*, jclass, jobjectArray javaMethods);
#endif

}  // namespace xposed

#endif  // LIBXPOSED_COMMON_H_
