import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

/**
 * Created by David on 13/03/2017.
 */
public class ThreadClient extends Thread implements OnMessageSentListener {
    private Socket m_canalClient;
    private OnDataReceivedListener m_OnDataReceivedListener;
    private OnClientDisconnectedListener m_OnClientDisconnectedListener;
    
    private BufferedReader m_canalLecture;
    private PrintStream m_canalEcriture;
    
    public ThreadClient(Socket s, OnDataReceivedListener odrl, OnClientDisconnectedListener ocdl) {
        m_canalClient = s;
        m_OnDataReceivedListener = odrl;
        m_OnClientDisconnectedListener = ocdl;
    }

    @Override
    public void run() {
        try {
        	m_canalLecture = new BufferedReader(new InputStreamReader(m_canalClient.getInputStream()));
        	m_canalEcriture = new PrintStream(m_canalClient.getOutputStream());

            String content;
            while ((content = m_canalLecture.readLine()) != null) {
            	m_OnDataReceivedListener.onDataReceived(content);
            }
        } catch (Exception e) { 
        	m_OnClientDisconnectedListener.onClientDisconnected(m_canalClient);
        }
    }

	@Override
	public void onMessageSentListener(String message) {
		m_canalEcriture.println(message);
		m_canalEcriture.flush();
	}
}
