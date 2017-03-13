import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import sun.security.jca.GetInstance;

/**
 * Created by David on 13/03/2017.
 */
@SuppressWarnings("unused")
public class Controller {
    private ServerSocket m_canalServeur;
    private OnClientConnectedListener m_OnClientConnectedListener;
    
    // Singleton
    private static Controller m_instance = new Controller();
    private Controller()  {
        try {
			m_canalServeur = new ServerSocket(2009);
		} catch (IOException e) { }
    }
    public static Controller getInstance() { return m_instance; }

    public void start() throws IOException {
    	new Thread(new Runnable() {
			@Override
			public void run() {
				 while(true) {
			        	Socket s;
						try {
							 while(true) {
									s = m_canalServeur.accept();
									m_OnClientConnectedListener.onClientConnected(s);
						        }
						} catch (IOException e) { }
			           
			        }
			}
		}).start();
    }
    
    public void setOnClientConnectedListener(OnClientConnectedListener o) {
    	m_OnClientConnectedListener = o;
    }
   
}
