class MyThread extends Thread {
   private String message;

   public MyThread(String m) {message = m;}

   public void run() {
      for(int r=0; r<20; r++)
         System.out.println(message);
   }


   public static void main(String[] args) {
      MyThread t1,t2;
      t1=new MyThread("primeira thread");
      t2=new MyThread("segunda thread");
      t1.start();
      t2.start();
  
}
}