package editing;
import photo.Photograph;
import photo.Pixel;

/**
 * This class will be written by the Student.  It provides various
 * static methods that take a photograph and produce a copy of it with
 * various modifications.
 * 
 * See the project description for details of method implementations.
 * 
 * @author CMSC 131 Student
 *
 */
public class PhotoTools {

	//This Method returns a new Photograph that is an exact copy of the parameter.
	public static Photograph copy(Photograph photo) {
		Photograph theCopy = new Photograph(photo.getWidth(), photo.getHeight());
		for (int row=0; row<photo.getHeight(); row++){
			for (int col=0; col<photo.getWidth(); col++){
				theCopy.setPixel(col, row, photo.getPixel(col, row));
			}
		}
		return theCopy;
	}

	/*This Method returns a new Photograph that is a black and white copy of the
	parameter.*/
	public static Photograph makeBlackAndWhite(Photograph photo) {
		Photograph theCopy = new Photograph(photo.getWidth(), photo.getHeight());
		int blackAndWhiteVal=0;
		for (int row=0; row<photo.getHeight(); row++){
			for (int col=0; col<photo.getWidth(); col++){
				blackAndWhiteVal=(photo.getPixel(col, row).getBlue()
						+photo.getPixel(col, row).getGreen()
						+photo.getPixel(col, row).getRed())/3;
				theCopy.setPixel(col, row, new Pixel(blackAndWhiteVal, 
						blackAndWhiteVal, blackAndWhiteVal));
			}
		}
		return theCopy;
	}

	/*This method will return a new Photograph where the first 10 columns look 
	 like the original; the next 10 columns are all black, etc.*/
	public static Photograph striped(Photograph photo) {
		Photograph theCopy = new Photograph(photo.getWidth(), photo.getHeight());
		for (int row=0; row<photo.getHeight(); row++){
			for (int col=0; col<photo.getWidth(); col++){
				if ((col/10)%2==0){ //Set Pixel to normal colors
					theCopy.setPixel(col, row, photo.getPixel(col, row));
				}else{ //Set Pixel to black
					theCopy.setPixel(col, row, new Pixel(0, 0, 0));
				}
			}
		}
		return theCopy;
	}

	/*This method will return a new Photograph that is a copy of the parameter, 
	 but with only  one of the three primary colors visible. Type 0 for red; 
	 1 for green; 2 for blue*/
	public static Photograph isolateColor(Photograph photo, int type) {
		Photograph theCopy = new Photograph(photo.getWidth(), photo.getHeight());
		for (int row=0; row<photo.getHeight(); row++){
			for (int col=0; col<photo.getWidth(); col++){
				if (type==0){ //Red
					theCopy.setPixel(col, row, 
							new Pixel(photo.getPixel(col, row).getRed(), 0, 0));
				}else if (type==1){ //Green
					theCopy.setPixel(col, row, 
							new Pixel(0, photo.getPixel(col, row).getGreen(), 0));
				}else if (type==2){ //Blue
					theCopy.setPixel(col, row, 
							new Pixel(0, 0, photo.getPixel(col, row).getBlue()));
				}
			}
		}
		return theCopy;
	}

	/*This method will return a new Photograph that is either twice as wide 
	 or twice as high as the original.  The parameter type will be either:  
	0 for a horizontal stretch, or 1 for a vertical stretch.*/
	public static Photograph stretched(Photograph photo, int type) {
		Photograph theCopy = null;
		if (type==1){ //Vertical Stretch
			theCopy = new Photograph(photo.getWidth(),photo.getHeight()*2);
			for (int col=0;col<photo.getWidth();col++){
				for (int row=0; row<photo.getHeight();row++){
					theCopy.setPixel(col, row*2, photo.getPixel(col, row));
					theCopy.setPixel(col, row*2+1, photo.getPixel(col, row));
				}
			}
		}else{ //Horizontal Stretch
			theCopy = new Photograph(photo.getWidth()*2, photo.getHeight());
			for (int row=0; row<photo.getHeight();row++){
				for (int col=0; col<photo.getWidth(); col++){
					theCopy.setPixel(col*2, row, photo.getPixel(col, row));
					theCopy.setPixel(col*2+1, row, photo.getPixel(col,row));
				}
			}
		}
		return theCopy;
	}

	/*This method returns a Photograph that is both twice as wide and high as
	the original*/
	public static Photograph enlargement(Photograph photo) {
		//Horizontal Stretching a Vertical Stretch
		return stretched((stretched(photo, 1)), 0); 
	}

	/*
	 * This method will return a new Photograph that is the same as the original, 
	 * but turned 90 degrees clockwise.  
	 */
	public static Photograph rotated(Photograph photo) {
		Photograph theCopy = new Photograph(photo.getHeight(), photo.getWidth());
		for (int row=0; row<photo.getWidth(); row++){
			for (int col=0; col<photo.getHeight(); col++){
				theCopy.setPixel(photo.getHeight()-col-1, row, photo.getPixel(row, col));
			}
		}
		return theCopy;
	}

	/*
	 * This method will return a new Photograph that is the same as the original, 
	 * but turned 180 degrees clockwise.  
	 */
	public static Photograph upsideDown(Photograph photo) {
		//Calls the rotated method two times to make a 90degree*2=180degree rotation
		return rotated(rotated(photo));
	}

	/*
	 * The new photo will consist of an upside-down copy of the original photo 
	 * positioned side-by-side with a copy of the photo rotated 90 degrees 
	 * clockwise.  The height of the new photo will be equal to either the height
	 * or the width of the original (whichever is larger).  The width of the new
	 * photo will be equal to the sum of the height and width of the original. 
	 * All pixels in the new photo that do not fall within either of the 
	 * original pictures must be set to black.
	 */
	public static Photograph weirdCombo(Photograph photo) {

		Photograph theCopy;

		/*Makes two different theCopy objects depending on whether the width or
		the height of the photo is bigger*/
		boolean heightGreaterThanWidth=false; //For deciding which loop to run.

		if (photo.getHeight()>photo.getWidth()){
			theCopy = new Photograph(photo.getWidth()+
					photo.getHeight(), photo.getHeight());
			heightGreaterThanWidth=true;
		}else{
			theCopy = new Photograph(photo.getWidth()+
					photo.getHeight(), photo.getWidth());
		}

		//Sets the Initial Background of the Picture to Black
		for (int row=0; row<theCopy.getHeight(); row++){
			for (int col=0; col<theCopy.getWidth(); col++){
				theCopy.setPixel(col, row, new Pixel(0, 0, 0));
			}
		}

		Photograph upsideDown = upsideDown(photo), rotated = rotated(photo);

		//If The pictures Height is > its Width
		if(heightGreaterThanWidth==true){
			for (int row=0; row<theCopy.getHeight(); row++){
				for (int col=0; col<photo.getHeight(); col++){
					if (col<upsideDown.getWidth()){
						theCopy.setPixel(col, row, upsideDown.getPixel(col, row));
					}
					if (row<rotated.getHeight()){
						theCopy.setPixel(col+rotated.getHeight(), row, 
								rotated.getPixel(col, row));
					}
				}
			}
		}else{ //If the pictures Width is > its Height
			for (int row=0; row<theCopy.getHeight(); row++){
				for (int col=0; col<photo.getWidth(); col++){

					if (row<upsideDown.getHeight()){
						theCopy.setPixel(col, row, upsideDown.getPixel(col, row));
					}
					if (col<rotated.getWidth()){
						theCopy.setPixel(col+rotated.getHeight(), row, 
								rotated.getPixel(col, row));
					}
				}
			}
		}
		return theCopy;
	}
}
