package cmsc420.pmquadtree;

import java.util.Iterator;

import cmsc420.city.City;
import cmsc420.pmquadtree.PMQuadtree.Black;
import cmsc420.road.Road;

/** PM1 rules:
 * If a region contains a vertex, then it can contain no q-edge that does not include that vertex
 * If a region contains no vertices, then it can contain at most one q-edge.
 * @author Josh
 *
 */
public class PM1Validator implements Validator {

	
	public boolean valid(Black node) {
		if(node.getNumPoints() > 1)
			return false;
		Iterator<Road> roads = node.geometry.iterator();
		if(node.getCity() == null){
			return node.geometry.size() <= 1;
		}else{
			City city = node.getCity();
			//skips the city object
			Road road = roads.next();
			while(roads.hasNext()){
				road = roads.next();
				if(!road.contains(city))
					return false;
			}
		}
		return true;
	}

}
