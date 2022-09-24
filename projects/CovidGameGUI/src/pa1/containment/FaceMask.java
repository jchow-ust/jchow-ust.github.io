package pa1.containment;

public class FaceMask extends Containment {

    public FaceMask() {
        super();
        this.name = "Facemask";
    }

    public int getProtection_level() {
        return protection_level;
    }

    @Override
    public String toString() {
        return name +", protection level=" + protection_level+"\n";
    }
}
