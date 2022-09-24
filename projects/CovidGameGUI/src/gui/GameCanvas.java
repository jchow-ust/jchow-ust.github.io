package gui;

import javafx.scene.canvas.Canvas;
import javafx.scene.image.Image;
import javafx.scene.layout.StackPane;
import pa1.Player;
import pa1.containment.Containment;
import pa1.containment.FaceMask;
import pa1.containment.Isolation;
import pa1.containment.Vaccination;
import pa1.util.GameMap;
import pa1.Block;

import java.util.List;

public class GameCanvas extends StackPane {
    private static final int CELL_WIDTH = 128;
    private static final int CELL_HEIGHT = 128;

    // Indices of the canvas layers
    private static final int BACKGROUND_LAYER = 0;
    private static final int LINE_LAYER = 1;
    private static final int ICON_LAYER = 2;
    private static final int FLAG_LAYER = 3;
    private static final int TEXT_LAYER = 4;

    private static Image[] flags = new Image[2];

    
    private final GameMap gameMap;
    private final GameMenu gameMenu;
    private final Canvas[] canvasLayers;
    private final Image background;

    public GameCanvas(GameMap gameMap, GameMenu gameMenu) {
        int canvasWidth = gameMap.getWidth() * CELL_WIDTH;
        int canvasHeight = gameMap.getHeight() * CELL_HEIGHT;
        this.gameMap = gameMap;
        this.gameMenu = gameMenu;
        canvasLayers = new Canvas[5];
        this.background = new Image("background.png", canvasWidth, canvasHeight, false, false);
        for (int i = 0; i < canvasLayers.length; ++i) {
            Canvas canvas = new Canvas(canvasWidth, canvasHeight);
            canvasLayers[i] = canvas;
            getChildren().add(canvas);
        }

        // set a mouse click event handler so that when a cell is clicked, the corresponding city
        // in the info bar is selected.
        setOnMouseClicked(e -> {
            int x = (int) e.getX() / CELL_WIDTH;
            int y = (int) e.getY() / CELL_HEIGHT;
            gameMenu.selectCell(new Block(x, y));
        });
    }

    public void render() {


        // clear the old content on the canvases
        for (Canvas canvas : canvasLayers)
            canvas.getGraphicsContext2D().clearRect(0, 0, canvas.getWidth(), canvas.getHeight());

        // draw the background image on the background canvas layer
        Canvas bg = canvasLayers[BACKGROUND_LAYER];
        bg.getGraphicsContext2D().drawImage(background, 0, 0);

        List<Player> players = gameMap.getPlayers();



        for (int i = 0; i < players.size(); ++i) {


            Image flag;
            int currProtectionLevel=0;

            /** TODO selecting a correct flag/coat-of-arm to indicate the protection level of the player
            * step 1: by referring to the code in computeNewInfectedCases() in Player.java of PA1
             *   calculate the sum of protection_level offered by FaceMask and Isolation objects (max could be 100+100=200 in this PA)
             *   put this sum of protection level to currProtectionLevel
             * step 2: if currProtectionLevel<50, set "flag" (which is an Image reference, see above) to point to an Image() object holding "protect-1.png",
             *    and show it with the size of 60 pixels x 60 pixels, and there is no need to preserve the width and height ratio, but it
             *    needs to be shown using a better quality smooth filtering algorithm, as that will make the png look nicer.
             *    You can do that by "flag = new Image("protect-1.png", 60, 60, false, true)",
             *    refer to https://openjfx.io/javadoc/16/javafx.graphics/javafx/scene/image/Image.html#%3Cinit%3E(java.lang.String,double,double,boolean,boolean)
             * step 3: if the 50<=currProtectionLevel<120, do a similar thing as step 2, but set the flag to use "protect-2.png"
             * step 4: if the currProtectionLevel>=120, do a similar thing as step 2, but set the flag to use "protect-3.png"
             */
            for (Containment contTech: players.get(i).getContainTechniques()) {
                if (contTech instanceof Isolation || contTech instanceof FaceMask)
                    currProtectionLevel += contTech.getProtection_level();
            }
            if (currProtectionLevel<50){
                flag = new Image("protect-1.png", 60, 60, false, true);
            }
            else if (currProtectionLevel<120 && currProtectionLevel>=50){
                flag = new Image("protect-2.png", 60, 60, false, true);
            }
            else{
                flag = new Image("protect-3.png", 60, 60, false, true);
            }

            //T*o*d*o above
            // Do not touch the code below
            // draw the icon, name and flag of each city
            drawCity(players.get(i), flag);
        }
    }

