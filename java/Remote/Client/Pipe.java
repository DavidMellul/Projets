import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by David on 13/03/2017.
 */

// Cette classe représente l'équivalent d'un pipe en C
public class Pipe implements Runnable{
    private InputStream m_fluxLecture;
    private OutputStream m_fluxEcriture;

    public Pipe(InputStream in, OutputStream out) {
        m_fluxLecture = in;
        m_fluxEcriture = out;
    }

    @Override
    public void run() {
        try
        {
            final byte[] buffer = new byte[1024];
            int tailleBuffer;

            // Tant qu'on peut lire des donn?es sur le flux de lecture, on les lit et on les envoie sur le flux d'?criture
            while((tailleBuffer = m_fluxLecture.read(buffer)) != -1) {
                m_fluxEcriture.write(buffer, 0, tailleBuffer);
            }
        }
        catch(Exception e)
        {
            System.err.println("Erreur de communication dans le pipe : ");
            e.printStackTrace();
        }
    }
}
