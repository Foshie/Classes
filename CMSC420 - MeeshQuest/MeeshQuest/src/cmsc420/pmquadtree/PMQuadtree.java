package cmsc420.pmquadtree;

import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;
import java.util.TreeSet;

import cmsc420.city.City;
import cmsc420.command.RoadOutOfSpatialBoundsThrowable;
import cmsc420.geom.Inclusive2DIntersectionVerifier;
import cmsc420.road.Road;
import cmsc420.road.RoadNameComparator;

/**
 * A Polygonal Map Quadtree (PM Quadtree) is an abstract multidimensional 4-ary
 * tree used to store edge data (and points). A PM Quadtree has a key space
 * partition. Shape is not insertion order-dependent but spatially dependent.
 * All boundaries closed, and any inserted edges may not intersect.
 * 
 * @author Ben Zoller
 * @version 1.0, 14 Mar 2007
 */
public abstract class PMQuadtree {

	/** stores all mapped roads in the PM Quadtree */
	final protected TreeSet<Road> roadsInPMQuadtree;

	/** stores how many roads are connected to each city */
	final protected HashMap<String, Integer> numRoadsForCity;

	int numIsolatedCities = 0;

	/** root of the PM Quadtree */
	protected Node root;

	/** spatial width of the PM Quadtree */
	final protected int spatialWidth;

	/** spatial height of the PM Quadtree */
	final protected int spatialHeight;

	/** spatial origin of the PM Quadtree (i.e. (0,0)) */
	final protected Point2D.Float spatialOrigin;

	/** validator for the PM Quadtree */
	final protected Validator validator;

	/** singleton white node */
	final protected White white = new White();

	/** order of the PM Quadtree (one of: {1,2,3}) */
	final protected int order;

	public abstract class Node {
		/** Type flag for an empty PM Quadtree leaf node */
		public static final int WHITE = 0;

		/** Type flag for a non-empty PM Quadtree leaf node */
		public static final int BLACK = 1;

		/** Type flag for a PM Quadtree internal node */
		public static final int GRAY = 2;

		/** type of PR Quadtree node (either empty, leaf, or internal) */
		protected final int type;

		/**
		 * Constructor for abstract Node class.
		 * 
		 * @param type
		 *            type of the node (either empty, leaf, or internal)
		 */
		protected Node(final int type) {
			this.type = type;
		}

		/**
		 * Gets the type of this PM Quadtree node. One of: BLACK, WHITE, GRAY.
		 * 
		 * @return type of this PM Quadtree node
		 */
		public int getType() {
			return type;
		}

		/**
		 * Adds a road to this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be added
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 * @throws InvalidPartitionThrowable
		 *             if the map if partitioned too deeply
		 * @throws IntersectingRoadsThrowable
		 *             if this road intersects with another road
		 */
		public Node add(final Road g, final Point2D.Float origin,
				final int width, final int height) throws RoadViolatesPMRulesThrowable{
			throw new UnsupportedOperationException();
		}

		/**
		 * Removes a road from this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be removed
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 */
		public Node remove(final Road g, final Point2D.Float origin,
				final int width, final int height) {
			throw new UnsupportedOperationException();
		}

		/**
		 * Returns if this node follows the rules of the PM Quadtree.
		 * 
		 * @return <code>true</code> if the node follows the rules of the PM
		 *         Quadtree; <code>false</code> otherwise
		 */
		public boolean isValid() {
			throw new UnsupportedOperationException();
		}

		/**
		 * Gets all the roads contained by this node and its descendant nodes
		 * (if applicable).
		 * 
		 * @return list of roads contained by this node
		 */
		public LinkedList<Road> getGeometry() {
			throw new UnsupportedOperationException();
		}

	}

	/**
	 * White class represents an empty PM Quadtree leaf node.
	 * 
	 * @author Ben Zoller
	 * @version 1.0, 14 Mar 2007
	 */
	public class White extends Node {
		/**
		 * Constructs and initializes an empty PM Quadtree leaf node.
		 */
		public White() {
			super(WHITE);
		}

		/**
		 * Adds a road to this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be added
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 * @throws InvalidPartitionThrowable
		 *             if the map if partitioned too deeply
		 * @throws IntersectingRoadsThrowable
		 *             if this road intersects with another road
		 */
		public Node add(final Road g, final Point2D.Float origin,
				final int width, final int height) throws RoadViolatesPMRulesThrowable{
			final Black blackNode = new Black();
			return blackNode.add(g, origin, width, height);
		}

