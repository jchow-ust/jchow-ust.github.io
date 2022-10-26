package pa1;

import javafx.scene.image.Image;
import pa1.exceptions.MedicalException;

import java.util.ArrayList;
import java.util.List;

/**
 * A class that represents a city of interest
 */
public class City {


    // Metadata
    private final int id;
    private final String name;

    // Attributes
    private int population;
    private boolean travelBanned;
    private int activeCases;
    private int recoveredCases;
    private int numNewCases;
    private int numFormerCases;

    // Improvements
    private int medicationFacilities;

    /**
     *  Initializes member variables.
     *
     * @param id
     * @param name
     * @param population
     * @param travelBanned
     * @param activeCases
     * @param recoveredCases
     */
    public City(int id, String name, int population,boolean travelBanned, int activeCases, int recoveredCases) {
        this.id = id;
        this.name = name;
        this.population = population;
        this.travelBanned = travelBanned;
        this.activeCases = activeCases;
        this.recoveredCases = recoveredCases;
    }

    public int getId() {
        return id;
    }

    /**
     * Adds number of medicationFacillities (hospitals) by one
     */
    public void addMedicationFacilities() {
        medicationFacilities++;
    }

    /**
     * set Medication Facility Out Of Service
     * 1. decrement facilities by 1
     */
    public void decreaseMedicationFacility() {
        if(medicationFacilities > 0)
            medicationFacilities--;
    }

    /**
     * Increases number of active cases by the amount specified
     *
     * 1. if the increment amount is positive
     * 1.1.  - if increase operation leads to active cases >= population
     *              - increment and limit the upperbound active cases to population
     *              - throw medical exception
     * 1.2. otherwise:
     *      - increase by increment amount
     *
     * @param increment
     * @throws MedicalException
     */
    public void increaseActiveCases(int increment) throws MedicalException {
        if (increment > 0) {
            if (activeCases + increment >= population) {
                activeCases = Math.min(population, activeCases + increment);
                throw new MedicalException(population, activeCases);
            } else
                activeCases += increment;
        }
    }

    /**
     * Decrease number of active cases and increase recovered cases by the amount specified
     *
     * 1. check if the decrement amount is positive
     *  1.1. decrease the active cases and limit the lowerbound to 0
     *  1.1. increase the recovered cases and limit the upperbound to population
     *
     * @param decrement
     */
    public void decreaseActiveCases(int decrement) {
        if (decrement > 0){
            int oldCases = activeCases;
            activeCases = Math.max(0, activeCases - decrement);
            recoveredCases = Math.min(population, recoveredCases + oldCases - activeCases);
        }
    }

    /**
     * set banTravel to a value
     * @param val
     */
    public void setTravelBanned(boolean val) {
        travelBanned = val;
    }

    public void setNumNewCases(int numNewCases) {
        this.numNewCases = numNewCases;
    }

    public void setNumFormerCases(int numFormerCases) {
        this.numFormerCases = numFormerCases;
    }

    public int getNumNewCases() {
        return numNewCases;
    }

    public String getName() {
        return name;
    }

    public int getPopulation() {
        return population;
    }

    public boolean isTravelBanned() {
        return travelBanned;
    }

    public int getActiveCases() {
        return activeCases;
    }

    public int getRecoveredCases() {
        return recoveredCases;
    }

    public int getMedicationFacilities() {
        return medicationFacilities;
    }

    public boolean isNewCasesIncreasing(){
        if(numNewCases > numFormerCases)
            return true;
        else
            return false;
    }

    @Override
    public String toString() {
        String toStr = String.format("%s | activeCases %d | recoveredCases %d | newCases %d |  population: %d | # of medication facilities: %d",
                name, activeCases, recoveredCases, numNewCases , population, medicationFacilities);
        return toStr;
    }

    /**
     * Return the image to represent this City
     * The
     *
     * @return
     */
    public Image getImage(int width, int height) {

        int size = medicationFacilities;
        if (size < 1)
            return new Image("city-small.png", width, height, false, true);
        else if (size < 2)
            return new Image("city-medium.png", width, height, false, true);
        else
            return new Image("city-large.png", width, height, false, true);
    }

    public String getDescription() {
        return String.format("[%s], ActiveCase: %s, Population: %s", getName(), getActiveCases(), getPopulation());
    }
}
