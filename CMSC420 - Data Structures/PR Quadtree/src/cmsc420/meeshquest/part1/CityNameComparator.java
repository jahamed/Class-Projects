package cmsc420.meeshquest.part1;

import java.util.Comparator;


public class CityNameComparator implements Comparator<String>{

	public int compare(String cityName1, String cityName2) {
		if(cityName1.compareTo(cityName2) < 0){
			return -1;
		}else if(cityName1.compareTo(cityName2) > 0){
			return 1;
		}else{
			return 0;
		}
	}
}
