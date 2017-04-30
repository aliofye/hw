


public class MoneyHandler
{
static int currentCash = 1000;
static int bet;
	public static int getCash()
	{
		return currentCash;
	}
	public static int getBet()
	{
		return bet;
	}

	public static void displayCash()
		{
			UserInterface.moneylabel.setText(Integer.toString(currentCash))
	}

	public static void displayBet()
		{
		UserInterface.potlabel.setText(Integer.toString(bet))
	}

} // end class Craps

