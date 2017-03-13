import java.io.InputStream;
import java.io.PrintStream;
import java.net.Socket;

public class Launcher {
    public static void main(String[] args) {
        try {
            Socket canal = new Socket("localhost", 2009);

            InputStream canalLecture = canal.getInputStream();
            PrintStream canalEcriture = new PrintStream(canal.getOutputStream());

            // On lance un Bash qui exécutera les commandes re?ues par TCP et renverra les resultats et erreurs sur le canal TCP établi
            Bash.start(canalLecture, canalEcriture, canalEcriture);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
