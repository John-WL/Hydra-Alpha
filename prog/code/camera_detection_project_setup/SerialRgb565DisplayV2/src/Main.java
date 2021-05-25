import com.fazecast.jSerialComm.SerialPort;

public class Main {

    public static void main(String[] args)
    {
        Rgb565DisplayGui rgbDisplay = new Rgb565DisplayGui();

        SerialPort comPort = SerialPort.getCommPort("COM4");
        comPort.setBaudRate(115200);
        comPort.openPort();
        comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 20000, 0);

        comPort.writeBytes(new byte[]{'0', -128}, 2);

        try {
            while(true) {
                int numRead = comPort.readBytes(rgbDisplay.displayData, 153600);
                System.out.println("Read " + numRead + " bytes.");
                System.out.println(rgbDisplay.displayData[0]);
                //fillArray(rgbDisplay.displayData);

                rgbDisplay.repaint();
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        comPort.closePort();
    }

    static void fillArray(byte[] array) {
        PixelColor pixelColor = new PixelColor(0, 160, 255);
        for(int i = 0; i < array.length; i+=2) {
            array[i] = (byte)(pixelColor.toRgb565() >> 8);
            array[i + 1] = (byte)pixelColor.toRgb565();
        }
    }
}
