package gui;

import pa1.City;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.containment.Containment;

public interface GameActionHandler {
    void handle(int actionNum, HealthAuthorityStaff staff, City selected, Containment tech);
}
