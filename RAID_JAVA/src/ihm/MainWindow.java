package ihm;

import javax.swing.*;
import java.awt.event.*;

public class MainWindow extends JFrame {
	private static final long serialVersionUID = 1L;

	public MainWindow(String title) {
        super(title);

        // Affichage
        setSize(400, 200);
        setResizable(false);
        setVisible(true);
    }

    public void constructWindow() {
        JList lsLIST = new JList<>();

        JPanel panel = new JPanel();
        setContentPane(panel);
    }









    public void listenEvent() {
        // Action a la fermeture de la fenetre
        WindowListener l = new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                // switch off RAID system
                System.exit(0);
            }
        };
        addWindowListener(l);


    }
}