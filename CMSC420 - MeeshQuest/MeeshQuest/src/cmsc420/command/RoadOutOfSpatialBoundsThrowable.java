package cmsc420.command;

public class RoadOutOfSpatialBoundsThrowable extends Throwable {
	private static final long serialVersionUID = 1L;
	public RoadOutOfSpatialBoundsThrowable() {
    }
    public RoadOutOfSpatialBoundsThrowable(String msg) {
    	super(msg);
    } 
}
