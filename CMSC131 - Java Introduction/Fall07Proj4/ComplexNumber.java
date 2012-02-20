/*
 * By: Javed Ahamed (09365000)
 * CMSC131-Project 4 MandelBrot Set
 * Purpose: To Draw the MandelBrot Set
 */

public class ComplexNumber {

	/* STUDENTS:  You may NOT add any further instance or static variables! */
	private final MyDouble real;   // To be initialized in constructors
	private final MyDouble imag;   // To be initialized in constructors


	/* STUDENTS: Put your methods here, as described in the project description.
	 * 
	 * IMPORTANT:  You may NOT call the toString method for the MyDouble class except
	 * while you are writing the toString method for the Complex class.  You may NOT
	 * call the toString method of the Complex class ANYWHERE.  If you don't adhere
	 * to this rule, you will fail some (or possibly all) release tests. */

	public ComplexNumber(MyDouble realIn, MyDouble imagIn){
		real=realIn;
		imag=imagIn;
	}

	public ComplexNumber(MyDouble realIn){
		real=realIn;
		imag=new MyDouble(0.0);
	}

	//Copy Constructor
	public ComplexNumber(ComplexNumber originalIn){
		real=originalIn.real;
		imag=originalIn.imag;
	}

	//Gets real value of a ComplexNumber
	public MyDouble getReal(){
		return real;
	}

	//Gets imag value of a ComplexNumber
	public MyDouble getImag(){
		return imag;
	}

	//Returns ComplexNumber equal to the sum of the current object and parameter
	public ComplexNumber add(ComplexNumber numberIn){
		return new ComplexNumber(real.add(numberIn.real),imag.add(numberIn.imag));
	}

	//Returns ComplexNumber equal to the current object minus the parameter 
	public ComplexNumber subtract(ComplexNumber numberIn){
		return new ComplexNumber(real.subtract(numberIn.real),
				imag.subtract(numberIn.imag));
	}

	//Returns ComplexNumber equal to the current object times the parameter
	public ComplexNumber multiply(ComplexNumber numberIn){
		//(a+bi)*(c+di)=(ac-bd)+(bc+ad)i
		MyDouble realPart, imagPart;
		realPart=((real.multiply(numberIn.real))
				.subtract(imag.multiply(numberIn.imag)));
		imagPart=(imag.multiply(numberIn.real))
				.add(real.multiply(numberIn.imag));
		return new ComplexNumber(realPart, imagPart);
	}

	//Returns ComplexNumber equal to the current object divided by the parameter
	public ComplexNumber divide(ComplexNumber numberIn){
		//(a+bi)/(c+di)=((ac+bd)/(c^2+d^2))+((bc-ad)/(c^2+d^2))
		MyDouble num1, num2, den;
		num1=(real.multiply(numberIn.real)).add(imag.multiply(numberIn.imag));
		num2=(imag.multiply(numberIn.real)).subtract(real.multiply(numberIn.imag));
		den=((numberIn.real).multiply(numberIn.real)).add((numberIn.imag)
				.multiply(numberIn.imag));
		return new ComplexNumber((num1.divide(den)),(num2.divide(den)));
	}
	
	//Checks to see if current ComplexNumber is equal to parameter
	public boolean equals(ComplexNumber numberIn){
		if(real.equals(numberIn.real)&&imag.equals(numberIn.imag)){
			return true;
		}else{
			return false;
		}
	}
	
	/*Compares the norm of the current object with the norm of the parameter. If
	  the norms are equal, this method returns 0; if the norm of the current
	   object is less than the norm of the parameter, this method returns -1; 
	   if the norm of the current object is greater than the norm of the 
	   parameter, this method returns 1.
	 */
	public int compareTo(ComplexNumber numberIn){
		int compareToValue=norm(this).compareTo(norm(numberIn));
		if(compareToValue==0){
			return 0;
		}else if(compareToValue<0){
			return -1;
		}else{//(compareToValue>0)
			return 1;
		}
	}

	public String toString(){
		if(imag.toString().indexOf('-')==-1){ //- sign not found in String
			return real.toString()+"+"+imag.toString()+"i";
		}else{
			return real.toString()+""+imag.toString()+"i";
		}
	}

	//Static Methods Start Here
	
	//Returns the norm of a ComplexNumber
	public static MyDouble norm(ComplexNumber numberIn){
		MyDouble aSquared=(numberIn.real).multiply(numberIn.real);
		MyDouble bSquared=(numberIn.imag).multiply(numberIn.imag);
		return (aSquared.add(bSquared)).sqrt();
	}

	//this method will parse the String and return a ComplexNumber that represents
	//the value described by the String. 
	public static ComplexNumber parseComplexNumber(String stringIn){
		String noSpaces=stringIn.replaceAll(" ","");
		MyDouble parsedReal, parsedImag;
		if(noSpaces.indexOf('+')!=-1){ //+ instead of - in stringIn
			parsedReal = new MyDouble(Double.parseDouble(noSpaces.substring
					(0, noSpaces.indexOf('+'))));
			parsedImag = new MyDouble(Double.parseDouble(noSpaces.substring
					(noSpaces.indexOf('+'), noSpaces.indexOf('i'))));
		}else{ //- instead of + in stringIn
			parsedReal = new MyDouble(Double.parseDouble(noSpaces.substring
					(0, noSpaces.indexOf('-', 1))));
			parsedImag = new MyDouble(Double.parseDouble(noSpaces.substring
					(noSpaces.indexOf('-', 1), noSpaces.indexOf('i'))));
		}
		return new ComplexNumber(parsedReal,parsedImag);	
	}




}
