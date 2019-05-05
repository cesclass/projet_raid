/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ihm;

import javax.swing.JButton;

/**
 *
 * @author Dylan
 */
public class Error extends javax.swing.JDialog{

    private static final long serialVersionUID = 1L;
	/** Creates new form error */
    public Error() {
        initComponents();
    }

    /**
     * Setter du titre de l'erreur
     * 
     * @param errTitle : titre de l'erreur a afficher 
     */
    public void setErrTitle(String errTitle) {
        lblErrTitle.setText(errTitle);
    }

    /**
     * Setter du message d'erreur
     * 
     * @param errMsg : message d'erreur a afficher
     */
    public void setErrMsg(String errMsg) {
        lblErrMsg.setText(errMsg);
    }

    /**
     * Getter du bouton "OK"
     * 
     * @return btnOK
     */
    public JButton getBtnOk() {
        return btnOk;
    }
    
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        this.setResizable(false); /* taille de la fenetre non redimensionnable */
        this.setTitle("ERROR"); /* titre de la fenetre */
        this.setModal(true); /* declaration de la fenetre en modal */
        
        /* Creation des composants de la fenetre */
        lblErrTitle = new javax.swing.JLabel();
        lblErrMsg = new javax.swing.JLabel();
        btnOk = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        lblErrTitle.setForeground(new java.awt.Color(204, 0, 0));
        lblErrTitle.setText("ERREUR !");

        lblErrMsg.setForeground(new java.awt.Color(153, 0, 0));
        lblErrMsg.setText("Message d'erreur...");

        btnOk.setText("OK");
        btnOk.addActionListener(new java.awt.event.ActionListener() {
            /* Ferme la fenetre d'erreur lorsque l'utilisateur appuie sur le bout "OK" */
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                setVisible(false);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(lblErrTitle)
                    .addComponent(lblErrMsg))
                .addContainerGap(180, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(btnOk)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(lblErrTitle)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblErrMsg)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 36, Short.MAX_VALUE)
                .addComponent(btnOk)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * @param args the command line arguments
     */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnOk;
    private javax.swing.JLabel lblErrMsg;
    private javax.swing.JLabel lblErrTitle;
    // End of variables declaration//GEN-END:variables

}
