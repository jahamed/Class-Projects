package cmsc420.meeshquest.part1;

/*This class came from code from my README reference*/

public class PRKeyNode extends PRNode {

	public City key;
	
	public PRKeyNode(City tempkey){
		key = tempkey;
	}
	
	public boolean isLeaf() {
		return true;
	}
	
}
