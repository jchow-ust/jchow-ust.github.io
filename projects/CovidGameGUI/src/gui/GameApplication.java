package gui;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import pa1.City;
import pa1.GameEngine;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.Player;
import pa1.containment.Containment;
import pa1.exceptions.MedicalException;

import java.io.IOException;
import java.util.List;
import java.util.Random;

public class GameApplication extends Application {
    // Game Engine
    private static GameEngine gameEngine = new GameEngine();

    // UI Panes
    StartMenu startMenu = new StartMenu();
    GameCanvas gameCanvas;
    GameMenu gameMenu = new GameMenu();

    // UI Scenes
    Scene menuScene = new Scene(startMenu);
    Scene gameplayScene;

    private Player currentPlayer;
    private Stage stage;

    private static Random random = new Random();

    // Generate a random integer between 0 (inclusive) and max (exclusive)
    private static int getRandomInt(int max) {
        return max > 0 ? random.nextInt(max) : 0;
    }

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        menuScene.getStylesheets().add("style.css");
        primaryStage.setScene(menuScene);
        primaryStage.show();
        primaryStage.setTitle("COMP3021 PA2");
        initHandlers(primaryStage);
    }

    private void initHandlers(Stage primaryStage) {
        this.stage = primaryStage;

        startMenu.setNewGameHandler(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                newGameHandler();
            }
        });

        startMenu.setQuitGameHandler(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                quitGameHandler();
            }
        });

        gameMenu.setGameActionHandler(new GameActionHandlerImpl());

        /**
         * TODO set event handler to skip turn for the current player in the following setSkipButtonHandler()
         * step: Create an anonymous inner class that implements the EventHandler<ActionEvent> interface inside the
         *    gameMenu.setSkipButtonHandler() function call brackets
         *    Define the handle() method of this interface to run endCurrentPlayerTurn()
         *    use that anonymous inner class to create an handler/listener object on the fly
         *    See slides 23-26 of https://course.cse.ust.hk/comp3021/notes/8-event-driven-full.pdf for examples
         *    also see the implementation in above startMenu.setQuitGameHandler() and the following
         *    gameMenu.setMenuButtonHandler() methods for reference
         */
        gameMenu.setSkipButtonHandler(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                endCurrentPlayerTurn();
            }
        }
        );

        gameMenu.setMenuButtonHandler(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                primaryStage.setScene(menuScene);
            }
        }
        );
    }

    private class GameActionHandlerImpl implements GameActionHandler {


        @Override
        public void handle(int actionNum, HealthAuthorityStaff staff, City city, Containment tech) {
            /**
             * TODO: Implement game action handler to handle actions when the button in the gameMenu has been clicked.
             *       possible buttons are the one shown ""Develop Medical Facility", "Build Mask Factory" or "Upgrade Mask Factory"
             *
             *      Assume that when this method is called, the staff selected for doing the task is in "selectedStaff" argument passed
             *      Assume that when this method is called, the city selected for doing the task is in "city"
             *      Assume that when this method is called, the "actionNum" indicates what to do (i.e. it is the "int command" to be passed to gameEngine.processPlayerCommand())
             *
             *
             * 1. check if "selectedstaff" is null, if this is the case write the message "No staff selected" to "Message Box" in the lower right corner of the gameMenu,
             *    you can do that by "gameMenu.writeLog(currentPlayer, "No staff selected");", the line "gameCanvas.render();" below will show the message to the message box
             * 2. check if "selectedcity" is null, if this is the case write the message "No city selected" to "Message Box" in the lower right corner of the gameMenu.
             *
             * 3. now if none of the references in steps 1-2 are null, check if the "selectedstaff" is ready, if the staff is not ready  do nothing and write the message "The selected staff is already done."
             *    otherwise call gameEngine.processPlayerCommand() and pass it actionNum, currentPlayer, selectedStaff and selectedCity.
             *    gameEngine.processPlayerCommand() will then return a message in the form of a string, write that returned string to the "Message Box" in the lower right corner of the game Menu
             */

            if (staff==null){
                gameMenu.writeLog(currentPlayer, "No staff selected");
                gameCanvas.render();
            }
            if (city==null){
                gameMenu.writeLog(currentPlayer, "No city selected");
                gameCanvas.render();
            }
            if (staff!=null&&city!=null){
                if (staff.isReady()){
                    String processedCmd = gameEngine.processPlayerCommand(actionNum, currentPlayer, staff, city);
                    gameMenu.writeLog(currentPlayer, processedCmd);
                    gameCanvas.render();

                }
                else{
                    gameMenu.writeLog(currentPlayer, "The selected staff is already done.");
                    gameCanvas.render();
                }
            }


            //T*o*d*o above
            //do not touch the lines below
            gameCanvas.render();
            gameMenu.displayPlayer(currentPlayer);

            if (!currentPlayer.hasReadyHAStaff() || gameEngine.isGameOver())
                endCurrentPlayerTurn();
        }
    }

    private void beginCurrentPlayerTurn(Player player) {
        /**
         * TODO Prepare for a player to begin the turn
         * step 1. set currentPlayer = player, where "player" is the player object passed to this method
         * step 2. Get every single HA Staff of currentPlayer (using a for-each loop, and currentPlayer.getHAstaffs(),
         *    or any other approach that works). For each of these HA staffs make them "ready" by calling the
         *    beginTurn() method using each of the HA staff object
         */
        currentPlayer = player;
        for (HealthAuthorityStaff staffMember : currentPlayer.getHAStaffs()){
            staffMember.beginTurn();
        }


        if (player.isHuman()) {
            //update UI for human player
            /**
             * step 3. If currentPlayer is Human (player.isHuman() returns true), then
             *    - enable all buttons of the gameMenu (gameMenu.setDisableButtons(false))
             *    - display player information by calling gameMenu.displayPlayer()
             *    - display cities in canvas by calling gameCanvas.render()
             */

            // TODO check need use thread?
            gameMenu.setDisableButtons(false);
            gameMenu.displayPlayer(currentPlayer);
            gameCanvas.render();
        } else {
            // T*o*d*o above, keep this part
            // invoke a thread to mimic a virtual player
            // currentPlayer is Computer, so we
            //  - disable all buttons
            //  - Instantiate a ComputerThread and start it
            //    using thread.start()
            gameMenu.setDisableButtons(true);
            Runnable task = new ComputerThread();
            Thread thread = new Thread(task);
            thread.start();
        }
    }

    private void endCurrentPlayerTurn() {
        /**
         * TODO End the turn for currentPlayer
         * step 1. Update points and income and infected cases for currentPlayer, by calling currentPlayer.updateStatusAfterTurn().
         *    This method will throw the checked exception "MedicalException", please use try-catch to handle the exception.
         *    If the MedicalException is caught, write the error message into the "Message Box" at the lower right corner of
         *    the GameMenu. Just like in the Lab 10, you can do that using "gameMenu.writeLog()". The message to be written
         *    could be retrieved from the getMessage() method of the MedicalException object
         *
         * step 2. Then check if the end game condition is reached by calling gameEngine.isGameOver(). If it returns true,
         *    display the EndGame UI using displayEndGameScene() and then return.
         *
         * step 3. End game condition is not reached, generate random disasters for currentPlayer (using currentPlayer.generateUnexpectedDisasters()),
         *     and then if there is indeed a disaster (i.e. the String return by currentPlayer.generateUnexpectedDisasters() not an empty string), write
         *     the String returned into the "Message Box" at the lower right corner of the GameMenu. Again you can use "gameMenu.writeLog()" for that.
         */
        try{
            currentPlayer.updateStatusAfterTurn();
        }
        catch(MedicalException medExcept){
            gameMenu.writeLog(currentPlayer, medExcept.getMessage());
            gameCanvas.render();
        }

        if (gameEngine.isGameOver()){
            displayEndGameScene();
            return;
        }
        else{
            String disasterMsg = currentPlayer.generateUnexpectedDisasters();
            if (disasterMsg != ""){
                gameMenu.writeLog(currentPlayer, disasterMsg);
                gameCanvas.render();
            }
        }


        // T*od*o above
        // begin next player turn
        beginCurrentPlayerTurn(getNextPlayer(currentPlayer));
    }

    private void displayEndGameScene() {

        Player winner = gameEngine.announceWinner();
        EndMenu endMenu = new EndMenu(winner);
        endMenu.setMenuButtonHandler(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                stage.setScene(menuScene);
            }
        });
        Scene endGameScene = new Scene(endMenu);
        endGameScene.getStylesheets().add("style.css");
        stage.setScene(endGameScene);
    }

    private Player getNextPlayer(Player currentPlayer) {
        List<Player> players = gameEngine.getMap().getPlayers();
        int index = players.indexOf(currentPlayer);
        index = (index + 1) % players.size();
        return players.get(index);
    }

    private void newGameHandler() {
        //load the game
        try {
            gameEngine.getMap().loadPlayers("players.txt");
            gameEngine.getMap().loadMap("map.txt");
        } catch (IOException e) {
            Platform.exit();
        }

        // set up the GUI
        gameCanvas = new GameCanvas(gameEngine.getMap(), gameMenu);
        gameCanvas.render();

        gameMenu.clearLogs();

        HBox hBox = new HBox(gameCanvas, gameMenu);
        gameplayScene = new Scene(hBox);
        gameplayScene.getStylesheets().add("style.css");
        stage.setScene(gameplayScene);

        // get the player and then start the new turn for the player
        Player player = gameEngine.getMap().getPlayers().get(0);
        beginCurrentPlayerTurn(player);
    }

    private void quitGameHandler() {
        Platform.exit();
    }

    private class ComputerThread implements Runnable {

        private Player player;

        ComputerThread() {
            this.player = currentPlayer;
        }

        @Override
        public void run() {
            for (HealthAuthorityStaff staff : player.getHAStaffs()) {
                if (!staff.isReady()) {
                    //do nothing;
                    gameMenu.writeLog(player, "The selected staff is already done.");
                    return;
                }

                // TODO: implement a computer thread that makes random decisions

                /**
                 * Step 1:
                 * Choose action randomly for the current staff of player
                 * 1. choose a random action number from 1 to 7
                 * You may find the methods getRandomInt() provided useful
                 *
                 */
                int randInt = getRandomInt(7)+1;


                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        /**
                         * Step2:
                         *    a. in the run() method call gameEngine.processPlayerCommand() method, using the randomly chosen action in step 1,
                         *       pass player, staff, and the city of the player (player.getCity()) as the arguments.
                         *    b. write the message returned by gameEngine.processPlayerCommand() to the "Message Box" window
                         *       at the lower right corner of the gameMenu. Just like in the Lab 10, you can do that using "gameMenu.writeLog()".
                         *
                         */
                        String playerCmd = gameEngine.processPlayerCommand(randInt, player, staff, player.getCity());
                        gameMenu.writeLog(player, playerCmd);

                        /**
                         * Step 3: in the run() Update UI for computer player
                         *    a. call the render() of gameCanvas to update canvas
                         *    b. call the displayPlayer() of gameMenu to update ListViews of the player
                         */
                        gameCanvas.render();
                        gameMenu.displayPlayer(player);



                    }
                });

                // sleep for 0.5 seconds, not to overwhelm the JavaFX GUI thread
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                }
            }


            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    endCurrentPlayerTurn();
                }
            });
        }
    }

}
