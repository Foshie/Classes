/*
 * @(#)Command.java        1.0 2007/01/23
 *
 * Copyright Ben Zoller (University of Maryland, College Park), 2007
 * All rights reserved. Permission is granted for use and modification in CMSC420 
 * at the University of Maryland.
 */
package cmsc420.command;

import java.awt.Color;
import java.awt.geom.Arc2D;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Float;
import java.io.File;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import cmsc420.city.City;
import cmsc420.city.CityLocationComparator;
import cmsc420.city.CityNameComparator;
import cmsc420.dijkstra.Dijkstranator;
import cmsc420.dijkstra.Path;
import cmsc420.drawing.CanvasPlus;
import cmsc420.geom.Circle2D;
import cmsc420.geom.Inclusive2DIntersectionVerifier;
import cmsc420.geom.Shape2DDistanceCalculator;
import cmsc420.hextrie.HexTrie;
import cmsc420.hextrie.StringComparator;
import cmsc420.pmquadtree.IsolatedCityAlreadyExistsThrowable;
import cmsc420.pmquadtree.IsolatedCityNotMappedThrowable;
import cmsc420.pmquadtree.IsolatedCityOutOfSpatialBoundsThrowable;
import cmsc420.pmquadtree.PM1Quadtree;
import cmsc420.pmquadtree.PM2Quadtree;
import cmsc420.pmquadtree.PM3Quadtree;
import cmsc420.pmquadtree.PMQuadtree;
import cmsc420.pmquadtree.PMQuadtree.Black;
import cmsc420.pmquadtree.PMQuadtree.Gray;
import cmsc420.pmquadtree.PMQuadtree.Node;
import cmsc420.pmquadtree.RoadAlreadyExistsThrowable;
import cmsc420.pmquadtree.RoadIntersectsAnotherRoadThrowable;
import cmsc420.pmquadtree.RoadNotMappedThrowable;
import cmsc420.pmquadtree.RoadViolatesPMRulesThrowable;
import cmsc420.road.Road;
import cmsc420.road.RoadAdjacencyList;
import cmsc420.road.RoadNameComparator;
import cmsc420.xml.XmlUtility;

/**
 * Processes each command in the MeeshQuest program. Takes in an XML command
 * node, processes the node, and outputs the results.
 * 
 * Modified by Alan Jackoway to include a BP tree.
 * 
 * @author Ben Zoller
 * @version 2.0, 23 Jan 2007
 */
public class Command {
	/** output DOM Document tree */
	protected Document results;

	/** root node of results document */
	protected Element resultsNode;

	/**
	 * stores created cities sorted by their names (used with listCities
	 * command)
	 */
	protected final HexTrie<String, City> citiesByName;
	protected final TreeMap<String, City> cities = new TreeMap<String, City>(new StringComparator());
	protected final HexTrie<String, City> isoCities;

	/**
	 * stores created cities sorted by their locations (used with listCities
	 * command)
	 */
	protected final TreeSet<City> citiesByLocation = new TreeSet<City>(
			new CityLocationComparator());

	private final RoadAdjacencyList roads = new RoadAdjacencyList();

	/** stores mapped cities in a spatial data structure */
	protected PMQuadtree pmQuadtree;

	/** order of the PM Quadtree */
	protected int pmOrder;

	/** spatial width of the PM Quadtree */
	protected int spatialWidth;

	/** spatial height of the PM Quadtree */
	protected int spatialHeight;
	protected boolean bstarMode = false;

	/** graphical mapping tool (used with saveMap command) */
	// protected CanvasPlus canvas;
	/**
	 * Set the graphical mapping tool to be used.
	 * 
	 * @param canvas
	 *            graphical mapping tool
	 */
	/*
	 * public void setCanvas(CanvasPlus canvas) { this.canvas = canvas; }
	 */

	public Command(int leafOrder, boolean bStarplus) {

		citiesByName = new HexTrie<String, City>(new StringComparator(), leafOrder, bStarplus);
		isoCities = new HexTrie<String, City>(new StringComparator(), leafOrder, bStarplus);
	}

	/**
	 * Set the DOM Document tree to send the results of processed commands to.
	 * Creates the root results node.
	 * 
	 * @param results
	 *            DOM Document tree
	 */
	public void setResults(Document results) {
		this.results = results;
		resultsNode = results.createElement("results");
		results.appendChild(resultsNode);
	}

	/**
	 * Creates a command result element. Initializes the command name.
	 * 
	 * @param node
	 *            the command node to be processed
	 * @return the results node for the command
	 */
	private Element getCommandNode(final Element node) {
		final Element commandNode = results.createElement("command");
		commandNode.setAttribute("name", node.getNodeName());
		commandNode.setAttribute("id", node.getAttribute("id"));
		return commandNode;
	}

	/**
	 * Processes an integer attribute for a command. Appends the parameter to
	 * the parameters node of the results. Should not throw a number format
	 * exception if the attribute has been defined to be an integer in the
	 * schema and the XML has been validated beforehand.
	 * 
	 * @param commandNode
	 *            node containing information about the command
	 * @param attributeName
	 *            integer attribute to be processed
	 * @param parametersNode
	 *            node to append parameter information to
	 * @return integer attribute value
	 */
	private int processIntegerAttribute(final Element commandNode,
			final String attributeName, final Element parametersNode) {
		final String value = commandNode.getAttribute(attributeName);

		if (parametersNode != null) {
			/* add the parameters to results */
			final Element attributeNode = results.createElement(attributeName);
			attributeNode.setAttribute("value", value);
			parametersNode.appendChild(attributeNode);
		}

		/* return the integer value */
		return Integer.parseInt(value);
	}

