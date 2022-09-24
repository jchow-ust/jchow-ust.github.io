package pa1.HAstaff;


import pa1.City;
import pa1.Player;
import pa1.containment.*;
import pa1.exceptions.BudgetRunOutException;
import pa1.exceptions.NoEnoughBudgetException;
import pa1.util.Constants;

/**
 * An abstract class that represents a health authority staff (haStaffs) in the game.
 * All actions in the game are done through haStaffs.
 * Therefore this class will contain the implementations of the actions to take in order to contain COVID in the game.
 */
public abstract class HealthAuthorityStaff {

    // Attributes
    protected final int leadership, medicine, experience;
    private boolean isReady = false;

    /**
     * Initializes the attributes of a HAstaff
     * @param leadership
     * @param medicine
     * @param experience
     */
    public HealthAuthorityStaff(int leadership, int medicine, int experience) {
        this.leadership = leadership;
        this.medicine = medicine;
        this.experience = experience;
    }

    /**
     * @return Whether or not the minister is ready
     */
    public boolean isReady() {
        return isReady;
    }

    /**
     * Changes isReady to true
     */
    public void beginTurn() {
        isReady = true;
    }

    /**
     * Changes isReady to false
     */
    public void endTurn() {
        isReady = false;
    }

    protected int getBonusPoints(){
        return 0;
    }

    /**
     * Develop a medication facility in the city
     * 1. Get the cost of developing a facility
     * 2. if the player doesn't have enough budget, throw an exception
     *    otherwise:
     * 3. decrease the player's budget by the cost
     * 4. Increment the city's medication facilities by one
     * 5. set medication level to: recovered * 100/ (active + recovered)
     * <p>
     * HINT:
     *  define a class of constant final variable to include the costs, percentages, ..etc
     * @param player
     * @param city
     * @throws NoEnoughBudgetException
     * @throws BudgetRunOutException
     */
    public void developMedicationFacility(Player player, City city) throws NoEnoughBudgetException, BudgetRunOutException {
        if (player.getBudget()<Constants.MIN_ALLOWED_BUDGET)
            throw new BudgetRunOutException(player);

        //update the player's budget if can afford the action
        int facilityCost = Constants.MEDICATION_FACILITY_COST;
        boolean cantDevelopFacility = facilityCost > player.getBudget();
        if (cantDevelopFacility) throw new NoEnoughBudgetException(player, facilityCost);
        player.decreaseBudget(facilityCost);
        city.addMedicationFacilities();
        city.decreaseActiveCases(Constants.MEDICATION_FACILITY_CAPACITY );

        //Add Treatment to the player's containment techniques
        boolean alreadyExists = false;
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Treatment){
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists){
            Treatment treat = new Treatment();
            player.addContainmentTech(treat);
        }

