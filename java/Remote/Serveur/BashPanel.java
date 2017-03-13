import java.net.Socket;

import javax.swing.JPanel;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JScrollPane;
import javax.swing.JTextField;
import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JButton;
import java.awt.Dimension;
import javax.swing.ScrollPaneConstants;
import javax.swing.text.DefaultCaret;

@SuppressWarnings({ "unused", "serial" })
public class BashPanel extends JPanel implements OnDataReceivedListener{
	private Socket m_canalCourant;
	private JTextField m_bashInput;
	private JTextArea m_bashTextArea;
	private JButton m_bashSendButton;

	private OnMessageSentListener m_OnMessageSentListener;
	private JScrollPane scrollPane;

	public BashPanel(Socket s) {
		super();
		
		m_canalCourant = s;
		
		initializeComponents();
		createListeners();
	}
	
	private void initializeComponents() {
		setBackground(Color.BLACK);
		setLayout(new BorderLayout());
		
		
		
		
		m_bashTextArea = new JTextArea();
		m_bashTextArea.setEditable(false);
		m_bashTextArea.setLineWrap(true);
		m_bashTextArea.setWrapStyleWord(true);
		m_bashTextArea.setColumns(45);
		m_bashTextArea.setBackground(Color.BLACK);
		m_bashTextArea.setForeground(Color.WHITE);
		DefaultCaret caret = (DefaultCaret)m_bashTextArea.getCaret();
		 caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
		
		scrollPane = new JScrollPane(m_bashTextArea);
		scrollPane.setPreferredSize(new Dimension(640, 480));
		scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scrollPane.setBorder(null);
		scrollPane.setAutoscrolls(true);
//		scrollPane.getViewport().setBackground(Color.BLACK);
		
		add(scrollPane, BorderLayout.CENTER);
		
		JPanel panel = new JPanel();
		add(panel, BorderLayout.SOUTH);
		
		m_bashInput = new JTextField();
		m_bashInput.setColumns(45);
		panel.add(m_bashInput);
		
		m_bashSendButton = new JButton("Envoyer");
		panel.add(m_bashSendButton);
		
		setVisible(true);
	}
	
	public void setOnMessageSentListener(OnMessageSentListener osml) {
		m_OnMessageSentListener = osml;
	}
	
	private void createListeners() {
		m_bashSendButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(m_bashInput.getText().equals("cls")) { m_bashTextArea.setText(""); m_bashInput.setText(""); return; }
				m_OnMessageSentListener.onMessageSentListener(m_bashInput.getText());
				m_bashInput.setText("");
			}
		});
		
		m_bashInput.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				m_bashSendButton.doClick();
			}
		});
	}

	@Override
	public void onDataReceived(String s) {
		m_bashTextArea.append(s+"\n");
	}
	
}
