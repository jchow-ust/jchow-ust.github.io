package pa1.exceptions;

/**
 * Exception thrown when player does not have enough budget to afford a cost
 */
public class MedicalException extends Exception {

    private final int population;
    private final int activeCases;

    /**
     * Initializes member variables
     *
     * @param population
     * @param activeCases
     */
    //
    // mote: 1. set population of this Exception object to be the same as the passed int population
    //       2. set activeCases of this Exception object to be the same as the passed int activeCases
    public MedicalException(int population, int activeCases) {
        this.population = population;
        this.activeCases = activeCases;
    }

    /**
     * Constructs an error message in the form:
     * Infected cases %d reached city's population %d
     * @return
     */
    @Override
    public String getMessage() {
        return String.format("activeCases cases %d reached city's population %d",
                activeCases, population);
    }

    @Override
    public String toString() {
        return String.format("MedicalException");
    }
}
