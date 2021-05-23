import javax.swing.*;
import java.awt.*;

public class Rgb565DisplayGui extends Canvas {

    // pixel count *2 for the rgb565 format
    public byte[] displayData = new byte[320*240*2];

    public Rgb565DisplayGui() {
        super();
        JFrame frame = new JFrame("Image view");
        this.setSize(320, 240);
        frame.add(this);
        frame.pack();
        frame.setVisible(true);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        for(int i = 0; i < displayData.length; i+=2) {
            PixelColor color = new PixelColor(displayData[i], displayData[i+1]);
            g.setColor(color.toAwt());

            int halfI = i >> 1;
            g.drawRect(
                    halfI % 320,
                    halfI / 320,
                    1,
                    1
            );
        }
    }
}
