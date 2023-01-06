public class BadSynchImpl extends Thread {
  BadSynchClass a, b;

  public BadSynchImpl(BadSynchClass a, BadSynchClass b) {
    this.a = a;
    this.b = b;
  }

  public void run() {
    a.swap(b);
    System.out.println("A: " + a.get() + " B: " + b.get());

  }

  public static void main (String[] args) {
   
	BadSynchClass a = new BadSynchClass(1);
    BadSynchClass b = new BadSynchClass(2);

    (new BadSynchImpl(a, b)).start();
    (new BadSynchImpl(b, a)).start();
  }
}


