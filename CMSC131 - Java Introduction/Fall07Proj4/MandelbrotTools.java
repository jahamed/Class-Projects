import java.awt.Color;

public class MandelbrotTools {
	
	/*  STUDENTS:  Put your "isBig" and "divergence" methods here. */
	
	//This method computes a^2+b^2 and compares it to the DIVERGENCE_BOUNDRY.
	public static boolean isBig(ComplexNumber numberIn){
		MyDouble aSquared=(numberIn.getReal()).multiply(numberIn.getReal());
		MyDouble bSquared=(numberIn.getImag()).multiply(numberIn.getImag());
		
		if((aSquared.add(bSquared)).compareTo(Controller.DIVERGENCE_BOUNDARY)>0){
			return true;
		}else{
			return false;
		}
	}
	
	// This method calculates a sequence of complex numbers z1, z2, z3,  z4, etc,
	//checking them against isBig and Controller.LIMIT
	public static int divergence(ComplexNumber Z0){
		ComplexNumber lastZ=Z0, newZ=Z0;
		if(isBig(newZ)){ 
			return 0;
		}
		for(int limitCount=1; limitCount<Controller.LIMIT; limitCount++){
			newZ=(lastZ.multiply(lastZ)).add(Z0);
			if(isBig(newZ)){
				return limitCount;
			}
			lastZ=newZ;
		}
		return -1;
	}
	
	
	
	
	
	
	
	
	
	
	/* This method selects a non-black color for a point which DIVERGED when 
	 * tested with the Mandelbrot recurrence, based on how many terms in the 
	 * sequence were computed before the terms got "too big".
	 * 
	 * The parameter represents the index of the term in the sequence which was 
	 * first to be "too big".  This value could be anything from 0 to 
	 * Controller.LIMIT.  The return value is the Color to be used 
	 * to color in the point.
	 * 
	 * STUDENTS:  IF you want to have some fun, write code for the else-if 
	 * clause below which says "modify this block to create your own color 
	 * scheme".  When someone runs the program and selects "Student Color 
	 * Scheme", the code you have written below will determine the colors.
	 */
	public static Color getColor(int divergence) {
		Color returnValue;
		
		if (Controller.colorScheme == Controller.RED_AND_WHITE_BANDS) {
			returnValue = (divergence  % 2 == 0)? Color.WHITE : Color.RED;
		}
		
		else if (Controller.colorScheme == Controller.CRAZY_COLORS) {
			int value = divergence * 2;
			int redAmount = (value % 5) * (255/5);
			int greenAmount = (value % 7) * (255/7);
			int blueAmount = (value % 9) * (255/9);
			returnValue = new Color(redAmount, greenAmount, blueAmount); 
		}
		
		else if (Controller.colorScheme == Controller.STUDENT_DEFINED){
			
			
			/***************************************************************
			 * Modify this block to create your own color scheme!          *
			 ***************************************************************/
			returnValue = Color.WHITE;  // take out and return something useful 
			
			
		}
		else
			throw new RuntimeException("Unknown color scheme selected!");
		return returnValue;
	}
	
}