    private void drawCity(Player player, Image flag) {
        Image image = player.getCity().getImage(CELL_WIDTH, CELL_HEIGHT);
        Block location = gameMap.getCityLocation(player.getCity());
        int x = location.getX() * CELL_WIDTH;
        int y = location.getY() * CELL_HEIGHT;

        canvasLayers[ICON_LAYER].getGraphicsContext2D().drawImage(image, x, y);
        canvasLayers[TEXT_LAYER].getGraphicsContext2D().strokeText(player.getCity().getDescription(), x + CELL_WIDTH / 4, y);
        canvasLayers[FLAG_LAYER].getGraphicsContext2D().drawImage(flag, x, y);

        //to draw medication facility, vaccination factory and face mask factory for current city
        drawMedicationFacility(player, x, y);
        drawVaccinationFactory(player, x, y);
        drawFaceMaskFactory(player, x, y);
    }

    private void drawFaceMaskFactory(Player player, int x, int y) {

        // Adjust x and y to not overlap with the image of city
        x += CELL_WIDTH;
        y += CELL_HEIGHT / 2;

        //Get the face mask factory image by calling player.getFaceMaskFactoryImage()
        // Draw the image on ICON_LAYER
        canvasLayers[ICON_LAYER].getGraphicsContext2D()
                .drawImage(player.getFaceMaskFactoryImage(CELL_WIDTH, CELL_HEIGHT), x, y);

        //Draw the text like "FaceMask Protection Level 50" on TEXT_LAYER
        y += CELL_HEIGHT / 2;
        canvasLayers[TEXT_LAYER].getGraphicsContext2D()
                .strokeText(String.format("FaceMask Protection Level %s", player.getMaskProtectionLevel()), x, y);
    }


    private void drawVaccinationFactory(Player player, int x, int y) {
        /**
         * TODO draw vaccination factory, see the above drawFaceMaskFactory() for how this could be done
         *
         * step 1. Adjust x and y to not overlap with the image of city and other facilities, you may need to do that
         *    using trial and error approach
         * step 2. Get the vaccination factory image by calling player.getVaccineFactoryImage(), refer to the the above
         *    drawFaceMaskFactory() above for hint on how this could be done. Draw the factory image in the ICON_LAYER of the
         *    canvasLayer[] array, see drawFaceMaskFactory() above for hint on how this could be done.
         * step 3. Draw the text like "Vaccination Level 50" in the TEXT_LAYER of the canvasLayer[] array. Again you
         *    can refer to the implementation in drawFaceMaskFactory() for the hints.
         */
        // Adjust x and y to not overlap with the image of city
        y += CELL_HEIGHT / 2;

        //Get the vaccination factory image by calling player.getVaccineFactoryImage()
        // Draw the image on ICON_LAYER
        canvasLayers[ICON_LAYER].getGraphicsContext2D()
                .drawImage(player.getVaccineFactoryImage(CELL_WIDTH, CELL_HEIGHT), x, y);

        //Draw the text like "Vaccination Level 50" on TEXT_LAYER
        y += 3*CELL_HEIGHT / 8;
        canvasLayers[TEXT_LAYER].getGraphicsContext2D()
                .strokeText(String.format("Vaccination Level %s", player.getVaccineLevel()), x, y);

    }



    private void drawMedicationFacility(Player player, int x, int y) {
        /**
         * TODO draw vaccination factory, see the above drawFaceMaskFactory() for how this could be done
         *
         * step 1. Adjust x and y to not overlap with the image of city and other facilities, you may need to do that
         *    using trial and error approach
         * step 2. Get the medication facility image by calling player.getMedicationFacilityImage(), refer to the the above
         *    drawFaceMaskFactory() for how this could be done. Draw the Medication Facility image in the ICON_LAYER of the
         *    canvasLayer[] array.
         * step 3. Draw the text like "Medication Treatment Level 10" in the TEXT_LAYER of the canvasLayer[] array. Again you
         *    can refer to the implementation in drawFaceMaskFactory() for the hints.
         */
        // Adjust x and y to not overlap with the image of city
        x += CELL_WIDTH;

        //Get the medication facility image by calling player.getMedicationFacilityImage()
        // Draw the image on ICON_LAYER
        canvasLayers[ICON_LAYER].getGraphicsContext2D()
                .drawImage(player.getMedicationFacilityImage(CELL_WIDTH, CELL_HEIGHT), x, y);

        //Draw the text like "Medication Treatment Level 10" on TEXT_LAYER
        y += CELL_HEIGHT/8;
        canvasLayers[TEXT_LAYER].getGraphicsContext2D()
                .strokeText(String.format("Medication Treatment Level %s", player.getMedicationLevel()), x, y);


    }

}
