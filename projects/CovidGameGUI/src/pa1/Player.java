package pa1;

import gui.GameApplication;
import javafx.scene.image.Image;
import pa1.containment.*;
import pa1.exceptions.MedicalException;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.util.Constants;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * A class that represents a player in the game.
 * It contains the player's attribute such as budget and points,
 * as well as the player's assets such as ministers, cities, and virus containment techniques.
 */
public class Player {

    // Assets
    private final List<HealthAuthorityStaff> haStaffs = new ArrayList<>();
    private final List<Containment> containTechniques = new ArrayList<>();

    // Attributes
    private final String name;
    private int budget;
    private int tourismIncome;
    private int points;
    private boolean isHuman;

    private City city;

    /**
     * Initializes member variables.
     * @param name
     * @param budget
     * @param tourismIncome
     * @param points
     */
    public Player(String name, int budget, int tourismIncome, int points, boolean isHuman) {
        this.name = name;
        this.budget = budget;
        this.tourismIncome = tourismIncome;
        this.points = points;
        this.isHuman = isHuman;
    }

    @Override
    public String toString() {
        String toStr = String.format("Player: %s | budget: %d | tourism income: %d | points: %d\n",
                name, budget, tourismIncome, points);
        toStr += city.toString() +"\n";

        String contNames = "";
        int protection_level = 0;
        int vaccination_level = 0;
        int medication_level = 0;
        for (Containment cont:containTechniques) {
                contNames += cont.getName() +",";
            if (cont instanceof FaceMask || cont instanceof Isolation) {
                protection_level += cont.getProtection_level();
            }else if (cont instanceof Vaccination) {
                vaccination_level = cont.getVaccination_level();
            } else if (cont instanceof Treatment) {
                medication_level = cont.getMedication_level();
            }
        }
        toStr += String.format("Health Authority Staff:\n");
        for (HealthAuthorityStaff healthAuthorityStaff :  getHAStaffs()) {
            toStr += String.format("\t %s \n", healthAuthorityStaff);
        }

        toStr += String.format("Containment : %s | protection level: %d | vaccination level: %d | medication level: %d ",
                contNames, protection_level, vaccination_level, medication_level);

        return toStr;
    }

    /**
     * Decreases the player's budget by amount
     * Cap the value to 0.
     *
     * @param decrement
     */
    public void decreaseBudget(int decrement) {

        budget = Math.max(0, budget - decrement);
    }

    /**
     * Increase the player's budget by amount
     *
     * @param increment
     */
    public void increaseBudget(int increment) {
        if (increment > 0)
            budget += increment;
    }



    /**
     * Adds player's points by specified increment.
     *
     * @param increment
     */
    public void addPoints(int increment) {

        if (increment > 0)
           points += increment;
    }

    /**
     * Decreases the player's points by specified decrement.
     *
     * @param decrement
     */
    public void decreasePoints(int decrement) {

        points = Math.max(0, points - decrement);
    }

    /**
     * @return true if the player has at least one ready HAStaff
     */
    public boolean hasReadyHAStaff() {
        for (HealthAuthorityStaff haStaff: getHAStaffs()) {
            if(haStaff.isReady())
                return true;
        }
        return false;
    }

    /**
     * Compute new infected cases and updated total infected cases
     *
     * 1. get current protection and vaccination level
     * 2. compute: IF = .5*(100-protection level) + .5*(100-vaccination level)
     * 3. define a factor called spreadRate  = 1
     * 4.  if there is no protection at all:
     *      set spreadRate to 3, i.e., on average an active patient can pass the virus to 3 more people)
     * 5. compute: new infected cases = spreadRate * IF * infectedCases * population
     * 6. add new cases to city's total infected cases
     * @throws MedicalException
     */
    public void computeNewInfectedCases() throws MedicalException {
        // do not change the two lines below!
        int currProtectionLevel = 0;
        int currVaccinationLevel = 0;

        for (Containment contTech: containTechniques) {
            if (contTech instanceof Isolation || contTech instanceof FaceMask)
                currProtectionLevel += contTech.getProtection_level();
            else if (contTech instanceof Vaccination)
                currVaccinationLevel = contTech.getVaccination_level();
        }

        // don not change the lines below!
        double increaseFactor = 0.5 * (Constants.MAX_LEVEL - currProtectionLevel)/Constants.MAX_LEVEL + 0.5 * (Constants.MAX_LEVEL - currVaccinationLevel)/Constants.MAX_LEVEL;
        //If there is no protection measures were applied, set spread rate to 3
        double spreadRate= 3.0*increaseFactor;

        int newInfectedCases =(int) Math.ceil(spreadRate * increaseFactor * city.getActiveCases() );

        // memorize the new cases of the previous round, so that we can calculate the difference in new cases for 2 consecutive rounds
        // this is not present in the labs.
        city.setNumFormerCases(city.getNumNewCases());


        city.setNumNewCases(newInfectedCases);

        // the following method will throw MedicalException if the total active cases is the same as population of the city
        city.increaseActiveCases(newInfectedCases);
    }