		/**
		 * Removes a road from this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be removed
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 */
		public Node remove(final Road g, final Point2D.Float origin,
				final int width, final int height) {
			/* this is necessary for cleanup operations */
			return this;
		}

		/**
		 * Returns if this node follows the rules of the PM Quadtree.
		 * 
		 * @return <code>true</code> if the node follows the rules of the PM
		 *         Quadtree; <code>false</code> otherwise
		 */
		public boolean isValid() {
			return true;
		}

		public String toString() {
			return "white";
		}

	}

	/**
	 * Black class represents a non-empty PM Quadtree leaf node. Black nodes are
	 * capable of storing both cities (points) and roads (line segments).
	 * <p>
	 * Each black node stores cities and roads into its own sorted geometry
	 * list.
	 * <p>
	 * Black nodes are split into a gray node if they do not satisfy the rules
	 * of the PM Quadtree.
	 * 
	 * @author Ben Zoller
	 * @version 1.0, 14 Mar 2007
	 */
	public class Black extends Node {

		/** list of cities and roads contained within black node */
		final protected LinkedList<Road> geometry;

		/** number of cities contained within this black node */
		protected int numPoints;

		/**
		 * Constructs and initializes a non-empty PM Quadtree leaf node.
		 */
		public Black() {
			super(BLACK);
			geometry = new LinkedList<Road>();
			numPoints = 0;
		}

		/**
		 * Gets a linked list of the cities and roads contained by this black
		 * node.
		 * 
		 * @return list of cities and roads contained within this black node
		 */
		public LinkedList<Road> getGeometry() {
			return geometry;
		}

		/**
		 * Gets the index of the road in this black node's geometry list.
		 * 
		 * @param g
		 *            road to be searched for in the sorted geometry list
		 * @return index of the search key, if it is contained in the list;
		 *         otherwise, (-(insertion point) - 1)
		 */
		private int getIndex(final Road g) {
			return Collections.binarySearch(geometry, g,
					new GeometryComparator());
		}

		/**
		 * Adds a road to this black node. After insertion, if the node becomes
		 * invalid, it will be split into a Gray node.
		 */
		public Node add(final Road g, final Point2D.Float origin,
				final int width, final int height) throws RoadViolatesPMRulesThrowable {
			int isoFlag = 0, startFlag = 0, endFlag = 0;
			Road startRoad = new Road(g.getStart(), g.getStart());
			Road endRoad = new Road(g.getEnd(), g.getEnd());
			if (!g.isIsolatedCity()) {
				/* create region rectangle */
				final Rectangle2D.Float rect = new Rectangle2D.Float(origin.x,
						origin.y, width, height);
				isoFlag = 1;
				/* check if start point intersects with region */
				if (Inclusive2DIntersectionVerifier.intersects(g.getStart()
						.toPoint2D(), rect)) {
					addRoadToList(startRoad);
					startFlag=1;
				}

				/* check if end point intersects with region */
				if (Inclusive2DIntersectionVerifier.intersects(g.getEnd()
						.toPoint2D(), rect)) {
					addRoadToList(endRoad);
					endFlag = 1;
				}

			}

			/* add the road to the geometry list */
			addRoadToList(g);

			/* check if this node is valid */
			if (isValid()) {
				/* valid so return this black node */
				return this;
			} else {
				/* invalid so partition into a Gray node */
				Node toRet;
				try{
					toRet =  partition(origin, width, height);
				}catch(RoadViolatesPMRulesThrowable e){
					throw new RoadViolatesPMRulesThrowable();
				}
				return toRet;
			}
		}

		/**
		 * Adds a road to this node's geometry list.
		 * 
		 * @param g
		 *            road to be added
		 */
		private boolean addRoadToList(final Road g) {
			/* search for the non-existent item */
			final int index = getIndex(g);

			/* add the non-existent item to the list */
			if (index < 0) {
				geometry.add(-index - 1, g);

				if (g.isCity()) {
					numPoints++;
				}
				return true;
			}
			return false;
		}

