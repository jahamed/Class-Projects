import java.util.Scanner;

public class OnTheMoney {

	public static void main(String[] args) {

		final int WASHINGTON_DENOM=1, LINCOLN_DENOM=5, JACKSON_DENOM=20;
		String president;
		int answer, denomination;

		Scanner input = new Scanner(System.in);

		System.out.println("Type 1 to enter a denomination, 2 to enter a president: ");
		answer = input.nextInt();
		if(answer==1){
			System.out.println("Choose a denomination: ");
			denomination = input.nextInt();

			if (denomination==1 || denomination==5 || denomination==20){
				System.out.println("Which president appears on the "
						+denomination+" dollar bill?");
				president = input.next();
				if (president.equals("Washington") && WASHINGTON_DENOM==denomination){
					System.out.println("Correct!");
				}else if(president.equals("Lincoln") && LINCOLN_DENOM==denomination){
					System.out.println("Correct!");
				}else if(president.equals("Jackson") && JACKSON_DENOM==denomination){
					System.out.println("Correct!");
				}else{
					System.out.println("Incorrect!");
				}
			}else{
				System.out.println("Invalid choice!");
			}
		}
		else{
			System.out.println("Choose a president: ");
			president = input.next();

			if (president.equals("Washington")||president.equals("Lincoln")||
					president.equals("Jackson")){
				System.out.println("Which denomination does "+president+" appear on?");
				denomination = input.nextInt();

				if (president.equals("Washington") && denomination==WASHINGTON_DENOM){
					System.out.println("Correct!");
				}else if (president.equals("Lincoln") && denomination==LINCOLN_DENOM){
					System.out.println("Correct!");
				}else if (president.equals("Jackson") && denomination==JACKSON_DENOM){
					System.out.println("Correct!");
				}else{
					System.out.println("Incorrect!");
				}

			}else{
				System.out.println("Invalid choice!");
			}

		}
	}
}



