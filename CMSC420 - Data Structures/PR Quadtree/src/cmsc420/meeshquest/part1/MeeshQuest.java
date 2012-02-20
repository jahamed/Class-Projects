package cmsc420.meeshquest.part1;

import java.awt.Color;
import java.awt.geom.Point2D;
import java.io.*;
import java.util.Collection;
import java.util.Iterator;
import java.util.TreeMap;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import org.w3c.dom.*;
import org.xml.sax.SAXException;
import cmsc420.drawing.CanvasPlus;
import cmsc420.xml.XmlUtility;

public class MeeshQuest {

	public static void main(String[] args) {

		//maximum width/height of the canvas
		int spatialWidth = 1024;
		int spatialHeight = 1024;

		TreeMap<String, City> nameToCityMap = new TreeMap<String, City>(new CityNameComparator());
		TreeMap<Point2D.Float, City> coordToCityMap = new TreeMap<Point2D.Float, City>(new CityCoordComparator());
		CanvasPlus canvas = new CanvasPlus("MeeshQuest", spatialWidth, spatialHeight);
		PRQuadTree prQuadTree = new PRQuadTree(spatialWidth, spatialHeight, canvas);

		//add the rectangle outline to the canvas drawing
		canvas.addRectangle(0, 0, spatialWidth, spatialHeight, Color.BLACK, false);

		//create the xml document that we will be outputting to
		Document results = null;
		try {
			results = XmlUtility.getDocumentBuilder().newDocument();
		} catch (ParserConfigurationException e1) {
			e1.printStackTrace();
		}
		
		//append the main tag to the xml document
		Element rootElement = results.createElement("results");
		results.appendChild(rootElement);

		//get input xml
		Document doc = null;
		try {
			//doc = XmlUtility.validateNoNamespace(System.in);
			doc = XmlUtility.validateNoNamespace(new File("part1.rangeCitiesAndSaveMap.input.xml"));
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		}
		Element docElement = doc.getDocumentElement();
		NodeList nl = docElement.getChildNodes();
		for(int i = 0; i < nl.getLength(); ++i) {
			Node commands = nl.item(i); 
			if (commands instanceof Element){ 

				//this is the "command" extracted from the xml with set attributes
				Element commandsElement = (Element) commands;

				if(commands.getNodeName().equals("createCity")){
					City cityToInsert = new City(commandsElement.getAttribute("name"), 
							commandsElement.getAttribute("color"), Integer.parseInt(commandsElement.getAttribute("x")), 
							Integer.parseInt(commandsElement.getAttribute("y")),
							Integer.parseInt(commandsElement.getAttribute("radius")));

					if(nameToCityMap.containsKey(cityToInsert.getName())){
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "duplicateCityName");
						command.setAttribute("name", "createCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);
					}else if(coordToCityMap.containsKey(new Point2D.Float((float) cityToInsert.getX(), (float) cityToInsert.getY()))){
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "duplicateCityCoordinates");
						command.setAttribute("name", "createCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);
					}else{
						nameToCityMap.put(commandsElement.getAttribute("name"), cityToInsert);
						coordToCityMap.put(new Point2D.Float(Integer.parseInt(commandsElement.getAttribute("x")), 
								Integer.parseInt(commandsElement.getAttribute("y"))), 
								cityToInsert);

						Element success = results.createElement("success");
						Element command = results.createElement("command");
						Element parameters = results.createElement("parameters");
						Element name = results.createElement("name");
						Element x = results.createElement("x");
						Element y = results.createElement("y");
						Element radius = results.createElement("radius");
						Element color = results.createElement("color");
						Element output = results.createElement("output");

						command.setAttribute("name", "createCity");
						name.setAttribute("value", cityToInsert.getName());
						x.setAttribute("value", String.valueOf((int) cityToInsert.getX()));
						y.setAttribute("value", String.valueOf((int) cityToInsert.getY()));
						radius.setAttribute("value", String.valueOf(cityToInsert.getRadius()));
						color.setAttribute("value", String.valueOf(cityToInsert.getColor()));

						rootElement.appendChild(success);
						success.appendChild(command);
						success.appendChild(parameters);
						parameters.appendChild(name);
						parameters.appendChild(x);
						parameters.appendChild(y);
						parameters.appendChild(radius);
						parameters.appendChild(color);
						success.appendChild(output);
					}
				}
				
				else if(commands.getNodeName().equals("deleteCity")){
					
					City tempcity = nameToCityMap.get(commandsElement.getAttribute("name"));
					if(nameToCityMap.containsKey(commandsElement.getAttribute("name"))){
						prQuadTree.delete(nameToCityMap.get(commandsElement.getAttribute("name")));
						nameToCityMap.remove(commandsElement.getAttribute("name"));
						coordToCityMap.remove(new Point2D.Float((float) tempcity.getX(), (float) tempcity.getY()));

						Element success = results.createElement("success");
						Element command = results.createElement("command");
						Element parameters = results.createElement("parameters");
						Element name = results.createElement("name");
						Element output = results.createElement("output");

						command.setAttribute("name", "deleteCity");
						name.setAttribute("value", commandsElement.getAttribute("name"));

						rootElement.appendChild(success);
						success.appendChild(command);
						success.appendChild(parameters);
						parameters.appendChild(name);
						success.appendChild(output);
					}else{ //the city does not exist to delete in the first place
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "cityDoesNotExist");
						command.setAttribute("name", "deleteCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);
					}
				}
				
				else if(commands.getNodeName().equals("clearAll")){
					nameToCityMap = new TreeMap<String, City>(new CityNameComparator());
					coordToCityMap = new TreeMap<Point2D.Float, City>(new CityCoordComparator());
					prQuadTree = new PRQuadTree(spatialWidth, spatialHeight, canvas);

					Element success = results.createElement("success");
					Element command = results.createElement("command");
					Element parameters = results.createElement("parameters");
					Element output = results.createElement("output");

					command.setAttribute("name", "clearAll");

					rootElement.appendChild(success);
					success.appendChild(command);
					success.appendChild(parameters);
					success.appendChild(output);

				}
				
				else if(commands.getNodeName().equals("listCities")){
					if(nameToCityMap.size() == 0){ //no cities in dictionary : error condition
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "noCitiesToList");
						command.setAttribute("name", "listCities");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);
					}else{
						Element success = results.createElement("success");
						Element command = results.createElement("command");
						Element parameters = results.createElement("parameters");
						Element sortBy = results.createElement("sortBy");
						Element output = results.createElement("output");
						Element cityList = results.createElement("cityList");
						Element city = results.createElement("city");

						if(commandsElement.getAttribute("sortBy").equals("name")){
							Collection<City> c = nameToCityMap.values();
							Iterator<City> itr = c.iterator();

							command.setAttribute("name", "listCities");
							sortBy.setAttribute("value", commandsElement.getAttribute("sortBy"));

							while(itr.hasNext()){
								City itrTemp = itr.next();
								city.setAttribute("name", itrTemp.getName());
								city.setAttribute("x", String.valueOf((int) itrTemp.getX()));
								city.setAttribute("y", String.valueOf((int) itrTemp.getY()));
								city.setAttribute("radius", String.valueOf(itrTemp.getRadius()));
								city.setAttribute("color", itrTemp.getColor());

								cityList.appendChild(city);
								city = results.createElement("city");
							}
						}else{ //sortBy equals coordinate
							Collection<City> c = coordToCityMap.values();
							Iterator<City> itr = c.iterator();

							command.setAttribute("name", "listCities");
							sortBy.setAttribute("value", commandsElement.getAttribute("sortBy"));

							while(itr.hasNext()){
								City itrTemp = itr.next();
								city.setAttribute("name", itrTemp.getName());
								city.setAttribute("x", String.valueOf((int) itrTemp.getX()));
								city.setAttribute("y", String.valueOf((int) itrTemp.getY()));
								city.setAttribute("radius", String.valueOf(itrTemp.getRadius()));
								city.setAttribute("color", itrTemp.getColor());

								cityList.appendChild(city);
								city = results.createElement("city");
							}
						}


						rootElement.appendChild(success);
						success.appendChild(command);
						success.appendChild(parameters);
						parameters.appendChild(sortBy);
						success.appendChild(output);
						output.appendChild(cityList);
					}

				}
				
				else if(commands.getNodeName().equals("mapCity")){
					City tempCity = nameToCityMap.get(commandsElement.getAttribute("name"));
					if(!(nameToCityMap.containsKey(commandsElement.getAttribute("name")))){
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "nameNotInDictionary");
						command.setAttribute("name", "mapCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);	
					}
					else if(prQuadTree.find(nameToCityMap.get(commandsElement.getAttribute("name"))) != null){
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "cityAlreadyMapped");
						command.setAttribute("name", "mapCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);	
					}else if(tempCity.getX()<0 || tempCity.getX()>spatialWidth || tempCity.getY()<0 || tempCity.getY()>spatialHeight){
						Element error = results.createElement("error");
						Element parameters = results.createElement("parameters");
						Element command = results.createElement("command");

						error.setAttribute("type", "cityOutOfBounds");
						command.setAttribute("name", "mapCity");

						rootElement.appendChild(error);
						error.appendChild(command);
						error.appendChild(parameters);	
					}else{
						City cityToInsert = nameToCityMap.get(commandsElement.getAttribute("name"));
						prQuadTree.insert(cityToInsert);
						
						Element success = results.createElement("success");
						Element command = results.createElement("command");
						Element parameters = results.createElement("parameters");
						Element name = results.createElement("name");
						Element output = results.createElement("output");
						
						command.setAttribute("name", "mapCity");
						name.setAttribute("value", cityToInsert.getName());
						
						rootElement.appendChild(success);
						success.appendChild(command);
						success.appendChild(parameters);
						parameters.appendChild(name);
						success.appendChild(output);
					}
				}
				
				else if(commands.getNodeName().equals("unmapCity")){

				}
				
				else if(commands.getNodeName().equals("printPRQuadtree")){

				}
				
				else if(commands.getNodeName().equals("saveMap")){

				}
				
				else if(commands.getNodeName().equals("rangeCities")){

				}
				
				else if(commands.getNodeName().equals("nearestCity")){

				}
			}
		}

		//canvas.draw();
		//print the output xml out
		try {
			XmlUtility.print(results);
		} catch (TransformerException e) {
			e.printStackTrace();
		}

	}

}


