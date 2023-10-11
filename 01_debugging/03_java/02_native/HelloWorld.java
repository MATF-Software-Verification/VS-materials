import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("----- Hello, world! -----");
        System.out.println("args: " + Arrays.toString(args));
        System.out.println(System.getProperty("java.vm.name"));
        System.out.println(System.getProperty("java.home"));
        System.out.println(System.getProperty("java.vendor"));
        System.out.println(System.getProperty("java.version"));
        System.out.println(System.getProperty("java.specification.vendor"));
        System.out.println("-------------------------");
    }
}
