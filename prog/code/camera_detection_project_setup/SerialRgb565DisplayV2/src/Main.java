import com.fazecast.jSerialComm.SerialPort;

public class Main {

    public static void main(String[] args)
    {
        Rgb565DisplayGui rgbDisplay = new Rgb565DisplayGui();

        SerialPort comPort = SerialPort.getCommPort("COM4");
        comPort.setBaudRate(115200);
        comPort.openPort();
        comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 20000, 0);
        try {
            while(true) {
                int numRead = comPort.readBytes(rgbDisplay.displayData, rgbDisplay.displayData.length);
                System.out.println("Read " + numRead + " bytes.");
                rgbDisplay.repaint();
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        comPort.closePort();


    }
}
