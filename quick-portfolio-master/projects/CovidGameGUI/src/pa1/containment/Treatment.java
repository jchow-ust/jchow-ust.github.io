package pa1.containment;

public class Treatment extends Containment {

    public Treatment() {
        super();
        this.name = "Treatment";
    }

    @Override
    public int getMedication_level() {
        return medication_level;
    }

    @Override
    public String toString() {
        return name +", medication level=" + medication_level + "\n";
    }
}
