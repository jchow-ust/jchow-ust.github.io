package gui;

import javafx.scene.control.ListView;
import pa1.Player;

public class MessageBox extends ListView<String> {

    public MessageBox() {
        setPrefHeight(150);
    }

    /**
     * Convenience method to print the output to the Message Box UI
     */
    public void writeLog(Player player, String message) {
        if (message == null || message.isEmpty())
            return;

        String format = "%s:    %s";
        getItems().add(String.format(format, player.getName(), message));
        scrollTo(getItems().size());
    }
}
