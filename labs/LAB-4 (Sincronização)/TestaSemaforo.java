class TestaSemaforo extends Thread {

   ExemploSemaforo e;

   public TestaSemaforo(ExemploSemaforo e) {this.e = e;}

   public void run() {
      try { 
        for (int i=0; i < 20000; i++) {
           System.out.println(e.getNextValue()); 
        }
       } catch (Exception e) {} 
   }


   public static void main(String[] args) {
      TestaSemaforo t1,t2;
      ExemploSemaforo e = new ExemploSemaforo();
      t1=new TestaSemaforo(e);
      t2=new TestaSemaforo(e);
      t1.start();
      t2.start();
}
}