    /**
     * Unpredicted disasters at the end of turn.
     * There are three types of disasters, that affect both protection level, vaccination_level, and medical level.
     * A disaster happens when disasterOccured <= 0.4, it halves the level.
     * Otherwise the level is left unchanged
     * disasterType [0: Fake face masks, 1: drop vaccination efficiency, 3: destruction of medication facility]
     *
     * 1. pick two random variables, one to select disasterType, and another to select disasterOccured propoability
     * 2. if there is disasterOccured:
     *      2.1. switch case 0: halve the protection level
     *      2.2.             1: halve the vaccination level
     *      2.3.             2. decrease the medication facility
     */
    public String generateUnexpectedDisasters() {
        String result = "";

        // Do not change the lines below!
        Random rand = new Random();
        int disasterType = rand.nextInt(3);
        boolean disasterOccured = rand.nextDouble() <= 0.4;

        if (disasterOccured){
            switch (disasterType) {
                case 0:
                    for (Containment cont:containTechniques) {
                        if (cont instanceof FaceMask) {
                            halfProtection_level();
                            result = "Disaster: Fake face masks that halves the protection\n";
                            break;
                        }
                    }
                    break;
                case 1:
                    for (Containment cont:containTechniques) {
                        if (cont instanceof Vaccination) {
                            halfVaccination_level();
                            result = "Disaster: Weather/physical changes that halves the vaccination efficiency\n";
                            break;
                        }
                    }
                    break;
                case 2:
                    city.decreaseMedicationFacility();
                    result = "Disaster: One medication facility is out of service\n";
                    break;
            }
        }
        return result;
    }


    /**
     * Adds a containment technique.
     *
     * @param cont
     */
    public void addContainmentTech(Containment cont) {
        containTechniques.add(cont);
    }

    /**
     * Removes a containment technique.
     *
     * @param cont
     */
    public void removeContainmentTech(Containment cont) {
        containTechniques.remove(cont);
    }

    public void setCity(City city) {
        this.city = city;
    }

    /**
     * Increment protection level.
     * 1. if cont in the containment techniques, increase the protection level by inLevel and set upperbound to 100
     *
     * @param inLevel
     * @param cont
     */
    public void incrementProtection_level(int inLevel, Containment cont ) {
        if (containTechniques.contains(cont)) {
            int index = containTechniques.indexOf(cont);
            int newProtectionLevel =  Math.min(100, cont.getProtection_level() + inLevel);
            containTechniques.get(index).setProtection_level(newProtectionLevel);
        }
    }

    /**
     * halve the protection level.
     * 1. if FaceMask is in the containment techniques, halve the protection level
     *
     */
    public void halfProtection_level() {
        for (Containment cont:containTechniques) {
            if (cont instanceof FaceMask) {
                int newValue = (int) Math.ceil(cont.getProtection_level() * 0.5f);
                cont.setProtection_level(newValue);
            }
        }
    }

    /**
     * Increment vaccination level.
     * 1. if cont in the containment techniques, increase the vaccination level by inLevel  and set upperbound to 100
     * @param inLevel
     * @param cont
     */
    public void incrementVaccination_level(int inLevel, Containment cont) {
        if (containTechniques.contains(cont)) {
            int index = containTechniques.indexOf(cont);
            int newVaccLevel =  Math.min(100, cont.getVaccination_level() + inLevel);
            containTechniques.get(index).setVaccination_level(newVaccLevel);
        }
    }

    /**
     * halve the vaccination level.
     * 1. if Vaccination is in the containment techniques, halve the vaccination level
     *
     */
    public void halfVaccination_level() {
        for (Containment cont:containTechniques) {
            if (cont instanceof Vaccination) {
                int newValue = (int) Math.ceil(cont.getVaccination_level() * 0.5f);
                cont.setVaccination_level(newValue);
            }
        }
    }

    // Trivial getters
    public List<HealthAuthorityStaff> getHAStaffs() {
        return haStaffs;
    }

    public City getCity() {
        return city;
    }

    public List<Containment> getContainTechniques() {
        return containTechniques;
    }

    public String getName() {
        return name;
    }

    public int getBudget() {
        return budget;
    }

    public int getTourismIncome() {
        return tourismIncome;
    }

    public int getPoints() {
        return points;
    }

    public boolean isHuman() {
        return isHuman;
    }

