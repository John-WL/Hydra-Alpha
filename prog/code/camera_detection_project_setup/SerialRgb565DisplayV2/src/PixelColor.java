import java.awt.*;

public class PixelColor {

    public double r;
    public double g;
    public double b;

    public PixelColor(double r, double g, double b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    public PixelColor(int rgb565) {
        r = (rgb565 & 0b1111100000000000) >> 8;
        g = (rgb565 & 0b11111100000) >> 3;
        b = (rgb565 & 0b11111) << 3;
    }

    public PixelColor(byte rgb565Msb, byte rgb565Lsb) {
        this(
            ((rgb565Msb > 0 ? (int)rgb565Msb : ((int)rgb565Msb) + 256) << 8)
                  | (rgb565Lsb > 0 ? (int)rgb565Lsb : ((int)rgb565Lsb) + 256)
        );
    }

    public double computeDistance(PixelColor other) {
        return Math.sqrt(
            square(this.r - other.r)
            + square(this.g - other.g)
            + square(this.b - other.b));
    }

    private double square(double x) {
        return x*x;
    }

    public long toRgb565() {
        return (((long)r >> 3) << 11) | (((long)g >> 2) << 5) | ((long)b >> 3);
    }

    public Color toAwt() {
        return new Color((int)r, (int)g, (int)b);
    }
}
