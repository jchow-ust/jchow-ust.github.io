package pa1.containment;

public class Isolation extends Containment {

    public Isolation() {
        super();
        this.name = "Isolation";
    }

    @Override
    public int getProtection_level() {
        return protection_level;
    }

    @Override
    public String toString() {
        return name +", protection level=" + protection_level + "\n";
    }
}
