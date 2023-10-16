//Jordan Dube
public class FoodBank {
    private int food;
    private void setFood(int amount){
        food = amount;
    }
    public int getFood(){
        return food;
    }
    public FoodBank(){
        setFood(0);
    }
    synchronized public void takeFood(int amount) {
        if(getFood() >= amount) {
            setFood(getFood() - amount);
            System.out.println("Took " + amount + " items from bank ; New amount: " + getFood());
        }
    }
    synchronized public void giveFood(int amount) {
        setFood(getFood()+amount);
        System.out.println("Added " + amount + " items to bank ; New amount: " + getFood());
    }
}
class FoodProducer extends Thread {
    private FoodBank bank;
    public FoodProducer(FoodBank b) { this.bank = b; }
    @Override
    public void run()
    {
        while(true) {
            bank.giveFood((int) (Math.random()*100) + 1);
            try { Thread.sleep(100); }
            catch (Exception e) { e.printStackTrace(); }
        }
    }
}
class FoodConsumer extends Thread {
    private FoodBank bank;
    public FoodConsumer(FoodBank b) { this.bank = b; }
    @Override
    public void run()
    {
        while(true) {
            bank.takeFood((int) (Math.random()*100) + 1);
            try { Thread.sleep(100); }
            catch (Exception e) { e.printStackTrace(); }
        }
    }
}
class FoodBankPatrons {
    public static void main(String[] args)
    {
        FoodBank bank = new FoodBank();
        FoodConsumer fc = new FoodConsumer(bank);
        FoodProducer fp = new FoodProducer(bank);
        fp.start();
        fc.start();
    }
}