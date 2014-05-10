package cmsc420.pmquadtree;

import cmsc420.pmquadtree.PMQuadtree;

public class PM1Quadtree extends PMQuadtree {

	public PM1Quadtree(int spatialWidth,int spatialHeight) {
		super(new PM1Validator(), spatialWidth, spatialHeight, 1);
	}

}
