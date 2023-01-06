import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SimpleMonitor {
    private final Lock lock = new ReentrantLock();

    public void testA() {
        lock.lock();

        try {
            //Some code
        } finally {
            lock.unlock();
        }
    }

    public int testB() {
        lock.lock();

        try {
            return 1;
        } finally {
            lock.unlock();
        }
    }
}