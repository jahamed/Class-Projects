package cmsc420.meeshquest.part1;

import java.awt.Color;
import java.awt.geom.Point2D;
import java.lang.Math;
import java.util.ArrayList;
import cmsc420.drawing.CanvasPlus;

/*This class came from code from my README reference*/

public class PRQuadTree {

	int horbound = 1024;
	int verbound = 1024;
	private PRNode root = null;
	CanvasPlus canvas = null;

	public PRQuadTree(int x, int y, CanvasPlus canvas){
		horbound = x;
		verbound = x;
		root = null;
		this.canvas = canvas;
	}

	static public int getKeyX(City key){
		return (int) key.getX();
	}

	static public int getKeyY(City key){
		return (int) key.getY();
	}

	public City insert(City x){
		return insert(x, root, 0);
	}

	private City insert(City x, PRNode t, int level){
		if(t == null){ //no elements in tree yet
			root = new PRKeyNode(x);
			canvas.addPoint(x.getName(), x.getX(), x.getY(), Color.BLACK);
		}else if(t.isLeaf()){
			PRGuideNode newguide = new PRGuideNode(horbound/2, verbound/2);
			canvas.addLine(horbound/2, 0, horbound/2, verbound, Color.BLACK);
			canvas.addLine(0, verbound/2, horbound, verbound/2, Color.BLACK);
			PRKeyNode oldnode = (PRKeyNode) t;
			root = newguide;
			insert(oldnode.key, root, 0);
			return insert(x, root, 0);
		}else{
			PRGuideNode myguide = (PRGuideNode) t;
			int xsplit = (new Double(horbound/Math.pow(2, level+2))).intValue();
			int ysplit = (new Double(verbound/Math.pow(2, level+2))).intValue();
			int newxcoord = 0;
			int newycoord = 0;

			int mychild = 0;
			if(getKeyX(x) >= myguide.xcoord){ //2nd or 4th Quadrant
				if(getKeyY(x) >= myguide.ycoord){ //2nd Quadrant
					mychild = 1;
					newxcoord = myguide.xcoord + xsplit;
					newycoord = myguide.ycoord + ysplit;
					if(myguide.children[mychild] != null && myguide.children[mychild].isLeaf()){
						canvas.addLine(newxcoord, newycoord-ysplit, newxcoord, newycoord+ysplit, Color.BLACK);
						canvas.addLine(newxcoord-xsplit, newycoord, newxcoord+xsplit, newycoord, Color.BLACK);
					}

				}else{ //4th Quadrant
					mychild = 3;
					newxcoord = myguide.xcoord + xsplit;
					newycoord = myguide.ycoord - ysplit;
					if(myguide.children[mychild] != null && myguide.children[mychild].isLeaf()){
						canvas.addLine(newxcoord, newycoord-ysplit, newxcoord, myguide.ycoord, Color.BLACK);
						canvas.addLine(newxcoord-xsplit, newycoord, newxcoord+xsplit, newycoord, Color.BLACK);
					}
				}
			}else{ //1st or 3rd Quadrant
				if(getKeyY(x) >= myguide.ycoord){ //1st Quadrant
					mychild = 0;
					newxcoord = myguide.xcoord - xsplit;
					newycoord = myguide.ycoord + ysplit;
					if(myguide.children[mychild] != null && myguide.children[mychild].isLeaf()){
						canvas.addLine(newxcoord, newycoord-ysplit, newxcoord, myguide.ycoord*2, Color.BLACK);
						canvas.addLine(newxcoord-xsplit, newycoord, myguide.xcoord, newycoord, Color.BLACK);
					}

				}else{ //3rd Quadrant
					mychild = 2;
					newxcoord = myguide.xcoord - xsplit;
					newycoord = myguide.ycoord - ysplit;
					if(myguide.children[mychild] != null && myguide.children[mychild].isLeaf()){
						canvas.addLine(newxcoord, newycoord-ysplit, newxcoord, myguide.ycoord, Color.BLACK);
						canvas.addLine(0, ysplit, xsplit*2, ysplit, Color.BLACK);
					}
				}
			}

			if(myguide.children[mychild] == null){
				myguide.children[mychild] = new PRKeyNode(x);
				canvas.addPoint(x.getName(), x.getX(), x.getY(), Color.BLACK);

			}else{
				if(myguide.children[mychild].isLeaf()){
					PRKeyNode mytempkey = (PRKeyNode) myguide.children[mychild];
					myguide.children[mychild] = new PRGuideNode(newxcoord, newycoord);

					insert(mytempkey.key, myguide.children[mychild], level+1);
					return insert(x, myguide.children[mychild], level+1);
				}else{
					return insert(x, myguide.children[mychild], level+1);
				}
			}
		}
		return null;
	}

