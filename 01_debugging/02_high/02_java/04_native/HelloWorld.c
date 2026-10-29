#include "HelloWorld.h"
#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_HelloWorld_print(JNIEnv *env, jobject obj) {
    printf("Hello native world!\n");
}
