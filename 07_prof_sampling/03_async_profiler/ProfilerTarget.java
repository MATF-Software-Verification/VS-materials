import java.util.ArrayList;
import java.util.List;

public class ProfilerTarget {
    private static final Object LOCK = new Object();
    private static volatile boolean running = true;
    private static volatile long sink = 0;

    private static boolean isPrime(int value) {
        if (value < 2) {
            return false;
        }

        for (int i = 2; i * i <= value; i++) {
            if (value % i == 0) {
                return false;
            }
        }

        return true;
    }

    private static void cpuWorker() {
        int candidate = 10_000;
        while (running) {
            if (isPrime(candidate)) {
                sink += candidate;
            }
            candidate++;
            if (candidate > 30_000) {
                candidate = 10_000;
            }
        }
    }

    private static void allocationWorker() {
        while (running) {
            List<byte[]> batch = new ArrayList<>();
            for (int i = 0; i < 200; i++) {
                batch.add(new byte[4096]);
            }
            sink += batch.size();
        }
    }

    private static void lockWorker() {
        while (running) {
            synchronized (LOCK) {
                for (int i = 0; i < 50_000; i++) {
                    sink += i & 7;
                }
            }
            Thread.yield();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int seconds = args.length > 0 ? Integer.parseInt(args[0]) : 120;

        System.out.printf("pid=%d duration=%ds%n", ProcessHandle.current().pid(),
                          seconds);
        System.out.println("Attach async-profiler from another terminal.");

        Thread cpu = new Thread(ProfilerTarget::cpuWorker, "cpu-worker");
        Thread alloc = new Thread(ProfilerTarget::allocationWorker,
                                  "allocation-worker");
        Thread lockA = new Thread(ProfilerTarget::lockWorker, "lock-worker-a");
        Thread lockB = new Thread(ProfilerTarget::lockWorker, "lock-worker-b");

        cpu.start();
        alloc.start();
        lockA.start();
        lockB.start();

        Thread.sleep(seconds * 1000L);
        running = false;

        cpu.join();
        alloc.join();
        lockA.join();
        lockB.join();

        System.out.println("sink=" + sink);
    }
}
