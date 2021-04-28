public class ArrayGenerator {

    public static void main(String[] args) {
        System.out.println("Creating memory space for calculations...");
        int[] values = new int[8192];
        System.out.println("Done.\n");

        System.out.println("Calculating entries...");
        for(int i = 0; i < 65536; i++) {
            int redAmount = i >> 11;
            int greenAmount = (i & 0b11111100000) >> 5;
            int blueAmount = i & 0b11111;

            if(compare(redAmount << 3, greenAmount << 2, blueAmount << 3)) {
                values[i >> 3] |= (1 << (blueAmount & 7));
            }
        }
        System.out.println("Done.\n");

        System.out.println("Exporting to file...");
        IOFile.safeCreateFileWithContent(
                "..\\..\\hydra_alpha_v1\\config\\CustomTankDetectionColorValidation.h",
                buildArrayAsString(values)
        );
    }

    public static final int RED_SELECTED_COLOR = 20;
    public static final int GREEN_SELECTED_COLOR = 75;
    public static final int BLUE_SELECTED_COLOR = 163;
    public static final PixelColor SELECTED_COLOR = new PixelColor(RED_SELECTED_COLOR, GREEN_SELECTED_COLOR, BLUE_SELECTED_COLOR);
    public static final double MAX_COLOR_DISTANCE_TO_BE_CONSIDERED_VALID = 20;

    public static boolean compare(double red, double green, double blue) {
        return new PixelColor(red, green, blue).computeDistance(SELECTED_COLOR)
                > MAX_COLOR_DISTANCE_TO_BE_CONSIDERED_VALID;
    }

    public static double square(double x) {
        return x*x;
    }

    public static String buildArrayAsString(int[] values) {
        StringBuilder stringBuilder = new StringBuilder();

        System.out.println("File generation starts...");

        stringBuilder.append("unsigned char byteColorValidationValues[8192] = {\n");
        stringBuilder.append("\t").append(values[0]);
        for(int i = 1; i < values.length; i++) {
            stringBuilder.append(",\n").append("\t").append(values[i]);
        }
        stringBuilder.append("\n};\n");
        stringBuilder.append("#define validateColor565(color) (byteColorValidationValues[color >> 3] & (1 << (color & 7)))\n");

        System.out.println("File generation ends.");
        return stringBuilder.toString();
    }

}
