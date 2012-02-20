package cmsc420.meeshquest.part1;

import java.awt.geom.*;

public class City extends Point2D.Float{
	

	private String name;
	private String color;
	private int radius;

	public City(String name, String color, int x, int y, int radius){
		this.name = name;
		this.color = color;
		this.radius = radius;
		super.x = x;
		super.y = y;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public int getRadius() {
		return radius;
	}

	public void setRadius(int radius) {
		this.radius = radius;
	}
	
}
