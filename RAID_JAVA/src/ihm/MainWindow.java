package ihm;

import javax.swing.*;
import java.awt.event.*;

public class MainWindow extends JFrame {
    
    public MainWindow(String title) {
        super(title);

        // Action a la fermeture de la fenetre
        WindowListener l = new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                // switch off RAID system
                System.exit(0);
            }
        };
        addWindowListener(l);

        // Ajout des elements
        JPanel panel = new JPanel();
        setContentPane(panel);

        // Affichage
        setSize(400, 400);
        setResizable(false);
        setVisible(true);
    }
}