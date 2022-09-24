package gui;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import pa1.Block;
import pa1.City;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.Player;
import pa1.containment.Containment;
import pa1.containment.FaceMask;
import pa1.containment.Isolation;
import pa1.util.GameMap;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class GameMenu extends VBox {
    private final List<Button> buttons = new ArrayList<>();
    private final ObservableList<City> cities = FXCollections.observableArrayList();
    private final ObservableList<Containment> containTechniques = FXCollections.observableArrayList();
    private final ObservableList<HealthAuthorityStaff> HAstaffs = FXCollections.observableArrayList();

    private ListView<City> cityListView;
    private ListView<HealthAuthorityStaff> staffListView;
    private ListView<Containment> containmentListView;

    private final Label playerName = new Label();
    private Player currentPlayer;

    private Button skipButton = new Button("Skip Turn");
    private Button menuButton = new Button("Exit to Menu");

    private final Label budgetTitle = new Label("Budget:");
    private final Text budgetValue = new Text();
    private final Label touristIncomeTitle = new Label("Tourist Income:");
    private final Text touristIncomeValue = new Text();
    private final Label gamePointsTitle = new Label("Game Points:");
    private final Text gamePointsValue = new Text();

    private MessageBox messageBox = new MessageBox();
    private GameActionHandler gameActionHandler;

    public GameMenu() {

        // budget
        HBox budget = new HBox(budgetTitle, budgetValue);

        // income
        HBox touristIncome = new HBox(touristIncomeTitle, touristIncomeValue);

        // points
        HBox gamePoints = new HBox(gamePointsTitle, gamePointsValue);

        // info group
        VBox infoGroup = new VBox(playerName, budget, touristIncome, gamePoints);
        infoGroup.setPrefHeight(100);
        infoGroup.setAlignment(Pos.CENTER_LEFT);

        // city
        cityListView = new ListView<>(cities);
        cityListView.setPrefHeight(150);
        cityListView.setPrefWidth(400);

        // staff
        staffListView = new ListView<>(HAstaffs);
        staffListView.setPrefHeight(150);
        staffListView.setPrefWidth(400);

        // containment techniques
        containmentListView = new ListView<>(containTechniques);
        containmentListView.setPrefHeight(150);
        containmentListView.setPrefWidth(400);

        // button group
        Pane buttonGroup = createActionButtonGroup();

        // add
        getChildren().addAll(
                infoGroup,
                new Label("Cities"), cityListView,
                new Label("Health Authority Staff"), staffListView,
                new Label("Containment Techniques"), containmentListView,
                buttonGroup,
                new Label("Message Box"), messageBox
        );

        initHandlers();

        // Set the ID to "info-bar" so that the style defined in "style.css" can
        // be applied to make this info bar better looking
        setId("info-bar");
    }

    private void initHandlers() {
        cityListView.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                City city = cityListView.getSelectionModel().getSelectedItem();
                if(city != null) {
                    onSelectCity(city);
                }
            }
        });

        /**
         * TODO: to register the event handlers into ListViews to so that mouse click on an item would select the item in the ListViews, and then
         *        display to the "Message Box" at the lower right corner of the GUI
         *       For example if the mouse clicks on a Health Authority Staff, in the Listview on the GUI, then this Health
         *       Authority Staff will be selected, it then can be retrieved in the code by staffListView.getSelectionModel().getSelectedItem(),
         *       and then its information will be displayed to the "Message Box" through onSelectStaff(staff) method.
         *
         *       An example of registering the event handle to the cityListView even has been done for you above. You can refer to it doing
         *       the same task for staffListView
         *
         * Step :
         * Register a mouse click event handler/listener for staffListView such that when a staff in the
         * staffListView is selected, the onSelectStaff() method is called to output a string to the "Message Box" at
         * the lower right corner of the GUI, indicating which staff has been selected.
         *
         * a. You can use the setOnMouseClicked() method of staffLstView to provide the event handler (also known as handler or listener).
         *    Provide the event handler using an anonymous inner class that implements the "EventHandler<MouseEvent>" interface.
         *    check out slides 23-26 of https://course.cse.ust.hk/comp3021/notes/8-event-driven-full.pdf for example of doing that.
         * b. The event handler should:
         *    2.1. Get the currently selected staff using staffListView.getSelectionModel().getSelectedItem()
         *    2.2. Check if the selected staff is null (because a staffListView can be clicked
         *         with no item selected. In that case, "staffListView.getSelectionModel().getSelectedItem()"
         *         returns null)
         *    2.3. If the selected staff is not null, call the method onSelectCity() with the selected city.
         *
         * hint: *refer to the provided code above for "cityListView" for the details*
         */
        staffListView.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                HealthAuthorityStaff selectedStaff = staffListView.getSelectionModel().getSelectedItem();
                if (selectedStaff!=null){
                    onSelectStaff(selectedStaff);
                }
            }
        });
    }



    private void onSelectStaff(HealthAuthorityStaff staff) {
        messageBox.writeLog(currentPlayer,
                String.format("selects staff %s", staff.getName()));
    }

    private void onSelectCity(City city) {
        messageBox.writeLog(currentPlayer,
                String.format("selects city %s", city.getName()));
    }

    private Pane createActionButtonGroup() {
        VBox[] vBoxes = new VBox[3];

        /**
         * TODO to instantiate all the action buttons
         * There should be 7 game action buttons
         * - A button with text "Develop Medication Facility"
         * - A button with text "Build Mask Factory"
         * - A button with text "Upgrade Mask Quality"
         * - A button with text "Ban Travel"
         * - A button with text "Develop Vaccine"
         * - A button with text "Upgrade the Vaccine"
         * - A button with text "Lift Travel Ban"
         *
         *  step 1. Create the above 7 buttons, refer to "createActionButtonGroup()" of the GameMenu.java in lab 10 for hint.
         *
         *  step 2. Set handler/listener for each above button you can do that by calling button1.setOnAction(), where "button1" is
         *     a reference to a button you have created in step 1. For the button with the text "Develop Medication Facility", whenever this
         *     button is clicked your handler/listener should run then method "actionButtonHandler(actionNum)", with actionNum to be 1.
         *     You need to use the anonymous inner class approach to create a class for the handler/listener (refer to the TODOs in initHandlers()
         *     to see how this could be done). Java will then create a handler/listener using the anonymous inner class, and that handler/listener
         *     will be listening to clicks on the button, whenever the button is clicked, the handle() method of the handler/listener will be run.
         *     note that when the button with label "Build Mask Factory" is clicked, you should run actionButtonHandler(2) in the handle() method
         *     of the handler/listener. When the button with the label  "Upgrade Mask Factory" is clicked, you should run actionButtonHandler(3) in the
         *     handle() method. When the button with the label  "Ban Travel" is clicked, you should run actionButtonHandler(4) in the
         *     handle() method. When the button with the label  "Develop Vaccine" is clicked, you should run actionButtonHandler(5) in the
         *     handle() method. When the button with the label  "Upgrade the Vaccine" is clicked, you should run actionButtonHandler(6) in the
         *     handle() method. When the button with the label  "Lift Travel Ban" is clicked, you should run actionButtonHandler(7) in the
         *     handle() method.
         *
         *     Use the above knowledge to define the handle() method for the handler/listener assgined to the different buttons.
         *     There is no need to do this for the "menuButton", it will be done elsewhere.
         *
         *  step 3. Create an ArrayList "buttons" to store all the buttons in step 1. Add all the buttons in step 1, and also
         *     the "skipButton" and then "menuButton" to the buttons ArrayList. This ArrayList is not a GUI component, but it will help us
         *     accessing the buttons easier.
         *
         *  step 4. Now create the GUI components to hold the 9 buttons of step 3. Arrange the 9 buttons of step 3 using
         *     3x3 grid style with the help of using three VBoxes and one HBox, use each VBox to hold three buttons vertically,
         *     Put the 3 VBoxes into a Hbox. Refer to the PA description document on page 6 for the layout of the 9 buttons.
         *     Note that you are free to set the style, e.g., spacing, padding, font size, etc.
         *
         *  step 5. return the HBox created in step 4
         */
        Button dmfButton = new Button("Develop Medication Facility");
        Button bmfButton = new Button("Build Mask Factory");
        Button umqButton = new Button("Upgrade Mask Quality");
        Button btButton = new Button("Ban Travel");
        Button dvButton = new Button("Develop Vaccine");
        Button utvButton = new Button("Upgrade the Vaccine");
        Button ltbButton = new Button("Lift Travel Ban");
        dmfButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(1);
            }
        });
        bmfButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(2);
            }
        });
        umqButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(3);
            }
        });
        btButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(4);
            }
        });
        dvButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(5);
            }
        });
        utvButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(6);
            }
        });
        ltbButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                actionButtonHandler(7);
            }
        });

        buttons.add(dmfButton);
        buttons.add(bmfButton);
        buttons.add(umqButton);
        buttons.add(btButton);
        buttons.add(dvButton);
        buttons.add(utvButton);
        buttons.add(ltbButton);
        buttons.add(skipButton);
        buttons.add(menuButton);

        // remember that in order to initialise array of objects in Java we need a loop, otherwise they start off as null
        for (int i=0; i<3; i++){
            vBoxes[i] = new VBox();
        }
        vBoxes[0].getChildren().addAll(dmfButton, bmfButton, umqButton);
        vBoxes[1].getChildren().addAll(btButton, dvButton, utvButton);
        vBoxes[2].getChildren().addAll(ltbButton, skipButton, menuButton);
        HBox finalHBox = new HBox(vBoxes[0], vBoxes[1], vBoxes[2]);
        return finalHBox;

    }

    private void actionButtonHandler(int actionNumber) {
        /**
         * TODO: to implement event handler for game action buttons
         * This method will be run by the handle() method of the listeners of following buttons:
         * - the button showing "Develop Medication Facility", the listener of this button will run actionButtonHandler() with actionNum=1;
         * - the button showing "Build Mask Factory", the listener of this button will the method with actionNum=2;
         * - the button showing  "Upgrade Mask Quality", the listener of this button will the method with actionNum=3;
         * - the button showing "Ban Travel", the listener of this button will the method with actionNum=4;
         * - the button showing "Develop Vaccine", the listener of this button will the method with actionNum=5;
         * - the button showing "Upgrade the Vaccine", the listener of this button will the method with actionNum=6;
         * - the button showing "Lift Travel Ban", the listener of this button will the method with actionNum=7;
         *
         * step 1. Get current selected "city","staff", "containmentTech" from the GUI through cityListView, staffListView
         *    and containmentListView, after user has clicked one the buttons above.
         *    We can get the "city" selected by calling "cityListView.getSelectionModel().getSelectedItem()"*
         *    In general we can get the ListView item selected by "listViewName.getSelectionModel().getSelectedItem()".
         *    In here we have the cityListView, containmentListView and staffListView being shown to the GUI.
         *    see : https://openjfx.io/javadoc/12/javafx.controls/javafx/scene/control/SelectionModel.html#getSelectedItem()
         *          https://openjfx.io/javadoc/12/javafx.controls/javafx/scene/control/ListView.html
         *
         * step 2. Call gameActionHandler.handle() to eventually process the the action
         *          by passing all selected items we've got from step 1. When you call gameActionHandler.handle(), pass
         *          in the order of : selected actionNum, staff, city and containmentTech
         *
         */
        City selCity = cityListView.getSelectionModel().getSelectedItem();
        HealthAuthorityStaff selStaff = staffListView.getSelectionModel().getSelectedItem();
        Containment selCont = containmentListView.getSelectionModel().getSelectedItem();
        gameActionHandler.handle(actionNumber, selStaff, selCity, selCont);

    }

    public void setGameActionHandler(GameActionHandler eventHandler) {
        gameActionHandler = eventHandler;
    }

    public void setMenuButtonHandler(EventHandler<ActionEvent> eventHandler) {
        menuButton.setOnAction(eventHandler);
    }

    public void setSkipButtonHandler(EventHandler<ActionEvent> eventHandler) {
        skipButton.setOnAction(eventHandler);
    }

    public void selectCell(Block block) {
        writeLog(currentPlayer, block.toString());
    }

    public void displayPlayer(Player player) {
        if (currentPlayer != player) {
            currentPlayer = player;
            messageBox.writeLog(currentPlayer, "It's my turn!");
        }

        playerName.setText(player.getName());
        budgetValue.setText(String.format("$%d", player.getBudget()));
        touristIncomeValue.setText(String.format("$%d", player.getTourismIncome()));
        gamePointsValue.setText(String.format("%d", player.getPoints()));

        cities.clear();
        HAstaffs.clear();
        containTechniques.clear();

        cities.addAll(player.getCity());
        HAstaffs.addAll(player.getHAStaffs());
        containTechniques.addAll(player.getContainTechniques());
    }

    public void setDisableButtons(boolean isDisabled) {
        for(Button b: buttons) {
            b.setDisable(isDisabled);
        }
    }

    public void writeLog(Player currentPlayer, String message) {
        messageBox.writeLog(currentPlayer, message);
    }

    public void clearLogs() {
        messageBox.getItems().clear();
    }
}