		/**
		 * Removes a road from this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be removed
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 */
		public Node remove(final Road g, final Point2D.Float origin,
				final int width, final int height) {

			if (!g.isIsolatedCity()) {
				/* create region rectangle */
				final Rectangle2D.Float rect = new Rectangle2D.Float(origin.x,
						origin.y, width, height);

				/* check if start point intersects the region */
				if (Inclusive2DIntersectionVerifier.intersects(g.getStart()
						.toPoint2D(), rect)
						&& numRoadsForCity.get(g.getStart().getName()) == 1) {
					removeRoadFromList(new Road(g.getStart(), g.getStart()));
				}

				/* check if end point intersects the region */
				if (Inclusive2DIntersectionVerifier.intersects(g.getEnd()
						.toPoint2D(), rect)
						&& numRoadsForCity.get(g.getEnd().getName()) == 1) {
					removeRoadFromList(new Road(g.getEnd(), g.getEnd()));
				}
			}

			/* remove the road */
			removeRoadFromList(g);

			if (geometry.isEmpty()) {
				return white;
			} else {
				return this;
			}
		}

		/**
		 * Removes a specified road from this black node.
		 * 
		 * @param g
		 *            road to be removed
		 * @return if the road was successfully removed from this black node
		 */
		private boolean removeRoadFromList(final Road g) {
			final int index = getIndex(g);
			if (index >= 0) {
				geometry.remove(index);

				if (g.isCity()) {
					numPoints--;
				}
				return true;
			}
			return false;
		}

		/**
		 * Returns if this node follows the rules of the PM Quadtree.
		 * 
		 * @return <code>true</code> if the node follows the rules of the PM
		 *         Quadtree; <code>false</code> otherwise
		 */
		public boolean isValid() {
			return validator.valid(this);
		}

		/**
		 * Gets the number of cities contained in this black node.
		 * 
		 * @return number of cities contained in this black node
		 */
		public int getNumPoints() {
			return numPoints;
		}

		/**
		 * Partitions an invalid back node into a gray node and adds this black
		 * node's roads to the new gray node.
		 * 
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return the new gray node
		 * @throws InvalidPartitionThrowable
		 *             if the quadtree was partitioned too deeply
		 * @throws IntersectingRoadsThrowable
		 *             if two roads intersect
		 */
		private Node partition(final Point2D.Float origin, final int width,
				final int height) throws RoadViolatesPMRulesThrowable {
			if(width == 1 || height == 1)
				throw new RoadViolatesPMRulesThrowable();
			/* create new gray node */
			Node gray = new Gray(origin, width, height);


			for (int i = 0; i < numPoints; i++) {
				final Road road = geometry.get(i);
				if (road.isIsolatedCity()) {
					gray = gray.add(road, origin, width, height);
				}
			}

			/* only add roads */
			for (int i = numPoints; i < geometry.size(); i++) {
				final Road road = geometry.get(i);
				gray = gray.add(road, origin, width, height);
			}
			return gray;
		}

		/**
		 * Returns a string representing this black node and its road list.
		 * 
		 * @return a string representing this black node and its road list
		 */
		public String toString() {
			return "black: " + geometry.toString();
		}

		/**
		 * Returns if this black node contains a city.
		 * 
		 * @return if this black node contains a city
		 */
		public boolean containsCity() {
			return (numPoints > 0);
		}

		/**
		 * If this black node contains a city, returns the city contained within
		 * this black node. Else returns <code>null</code>.
		 * 
		 * @return the city if it exists, else <code>null</code>
		 */
		public City getCity() {
			final Road g = geometry.getFirst();
			return g.isCity() ? g.getStart() : null;
		}

		public boolean isIsolated() {
			final Road g = geometry.getFirst();
			if (!g.isCity()) {
				return false;
			}
			if (!g.isIsolatedCity()) {
				return false;
			}
			return true;
		}
	}

	/**
	 * Gray class represents an internal PM Quadtree node.
	 * 
	 * @author Ben Zoller
	 * @version 1.0, 14 Mar 2007
	 */
	public class Gray extends Node {
		/** this gray node's 4 child nodes */
		final protected Node[] children;

		/** regions representing this gray node's 4 child nodes */
		final protected Rectangle2D.Float[] regions;

		/** origin of the rectangular bounds of this node */
		final protected Point2D.Float origin;

		/** the origin of rectangular bounds of each of the node's child nodes */
		final protected Point2D.Float[] origins;

		/** half the width of the rectangular bounds of this node */
		final protected int halfWidth;

		/** half the height of the rectangular bounds of this node */
		final protected int halfHeight;

