public class PixelColor {

    public double r;
    public double g;
    public double b;

    public PixelColor(double r, double g, double b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    public PixelColor(long rgb565) {
        r = (rgb565 & 0b1111100000000000) >> 8;
        g = (rgb565 & 0b11111100000) >> 3;
        b = rgb565 & 0b11111;
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

}
