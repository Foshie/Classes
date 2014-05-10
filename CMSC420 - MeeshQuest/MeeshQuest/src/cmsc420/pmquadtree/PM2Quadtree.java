package cmsc420.pmquadtree;

import cmsc420.pmquadtree.PMQuadtree;

public class PM2Quadtree extends PMQuadtree {

	public PM2Quadtree(int spatialWidth,int spatialHeight) {
		super(new PM2Validator(), spatialWidth, spatialHeight, 2);
	}

}