	/**
	 * Processes a string attribute for a command. Appends the parameter to the
	 * parameters node of the results.
	 * 
	 * @param commandNode
	 *            node containing information about the command
	 * @param attributeName
	 *            string attribute to be processed
	 * @param parametersNode
	 *            node to append parameter information to
	 * @return string attribute value
	 */
	private String processStringAttribute(final Element commandNode,
			final String attributeName, final Element parametersNode) {
		final String value = commandNode.getAttribute(attributeName);

		if (parametersNode != null) {
			/* add parameters to results */
			final Element attributeNode = results.createElement(attributeName);
			attributeNode.setAttribute("value", value);
			parametersNode.appendChild(attributeNode);
		}

		/* return the string value */
		return value;
	}

	/**
	 * Reports that the requested command could not be performed because of an
	 * error. Appends information about the error to the results.
	 * 
	 * @param type
	 *            type of error that occurred
	 * @param command
	 *            command node being processed
	 * @param parameters
	 *            parameters of command
	 */
	private void addErrorNode(final String type, final Element command,
			final Element parameters) {
		final Element error = results.createElement("error");
		error.setAttribute("type", type);
		error.appendChild(command);
		error.appendChild(parameters);
		resultsNode.appendChild(error);
	}

	/**
	 * Reports that a command was successfully performed. Appends the report to
	 * the results.
	 * 
	 * @param command
	 *            command not being processed
	 * @param parameters
	 *            parameters used by the command
	 * @param output
	 *            any details to be reported about the command processed
	 */
	private Element addSuccessNode(final Element command,
			final Element parameters, final Element output) {
		final Element success = results.createElement("success");
		success.appendChild(command);
		success.appendChild(parameters);
		success.appendChild(output);
		resultsNode.appendChild(success);
		return success;
	}

	/**
	 * Processes the commands node (root of all commands). Gets the spatial
	 * width and height of the map and send the data to the appropriate data
	 * structures.
	 * 
	 * @param node
	 *            commands node to be processed
	 */
	public void processCommands(final Element node) {
		spatialWidth = Integer.parseInt(node.getAttribute("spatialWidth"));
		spatialHeight = Integer.parseInt(node.getAttribute("spatialHeight"));
		pmOrder = Integer.parseInt(node.getAttribute("pmOrder"));
		/* initialize canvas */
		// canvas.setFrameSize(spatialWidth, spatialHeight);
		/* add a rectangle to show where the bounds of the map are located */
		// canvas.addRectangle(0, 0, spatialWidth, spatialHeight, Color.BLACK,
		// false);
		/* create PM Quadtree */
		pmQuadtree = null;
		if (pmOrder == 3)
			pmQuadtree = new PM3Quadtree(spatialWidth, spatialHeight);
		if(pmOrder == 2)
			pmQuadtree = new PM2Quadtree(spatialWidth, spatialHeight);
		if(pmOrder == 1)
			pmQuadtree = new PM1Quadtree(spatialWidth, spatialHeight);
		// pmQuadtree.setCanvas(canvas);
	}

	/**
	 * Processes a createCity command. Creates a city in the dictionary (Note:
	 * does not map the city). An error occurs if a city with that name or
	 * location is already in the dictionary.
	 * 
	 * @param node
	 *            createCity node to be processed
	 */
	public void processCreateCity(final Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");

		final String name = processStringAttribute(node, "name", parametersNode);
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);
		final int radius = processIntegerAttribute(node, "radius",
				parametersNode);
		final String color = processStringAttribute(node, "color",
				parametersNode);

		/* create the city */
		final City city = new City(name, x, y, radius, color);

		if (cities.containsKey(name)) {
			addErrorNode("duplicateCityName", commandNode, parametersNode);
		} else if (citiesByLocation.contains(city)) {
			addErrorNode("duplicateCityCoordinates", commandNode,
					parametersNode);
		} else {
			final Element outputNode = results.createElement("output");

			/* add city to dictionary */
			cities.put(name, city);
			citiesByName.put(name, city);
			citiesByLocation.add(city);

			/* add success node to results */
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}

