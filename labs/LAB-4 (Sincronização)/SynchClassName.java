public class SynchClassName {
   private String globalVar;

   public SynchClassName() {
   }

   public synchronized void synchMethod() {
      String localVar;
   }

   public void nonSynchMethod() {
   }

   public static synchronized void synchStaticMethod() {
   }
   
   public static void nonSynchStaticMethod() {
   }
}
