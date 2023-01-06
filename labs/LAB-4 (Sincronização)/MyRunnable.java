class MyRunnable implements Runnable {
   private String message;

   public MyRunnable(String m) {message = m;}

   public void run() {
      for(int r=0; r<20; r++)
         System.out.println(message);
   }


public static void main(String[] args) {
      MyRunnable r1;
	  MyRunnable r2;
      Thread t1, t2;
      r1=new MyRunnable("primeira thread");
      r2=new MyRunnable("segunda thread");
      t1 = new Thread(r1);
      t2 = new Thread(r2);
      t1.start();
      t2.start();
   }
}
