import java.util.concurrent.Semaphore;

public class ExemploSemaforo
{
  private int value = 0;

    private final Semaphore mutex = new Semaphore(1);

    public int getNextValue() throws InterruptedException {
        try {
            mutex.acquire();
            return ++value;
        } finally {
            mutex.release();
        }
    }

}
