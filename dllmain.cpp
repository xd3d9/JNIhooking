#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <iostream>
#include "jni includes/jni.h"
typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);

hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;

HMODULE jvmHandle;
FARPROC func_JNI_GetCreatedJavaVMs;
JavaVM* jvm;
JNIEnv* jenv;

void main() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    jvmHandle = GetModuleHandleA("jvm.dll");

    if (!jvmHandle) {
        std::cout << "ver vchitavt karoche jvms" << std::endl;
        return;
    }

    func_JNI_GetCreatedJavaVMs = GetProcAddress(jvmHandle, "JNI_GetCreatedJavaVMs");
    oJNI_GetCreatedJavaVMs = (hJNI_GetCreatedJavaVMs)func_JNI_GetCreatedJavaVMs;
    jint rf = oJNI_GetCreatedJavaVMs(&jvm, 1, NULL); // sanity chekebia dasamatebeli ^^
    jint rf1 = jvm->AttachCurrentThread((void**)&jenv, NULL);

    if (jenv != nullptr)
    {
        //MCPMappingViewer tesli toolia))) jerjeobit ase ikos da sheidzleba mere shevcvalo 1.8.9 ze vechalichebi
        jclass MinecraftClass = jenv->FindClass("ave"); // net/minecraft/client Minecraft
        std::cout << MinecraftClass << std::endl;

        jmethodID GetMinecraftMethod = jenv->GetStaticMethodID(MinecraftClass, "A", "()Lave;"); // getMinecraft - ()Lnet/minecraft/client/Minecraft;
        std::cout << GetMinecraftMethod << std::endl;

        jobject MinecraftMethod = jenv->CallStaticObjectMethod(MinecraftClass, GetMinecraftMethod);
        std::cout << MinecraftMethod << std::endl;

        jfieldID playerid = jenv->GetFieldID(MinecraftClass, "h", "Lbew;"); // getPlayer, EntityPlayerSP
        jobject player = jenv->GetObjectField(MinecraftMethod, playerid); // amjamad vqrashavt ak da mere gavarkvev axa mezareba
        std::cout << player << std::endl;
    } // calke thread ar awkenda amas


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

