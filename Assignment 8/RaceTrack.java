//Jordan Dube

//import statements
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

public class RaceTrack extends Application {
    //image path
    private static final String imagePath = "sportive-car.png";
    //finish line
    private static final int endOfRace = 400;
    //control variable for the movement of the cars
    private boolean movementToggle;
    //setting up the cars for each racetrack
    private final Image car = new Image(imagePath);
    private final ImageView car1 = new ImageView(car);
    private final ImageView car2 = new ImageView(car);
    private final ImageView car3 = new ImageView(car);
    //initialize the Alert for future customization
    private final Alert winnerAlert = new Alert(Alert.AlertType.INFORMATION);
    
    //method to move cars, keeping it abstracted from threads
    synchronized private void move(ImageView car){
        //get a random number 0-10
        int random = (int) (Math.random() * 11);
        //move the car forward
        car.setX(car.getX() + random);
        //checks if the car went past the end
        if(car.getX() > endOfRace){
            //if it finishes, set the alert to reflect the winner
            // if winner is car1
            if(car.getY() == 50){ winnerAlert.setContentText("Car One Wins!"); }
            //if winner is car 2
            else if(car.getY() == 100){ winnerAlert.setContentText("Car Two Wins!"); }
            //if winner is car 3
            else if(car.getY() == 150){ winnerAlert.setContentText("Car Three Wins!"); }
            //run it later since we don't want to run it from a non-gui thread and move is called only from non-gui threads
            Platform.runLater(new Thread(winnerAlert::show));
            //pause the movement
            pause();
        }
    }
    
    //start method that takes a stage object and adds the images, and updates the car positions
    @Override
    public void start(Stage primaryStage){
        //root for the scene constructor
        Group root = new Group();
        
        //setting title and icon
        primaryStage.setTitle("Richmond Raceway");
        primaryStage.getIcons().add(car);
        
        //first track, setting properties
        Rectangle rect1= new Rectangle();
        rect1.setX(50);
        rect1.setY(50);
        rect1.setWidth(400);
        rect1.setHeight(20);
        rect1.setFill(Color.LIGHTGRAY);
        root.getChildren().add(rect1);
        
        //second track, setting properties
        Rectangle rect2= new Rectangle();
        rect2.setX(50);
        rect2.setY(100);
        rect2.setWidth(400);
        rect2.setHeight(20);
        rect2.setFill(Color.LIGHTGRAY);
        root.getChildren().add(rect2);
        
        //third track, setting properties
        Rectangle rect3= new Rectangle();
        rect3.setX(50);
        rect3.setY(150);
        rect3.setWidth(400);
        rect3.setHeight(20);
        rect3.setFill(Color.LIGHTGRAY);
        root.getChildren().add(rect3);
        
        //initialize first car
        car1.setLayoutX(20);
        car1.setY(50);
        root.getChildren().add(car1);
        
        //initialize second car
        car2.setLayoutX(20);
        car2.setY(100);
        root.getChildren().add(car2);
        
        //initialize third car
        car3.setLayoutX(20);
        car3.setY(150);
        root.getChildren().add(car3);
        
        //set up start button
        Button startButton = new Button("Start");
        startButton.setLayoutX(100);
        startButton.setLayoutY(0);
        //map the start button to the startRace method
        startButton.setOnAction(actionEvent -> startRace());
        root.getChildren().add(startButton);
        
        //set up pause button
        Button pauseButton = new Button("Pause");
        pauseButton.setLayoutX(200);
        pauseButton.setLayoutY(0);
        //map pause button to pause method
        pauseButton.setOnAction(actionEvent -> pause());
        root.getChildren().add(pauseButton);
        
        //set up reset button
        Button resetButton = new Button("Reset");
        resetButton.setLayoutX(300);
        resetButton.setLayoutY(0);
        //map reset button to reset method
        resetButton.setOnAction(actionEvent -> reset());
        root.getChildren().add(resetButton);
        
        //set up the stage, adding the Group and showing it
        primaryStage.setScene(new Scene(root, 500, 200));
        primaryStage.setResizable(false);
        primaryStage.show();
        //set a close method to help the system exit the program and not get caught waiting
        primaryStage.setOnCloseRequest(actionEvent->onClose(primaryStage));
        
        //controller thread for the first car, NON-GUI
        new Thread(()->
        {
            //infinite loop like prod-con problem
            while(true) {
                //checks if the car can move
                if (movementToggle){
                    //if the car is currently behind the end
                    if(car1.getX() < endOfRace){
                        //move the car
                        move(car1);
                    }
                }
                //sleep for 50ms
                try{ Thread.sleep(50); }
                catch(InterruptedException e){ e.printStackTrace(); }
            }
        }
        //start the thread
        ).start();
    
        //controller thread for the second car, NON-GUI
        new Thread(()->
        {
            //infinite loop like prod-con problem
            while(true) {
                //checks if the car can move
                if (movementToggle){
                    //if the car is currently behind the end
                    if(car2.getX() < endOfRace){
                        //move the car
                        move(car2);
                    }
                }
                //sleep for 50ms
                try{ Thread.sleep(50); }
                catch(InterruptedException e){ e.printStackTrace(); }
            }
        }
                //start the thread
        ).start();

        //controller thread for the third car, NON-GUI
        new Thread(()->
        {
            //infinite loop like prod-con problem
            while(true) {
                //checks if the car can move
                if (movementToggle){
                    //if the car is currently behind the end
                    if(car3.getX() < endOfRace){
                        //move the car
                        move(car3);
                    }
                }
                //sleep for 50ms
                try{ Thread.sleep(50); }
                catch(InterruptedException e){ e.printStackTrace(); }
            }
        }
                //start the thread
        ).start();
    }
    //method to start the race
    private void startRace(){ movementToggle = true; }
    //method to pause the race
    private void pause(){ movementToggle = false; }
    //method to reset the cars to the start
    private void reset(){
        //stops movement, could call pause
        movementToggle = false;
        //set each car to the start. The cars actually go back to X = 20 since the layout X is 20,
        // so setting X simply eliminates the accumulated offset
        car1.setX(0);
        car2.setX(0);
        car3.setX(0);
    }
    //method to gracefully close the program when the X button is pressed in the Racetrack window
    //takes in a stage object
    private void onClose(Stage s){
        System.out.print("Thanks For Racing :)");
        //closes the stage
        s.close();
        //exits the program
        System.exit(0);
    }
    //main method to launch the window
    public static void main(String[] args) { launch(args); }
}