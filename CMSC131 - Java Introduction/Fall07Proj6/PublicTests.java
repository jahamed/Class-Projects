import junit.framework.TestCase;
import foodManagement.*;

public class PublicTests extends TestCase {

	private static final Food BACON = Food.FOOD_OBJECTS[0];
	private static final Food WAFFLE = Food.FOOD_OBJECTS[1];
	private static final Food EGG = Food.FOOD_OBJECTS[2];
	private static final Food OJ = Food.FOOD_OBJECTS[3];
	private static final Food MILK = Food.FOOD_OBJECTS[4];
	
	public void testDefaultConstructorAndGetSize() {
		SortedListOfImmutables list = new SortedListOfImmutables();
		assertTrue(list.getSize() == 0);
		assertEquals("[  ]", list.toString());
	}
	
	public void testListSimpleAdd() {
		SortedListOfImmutables list = new SortedListOfImmutables();
		for (int i = Food.FOOD_OBJECTS.length - 1; i >= 0; i--) {
	//		System.out.println(i);
			list.add(Food.FOOD_OBJECTS[i]);
		}
		assertEquals(Food.FOOD_OBJECTS.length, list.getSize());
		assertEquals("[ Bacon, Cereal, Coffee, Croissant, Donut, Egg, Hashbrowns, Melon, Milk, Orange Juice, Pancakes, Pie, Toast, Waffle ]",
				list.toString());
		
		list.add(BACON);
		list.add(WAFFLE);
		list.add(EGG);
		list.add(MILK);
		list.add(EGG);
		list.add(OJ);
		assertEquals(20, list.getSize());
		assertEquals("[ Bacon, Bacon, Cereal, Coffee, Croissant, Donut, Egg, Egg, Egg, Hashbrowns, Melon, Milk, Milk, " +
				"Orange Juice, Orange Juice, Pancakes, Pie, Toast, Waffle, Waffle ]" , list.toString());
	}	
	
	
}
