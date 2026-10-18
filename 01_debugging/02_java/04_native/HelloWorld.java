class HelloWorld {
    static {
        System.loadLibrary("HelloWorld");
    }

    private native void print();

    public static void main(String[] args) throws InterruptedException {
        Thread.sleep(10000);
        new HelloWorld().print();
    }
}
