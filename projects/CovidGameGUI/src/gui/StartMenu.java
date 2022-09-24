package gui;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class StartMenu extends VBox {
    private final Button newButton, quitButton;


    public StartMenu() {
        newButton = new Button("New Game");
        quitButton = new Button("Quit");
        getChildren().addAll(new Label("Fight Covid19 - GUI version"), newButton, quitButton);

        setId("menu");
    }

    public void setNewGameHandler(EventHandler<ActionEvent> eventHandler) {
        newButton.setOnAction(eventHandler);
    }

    public void setQuitGameHandler(EventHandler<ActionEvent> eventHandler) {
        quitButton.setOnAction(eventHandler);
    }
}
