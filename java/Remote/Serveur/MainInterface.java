import java.awt.BorderLayout;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import java.awt.Color;

@SuppressWarnings("serial")
public class MainInterface extends JFrame implements OnClientConnectedListener, OnClientDisconnectedListener{

	private JPanel contentPane;
	private JTabbedPane m_boiteOnglets;
	private ArrayList<Socket> m_listeCanaux;

	/**
	 * Create the frame.
	 */
	public MainInterface() {
		super();
		setBackground(Color.BLACK);
		m_listeCanaux = new ArrayList<Socket>();
		initializeComponents();
	}
	
	private void initializeComponents() {
		setTitle("Spy - Serveur");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(640, 480);
		setLocationRelativeTo(null);

		
		contentPane = new JPanel();
		contentPane.setBackground(Color.BLACK);
		contentPane.setBorder(null);
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		
		m_boiteOnglets = new JTabbedPane(JTabbedPane.TOP);
		m_boiteOnglets.setBackground(Color.BLACK);
		contentPane.add(m_boiteOnglets, BorderLayout.CENTER);
		
		try {
			Controller.getInstance().setOnClientConnectedListener(this);
			Controller.getInstance().start();
		} catch (IOException e) { }
	}

	@Override
	public void onClientConnected(Socket s) {
		m_listeCanaux.add(s);
		
        BashPanel b = new BashPanel(s);
        ThreadClient t = new ThreadClient(s, b, this);
        b.setOnMessageSentListener(t);
        t.start();
		
		m_boiteOnglets.add("Client "+m_listeCanaux.size(), b);
	}
	
	@Override
	public void onClientDisconnected(Socket s) {
		m_boiteOnglets.remove(m_listeCanaux.indexOf(s));
	}

}
