package pa1.exceptions;

import pa1.Player;

/**
 * Exception thrown when player does not have enough budget to afford a cost
 */
public class BudgetRunOutException extends Exception {

    private final Player player;
    /**
     * Initializes member variables
     *
     * @param player
     */
    public BudgetRunOutException(Player player) {
        this.player = player;
    }

    /**
     * @return an error message in the form:
     * "run out of budget %d budget"
     */
    @Override
    public String getMessage() {
        return String.format("run out of budget %d ", player.getBudget());
    }

    @Override
    public String toString() {
        return String.format("BudgetRunOutException for player %s", player.getName());
    }
}
