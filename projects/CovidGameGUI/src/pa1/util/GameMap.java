package pa1.util;


import pa1.City;
import pa1.Player;
import pa1.Block;
import pa1.HAstaff.ChiefExecutiveOfHA;
import pa1.HAstaff.HealthAuthorityStaff;
import pa1.HAstaff.Epidemiologist;
import pa1.HAstaff.HealthMinister;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Holds the necessary components for running the game
 */
public class GameMap {
    private List<Player> players;
    private Map<Integer, Block> cityLocations;

    private int width;
    private int height;

    public GameMap() {
        players = new ArrayList<>();
        cityLocations = new HashMap<>();
    }

    /**
     * Loads map data from text file
     *
     * @param filename
     * @throws IOException
     */
    public void loadMap(String filename) throws IOException {
        cityLocations.clear();
        File file = new File(filename);
        try (Scanner sc = new Scanner(file)) {
            width = sc.nextInt();
            height = sc.nextInt();
            int numOfCities = sc.nextInt();
            for (int i = 0; i < numOfCities; ++i) {
                int cityId = sc.nextInt();
                String[] coordinates = sc.next().split(",");
                int x = Integer.parseInt(coordinates[0]);
                int y = Integer.parseInt(coordinates[1]);
                Block location = new Block(x, y);
                cityLocations.put(cityId, location);
            }
        }
    }

    /**
     * Loads player data from text file
     *
     * @param filename
     * @throws IOException
     */
    public void loadPlayers(String filename) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader(filename))) {
            int numPlayers = Integer.parseInt(in.readLine());
            in.readLine();

            players = new ArrayList<>();
            for (int i = 0; i < numPlayers; i++) {
                String[] tokens = in.readLine().split(" ");
                String playerName = tokens[0];
                int budget = Integer.parseInt(tokens[1]);
                int tourismIncome = Integer.parseInt(tokens[2]);
                int points = Integer.parseInt(tokens[3]);
                boolean isHuman = tokens[4].equals("Human");
                Player player = new Player(playerName, budget, tourismIncome, points, isHuman);
                tokens = in.readLine().split(" ");
                int cityId = Integer.parseInt(tokens[0]);
                String name = tokens[1];
                int population = Integer.parseInt(tokens[2]);
                int infectedCases = Integer.parseInt(tokens[3]);
                int recoverCases = Integer.parseInt(tokens[4]);

                City city = new City(cityId, name, population, false, infectedCases,recoverCases);
                player.setCity(city);

                for (int m = 0; m < 3; m++) { //numMinisters = 3
                    tokens = in.readLine().split(" ");
                    String type = tokens[0];
                    int leadership = Integer.parseInt(tokens[1]);
                    int medicine = Integer.parseInt(tokens[2]);
                    int experience = Integer.parseInt(tokens[3]);

                    HealthAuthorityStaff healthAuthorityStaff = null;
                    switch (type.toLowerCase()) {
                        case "healthminister":
                            healthAuthorityStaff = new HealthMinister(leadership,medicine,experience );
                            break;
                        case "chiefexecutive":
                            healthAuthorityStaff = new ChiefExecutiveOfHA(leadership,medicine,experience);
                            break;
                        case "epidemiologist":
                            healthAuthorityStaff = new Epidemiologist(leadership,medicine,experience);
                            break;
                        default:
                            break;
                    }

                    player.getHAStaffs().add(healthAuthorityStaff);
                }

                players.add(player);
                in.readLine();
            }
        }
    }

    public List<Player> getPlayers() {
        return players;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public Block getCityLocation(City city) {
        return cityLocations.getOrDefault(city.getId(), null);
    }
}
