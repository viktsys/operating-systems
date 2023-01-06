public class MySecondRunnable implements Runnable{

    public void run() {
        System.out.printf("I'm running in thread %s \n", Thread.currentThread().getName());
 
    }
    public static void main(String[] args) {
Runnable runnable = new MySecondRunnable();

for(int i = 0; i < 25; i++){
    Thread thread = new Thread(runnable);
    thread.setName("Thread " + i);
    thread.start();
}
}
 
}