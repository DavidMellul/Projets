import java.net.Socket;

public interface OnClientDisconnectedListener {
	void onClientDisconnected(Socket s);
}
