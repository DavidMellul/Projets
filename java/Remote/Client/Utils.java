/**
 * Created by David on 13/03/2017.
 */
public class Utils {
    public static boolean runningOnWindowsOS() {
        return (System.getProperty("os.name").toLowerCase().contains("win"));
    }
}
