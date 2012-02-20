package cmsc420.meeshquest.part1;

/*This class came from code from my README reference*/

public class PRGuideNode extends PRNode{

	public int xcoord;
	public int ycoord;
	
	public PRNode[] children;
	
	public PRGuideNode(int x, int y){
		xcoord = x;
		ycoord = y;
		children = null;
		children = new PRNode[4];
		
		//set all children to empty nodes to begin with
		for(int i = 0; i<4; i++){
			children[i] = null;
		}
	}
	
	public boolean isLeaf(){
		return false;
	}
	
	public boolean equals(PRGuideNode t){
		return (t.xcoord == xcoord & t.ycoord == ycoord);
	}
}
