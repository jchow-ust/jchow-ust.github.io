package pa1;


/**
 * An immutable class that represents a cell in the grid map
 */

public class Block {
    private int x;
    private int y;

    public Block(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Block block = (Block) o;
        return x == block.x && y == block.y;
    }
}
