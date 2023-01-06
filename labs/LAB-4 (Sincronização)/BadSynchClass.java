public class BadSynchClass
{
	private int value;

	public BadSynchClass(int v)
	{
		value = v;
	}

	public synchronized int get()
	{
		return value;
	}

	public synchronized void set(int i)
	{
		value = i;
	}

	public synchronized void swap(BadSynchClass bsc)
	{
		int tmp = get();
		set(bsc.get());
		bsc.set(tmp);
	}
}
