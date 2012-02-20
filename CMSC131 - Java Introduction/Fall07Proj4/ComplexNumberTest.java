import junit.framework.TestCase;


public class ComplexNumberTest extends TestCase {

	public void testComplexNumberMyDoubleMyDouble() {
		fail("Not yet implemented");
	}

	public void testComplexNumberMyDouble() {
		fail("Not yet implemented");
	}

	public void testComplexNumberComplexNumber() {
		fail("Not yet implemented");
	}

	public void testGetReal() {
		ComplexNumber testNumber=new ComplexNumber(new MyDouble(9),new MyDouble(-10));
		assertTrue(testNumber.getReal().equals(new MyDouble(9)));
		assertTrue(testNumber.getImag().equals(new MyDouble(-10)));
		ComplexNumber testNumber2=new ComplexNumber(new MyDouble(0));
		assertTrue(testNumber2.getReal().equals(new MyDouble(0)));
		assertTrue(testNumber2.getImag().equals(new MyDouble(0)));
	}

	public void testGetImag() {
		fail("Not yet implemented");
	}

	public void testAdd() {
		fail("Not yet implemented");
	}

	public void testSubract() {
		ComplexNumber number1=new ComplexNumber(new MyDouble(10), new MyDouble(7));
		ComplexNumber number2=new ComplexNumber(new MyDouble(-5), new MyDouble(0));
		assertTrue((number1.subtract(number2)).compareTo(new ComplexNumber(new MyDouble(15),
				new MyDouble(7)))==0);
	}

	public void testMultiply() {
		fail("Not yet implemented");
	}

	public void testDivide() {
		fail("Not yet implemented");
	}

	public void testEquals() {
		fail("Not yet implemented");
	}

	public void testCompareTo() {
		fail("Not yet implemented");
	}

	public void testToString() {
		fail("Not yet implemented");
	}

	public void testNorm() {
		fail("Not yet implemented");
	}

	public void testParseComplexNumber() {
	}

}