	/**
	 * Processes a deleteCity command. Deletes a city from the dictionary. An
	 * error occurs if the city does not exist or is currently mapped.
	 * 
	 * @param node
	 *            deleteCity node being processed
	 */
	public void processDeleteCity(final Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final String name = processStringAttribute(node, "name", parametersNode);

		if (!cities.containsKey(name)) {
			/* city with name does not exist */
			addErrorNode("cityDoesNotExist", commandNode, parametersNode);
		} else {
			/* delete city */
			final Element outputNode = results.createElement("output");
			final City deletedCity = (City)cities.get(name);
			if(pmQuadtree.containsCity(name)){
				pmQuadtree.deleteCity(deletedCity);		
				if(isoCities.containsKey(name))
					isoCities.remove(name);

			}
			cities.remove(name);
			citiesByName.remove(name);
			citiesByLocation.remove(deletedCity);

			/* add success node to results */
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}

	/**
	 * Clears all the data structures do there are not cities or roads in
	 * existence in the dictionary or on the map.
	 * 
	 * @param node
	 *            clearAll node to be processed
	 */
	public void processClearAll(final Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* clear data structures */
		citiesByName.clear();
		cities.clear();
		citiesByLocation.clear();
		pmQuadtree.clear();

		/* clear canvas */
		// canvas.clear();
		/* add a rectangle to show where the bounds of the map are located */
		// canvas.addRectangle(0, 0, spatialWidth, spatialHeight, Color.BLACK,
		// false);
		/* add success node to results */
		addSuccessNode(commandNode, parametersNode, outputNode);
	}

	/**
	 * Lists all the cities, either by name or by location.
	 * 
	 * @param node
	 *            listCities node to be processed
	 */
	public void processListCities(final Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final String sortBy = processStringAttribute(node, "sortBy",
				parametersNode);

		if (cities.isEmpty()) {
			addErrorNode("noCitiesToList", commandNode, parametersNode);
		} else {
			final Element outputNode = results.createElement("output");
			final Element cityListNode = results.createElement("cityList");

			Collection<City> cityCollection = null;
			if (sortBy.equals("name")) {
				List<City> cities = new ArrayList<City>(citiesByLocation.size());
				for (City c : citiesByLocation)
					cities.add(c);
				Collections.sort(cities, new Comparator<City>() {

					//@Override
					public int compare(City arg0, City arg1) {
						return arg0.getName().compareTo(arg1.getName());
					}
				});
				cityCollection = cities;
			} else if (sortBy.equals("coordinate")) {
				cityCollection = citiesByLocation;
			} else {
				/* XML validator failed */
				System.exit(-1);
			}

			for (City c : cityCollection) {
				addCityNode(cityListNode, c);
			}
			outputNode.appendChild(cityListNode);

			/* add success node to results */
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}

	/**
	 * Creates a city node containing information about a city. Appends the city
	 * node to the passed in node.
	 * 
	 * @param node
	 *            node which the city node will be appended to
	 * @param cityNodeName
	 *            name of city node
	 * @param city
	 *            city which the city node will describe
	 */
	private void addCityNode(final Element node, final String cityNodeName,
			final City city) {
		final Element cityNode = results.createElement(cityNodeName);
		cityNode.setAttribute("name", city.getName());
		cityNode.setAttribute("x", Integer.toString((int) city.getX()));
		cityNode.setAttribute("y", Integer.toString((int) city.getY()));
		cityNode.setAttribute("radius", Integer
				.toString((int) city.getRadius()));
		cityNode.setAttribute("color", city.getColor());
		node.appendChild(cityNode);
	}
	private void addRoadNode(final Element node, final Road road) {
		final Element cityNode = results.createElement("road");
		String start, end;
		if(road.getStart().getName().compareTo(road.getEnd().getName()) < 0){
			start = road.getStart().getName();
			end = road.getEnd().getName();
		}else{
			start = road.getEnd().getName();
			end = road.getStart().getName();
		}
		cityNode.setAttribute("end", end);
		cityNode.setAttribute("start", start);
		node.appendChild(cityNode);
	}
	/**
	 * Creates a city node containing information about a city. Appends the city
	 * node to the passed in node.
	 * 
	 * @param node
	 *            node which the city node will be appended to
	 * @param city
	 *            city which the city node will describe
	 */
	private void addCityNode(final Element node, final City city) {
		addCityNode(node, "city", city);
	}

	private void addIsolatedCityNode(final Element node, final City city) {
		addCityNode(node, "isolatedCity", city);
	}

	// /**
	// * Maps a city to the spatial map.
	// *
	// * @param node
	// * mapCity command node to be processed
	// */
	// public void processMapCity(final Element node) {
	// final Element commandNode = getCommandNode(node);
	// final Element parametersNode = results.createElement("parameters");
	//
	// final String name = processStringAttribute(node, "name", parametersNode);
	//
	// final Element outputNode = results.createElement("output");
	//
	// if (!citiesByName.containsKey(name)) {
	// addErrorNode("nameNotInDictionary", commandNode, parametersNode);
	// } else if (prQuadtree.contains(name)) {
	// addErrorNode("cityAlreadyMapped", commandNode, parametersNode);
	// } else {
	// City city = citiesByName.get(name);
	// try {
	// /* insert city into PR Quadtree */
	// prQuadtree.add(city);
	//
	// /* add city to canvas */
	// canvas.addPoint(city.getName(), city.getX(), city.getY(),
	// Color.BLACK);
	//
	// /* add success node to results */
	// addSuccessNode(commandNode, parametersNode, outputNode);
	// } catch (CityAlreadyMappedException e) {
	// addErrorNode("cityAlreadyMapped", commandNode, parametersNode);
	// } catch (CityOutOfBoundsException e) {
	// addErrorNode("cityOutOfBounds", commandNode, parametersNode);
	// }
	// }
	// }

	public void processMapRoad(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");

		final String start = processStringAttribute(node, "start",
				parametersNode);
		final String end = processStringAttribute(node, "end", parametersNode);

		final Element outputNode = results.createElement("output");

		if (!cities.containsKey(start)) {
			addErrorNode("startPointDoesNotExist", commandNode, parametersNode);
		} else if (!cities.containsKey(end)) {
			addErrorNode("endPointDoesNotExist", commandNode, parametersNode);
		} else {

			try {
				if (start.equals(end)) {
					pmQuadtree.add((City) cities.get(start));
					isoCities.put(start, (City) cities.get(start));
				} else {
					/* add road to spatial map */
					pmQuadtree.add(new Road((City)cities.get(start), 
							(City)cities.get(end)));

					/* add road to adjacency list */
					roads.addRoad((City)cities.get(start), (City)cities.get(end));
				}

				/* create roadCreated element */
				final Element roadCreatedNode = results
						.createElement("roadCreated");
				roadCreatedNode.setAttribute("start", start);
				roadCreatedNode.setAttribute("end", end);
				outputNode.appendChild(roadCreatedNode);

				/* add success node to results */
				addSuccessNode(commandNode, parametersNode, outputNode);

			} catch (RoadAlreadyExistsThrowable e) {
				addErrorNode("roadAlreadyMapped", commandNode, parametersNode);
			} catch (IsolatedCityAlreadyExistsThrowable e) {
				addErrorNode("isolatedCityAlreadyMapped", commandNode, parametersNode);
			}catch(IsolatedCityOutOfSpatialBoundsThrowable e){
				addErrorNode("isolatedCityOutOfSpatialBounds", commandNode, parametersNode);
			}catch(RoadOutOfSpatialBoundsThrowable e){
				addErrorNode("roadOutOfSpatialBounds", commandNode, parametersNode);
			} catch (RoadIntersectsAnotherRoadThrowable e) {
				addErrorNode("roadIntersectsAnotherRoad", commandNode, parametersNode);
			} catch (RoadViolatesPMRulesThrowable e) {
				try {

					if (start.equals(end)) {
						pmQuadtree.remove((City) cities.get(start));
					} else {
						/* remove road from spatial map */
						pmQuadtree.remove(new Road((City)cities.get(start), 
								(City)cities.get(end)));
					}
				} catch (IsolatedCityNotMappedThrowable e1) {

				} catch (RoadNotMappedThrowable e2) {
				}

				addErrorNode("roadViolatesPMRules", commandNode, parametersNode);
			}
		}
	}

	/**
	 * 
	 * Prints the BP tree that is being used to store the data.
	 * 
	 * @param node
	 *            clearAll node to be processed
	 */
	public void processPrintHexTrie(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		if (citiesByName.isEmpty()) {
			addErrorNode("emptyHexTrie", commandNode, parametersNode);
		} else {
			citiesByName.addToXmlDoc(results, outputNode);

			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}
	public void processPrintIsolatedCities(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		if (isoCities.isEmpty()) {
			addErrorNode("emptyHexTrie", commandNode, parametersNode);
		} else {

			isoCities.addToXmlDoc(results, outputNode);

			addSuccessNode(commandNode, parametersNode, outputNode);
		}

	}
	public void processUnmapRoad(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		final String start = processStringAttribute(node, "start", parametersNode);
		final String end = processStringAttribute(node, "end", parametersNode);

		if (!cities.containsKey(start)) {
			addErrorNode("startPointDoesNotExist", commandNode, parametersNode);
		} else if (!cities.containsKey(end)) {
			addErrorNode("endPointDoesNotExist", commandNode, parametersNode);
		}else{
			try{
				if (start.equals(end)) {
					pmQuadtree.remove((City) cities.get(start));
					//isoCities.remove(start);
				} else {
					/* remove road from spatial map */
					pmQuadtree.remove(new Road((City)cities.get(start), 
							(City)cities.get(end)));

					/* remove road to adjacency list */
					roads.removeRoad((City)cities.get(start), (City)cities.get(end));
				}
				/* create roadCreated element */
				final Element roadCreatedNode = results.createElement("roadDeleted");
				roadCreatedNode.setAttribute("start", start);
				roadCreatedNode.setAttribute("end", end);
				outputNode.appendChild(roadCreatedNode);

				/* add success node to results */
				addSuccessNode(commandNode, parametersNode, outputNode);

			}catch(IsolatedCityNotMappedThrowable e){
				addErrorNode("isolatedCityNotMapped", commandNode, parametersNode);			
			}catch(RoadNotMappedThrowable e){
				addErrorNode("roadNotMapped", commandNode, parametersNode);			

			}
		}
	}

	public void processShortestPath(final Element node) throws IOException,
	ParserConfigurationException, TransformerException {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");

		final String start = processStringAttribute(node, "start",
				parametersNode);
		final String end = processStringAttribute(node, "end", parametersNode);

		String saveMapName = "";
		if (!node.getAttribute("saveMap").equals("")) {
			saveMapName = processStringAttribute(node, "saveMap",
					parametersNode);
		}

		String saveHTMLName = "";
		if (!node.getAttribute("saveHTML").equals("")) {
			saveHTMLName = processStringAttribute(node, "saveHTML",
					parametersNode);
		}

		if (!pmQuadtree.containsCity(start)) {
			addErrorNode("nonExistentStart", commandNode, parametersNode);
		} else if (!pmQuadtree.containsCity(end)) {
			addErrorNode("nonExistentEnd", commandNode, parametersNode);
		} else if (!roads.getCitySet().contains(cities.get(start)) 
				|| !roads.getCitySet().contains(cities.get(end))) {
			// start or end is isolated
			if (start.equals(end)) {
				final Element outputNode = results.createElement("output");
				final Element pathNode = results.createElement("path");
				pathNode.setAttribute("length", "0.000");
				pathNode.setAttribute("hops", "0");

				LinkedList<City> cityList = new LinkedList<City>();
				cityList.add(cities.get(start));
				/* if required, save the map to an image */
				if (!saveMapName.equals("")) {
					saveShortestPathMap(saveMapName, cityList);
				}
				if (!saveHTMLName.equals("")) {
					saveShortestPathMap(saveHTMLName, cityList);
				}

				outputNode.appendChild(pathNode);
				Element successNode = addSuccessNode(commandNode,
						parametersNode, outputNode);

				if (!saveHTMLName.equals("")) {
					/* save shortest path to HTML */
					Document shortestPathDoc = XmlUtility.getDocumentBuilder()
							.newDocument();
					org.w3c.dom.Node spNode = shortestPathDoc.importNode(
							successNode, true);
					shortestPathDoc.appendChild(spNode);
					XmlUtility.transform(shortestPathDoc, new File(
							"shortestPath.xsl"), new File(saveHTMLName
									+ ".html"));
				}
			} else {
				addErrorNode("noPathExists", commandNode, parametersNode);
			}
		} else {
			final DecimalFormat decimalFormat = new DecimalFormat("#0.000");

			final Dijkstranator dijkstranator = new Dijkstranator(roads);

			final City startCity = (City)cities.get(start);
			final City endCity = (City)cities.get(end);

			final Path path = dijkstranator.getShortestPath(startCity, endCity);

			if (path == null) {
				addErrorNode("noPathExists", commandNode, parametersNode);
			} else {
				final Element outputNode = results.createElement("output");

				final Element pathNode = results.createElement("path");
				pathNode.setAttribute("length", decimalFormat.format(path
						.getDistance()));
				pathNode.setAttribute("hops", Integer.toString(path.getHops()));

				final LinkedList<City> cityList = path.getCityList();

				/* if required, save the map to an image */
				if (!saveMapName.equals("")) {
					saveShortestPathMap(saveMapName, cityList);
				}
				if (!saveHTMLName.equals("")) {
					saveShortestPathMap(saveHTMLName, cityList);
				}

				if (cityList.size() > 1) {

					/* add the first road */
					City city1 = cityList.remove();
					City city2 = cityList.remove();
					Element roadNode = results.createElement("road");
					roadNode.setAttribute("start", city1.getName());
					roadNode.setAttribute("end", city2.getName());
					pathNode.appendChild(roadNode);

					while (!cityList.isEmpty()) {
						City city3 = cityList.remove();

						/* process the angle */
						Arc2D.Float arc = new Arc2D.Float();
						arc.setArcByTangent(city1.toPoint2D(), city2
								.toPoint2D(), city3.toPoint2D(), 1);

						/* print out the direction */
						double angle = arc.getAngleExtent();
						final String direction;
						if (angle < -45) {
							direction = "left";
						} else if (angle >= 45) {
							direction = "right";
						} else {
							direction = "straight";
						}
						Element directionNode = results
								.createElement(direction);
						pathNode.appendChild(directionNode);

						/* print out the next road */
						roadNode = results.createElement("road");
						roadNode.setAttribute("start", city2.getName());
						roadNode.setAttribute("end", city3.getName());
						pathNode.appendChild(roadNode);

						/* increment city references */
						city1 = city2;
						city2 = city3;
					}
				}
				outputNode.appendChild(pathNode);
				Element successNode = addSuccessNode(commandNode,
						parametersNode, outputNode);

				if (!saveHTMLName.equals("")) {
					/* save shortest path to HTML */
					Document shortestPathDoc = XmlUtility.getDocumentBuilder()
							.newDocument();
					org.w3c.dom.Node spNode = shortestPathDoc.importNode(
							successNode, true);
					shortestPathDoc.appendChild(spNode);
					XmlUtility.transform(shortestPathDoc, new File(
							"shortestPath.xsl"), new File(saveHTMLName
									+ ".html"));
				}
			}
		}
	}

	private void saveShortestPathMap(final String mapName,
			final List<City> cityList) throws IOException {
		final CanvasPlus map = new CanvasPlus();
		/* initialize map */
		map.setFrameSize(spatialWidth, spatialHeight);
		/* add a rectangle to show where the bounds of the map are located */
		map.addRectangle(0, 0, spatialWidth, spatialHeight, Color.BLACK, false);

		final Iterator<City> it = cityList.iterator();
		City city1 = it.next();

		/* map green starting point */
		map.addPoint(city1.getName(), city1.getX(), city1.getY(), Color.GREEN);

		if (it.hasNext()) {
			City city2 = it.next();
			/* map blue road */
			map.addLine(city1.getX(), city1.getY(), city2.getX(), city2.getY(),
					Color.BLUE);

			while (it.hasNext()) {
				/* increment cities */
				city1 = city2;
				city2 = it.next();

				/* map point */
				map.addPoint(city1.getName(), city1.getX(), city1.getY(),
						Color.BLUE);

				/* map blue road */
				map.addLine(city1.getX(), city1.getY(), city2.getX(), city2
						.getY(), Color.BLUE);
			}

			/* map red end point */
			map
			.addPoint(city2.getName(), city2.getX(), city2.getY(),
					Color.RED);

		}

		/* save map to image file */
		map.save(mapName);

		map.dispose();
	}

	/**
	 * Processes a saveMap command. Saves the graphical map to a given file.
	 * 
	 * @param node
	 *            saveMap command to be processed
	 * @throws IOException
	 *             problem accessing the image file
	 */
	public void processSaveMap(final Element node) throws IOException {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");

		final String name = processStringAttribute(node, "name", parametersNode);

		final Element outputNode = results.createElement("output");

		CanvasPlus canvas = drawPMQuadtree();

		/* save canvas to '(name).png' */
		canvas.save(name);

		canvas.dispose();

		/* add success node to results */
		addSuccessNode(commandNode, parametersNode, outputNode);
	}

	private CanvasPlus drawPMQuadtree() {
		final CanvasPlus canvas = new CanvasPlus("MeeshQuest");

		/* initialize canvas */
		canvas.setFrameSize(spatialWidth, spatialHeight);

		/* add a rectangle to show where the bounds of the map are located */
		canvas.addRectangle(0, 0, spatialWidth, spatialHeight, Color.BLACK,
				false);

		/* draw PM Quadtree */
		drawPMQuadtreeHelper(pmQuadtree.getRoot(), canvas);

		return canvas;
	}

	private void drawPMQuadtreeHelper(Node node, CanvasPlus canvas) {
		/* I realize this is horribly inefficient; feel free to fix it */
		if (node.getType() == Node.BLACK) {
			Black blackNode = (Black) node;
			for (Road road : blackNode.getGeometry()) {
				if (road.isCity()) {
					City city = road.getStart();
					canvas.addPoint(city.getName(), city.getX(), city.getY(),
							Color.BLACK);
				} else {
					canvas.addLine(road.getStart().getX(), road.getStart()
							.getY(), road.getEnd().getX(),
							road.getEnd().getY(), Color.BLACK);
				}
			}
		} else if (node.getType() == Node.GRAY) {
			Gray grayNode = (Gray) node;
			canvas.addCross(grayNode.getCenterX(), grayNode.getCenterY(),
					grayNode.getHalfWidth(), Color.GRAY);
			for (int i = 0; i < 4; i++) {
				drawPMQuadtreeHelper(grayNode.getChild(i), canvas);
			}
		}
	}

	/**
	 * Prints out the structure of the PM Quadtree in an XML format.
	 * 
	 * @param node
	 *            printPMQuadtree command to be processed
	 */

	public void processPrintPMQuadtree(final Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		if (pmQuadtree.isEmpty()) {
			/* empty PR Quadtree */
			addErrorNode("mapIsEmpty", commandNode, parametersNode);
		} else {
			/* print PR Quadtree */
			final Element quadtreeNode = results.createElement("quadtree");
			quadtreeNode.setAttribute("order", Integer.toString(pmOrder));
			printPMQuadtreeHelper(pmQuadtree.getRoot(), quadtreeNode);

			outputNode.appendChild(quadtreeNode);

			/* add success node to results */
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}

	/**
	 * Traverses each node of the PR Quadtree.
	 * 
	 * @param currentNode
	 *            PR Quadtree node being printed
	 * @param xmlNode
	 *            XML node representing the current PR Quadtree node
	 */

	private void printPMQuadtreeHelper(final Node currentNode,
			final Element xmlNode) {
		if (currentNode.getType() == Node.WHITE) {
			Element white = results.createElement("white");
			xmlNode.appendChild(white);
		} else {
			if (currentNode.getType() == Node.BLACK) {
				Black currentLeaf = (Black) currentNode;
				Element blackNode = results.createElement("black");
				blackNode.setAttribute("cardinality", Integer
						.toString(currentLeaf.getGeometry().size()));
				for (Road g : currentLeaf.getGeometry()) {
					if (g.isCity()) {
						City c = (City) g.getStart();
						Element city = results.createElement(
								g.isIsolatedCity()? "isolatedCity" : "city");
						city.setAttribute("name", c.getName());
						city
						.setAttribute("x", Integer.toString((int) c
								.getX()));
						city
						.setAttribute("y", Integer.toString((int) c
								.getY()));
						city.setAttribute("radius", Integer.toString((int) c
								.getRadius()));
						city.setAttribute("color", c.getColor());
						blackNode.appendChild(city);
					} else {
						City c1 = (City) g.getStart();
						City c2 = (City) g.getEnd();
						Element road = results.createElement("road");
						road.setAttribute("start", c1.getName());
						road.setAttribute("end", c2.getName());
						blackNode.appendChild(road);
					}
				}

				xmlNode.appendChild(blackNode);

			} else {
				final Gray currentInternal = (Gray) currentNode;
				final Element gray = results.createElement("gray");
				gray.setAttribute("x", Integer.toString((int) currentInternal
						.getCenterX()));
				gray.setAttribute("y", Integer.toString((int) currentInternal
						.getCenterY()));
				for (int i = 0; i < 4; i++) {
					printPMQuadtreeHelper(currentInternal.getChild(i), gray);
				}
				xmlNode.appendChild(gray);
			}
		}
	}

	/**
	 * Finds the mapped cities within the range of a given point.
	 * 
	 * @param node
	 *            rangeCities command to be processed
	 * @throws IOException
	 */
	public void processRangeCities(final Element node) throws IOException {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		final TreeSet<City> citiesInRange = new TreeSet<City>(
				new CityNameComparator());

		/* extract values from command */
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);
		final int radius = processIntegerAttribute(node, "radius",
				parametersNode);

		String pathFile = "";
		if (!node.getAttribute("saveMap").equals("")) {
			pathFile = processStringAttribute(node, "saveMap", parametersNode);
		}

		if (radius == 0) {
			addErrorNode("noCitiesExistInRange", commandNode, parametersNode);
		} else {
			/* get cities within range */
			final Point2D.Double point = new Point2D.Double(x, y);
			rangeCitiesHelper(point, radius, pmQuadtree.getRoot(),
					citiesInRange);

			/* print out cities within range */
			if (citiesInRange.isEmpty()) {
				addErrorNode("noCitiesExistInRange", commandNode,
						parametersNode);
			} else {
				/* get city list */
				final Element cityListNode = results.createElement("cityList");
				for (City city : citiesInRange) {
					addCityNode(cityListNode, city);
				}
				outputNode.appendChild(cityListNode);

				/* add success node to results */
				addSuccessNode(commandNode, parametersNode, outputNode);

				if (pathFile.compareTo("") != 0) {
					/* save canvas to file with range circle */
					CanvasPlus canvas = drawPMQuadtree();
					canvas.addCircle(x, y, radius, Color.BLUE, false);
					canvas.save(pathFile);
					canvas.dispose();
				}
			}
		}
	}
	public void processRangeRoads(final Element node) throws IOException {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		final TreeSet<Road> roadsInRange = new TreeSet<Road>(new RoadNameComparator());

		/* extract values from command */
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);
		final int radius = processIntegerAttribute(node, "radius",
				parametersNode);

		String pathFile = "";
		if (!node.getAttribute("saveMap").equals("")) {
			pathFile = processStringAttribute(node, "saveMap", parametersNode);
		}

		if (radius == 0) {
			addErrorNode("noRoadsExistInRange", commandNode, parametersNode);
		}else {
			/* get Roads within range */
			final Point2D.Double point = new Point2D.Double(x, y);
			rangeRoadHelper2(point, radius, roadsInRange);

			/* print out cities within range */
			if (roadsInRange.isEmpty()) {
				addErrorNode("noRoadsExistInRange", commandNode,
						parametersNode);
			} else {
				/* get city list */
				final Element roadListNode = results.createElement("roadList");
				for (Road road: roadsInRange) {
					addRoadNode(roadListNode, road);
				}
				outputNode.appendChild(roadListNode);

				/* add success node to results */
				addSuccessNode(commandNode, parametersNode, outputNode);

				if (pathFile.compareTo("") != 0) {
					/* save canvas to file with range circle */
					CanvasPlus canvas = drawPMQuadtree();
					canvas.addCircle(x, y, radius, Color.BLUE, false);
					canvas.save(pathFile);
					canvas.dispose();
				}
			}
		}
	}

	/**
	 * Determines if any cities within the PM Quadtree not are within the radius
	 * of a given point.
	 * 
	 * @param point
	 *            point from which the cities are measured
	 * @param radius
	 *            radius from which the given points are measured
	 * @param node
	 *            PM Quadtree node being examined
	 * @param citiesInRange
	 *            a list of cities found to be in range
	 */
	private void rangeCitiesHelper(final Point2D.Double point,
			final int radius, final Node node, final TreeSet<City> citiesInRange) {
		if (node.getType() == Node.BLACK) {
			final Black leaf = (Black) node;
			if (leaf.containsCity()) {
				final double distance = point.distance(leaf.getCity()
						.toPoint2D());
				if (distance <= radius) {
					/* city is in range */
					final City city = leaf.getCity();
					citiesInRange.add(city);
				}
			}
		} else if (node.getType() == Node.GRAY) {
			/* check each quadrant of internal node */
			final Gray internal = (Gray) node;

			final Circle2D.Double circle = new Circle2D.Double(point, radius);
			for (int i = 0; i < 4; i++) {
				if (Inclusive2DIntersectionVerifier.intersects(internal
						.getChildRegion(i), circle)) {
					rangeCitiesHelper(point, radius, internal.getChild(i),
							citiesInRange);
				}
			}
		}
	}
	
	private void rangeRoadHelper2(final Point2D.Double point,
			final int radius, final TreeSet<Road> roadsInRange){
		TreeSet<Road> mappedRoads = pmQuadtree.getRoadsInPMQuadtree();
		for(Road r: mappedRoads){
			if(point.distance(r.getStart().toPoint2D()) <= radius){
				roadsInRange.add(r);
			}else if(point.distance(r.getEnd().toPoint2D()) <= radius){
				roadsInRange.add(r);
			}
		}
	}
	private void rangeRoadHelper(final Point2D.Double point,
			final int radius, final Node node, final TreeSet<Road> roadsInRange) {
		if (node.getType() == Node.BLACK) {
			final Black leaf = (Black) node;
			Iterator<Road> roadIter = node.getGeometry().iterator();
			while(roadIter.hasNext()){
				Road road = roadIter.next();
				City start = road.getStart();
				City end = road.getEnd();
				final double distance;
				if(start.getName().compareTo(end.getName()) == 0){
					distance = point.distance(start.toPoint2D());
					if(distance <= radius)
						roadsInRange.add(road);
				}else{
					final double d1, d2;
					d1 = point.distance(start.toPoint2D());
					d2 = point.distance(end.toPoint2D());
					if(d1 <= radius || d2 <= radius)
						roadsInRange.add(road);
				}
			}
		} else if (node.getType() == Node.GRAY) {
			/* check each quadrant of internal node */
			final Gray internal = (Gray) node;

			final Circle2D.Double circle = new Circle2D.Double(point, radius);
			for (int i = 0; i < 4; i++) {
				if (Inclusive2DIntersectionVerifier.intersects(internal
						.getChildRegion(i), circle)) {
					rangeRoadHelper(point, radius, internal.getChild(i),
							roadsInRange);
				}
			}
		}
	}


	public void processNameRange(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* extract attribute values from command */
		final String start = processStringAttribute(node, "start", parametersNode);
		final String end = processStringAttribute(node, "end", parametersNode);

		if(start.compareTo(end) >= 0){
			addErrorNode("startNotLessThanEnd", commandNode, parametersNode);
		}else{
			Iterator<String> cityIter = cities.keySet().iterator();
			TreeSet<String> citiesInRange = new TreeSet<String>();
			final Element cityListNode = results.createElement("cityList");
			while(cityIter.hasNext()){
				String city = cityIter.next();
				if(city.compareTo(start) >= 0 && city.compareTo(end) <= 0){
					citiesInRange.add(city);
				}
			}
			if(citiesInRange.isEmpty()){
				addErrorNode("noCitiesExistInRange", commandNode, parametersNode);
			}else{
				for(String city: citiesInRange){
					addCityNode(cityListNode, cities.get(city));
				}

				outputNode.appendChild(cityListNode);
				addSuccessNode(commandNode, parametersNode, outputNode);
			}

		}
	}

	public void processNearestRoad(Element node) {	
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* extract attribute values from command */
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);

		final Point2D.Float point = new Point2D.Float(x, y);
		if (pmQuadtree.getNumCities() - pmQuadtree.getNumIsolatedCities() == 0) {
			addErrorNode("roadNotFound", commandNode, parametersNode);
		}else{

			addRoadNode(outputNode, nearestRoadHelper(point));
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}


	/**
	 * Finds the nearest city to a given point.
	 * 
	 * @param node
	 *            nearestCity command being processed
	 */
	public void processNearestCity(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* extract attribute values from command */
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);

		final Point2D.Float point = new Point2D.Float(x, y);


		if (pmQuadtree.getNumCities() - pmQuadtree.getNumIsolatedCities() == 0) {
			addErrorNode("cityNotFound", commandNode, parametersNode);
		} else {
			addCityNode(outputNode, nearestCityHelper(point, false));
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}

	public void processNearestIsolatedCity(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* extract attribute values from command */
		final int x = processIntegerAttribute(node, "x", parametersNode);
		final int y = processIntegerAttribute(node, "y", parametersNode);

		final Point2D.Float point = new Point2D.Float(x, y);


		if (pmQuadtree.getNumIsolatedCities() == 0) {
			addErrorNode("cityNotFound", commandNode, parametersNode);
		} else {
			addIsolatedCityNode(outputNode, nearestCityHelper(point, true));
			addSuccessNode(commandNode, parametersNode, outputNode);
		}
	}


	public void processNearestCityToRoad(Element node) {
		final Element commandNode = getCommandNode(node);
		final Element parametersNode = results.createElement("parameters");
		final Element outputNode = results.createElement("output");

		/* extract attribute values from command */
		final String start = processStringAttribute(node, "start", parametersNode);
		final String end = processStringAttribute(node, "end", parametersNode);

		Set<City> citySet = roads.getCitySet();
		Set<Road> roadSet = null;
		for(City c: citySet){
			if(c.getName().equals(start)){
				roadSet = roads.getRoadSet(c);
				break;
			}
		}
		if(roadSet == null){
			addErrorNode("roadIsNotMapped", commandNode, parametersNode);
		}else{
			Road road = null;
			for(Road r: roadSet){
				if(r.getOtherCity(start).getName().equals(end)){
					road = r;
					break;
				}
			}
			if(road == null){
				addErrorNode("roadIsNotMapped", commandNode, parametersNode);
			}else{
				if(roads.getNumberOfCities() <=2){
					addErrorNode("noOtherCitiesMapped", commandNode, parametersNode);
				}
				else{
					addCityNode(outputNode, nearestCityToRoadHelper(road));
					addSuccessNode(commandNode, parametersNode, outputNode);
				}
				
				
			}
		}

	}

	private City nearestCityToRoadHelper(Road road) {
		City shortest= null;
		double distance = 0;
		for(String name: pmQuadtree.getCities()){
			City c = cities.get(name);
			if(!road.contains(c)){
				if(shortest == null){
					shortest = c;
					distance = road.toLine2D().ptSegDist(c.toPoint2D());
				}else{
					if(road.toLine2D().ptSegDist(c.toPoint2D()) < distance){
						shortest = c;
						distance = road.toLine2D().ptSegDist(c.toPoint2D());
					}else if(road.toLine2D().ptSegDist(c.toPoint2D()) == distance){
						if(c.getName().compareTo(shortest.getName())<0)
							shortest = c;						
					}
				}
			}
			
		}
		return shortest;
	}

	private Road nearestRoadHelper(Float point) {
		TreeSet<Road> mappedRoads = pmQuadtree.getRoadsInPMQuadtree();
		Road shortest= null;
		String shortestStart = "", shortestEnd = "";
		double distance = 0;
		for(Road road: mappedRoads){
			if(shortest == null ){
				distance = road.toLine2D().ptSegDist(point);
				shortest = road;
				if(road.getStart().getName().compareTo(road.getEnd().getName())<0){
					shortestStart = road.getStart().getName();
					shortestEnd = road.getEnd().getName();
				}else{
					shortestStart = road.getEnd().getName();
					shortestEnd = road.getStart().getName();
				}
			}else{
				if(road.toLine2D().ptSegDist(point) < distance){
					if(road.getStart().getName().compareTo(road.getEnd().getName())<0){
						shortestStart = road.getStart().getName();
						shortestEnd = road.getEnd().getName();
					}else{
						shortestStart = road.getEnd().getName();
						shortestEnd = road.getStart().getName();
					}

					distance = road.toLine2D().ptSegDist(point);
					shortest = road;
				}if(road.toLine2D().ptSegDist(point) == distance){
					String roadStart, roadEnd;
					if(road.getStart().getName().compareTo(road.getEnd().getName())<0){
						roadStart = road.getStart().getName();
						roadEnd = road.getEnd().getName();
					}else{
						roadStart = road.getEnd().getName();
						roadEnd = road.getStart().getName();
					}
					if(roadStart.compareTo(shortestStart)<0){
						shortest = road;
						shortestStart = roadStart;
						shortestEnd = roadEnd;
					}else if(roadStart.compareTo(shortestStart) == 0){
						if(roadEnd.compareTo(shortestEnd)<0){
							shortest = road;
							shortestEnd = roadEnd;
						}
					}

				}
			}

		}


		return shortest;
	}
	/**
	 * 3/3/10
	 */
	private City nearestCityHelper(Point2D.Float point, boolean isNearestIsolatedCity) {
		Node n = pmQuadtree.getRoot();
		PriorityQueue<NearestRegion> nearCities = new PriorityQueue<NearestRegion>();   

		if (n.getType() == Node.BLACK) {
			Black b = (Black) n;
			if (b.getCity() != null && b.isIsolated() == isNearestIsolatedCity) {
				return b.getCity();
			}
		}

		while (n.getType() == Node.GRAY) {
			Gray g = (Gray) n;
			Node kid;
			double dist = Double.MAX_VALUE;

			for (int i = 0; i < 4; i++) {
				kid = g.getChild(i);
				if (kid.getType() == Node.WHITE) {
					continue;
				}
				if (kid.getType() == Node.BLACK && (
						((Black) kid).getCity() == null
						|| ((Black) kid).isIsolated() != isNearestIsolatedCity
						)) {
					continue;
				}
				if (kid.getType() == Node.GRAY) {
					dist = Shape2DDistanceCalculator.distance(point, g.getChildRegion(i));
				} else if (kid.getType() == Node.BLACK){
					dist = point.distance(((Black) kid).getCity().toPoint2D());
				}
				nearCities.add(new NearestRegion(kid, dist));
			}
			try {
				n = nearCities.remove().node;
			} catch (Exception ex) {
				System.err.println(nearCities.size());
				throw new IllegalStateException();
			}
		}
		return ((Black) n).getCity();
	}


	private class NearestRegion implements Comparable<NearestRegion> {

		private Node node;
		private double distance;

		public NearestRegion(Node node, double distance) {
			this.node = node;
			this.distance = distance;
		}

		public int compareTo(NearestRegion o) {
			if (distance == o.distance) {
				if (node.getType() == Node.BLACK && o.node.getType() == Node.BLACK) {
					Black b1 = (Black) node;
					Black b2 = (Black) o.node;
					return b1.getCity().getName().compareTo(b2.getCity().getName());
				} else if (node.getType() == Node.BLACK && o.node.getType() == Node.GRAY) {
					return 1;
				} else if (node.getType() == Node.GRAY && o.node.getType() == Node.BLACK) {
					return -1;
				} else {
					Gray g1 = (Gray) node;
					Gray g2 = (Gray) o.node;
					return g2.hashCode() - g1.hashCode();
				}
			}
			return (distance < o.distance) ? -1 : 1; 
		}

	}




}
