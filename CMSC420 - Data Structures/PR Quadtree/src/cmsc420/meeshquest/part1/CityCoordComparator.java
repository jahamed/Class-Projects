package cmsc420.meeshquest.part1;

import java.awt.geom.Point2D;
import java.util.Comparator;


public class CityCoordComparator implements Comparator<Point2D.Float>{

	/*compare 2 point2Dfloats based on x and y coordinates, if x coordinates
	 * are equal then whichever one has the lowest y coordinate is less.
	 */
	public int compare(Point2D.Float point1, Point2D.Float point2) {
		if(point1.getX() > point2.getX()){
			return 1;
		}else if(point1.getX() < point2.getX()){
			return -1;
		}else{
			if(point1.getY() > point2.getY()){
				return 1;
			}else if(point1.getY() < point2.getY()){
				return -1;
			}else{
				return 0;
			}
		}
	}

}