	static public boolean isCoordEqual(City key1, City key2)
	{
		boolean xEqual = false;
		boolean yEqual = false;
		
		if(key1.getX() == key2.getX()){
			xEqual = true;
		}
		if(key1.getY() == key2.getY()){
			yEqual = true;
		}
		
		return xEqual && yEqual;
	}

	public void delete(City x){
		delete(x, root);
	}

	//delete basically works by finding the node and then setting it to null
	private void delete(City x, PRNode t){

		if(t == null){
			//do nothing, the city cannot be in an empty tree
		}else if(t.isLeaf()){
			PRKeyNode mykey = (PRKeyNode) t;
			if(isCoordEqual(x, mykey.key)){
				canvas.removePoint(x.getName(), x.getX(), x.getY(), Color.BLACK);
				t = null;
			}
		}else{ //t is a guide node
			PRGuideNode myguide = (PRGuideNode) t;
		       if(getKeyX(x)>=myguide.xcoord)  //belong to the 2nd and 4th quardrant
		       {
		         if(getKeyY(x)>=myguide.ycoord)  //belongs in the 2nd quardrant
		         {delete(x, myguide.children[1]);}
		         else   //belongs in the 4th
		         {delete(x, myguide.children[3]);}
		       }

		       else  //belong in the 1st and 3rd quardrant
		       {
		         if(getKeyY(x)>=myguide.ycoord)  //belongs in 1st
		         {delete(x, myguide.children[0]);}
		         else   //belongs in the 3rd
		         {delete(x, myguide.children[2]);}
		       }
		}
	}

	public ArrayList<City> rangeCities(int x, int y, int radius){
		ArrayList<City> cityRangeList = new ArrayList<City>();

		if(this.isEmpty()){
			//no elements in PRQuadTree do nothing
		}else{
			this.rangeCities(x, y, radius, cityRangeList, root);
		}
		return cityRangeList;
	}

	public void rangeCities(int x, int y, int radius, ArrayList<City> cityRangeList, PRNode t){
		if (t == null){
			return;
		}else if(t.isLeaf()){
			PRKeyNode tempnode = (PRKeyNode) t;
			if(Point2D.distance(getKeyX(tempnode.key), getKeyY(tempnode.key), x, y) <= radius){
				cityRangeList.add(tempnode.key);
			}
		}else{ //Guide Node
			PRGuideNode myguide = (PRGuideNode) t;
			boolean nwquad = (x < myguide.xcoord) && (y >= myguide.ycoord);
			boolean nequad = (x >= myguide.xcoord) && (y >= myguide.ycoord);
			boolean swquad = (x < myguide.xcoord) && (y < myguide.xcoord);
			boolean sequad = (x >= myguide.xcoord) && (y < myguide.ycoord);

			if(nwquad){ this.rangeCities(x, y, radius, cityRangeList, myguide.children[0]); }
			if(nequad){ this.rangeCities(x, y, radius, cityRangeList, myguide.children[1]); }
			if(swquad){ this.rangeCities(x, y, radius, cityRangeList, myguide.children[2]); }
			if(sequad){ this.rangeCities(x, y, radius, cityRangeList, myguide.children[3]); }

		}
	}

	public City find(City x){
		return find(x, root);
	}
	
	private City find(City x, PRNode t){
		if(t == null){
			return null;
		}else if(t.isLeaf()){
			PRKeyNode mykey = (PRKeyNode) t;
			if(isCoordEqual(x, mykey.key)){
				return mykey.key;
			}else{
				return null;
			}
		}else{
			 PRGuideNode myguide=((PRGuideNode)t);
		       //find out which child node to follow
		       if(getKeyX(x)>=myguide.xcoord)  //belong to the 2nd and 4th quardrant
		       {
		         if(getKeyY(x)>=myguide.ycoord)  //belongs in the 2nd quardrant
		         {return find(x, myguide.children[1]);}
		         else   //belongs in the 4th
		         {return find(x, myguide.children[3]);}
		       }

		       else  //belong in the 1st and 3rd quardrant
		       {
		         if(getKeyY(x)>=myguide.ycoord)  //belongs in 1st
		         {return find(x, myguide.children[0]);}
		         else   //belongs in the 3rd
		         {return find(x, myguide.children[2]);}
		       }

		}
	}
	
	public boolean isEmpty(){
		return root == null;
	}
}
