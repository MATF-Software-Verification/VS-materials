import java.util.*;

class Hello {

    public static void main(String[] args) {
        Foo.use();
        System.out.println(" m = " + System.nanoTime());
        new Foo(System.nanoTime()).foo();
    }

    static class Foo {

        private static long _t;

        static {
            _t = System.nanoTime();
        }

        private long t;

        Foo(long t) {
            this.t = t;
        }

        void foo() {
            System.out.println("_t = " + _t); 
            System.out.println(" t = " + this.t); 
        }

        static void use() {
            System.out.println("use()");
        }
    }

}
