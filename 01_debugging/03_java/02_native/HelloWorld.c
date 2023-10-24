#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj) {
	printf("Hello world!\n");
	return;
}
