public class HelloWorldThread2 implements Runnable {

   public void run() {
      System.out.println("Hello World");
   }

   public static void main(String[] args) {
      HelloWorldThread h = new HelloWorldThread();
      Thread t = new Thread(h);
      t.start();
   }
}