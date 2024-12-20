import java.awt.Color;

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdRandom;

/**
 * The {@code Particle} class represents a particle moving in the unit box,
 * with a given position, velocity, radius, and mass. Methods are provided
 * for moving the particle and for predicting and resolving elastic
 * collisions with vertical walls, horizontal walls, and other particles.
 * This data type is mutable because the position and velocity change.
 * <p>
 * For additional documentation,
 * see <a href="https://algs4.cs.princeton.edu/61event">Section 6.1</a> of
 * <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 * @author Robert Sedgewick
 * @author Kevin Wayne
 */
public class Particle {
    private static final double INFINITY = Double.POSITIVE_INFINITY;

    private double rx, ry;       // position
    private double vx, vy;       // velocity
    private final double radius; // radius
    private final double mass;   // mass
    private int count;           // number of collisions
    private final Color color;   // color

    /**
     * Initializes a particle with the specified position, velocity, radius, mass, and color.
     *
     * @param rx     <em>x</em>-coordinate of position
     * @param ry     <em>y</em>-coordinate of position
     * @param vx     <em>x</em>-coordinate of velocity
     * @param vy     <em>y</em>-coordinate of velocity
     * @param radius the radius
     * @param mass   the mass
     * @param color  the color
     */
    public Particle(double rx, double ry, double vx, double vy, double radius, double mass, Color color) {
        this.vx     = vx;
        this.vy     = vy;
        this.rx     = rx;
        this.ry     = ry;
        this.radius = radius;
        this.mass   = mass;
        this.color  = color;
    }

    /**
     * Initializes a particle with a random position and velocity.
     * The position is uniform in the unit box; the velocity in
     * either direction is chosen uniformly at random.
     */
    public Particle() {
        rx     = StdRandom.uniformDouble(0.0, 1.0);
        ry     = StdRandom.uniformDouble(0.0, 1.0);
        vx     = StdRandom.uniformDouble(-0.005, 0.005);
        vy     = StdRandom.uniformDouble(-0.005, 0.005);
        radius = 0.02;
        mass   = 0.5;
        color  = Color.BLACK;
    }

    /**
     * Moves this particle in a straight line (based on its velocity)
     * for the specified amount of time.
     *
     * @param dt the amount of time
     */
    public void move(double dt) {
        rx = rx + vx * dt;
        ry = ry + vy * dt;
    }

    /**
     * Draws this particle to standard draw.
     */
    public void draw() {
        StdDraw.setPenColor(color);
        StdDraw.filledCircle(rx, ry, radius);
    }

    /**
     * Returns the number of collisions involving this particle with
     * vertical walls, horizontal walls, or other particles.
     * This is equal to the number of calls to {@link #bounceOff},
     * {@link #bounceOffVerticalWall}, and
     * {@link #bounceOffHorizontalWall}.
     *
     * @return the number of collisions involving this particle with
     * vertical walls, horizontal walls, or other particles
     */
    public int count() {
        return count;
    }

    public double timeToHit(Particle that) {
        if (this == that) return INFINITY;
        double dx = that.rx - this.rx;
        double dy = that.ry - this.ry;
        double dvx = that.vx - this.vx;
        double dvy = that.vy - this.vy;
        double dvdr = dx * dvx + dy * dvy;
        if (dvdr > 0) return INFINITY;
        double dvdv = dvx * dvx + dvy * dvy;
        double drdr = dx * dx + dy * dy;
        double sigma = this.radius + that.radius;
        double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
        if (d < 0) return INFINITY;
        return -(dvdr + Math.sqrt(d)) / dvdv;
    }

    public double timeToHitVerticalWall() {
        if (vx > 0) return (1.0 - rx - radius) / vx;
        if (vx < 0) return (radius - rx) / vx;
        return INFINITY;
    }

    public double timeToHitHorizontalWall() {
        if (vy > 0) return (1.0 - ry - radius) / vy;
        if (vy < 0) return (radius - ry) / vy;
        return INFINITY;
    }

    /**
     * Updates the velocities of this particle and the specified particle according
     * to the laws of elastic collision. Assumes that the particles are colliding
     * at this instant.
     *
     * @param that the other particle
     */
    public void bounceOff(Particle that) {
        double dx = that.rx - this.rx, dy = that.ry - this.ry;
        double dvx = that.vx - this.vx, dvy = that.vy - this.vy;
        double dvdr = dx * dvx + dy * dvy;       // dv dot dr
        double dist = this.radius + that.radius; // distance between particle centers at collision

        // magnitude of normal force
        double J = 2 * this.mass * that.mass * dvdr / ((this.mass + that.mass) * dist);

        // normal force, and in x and y directions
        double Jx = J * dx / dist;
        double Jy = J * dy / dist;

        // update velocities according to normal force
        this.vx += Jx / this.mass;
        this.vy += Jy / this.mass;
        that.vx -= Jx / that.mass;
        that.vy -= Jy / that.mass;

        // update collision counts
        this.count++;
        that.count++;
    }

    /**
     * Updates the velocity of this particle upon collision with a vertical
     * wall (by reflecting the velocity in the <em>x</em>-direction).
     * Assumes that the particle is colliding with a vertical wall at this instant.
     */
    public void bounceOffVerticalWall() {
        vx = -vx;
        this.count++;
    }

    /**
     * Updates the velocity of this particle upon collision with a horizontal
     * wall (by reflecting the velocity in the <em>y</em>-direction).
     * Assumes that the particle is colliding with a horizontal wall at this instant.
     */
    public void bounceOffHorizontalWall() {
        vy = -vy;
        this.count++;
    }
}
