package com.example.agent;

import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtMethod;

import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.lang.instrument.Instrumentation;
import java.security.ProtectionDomain;

public class Agent {

    // Invoked during JVM initialization
    public static void premain(String agentArgs, Instrumentation inst) {

        System.out.println("premain() called with args: " + agentArgs);

        inst.addTransformer(new ClassFileTransformer() {
            @Override
            public byte[] transform(ClassLoader classLoader, String s, Class<?> aClass, ProtectionDomain protectionDomain, byte[] bytes) throws IllegalClassFormatException {
                if ("com/example/main/Test".equals(s)) {
                    // Javassist
                    try {
                        ClassPool cp = ClassPool.getDefault();
                        cp.insertClassPath(agentArgs + "/prog-test/target/prog-test-0.1-SNAPSHOT.jar");
                        CtClass cc = cp.get("com.example.main.Test");
                        CtMethod m = cc.getDeclaredMethod("myMethod");
                        m.setBody("{System.out.println(\"Method Hacked \");}");
                        byte[] byteCode = cc.toBytecode();
                        cc.detach();
                        return byteCode;
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
                return null;
            }
        });
    }

    // Invoked before application main method
    public static void agentmain(String agentArgs) {
        System.out.println("agentmain() called with args: " + agentArgs);
    }

}