		/**
		 * Constructs and initializes an internal PM Quadtree node.
		 * 
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 */
		public Gray(final Point2D.Float origin, final int width,
				final int height) {
			super(GRAY);

			/* set this node's origin */
			this.origin = origin;

			/* initialize the children as white nodes */
			children = new Node[4];
			for (int i = 0; i < 4; i++) {
				children[i] = white;
			}

			/* get half the width and half the height */
			halfWidth = width >> 1;
			halfHeight = height >> 1;

			/* initialize the child origins */
			origins = new Point2D.Float[4];
			origins[0] = new Point2D.Float(origin.x, origin.y + halfHeight);
			origins[1] = new Point2D.Float(origin.x + halfWidth, origin.y
					+ halfHeight);
			origins[2] = new Point2D.Float(origin.x, origin.y);
			origins[3] = new Point2D.Float(origin.x + halfWidth, origin.y);

			/* initialize the child regions */
			regions = new Rectangle2D.Float[4];
			for (int i = 0; i < 4; i++) {
				regions[i] = new Rectangle2D.Float(origins[i].x, origins[i].y,
						halfWidth, halfHeight);
			}
		}

		/**
		 * Adds a road to this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be added
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 * @throws InvalidPartitionThrowable
		 *             if the map if partitioned too deeply
		 * @throws IntersectingRoadsThrowable
		 *             if this road intersects with another road
		 */
		public Node add(final Road g, final Point2D.Float origin,
				final int width, final int height) throws RoadViolatesPMRulesThrowable {

			for (int i = 0; i < 4; i++) {
				/* check for line-rectangle intersection */
				if (Inclusive2DIntersectionVerifier.intersects(g.toLine2D(),
						regions[i])) {
					try{
						children[i] = children[i].add(g, origins[i], halfWidth,
								halfHeight);
					}catch(RoadViolatesPMRulesThrowable e){
						throw new RoadViolatesPMRulesThrowable();
					}
				}
			}
			return this;
		}

		/**
		 * Removes a road from this PM Quadtree node.
		 * 
		 * @param g
		 *            road to be removed
		 * @param origin
		 *            origin of the rectangular bounds of this node
		 * @param width
		 *            width of the rectangular bounds of this node
		 * @param height
		 *            height of the rectangular bounds of this node
		 * @return this node after the city has been added
		 */
		public Node remove(Road g, Point2D.Float origin, int width, int height) {
			if (g.isIsolatedCity()) {
				for (int i = 0; i < 4; i++) {
					if (Inclusive2DIntersectionVerifier.intersects(g.getStart().toPoint2D(),
							regions[i])) {
						children[i] = children[i].remove(g, origins[i], halfWidth,
								halfHeight);
					}
				}
			} else {
				for (int i = 0; i < 4; i++) {
					if (Inclusive2DIntersectionVerifier.intersects(g.toLine2D(),
							regions[i])) {
						children[i] = children[i].remove(g, origins[i], halfWidth,
								halfHeight);
					}
				}
			}

			if (numWhiteChildren() == 4) {
				return white;

			} else if (numWhiteChildren() == 3 && numBlackChildren() == 1) {
				for (final Node node : children) {
					if (node.getType() == BLACK) {
						return node;
					}
				}
				return this;

			} else if (numBlackChildren() >= 1 || numWhiteChildren() >= 1) {
				final Black b = new Black();
				for (final Node node : children) {
					if (node.getType() != WHITE) {
						for (final Road r : node.getGeometry()) {
							b.addRoadToList(r);
						}
					}
				}

				if (b.isValid()) {
					return b;
				} else {
					return this;
				}
			} else {
				return this;
			}
		}

		private int numWhiteChildren() {
			int total = 0;
			for (final Node n : children) {
				if (n == white) {
					total++;
				}
			}
			return total;
		}

		private int numBlackChildren() {
			int total = 0;
			for (final Node n : children) {
				if (n.getType() == BLACK) {
					total++;
				}
			}
			return total;
		}

		/**
		 * Returns if this node follows the rules of the PM Quadtree.
		 * 
		 * @return <code>true</code> if the node follows the rules of the PM
		 *         Quadtree; <code>false</code> otherwise
		 */
		public boolean isValid() {
			return children[0].isValid() && children[1].isValid()
					&& children[2].isValid() && children[3].isValid();
		}

		public String toString() {
			StringBuilder grayStringBuilder = new StringBuilder("gray:");
			for (Node child : children) {
				grayStringBuilder.append("\n\t");
				grayStringBuilder.append(child.toString());
			}
			return grayStringBuilder.toString();
		}

		public LinkedList<Road> getGeometry() {
			final LinkedList<Road> roads = new LinkedList<Road>();
			for (Node child : children) {
				if (child.getType() != WHITE) {
					roads.addAll(child.getGeometry());
				}
			}
			return roads;
		}

