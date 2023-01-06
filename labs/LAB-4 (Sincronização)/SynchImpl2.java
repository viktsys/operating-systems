public class SynchImpl2 extends Thread
{
	int id;
	SynchClass sc;

	public SynchImpl2(int id, SynchClass sc)
	{
		this.id = id;
		this.sc = sc;
	}

	public void run()
	{
		switch (id)
		{
		case 0:
		case 1:
			sc.synchThisMethod(id);
			break;
		case 2:
		case 3:
			sc.synchLock1Method(id);
			break;
		case 4:
		case 5:
			sc.synchLock2Method(id);
			break;
		}
	}

	public static void main(String[] args)
	{
		SynchClass sc = new SynchClass();
		for (int i = 0; i < 6; i++)
			(new SynchImpl2(i, sc)).start();
	}
}
