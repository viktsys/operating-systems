public class SynchImpl extends Thread
{
	int id;
	SynchClass sc;

	public SynchImpl(int id, SynchClass sc)
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
			sc.synchMethod(id);
			break;
		case 2:
		case 3:
			sc.nonSynchMethod(id);
			break;
		case 4:
		case 5:
			SynchClass.synchStaticMethod(id);
			break;
		case 6:
		case 7:
			SynchClass.nonSynchStaticMethod(id);
			break;
		}
	}

	public static void main(String[] args)
	{
		SynchClass sc = new SynchClass();
		for (int i = 0; i < 8; i++)
			(new SynchImpl(i, sc)).start();
	}
}