		/**
		 * Gets the child node of this node according to which quadrant it falls
		 * in.
		 * 
		 * @param quadrant
		 *            quadrant number (top left is 0, top right is 1, bottom
		 *            left is 2, bottom right is 3)
		 * @return child node
		 */
		public Node getChild(final int quadrant) {
			if (quadrant < 0 || quadrant > 3) {
				throw new IllegalArgumentException();
			} else {
				return children[quadrant];
			}
		}

		/**
		 * Gets the rectangular region for the specified child node of this
		 * internal node.
		 * 
		 * @param quadrant
		 *            quadrant that child lies within
		 * @return rectangular region for this child node
		 */
		public Rectangle2D.Float getChildRegion(int quadrant) {
			if (quadrant < 0 || quadrant > 3) {
				throw new IllegalArgumentException();
			} else {
				return regions[quadrant];
			}
		}

		/**
		 * Gets the center X coordinate of this node's rectangular bounds.
		 * 
		 * @return center X coordinate of this node's rectangular bounds
		 */
		public int getCenterX() {
			return (int) origin.x + halfWidth;
		}

		/**
		 * Gets the center Y coordinate of this node's rectangular bounds.
		 * 
		 * @return center Y coordinate of this node's rectangular bounds
		 */
		public int getCenterY() {
			return (int) origin.y + halfHeight;
		}

		/**
		 * Gets half the width of this internal node.
		 * 
		 * @return half the width of this internal node
		 */
		public int getHalfWidth() {
			return halfWidth;
		}

		/**
		 * Gets half the height of this internal node.
		 * 
		 * @return half the height of this internal node
		 */
		public int getHalfHeight() {
			return halfHeight;
		}
	}

	public PMQuadtree(final Validator validator, final int spatialWidth,
			final int spatialHeight, final int order) {
		if (order < 1 || order > 3) {
			throw new IllegalArgumentException("order must be one of: {1,2,3}");
		}

		root = white;
		this.validator = validator;
		this.spatialWidth = spatialWidth;
		this.spatialHeight = spatialHeight;
		spatialOrigin = new Point2D.Float(0.0f, 0.0f);
		roadsInPMQuadtree = new TreeSet<Road>(new RoadNameComparator());
		numRoadsForCity = new HashMap<String, Integer>();
		this.order = order;
	}

	public Node getRoot() {
		return root;
	}

	public void add(final Road g) throws RoadOutOfSpatialBoundsThrowable, RoadAlreadyExistsThrowable, IsolatedCityAlreadyExistsThrowable, RoadViolatesPMRulesThrowable, RoadIntersectsAnotherRoadThrowable {
		if(g.getStart().getX() < 0 || g.getStart().getX() > spatialWidth || g.getStart().getY() < 0 || g.getStart().getY() > spatialHeight ||
				g.getEnd().getX() < 0 || g.getEnd().getX() > spatialWidth || g.getEnd().getY() < 0 || g.getEnd().getY() > spatialHeight)
			throw new RoadOutOfSpatialBoundsThrowable();
		if (g.isCity()) {
			throw new IllegalArgumentException("Road g is a city");
		}
		if (cityIsIsolated(g.getStart().getName()) || 
				cityIsIsolated(g.getEnd().getName())) {
			throw new IsolatedCityAlreadyExistsThrowable();
		}

		final Road g2 = new Road(g.getEnd(), g.getStart());

		if (roadsInPMQuadtree.contains(g) || roadsInPMQuadtree.contains(g2)) {
			throw new RoadAlreadyExistsThrowable();
		}

		Iterator<Road> roadIter = roadsInPMQuadtree.iterator();
		while(roadIter.hasNext()){
			
			Road road = roadIter.next();
			if(Inclusive2DIntersectionVerifier.intersects(g.toLine2D(), road.toLine2D())){

				if(!road.contains(g.getStart()) && !road.contains(g.getEnd()))
					throw new RoadIntersectsAnotherRoadThrowable();
			}
		}
		try{

			roadsInPMQuadtree.add(g);
			increaseNumRoadsMap(g.getStart().getName());
			increaseNumRoadsMap(g.getEnd().getName());

			root = root.add(g, spatialOrigin, spatialWidth, spatialHeight);
		}catch(RoadViolatesPMRulesThrowable e){
			throw new RoadViolatesPMRulesThrowable();
		}

	}

