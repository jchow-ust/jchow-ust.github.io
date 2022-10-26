package pa1;

import pa1.exceptions.BudgetRunOutException;
import pa1.exceptions.MedicalException;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.exceptions.NoEnoughBudgetException;
import pa1.util.GameMap;

import java.util.Scanner;

/**
 * Implements the game logic
 */
public class GameEngine {

    private GameMap gameMap = new GameMap();
    private int turns;
    private Scanner userInputScanner = new Scanner(System.in);

    /**
     * The player wins the game
     * When the city under a player’s control has 0 active cases and 0 new infected cases.
     * If both players have 0 active cases and 0 new infected:
     *   - decides the winner based on the one with greater points.
     */
    public Player announceWinner( ) {
        // Do Not modify this part!
        Player firstPlayer = gameMap.getPlayers().get(0);
        Player secondPlayer = gameMap.getPlayers().get(1);
        Player winner = null;

        if (firstPlayer.getCity().getActiveCases() < secondPlayer.getCity().getActiveCases())
            winner =  firstPlayer;
        else if (firstPlayer.getCity().getActiveCases() > secondPlayer.getCity().getActiveCases())
            winner = secondPlayer;
        else {
            if( firstPlayer.getCity().getNumNewCases() < secondPlayer.getCity().getNumNewCases())
                winner =  firstPlayer;
            else if( firstPlayer.getCity().getNumNewCases() > secondPlayer.getCity().getNumNewCases())
                winner = secondPlayer;
            else{
                if( firstPlayer.getPoints() > secondPlayer.getPoints())
                    winner = firstPlayer;
                else if( firstPlayer.getPoints() < secondPlayer.getPoints())
                    winner = secondPlayer;
            }
        }



        // do not modify the part below!
        if (winner == null)
            System.out.printf("Players (%s has %d , %s has %d) are equal\n",firstPlayer.getName(), firstPlayer.getPoints(),
                    secondPlayer.getName(), secondPlayer.getPoints() );
        else
            System.out.printf("Player %s has %d infected Cases, %d new cases, %d points, wins the game\n", winner.getName(),winner.getCity().getActiveCases(), winner.getCity().getNumNewCases(), winner.getPoints());

        return winner;
    }

    private int getSelection(int min, int max, String name) {
        while (true) {
            try {
                System.out.printf("\nSelect %s (%d-%d):\n", name, min, max);
                int selection = userInputScanner.nextInt();
                if ((selection < min || selection > max) && selection != 0)
                    throw new IndexOutOfBoundsException();
                return selection;

            } catch (NumberFormatException | IndexOutOfBoundsException e) {
                System.out.print("Invalid option, choose again");
            }
        }
    }

//    private void processPlayersTurn() throws MedicalException {
//        turns++;
//        for (Player player :  gameMap.getPlayers()) {
//
//            player.computeNewInfectedCases();
//
//            System.out.printf("\n *********( TURN: %d )*************",turns);
//            for (HealthAuthorityStaff haStaff: player.getHAStaffs()) {
//                haStaff.beginTurn();
//            }
//
//            while (player.hasReadyHAStaff()) {
//                System.out.print("\n\n");
//                System.out.println(player);
//                System.out.print("\n\n");
//                HealthAuthorityStaff healthAuthorityStaff = selectHAStaff(player);
//
//                if (healthAuthorityStaff == null) break;
//
//                City city = player.getCity();
//
//                if (city == null) break;
//
//                System.out.print("\n\n");
//                selectAndPerformAction(player, healthAuthorityStaff, city);
//                healthAuthorityStaff.endTurn();
//            }
//
//            //Generate random disasters, then compute new infected cases & update total cases
//            player.generateUnexpectedDisasters();
//
//            //update player's points
//            if(player.getCity().getNumNewCases() == 0 || player.getCity().getActiveCases() == 0)
//                player.addPoints(player.getPoints() * 2);
//            if(player.getCity().isNewCasesIncreasing())
//                player.decreasePoints(player.getPoints()/ 3);
//
//            System.out.println(player);
//        }
//    }

    private HealthAuthorityStaff selectHAStaff(Player player) {
        System.out.println("HAStaff SELECTION");
        for (int i = 0; i < player.getHAStaffs().size(); i++)
            System.out.printf("\t[%d]\t%s\n", i + 1, player.getHAStaffs().get(i));

        HealthAuthorityStaff m = null;
        while (true) {
            int selection = getSelection(1, player.getHAStaffs().size(), "HAStaff (0 to skip turn)");
            if (selection == 0) break;
            m = player.getHAStaffs().get(selection - 1);
            if (!m.isReady()) {
                System.out.println("Selected HAStaff already performed a task");
            } else {
                break;
            }
        }

        return m;
    }

    private void selectAndPerformAction(Player player, HealthAuthorityStaff healthAuthorityStaff, City city) {
        System.out.println("SELECT HAStaff ACTION");
        System.out.println("\t[ 1]\tDevelop Medication Facility");
        System.out.println("\t[ 2]\tBuild Mask Factory");
        System.out.println("\t[ 3]\tUpgrade Mask Quality");
        System.out.println("\t[ 4]\tBan Travel");
        System.out.println("\t[ 5]\tDevelop Vaccine");
        System.out.println("\t[ 6]\tUpgrade the Vaccine");
        System.out.println("\t[ 7]\tLift Travel Ban");

        while (true) {
            int command = getSelection(1, 7, "action");
            processPlayerCommand(command, player, healthAuthorityStaff, city);
            break;
        }
    }

    public String processPlayerCommand(int command, Player player, HealthAuthorityStaff staff, City city)  {
        String logMessage ="nothing happened.";

        try {
            switch (command) {
                case 1:
                    staff.developMedicationFacility(player, city);
                    logMessage = String.format("%s develops a new medication facility in %s", staff.getName(), city.getName());
                    break;
                case 2:
                    staff.buildMasksFactory(player, city);
                    logMessage = String.format("%s builds a new face mask factory in %s", staff.getName(), city.getName());
                    break;
                case 3:
                    staff.upgradeFMaskQuality(player, city);
                    logMessage = String.format("%s upgrades the face mask factory in %s", staff.getName(), city.getName());
                    break;
                case 4:
                    staff.banTravel(player, city);
                    logMessage = String.format("%s bans travel in %s", staff.getName(), city.getName());
                    break;
                case 5:
                    staff.developVaccine(player, city);
                    logMessage = String.format("%s develops a new vaccine in %s", staff.getName(), city.getName());
                    break;
                case 6:
                    staff.upgradeVaccine(player, city);
                    logMessage = String.format("%s upgrades the vaccine in %s", staff.getName(), city.getName());
                    break;
                case 7:
                    staff.liftTravelBan(player, city);
                    logMessage = String.format("%s lifts the travel ban in %s", staff.getName(), city.getName());
                    break;
                default:
                    break;
            }
        }
        catch (BudgetRunOutException e) {
            logMessage = e.getMessage();
        }
        catch (NoEnoughBudgetException e) {
            logMessage = e.getMessage();
        }

        staff.endTurn();
        return logMessage;
    }

    public GameMap getMap() {
        return gameMap;
    }

    public boolean isGameOver() {

        for(Player player: gameMap.getPlayers()) {
            // winning condition, end the game
            if (player.getCity().getActiveCases() == 0
                    && player.getCity().getNumNewCases() ==0) {
                return true;
            }

            // failing condition, end the game too
            if (player.getCity().getActiveCases() >= player.getCity().getPopulation()) {
                return true;
            }
        }

        return false;
    }
}