    public Image getMedicationFacilityImage(int width, int height) {
        /**
         * Procided code, task being done here: get image of medication facility  for different medication levels levels
         * 1. get medication facility level by checking the getMedication_level of Treatment Containment
         * 2. Instantiate Image by using "hospital-#.png" according to different level
         *     - hospital-1.png for level < 20
         *     - hospital-2.png for level < 50
         *     - hospital-3.png for level < 80
         *     - hospital-4.png otherwise
         * 3. return the Image object we get
         */
        int level = getMedicationLevel();

        if (level < 20)
            return new Image("hospital-1.png", width, height, false, true);
        else if (level < 50)
            return new Image("hospital-2.png", width, height, false, true);
        else if (level < 80)
            return new Image("hospital-3.png", width, height, false, true);
        else
            return new Image("hospital-4.png", width, height, false, true);
    }

    public int getMedicationLevel() {
        int level = 0;
        for (Containment cont : containTechniques) {
            if (cont instanceof Treatment) {
                level = cont.getMedication_level();
            }
        }
        return level;
    }

    public Image getFaceMaskFactoryImage(int width, int height) {
        /**
         * TODO get image of face mask factory for different Mask protection levels
         * step 1. get mask protection level by running the getMaskProtectionLevel() method
         *
         * step 2. Instantiate Image by using "mask-#.png" according to different level
         *     - mask-1.png for level < 20
         *     - mask-2.png for level < 50
         *     - mask-3.png for level < 80
         *     - mask-4.png otherwise
         *     display the image width and height according to the supplied arguments: "width" and "height"
         *     display the image without requiring it to keep width/height ratio, but we do need the image to be shown
         *     using a better quality smooth filtering algorithm, as that will make the png look nicer.
         *     You can do that using "mask-1.png" like the following
         *
         *     new Image("mask-1.png", width, height, false, true)",
         *     refer to https://openjfx.io/javadoc/16/javafx.graphics/javafx/scene/image/Image.html#%3Cinit%3E(java.lang.String,double,double,boolean,boolean)
         *
         *
         * step 3. return the Image object we get
         *
         * hint: refer to the above getMedicationFacilityImage() method for hints on how this method could be implemented
         */
        int maskLvl = getMaskProtectionLevel();
        if (maskLvl<20){
            return new Image("mask-1.png", width, height, false, true);
        }
        else if (maskLvl<50){
            return new Image("mask-2.png", width, height, false, true);
        }
        else if (maskLvl<80){
            return new Image("mask-3.png", width, height, false, true);
        }
        else{
            return new Image("mask-4.png", width, height, false, true);
        }
    }

    public int getMaskProtectionLevel() {
        int level = 0;
        for (Containment cont : containTechniques) {
            if (cont instanceof FaceMask) {
                level = cont.getProtection_level();
            }
        }
        return level;
    }

    public Image getVaccineFactoryImage(int width, int height) {

        /**
         * TODO get image of vaccination factory for different vaccination levels
         * step 1. get mask vaccination level by running the getVaccineLevel() method
         *
         * step 2. Instantiate Image by using "vaccine-#.png" according to different level
         *     - vaccine-1.png for level < 20
         *     - vaccine-2.png for level < 50
         *     - vaccine-3.png for level < 80
         *     - vaccine-4.png otherwise
         *
         *     display the image width and height according to the supplied arguments: "width" and "height"
         *     display the image without requiring it to keep width/height ratio, but we do need the image to be shown
         *     using a better quality smooth filtering algorithm, as that will make the png look nicer.
         *
         * step 3. return the Image object we get
         *
         * hint: refer to the above getMedicationFacilityImage() method for hints on how this method could be implemented
         */
        int vacLvl = getVaccineLevel();
        if (vacLvl<20){
            return new Image("vaccine-1.png", width, height, false, true);
        }
        else if (vacLvl<50){
            return new Image("vaccine-2.png", width, height, false, true);
        }
        else if (vacLvl<80){
            return new Image("vaccine-3.png", width, height, false, true);
        }
        else{
            return new Image("vaccine-4.png", width, height, false, true);
        }

    }

    public int getVaccineLevel() {
        int level = 0;
        for (Containment cont : containTechniques) {
            if (cont instanceof Vaccination) {
                level = cont.getVaccination_level();
            }
        }
        return level;
    }

    public void updateStatusAfterTurn() throws MedicalException {
        /**
         * TODO update tourism income and new infected cases for current player
         *
         * step 1. If travel is not banned in the city, increase budget of player by amount returned by the
         *    getTourismIncome() method. You may find get the getcity(), isTravelBanned() and  increaseBudget() useful
         * step 2. Compute new infected cases by calling computeNewInfectedCases()
         */
        if (!(getCity().isTravelBanned())){
            increaseBudget(getTourismIncome());
        }
        computeNewInfectedCases();
    }
}
