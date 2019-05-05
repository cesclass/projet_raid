/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ihm;

/**
 *
 * @author Dylan
 */
public class Title extends javax.swing.JFrame {

    private static final long serialVersionUID = 1L;
	/** Creates new form error */
    public Title() {
        initComponents();
    }
    /**
     * Getter btnOk
     * 
     * @return btnOk
     */
    public javax.swing.JButton getBtnOk() {
        return btnOk;
    }

    /**
     * Getter TxtTitle
     * 
     * @return txtTitle
     */
    public javax.swing.JTextPane getTxtTitle() {
        return txtTitle;
    }

    /**
     * Getter btnCancel
     * 
     * @returnbtnCancel
     */
    public javax.swing.JButton getBtnCancel() {
        return btnCancel;
    }
    
    /**
     * Ferme la fenetre lorsque l'utilisateur appuie sur le bouton "Ok"
     * 
     * @param evt
     */
    private void btnOkActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_btnCreateMouseClicked
        this.setVisible(false);
        
    }
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        this.setResizable(false); /* taille de la fenetre non redimensionnable */
        this.setTitle("NEW"); /* titre de la fenetre */

        /* Creation des composants de la fenetre */
        lblErrTitle = new javax.swing.JLabel();
        btnOk = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        txtTitle = new javax.swing.JTextPane();
        btnCancel = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        
        this.setTitle("Create File");
        lblErrTitle.setText("Enter filename :                ");

        btnOk.setText("OK");
        btnOk.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnOkActionPerformed(evt);
            }
        });

        jScrollPane1.setViewportView(txtTitle);

        btnCancel.setText("Cancel");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(btnCancel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(btnOk))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(lblErrTitle)
                        .addGap(0, 122, Short.MAX_VALUE))
                    .addComponent(jScrollPane1))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(lblErrTitle)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 28, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnOk)
                    .addComponent(btnCancel))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * Setter txtTitle
     * 
     * @param s : String a affecter a txtTitle
     */
    public void setContent(String s) {
        txtTitle.setText(s);
    }

    /**
     * Getter txtTitle
     * 
     * @return le contenu de txtTitle
     */
    public String getContent() {
        return txtTitle.getText();
    }

    /**
     * @param args the command line arguments
     */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnOk;
    private javax.swing.JButton btnCancel;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextPane txtTitle;
    private javax.swing.JLabel lblErrTitle;
    // End of variables declaration//GEN-END:variables

}
