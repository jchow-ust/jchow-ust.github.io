package pa1.containment;


public class Vaccination extends Containment {

    public Vaccination() {
        this.name = "Vaccination";
    }

    @Override
    public int getVaccination_level() {
        return vaccination_level;
    }

    @Override
    public String toString() {
        return name + ", vaccination level=" + vaccination_level + "\n";
    }
}
