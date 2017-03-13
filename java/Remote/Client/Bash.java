import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created by David on 13/03/2017.
 */

/**
 * Cette classe représente un Bash en Java
 */
public class Bash {
    /**
     * Méthode qui permet de lancer une réplique d'un bash
     * @param err : Représente le flux d'erreur sur lequel rediriger la sortie d'erreur du Bash courant
     * @param out :  Représente le flux de sortie standard sur lequel rediriger la sortie standard du Bash courant
     */
    public static void start(InputStream in, PrintStream err, PrintStream out) {
        String[] cmd = new String[2];

        // On s'adapte en fonction de l'OS sur lequel on tourne
        if(Utils.runningOnWindowsOS()) cmd[0] = "cmd";
        else cmd[0] = "/bin/bash";
        cmd[1] = "";

        Process p;

        try {
            // Exécution du process de Bash/Cmd/Terminal
            p = Runtime.getRuntime().exec(cmd);

            // Redirection de la sortie d'erreur et de la sortie standard
            new Thread(new Pipe(p.getErrorStream(),err)).start();
            new Thread(new Pipe(p.getInputStream(),out)).start();

            String task ;
            Scanner sc = new Scanner(in);

            PrintWriter stdin = new PrintWriter(p.getOutputStream());

            while((task = sc.nextLine()) != null) {
                // Si on écrit "stop", le Bash s'arrête
                if(task.equals("stop")) break;
                stdin.println(task);
                // Le flush permet de forcer le buffer à se vider, et par conséquent de forcer l'envoi de la chaîne "task" directement quand cette instruction est atteinte
                stdin.flush();
            }
            stdin.close();
        }catch (Exception e) {
            err.println("Erreur pendant l'execution du bash :");
            e.printStackTrace(err);
        }
    }
}
