package cmsc420.command;

public class IsolatedCityNotMappedThrowable extends Throwable {
	private static final long serialVersionUID = 1L;
	
	public IsolatedCityNotMappedThrowable() {
    }

    public IsolatedCityNotMappedThrowable(String msg) {
    	super(msg);
    } 
}
