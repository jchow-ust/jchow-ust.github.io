package gui;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import pa1.Player;


public class EndMenu extends VBox {

    private Button button;
    private Label title;
    private Text winnerText;

    public EndMenu(Player winner) {
        /**
         * TODO: construct the End Game UI
         * This class is an extension of VBox with the following children:
         *  - title: A Label object that displays the title "Game Ended"
         *  - winnerText: A Text object that displays the message:
         *      winner.getName() + " Wins the Game", if one of the player wins the game
         *      (in that case "winner" passed to this EndMenu constructor will not be null)
         *      "Players are equal", if the game comes to a draw
         *      (in that case "winner" passed to this EndMenu constructor will be null)
         *  - A Button object with the text "Return to Main Menu". When it is clicked, the menu is shown.
         *      Its handler/listener is set in the initHandlers() method in GameApplication.
         *
         *  step 1. create all the UI elements describe above,
         *  step 2. add the Label, the Text, and the button created in step 1 into
         *     this EndMenu VBox by calling getChildren().addAll().
         */
        title = new Label("Game Ended");
        if (winner!=null){
            winnerText = new Text(winner.getName() + " Wins the Game");
        }
        else{
            winnerText = new Text("Players are equal");
        }
        button = new Button("Return to Main Menu");

        getChildren().addAll(title,winnerText,button);

        // do not touch the code below
        // set the ID to use the CSS format
        winnerText.setId("winner");
        setId("end-game");
    }

    public void setMenuButtonHandler(EventHandler<ActionEvent> handler) {
        button.setOnAction(handler);
    }
}
