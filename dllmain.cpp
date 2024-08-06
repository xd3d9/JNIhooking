#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <iostream>
#include "jni includes/jni.h"
class Java {
public:
    JavaVM* VM;
    JNIEnv* Env;
    JavaVMInitArgs Args;
};

typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);

hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;

HMODULE jvmHandle;
FARPROC func_JNI_GetCreatedJavaVMs;
JavaVM* jvm;
JNIEnv* jenv;

void main() {
    jsize JSize;
    jvmHandle = GetModuleHandleA("jvm.dll");

    if (!jvmHandle) {
        std::printf("ver vchitavt karoche jvms");
        return;
    }

    func_JNI_GetCreatedJavaVMs = GetProcAddress(jvmHandle, "JNI_GetCreatedJavaVMs");
    oJNI_GetCreatedJavaVMs = (hJNI_GetCreatedJavaVMs)func_JNI_GetCreatedJavaVMs;
    jint rf = oJNI_GetCreatedJavaVMs(&jvm, 1, NULL);
    jint rf1 = jvm->AttachCurrentThread((void**)&jenv, NULL);

    if (jenv != nullptr)
    {
        //funcs
    }


    if (jenv->ExceptionCheck())
    {
        jenv->ExceptionDescribe();
    }

    jvm->DetachCurrentThread();

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

