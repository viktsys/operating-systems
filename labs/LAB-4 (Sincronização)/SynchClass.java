public class SynchClass {

  public synchronized void synchMethod(int i) {
     while (true) System.out.println(i);
  }

  public void nonSynchMethod(int i) {
     while (true) System.out.println(i);
  }

  public static synchronized void synchStaticMethod(int i) { 
     while (true) System.out.println(i);
  }

  public static void nonSynchStaticMethod(int i) { 
     while (true) System.out.println(i);
  }

  private Object lock1 = new Object();
  private Object lock2 = new Object();

  public void synchThisMethod(int i) {
     synchronized (this) {
       while (true) System.out.println(i);
     }
  }

  public void synchLock1Method(int i) {
     synchronized (lock1) { 
       while (true) System.out.println(i);
     }
  }

  public void synchLock2Method(int i) {
     synchronized (lock2) { 
       while (true) System.out.println(i);
     }
  }


}