	public void add(final City c) throws IsolatedCityOutOfSpatialBoundsThrowable, IsolatedCityAlreadyExistsThrowable, RoadAlreadyExistsThrowable, RoadIntersectsAnotherRoadThrowable, RoadViolatesPMRulesThrowable {
		Road isoCity = new Road(c);
		if(c.getX() > spatialWidth || c.getX() < 0 || c.getY() > spatialHeight || c.getY() < 0)
			throw new IsolatedCityOutOfSpatialBoundsThrowable();
		if (numRoadsForCity.get(c.getName()) != null) {
			if (numRoadsForCity.get(c.getName()) > 0) {
				throw new RoadAlreadyExistsThrowable();
			} else {
				throw new IsolatedCityAlreadyExistsThrowable();
			}
		}

		Iterator<Road> roadIter = roadsInPMQuadtree.iterator();
		while(roadIter.hasNext()){
			Road road = roadIter.next();
			if(Inclusive2DIntersectionVerifier.intersects(c.toPoint2D(), road.toLine2D()))
				throw new RoadIntersectsAnotherRoadThrowable();
		}
		try{
			root = root.add(isoCity, spatialOrigin, spatialWidth, spatialHeight);
		}catch(RoadViolatesPMRulesThrowable e){
			throw new RoadViolatesPMRulesThrowable();
		}

		numIsolatedCities++;
		numRoadsForCity.put(c.getName(), 0);
	}

	private void increaseNumRoadsMap(final String name) {
		Integer numRoads = numRoadsForCity.get(name);
		if (numRoads != null) {
			numRoads++;
			numRoadsForCity.put(name, numRoads);
		} else {
			numRoadsForCity.put(name, 1);
		}
	}

	private void decreaseNumRoadsMap(final String name) {
		Integer numRoads = numRoadsForCity.get(name);
		numRoads--;
		if (numRoads > 0) {
			numRoadsForCity.put(name, numRoads);
		} else {
			numRoadsForCity.remove(name);
		}
	}

	public void remove(final Road g) throws RoadNotMappedThrowable {
		if (roadsInPMQuadtree.contains(g)) {
			root = root.remove(g, spatialOrigin, spatialWidth, spatialHeight);

			roadsInPMQuadtree.remove(g);
			decreaseNumRoadsMap(g.getStart().getName());
			decreaseNumRoadsMap(g.getEnd().getName());

		} else {
			throw new RoadNotMappedThrowable();
		}
	}

	public void remove(final City c) throws IsolatedCityNotMappedThrowable {
		Road isoCity = new Road(c);
		if (cityIsIsolated(c.getName())) {
			root = root.remove(isoCity, spatialOrigin, spatialWidth, spatialHeight);

			numIsolatedCities--;
			numRoadsForCity.remove(c.getName());
		} else {
			throw new IsolatedCityNotMappedThrowable();
		}
	}

	public void clear() {
		root = white;
		roadsInPMQuadtree.clear();
		numRoadsForCity.clear();
		numIsolatedCities = 0;
	}

	public boolean isEmpty() {
		return (root == white);
	}

	public boolean containsRoad(final Road g) {
		final Road g2 = new Road(g.getEnd(), g.getStart());

		return (roadsInPMQuadtree.contains(g) || roadsInPMQuadtree.contains(g2));
	}

	public boolean containsCity(final String name) {
		final Integer numRoads = numRoadsForCity.get(name);
		return (numRoads != null); // && (numRoads > 0);
	}

	public int getNumRoadsForCity(final String name) {
		final Integer numRoads = numRoadsForCity.get(name);
		if (numRoads == null) {
			return -1;
		}
		return numRoads.intValue();
	}

	public int getOrder() {
		return order;
	}

	public int getNumCities() {
		return numRoadsForCity.keySet().size();
	}

	public int getNumIsolatedCities() {
		return numIsolatedCities;
	}

	private boolean cityIsIsolated(String name) {
		Integer n = numRoadsForCity.get(name);
		if (n == null || n > 0) {
			return false;
		}
		return true;
	}

	public TreeSet<Road> getRoadsInPMQuadtree() {
		return roadsInPMQuadtree;
	}
	//Returns a Set of strings of all cities mapped
	public Set<String> getCities(){
		return (Set<String>) numRoadsForCity.keySet();
	}
	public void deleteCity(City deletedCity) {
		Iterator<Road> roadIter = roadsInPMQuadtree.iterator();
		while(roadIter.hasNext()){
			Road road = roadIter.next();
			if(road.contains(deletedCity))
				root.remove(road, spatialOrigin, spatialWidth, spatialHeight);
		}

	}

}
