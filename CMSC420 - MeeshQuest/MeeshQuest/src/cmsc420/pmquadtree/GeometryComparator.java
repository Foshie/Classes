package cmsc420.pmquadtree;

import java.util.Comparator;

import cmsc420.road.Road;

public class GeometryComparator implements Comparator<Road> {

	public int compare(final Road r1, final Road r2) {
		if (r1.isCity()) {
			/* r1 is a city */
			if (r2.isCity()) {
				/* r2 is a city */
				return r1.getStart().getName().compareTo(
						r2.getStart().getName());
			} else {
				/* r2 is a road */
				return -1;
			}
		} else {
			/* r1 is a road */
			if (r2.isCity()) {
				/* r2 is a city */
				return 1;
			} else {
				/* r2 is a road */
				if (r1.getStart().getName().compareTo(r2.getStart().getName()) == 0) {
					/* start names are the same so compare end names */
					return r1.getEnd().getName().compareTo(
							r2.getEnd().getName());
				} else {
					/* start names are different; compare start names */
					return r1.getStart().getName().compareTo(
							r2.getStart().getName());
				}
			}
		}
	}
}
