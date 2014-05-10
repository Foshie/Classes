package cmsc420.pmquadtree;

import java.util.Iterator;

import cmsc420.city.City;
import cmsc420.pmquadtree.PMQuadtree.Black;
import cmsc420.road.Road;
/**
 * Cl: At most one vertex can lie in a region represented by a quadtree leaf
 * C2’: If a region contains a vertex, then it can contain no q-edge that 
 * 		does not include that vertex..
 * C3’: If a region contains no vertices, then it can contain only q-edges that meet
 * 		at a common vertex exterior to the region.
 * @author Joshua Fann
 *
 */
public class PM2Validator implements Validator {

	public boolean valid(Black node) {
		//C1
		if(node.getNumPoints() > 1)
			return false;
		Iterator<Road> roads = node.geometry.iterator();
		//C3'
		if(node.getCity() == null){
			int flag = 0;
			Road road = roads.next();
			City city1 = road.getStart();
			City city2 = road.getEnd();
			if(roads.hasNext()){
				road = roads.next();
				if(road.contains(city1))
					flag = 1;
				else if(road.contains(city2))
					flag = 2;
				else
					return false;
				while(roads.hasNext()){
					road = roads.next();
					if(flag == 1){
						if(!road.contains(city1))
							return false;
					}
					if(flag == 2){
						if(!road.contains(city2))
							return false;
					}
				}
			}
			
		}else{
			//C2'
			City city = node.getCity();
			//skips the city object
			Road road = roads.next();
			while(roads.hasNext()){
				road = roads.next();
				if(!road.contains(city)){
					return false;
				}
			}
		}
		return true;
	}

}