        //update medication level: medication level = #med facilities * capacity * 100/ #recovered cases
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Treatment) {
                int index = player.getContainTechniques().indexOf(cont);
                player.getContainTechniques().get(index).setMedication_level((city.getRecoveredCases() * 100) / (city.getActiveCases() + city.getRecoveredCases()));
            }
        }

    }


    /**
     * Build a mask factory in the city
     * 1. Get the cost of building masks factory
     * 2. if the player doesn't have enough budget, throw an exception
     *      otherwise:
     * 3. decrease the player's budget according to the cost
     * 4. if not exists, add facemasks to the player's containment techniques
     * 5. increment the protection level by Constants.MASK_PROTECTION_Percentage
     * @param player
     * @param city
     * @throws NoEnoughBudgetException
     * @throws BudgetRunOutException
     */
    public void buildMasksFactory(Player player, City city) throws NoEnoughBudgetException, BudgetRunOutException {
        if (player.getBudget()<Constants.MIN_ALLOWED_BUDGET)
            throw new BudgetRunOutException(player);

        //update the player's budget if can afford the action
        int maskFactoryCost = Constants.BUILD_MASK_FACTORY_COST;
        boolean cantBuildMedFactory = maskFactoryCost > player.getBudget();
        if (cantBuildMedFactory) throw new NoEnoughBudgetException(player, maskFactoryCost);

        player.decreaseBudget(maskFactoryCost);

        //Add Facemasks to the player's containment techniques
        boolean alreadyExists = false;
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof FaceMask){
                alreadyExists = true;
            }
        }

        if (!alreadyExists){
            FaceMask fmask = new FaceMask();
            player.addContainmentTech(fmask);
        }

        //increment the protection level
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof FaceMask){
                player.incrementProtection_level(Constants.MASK_PROTECTION_Percentage,cont);
            }
        }

    }

    /**
     * upgrade quality of face masks
     * 1. Get the cost of upgrading mask quality
     * 2. if the player doesn't have enough budget, throw an exception
     *          otherwise:
     * 3. decrease budget according to the cost
     * 4. if exists, increment the protection level by Constants.UPGRADE_MASK_PROTECTION_Percentage
     * @param player
     * @param city
     * @throws NoEnoughBudgetException
     * @throws BudgetRunOutException
     */
    public void upgradeFMaskQuality(Player player, City city) throws NoEnoughBudgetException, BudgetRunOutException {
        if (player.getBudget()<Constants.MIN_ALLOWED_BUDGET)
            throw new BudgetRunOutException(player);

        //update the player's budget if can afford the action
        int upgradeMaskQualityCost = Constants.UPGRADE_MASK_QUALITY_COST;
        boolean cantUpgradeMaskQuality = upgradeMaskQualityCost > player.getBudget();
        if (cantUpgradeMaskQuality) throw new NoEnoughBudgetException(player, upgradeMaskQualityCost);
        player.decreaseBudget(upgradeMaskQualityCost);

        //increment the protection level
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof FaceMask){
                player.incrementProtection_level(Constants.UPGRADE_MASK_PROTECTION_Percentage,cont);
            }
        }
    }

    /**
     * Develop a Vaccine
     * 1. Get the cost of developing the vaccine
     * 2. if the player doesn't have enough budget, throw an exception
     *          otherwise:
     * 3. decrease budget according to upgrade cost
     * 4. if exists, increase the vaccination level by Constants.DEVELOP_VACCINE_Percentage
     * @param player
     * @param city
     * @throws NoEnoughBudgetException
     * @throws BudgetRunOutException
     */
    public void developVaccine(Player player, City city) throws NoEnoughBudgetException, BudgetRunOutException {
        if (player.getBudget()<Constants.MIN_ALLOWED_BUDGET)
            throw new BudgetRunOutException(player);

        //update the player's budget if can afford the action
        int developVaccineCost = Constants.DEVELOP_VACCINE_COST;
        boolean cantDevelopVaccine = developVaccineCost > player.getBudget();
        if (cantDevelopVaccine) throw new NoEnoughBudgetException(player, developVaccineCost);
        player.decreaseBudget(developVaccineCost);

        //Add Vaccination to the player's containment techniques
        boolean alreadyExists = false;
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Vaccination){
                alreadyExists = true;
            }
        }

        if (!alreadyExists){
            Vaccination vacc = new Vaccination();
            player.addContainmentTech(vacc);
        }

        //update vaccination level
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Vaccination){
                player.incrementVaccination_level(Constants.DEVELOP_VACCINE_Percentage,cont);
            }
        }

    }

    /**
     * Upgrade a Vaccine
     * 1. Get the cost of upgrading the vaccine
     * 2. if the player doesn't have enough budget, throw an exception
     *          otherwise:
     * 3. decrease budget according to upgrade cost by Constants.UPGRADE_VACCINE_Percentage
     * @param player
     * @param city
     * @throws NoEnoughBudgetException
     * @throws BudgetRunOutException
     */
    public void upgradeVaccine(Player player, City city) throws NoEnoughBudgetException, BudgetRunOutException {
        if (player.getBudget()<Constants.MIN_ALLOWED_BUDGET)
            throw new BudgetRunOutException(player);

        //update the player's budget if can afford the action
        int upgradeVaccineCost = Constants.UPGRADE_VACCINE_COST;
        boolean cantUpgradeVaccine = upgradeVaccineCost > player.getBudget();
        if (cantUpgradeVaccine) throw new NoEnoughBudgetException(player, upgradeVaccineCost);
        player.decreaseBudget(upgradeVaccineCost);

        //increment the vaccination level
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Vaccination){
                player.incrementVaccination_level(Constants.UPGRADE_VACCINE_Percentage,cont);
            }
        }
    }

    /**
     * Ban Travel
     * 1. set city's travelBanned to true
     * 2. if doesn't, add Isolation to the player's containment techniques
     * 3. if exists, increment the protection level by Constants.TRAVELBAN_PROTECTION_Percentage
     * @param player
     * @param city
     */
    public void banTravel(Player player, City city) {
        city.setTravelBanned(true);

        //add Isolation to the player's containment techniques
        boolean alreadyExists = false;
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Isolation){
                alreadyExists = true;
            }
        }

        if (!alreadyExists){
            Isolation iso = new Isolation();
            player.addContainmentTech(iso);
        }

        //increment the protection level
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Isolation){
                player.incrementProtection_level(Constants.TRAVELBAN_PROTECTION_Percentage, cont);
            }
        }
    }


    /**
     * Lift the travel ban
     * 1. set city's travelBanned to false
     * 2. if exists, remove Isolation from player's containment techniques
     * @param player
     * @param city
     */
    public void liftTravelBan(Player player, City city) {
        Isolation isoToBeRemoved=null;
        city.setTravelBanned(false);

        //remove Isolation from the player's containment techniques
        for (Containment cont:player.getContainTechniques()) {
            if (cont instanceof Isolation){
                isoToBeRemoved=(Isolation)cont;
            }
        }
        if (isoToBeRemoved!=null){player.removeContainmentTech(isoToBeRemoved);}

    }

    /**
     * Example string representation:
     * "HAStaff | READY, leadership, medicine, experience" - when isReady() == true
     * "HAStaff | DONE, leadership, medicine, experience" - when isReady() == false
     *
     * @return string representation of this object
     */
    @Override
    public String toString() {

        String toStr = String.format("HAStaff | %s, leadership %d, medicine %d, experience %d", isReady() ? "READY" : "DONE",leadership, medicine, experience);
        return toStr;
    }

    public String getName() {
        return "HealthAuthorityStaff";
    }

    public int getLeadership() {
        return leadership;
    }

    public int getMedicine() {
        return medicine;
    }

    public int getExperience() {
        return experience;
    }
}

