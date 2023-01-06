public class SleepThread {
    public static void main(String[] args) {
        System.out.println("Current time millis : " + System.currentTimeMillis());

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Current time millis : " + System.currentTimeMillis());

        System.out.println("Nano time : " + System.nanoTime());

        try {
            Thread.sleep(2, 5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Nano time : " + System.nanoTime());
    }
}