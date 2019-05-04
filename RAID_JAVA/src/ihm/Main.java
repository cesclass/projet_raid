/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ihm;

import java.awt.event.*;
import java.io.IOException;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.JFileChooser;
import javax.swing.JScrollPane;
import java.io.*;

import raid.*;

/**
 *
 * @author Dylan
 */
public class Main extends javax.swing.JFrame implements KeyListener {

    private static final long serialVersionUID = 1L;
    VirtualDisk r5Disk;
    
    private Title title;
    private Error errFrame;

    /**
     * Creates new form main
     * 
     * @throws ClassNotFoundException
     * @throws IOException
     */
    public Main() throws ClassNotFoundException, IOException {

        r5Disk = new VirtualDisk();

        title = new Title();
        title.getBtnCancel().addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                title.setVisible(false);
            }
        });
        title.getTxtTitle().addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {}
        
            @Override
            public void keyReleased(KeyEvent e) {}
        
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    createFile(title.getContent());
                    title.setVisible(false);
                }

                if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    title.setVisible(false);
                }
            }
        });

        errFrame = new Error();
        errFrame.getBtnOk().addKeyListener(new KeyListener(){
            @Override
            public void keyTyped(KeyEvent e) {}
        
            @Override
            public void keyReleased(KeyEvent e) {}
        
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER || e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    errFrame.setVisible(false);
                }
            }
        });

        initComponents();
        initList();

        lstFiles.addKeyListener(this);
    }

    public void initList() {
        for (int i = 0; i < RaidDefine.INODE_TABLE_SIZE; i++) {
            Inode in = r5Disk.getInode(i);
            if (!in.isUnused()) {
                listModel.addElement(new String(in.getFileName()));
            }
        }
    }

    public void createFile(String filename) {
        if (filename.getBytes().length > 31) {
            triggerError("Create error",
                    "File name is too long (> 31 Bytes)");
            return;
        }

        String [] interdit = new String[] {"\\", "/", " ", "\n", "$", "\t"};
        for (String s : interdit) {
            if (filename.contains(s)) {
                triggerError("Create error",
                    "<html>Forbidden characters. " +
                    "You can't use spaces, carry return, tabs or \\, /, $</html>");
                return;
            }
        }

        if (filename.isEmpty()) {
            triggerError("Create error",
                    "File name is empty.");
            return;
        }

        if (r5Disk.searchInode(filename.getBytes()) != null) {
            triggerError("Create error",
                    "File already exist.");
            return;
        }

        Inode in;

        if ((in = r5Disk.getUnusedInode()) == null) {
            triggerError("Create error",
                    "RAID 5 system is already full.");
            return;
        } else {
            in.init(filename.getBytes(), 0, r5Disk.getSuperBlock().getFirstFreeByte());
            listModel.addElement(filename);
            lstFiles.setSelectedValue(filename, false);
        }
    }

    public void showFile(String filename) throws IOException {
        if (filename == null) {
            txtDatas.setText("");
            lblSize.setText("");
            return;
        }
        
        byte[] buff = FS.readFile(r5Disk, filename.getBytes());
        txtDatas.setText(new String(buff));
        lblSize.setText("Size : " + buff.length + " Byte(s)");
    }

    public void modifyFile(String filename) throws IOException {
        FS.writeFile(r5Disk, filename.getBytes(), txtDatas.getText().getBytes());
        showFile(filename);
    }

    /**
     * Copie un fichier du systeme "hote" vers le systeme RAID
     *  avec le meme nom.
     * 
     * @param filename
     * 
     * @throws IOException
     */
    public void deleteFile(String filename) throws IOException{
        if (filename == null) {
            triggerError("Delete error", 
                    "There is no file selected.");
            return;
        }
        
        FS.deleteFile(r5Disk, filename.getBytes());
        listModel.removeElement(filename);
    }

    /**
     * Copie un fichier du systeme "hote" vers le systeme RAID
     *  avec le meme nom.
     * 
     * @throws IOException
     */
    public void loadFile() throws IOException {
        JFileChooser fc = new JFileChooser();

        /*  Configuration de l'explorateur */
        fc.setApproveButtonText("Load");
        fc.setDialogTitle("Load");
        
        if(fc.showOpenDialog(null) == JFileChooser.APPROVE_OPTION){
            File fichier = fc.getSelectedFile();

            /*  Gestion d'erreurs */
            /*   - Nom de fichier trop long */
            if (fichier.getName().getBytes().length >= RaidDefine.FILENAME_MAX_SIZE) {
                triggerError("Load error",
                        "File name is too long (>= " + RaidDefine.FILENAME_MAX_SIZE + " Bytes)");
                return;
            }
            
            /*   - Fichier trop gros */
            if (fichier.length() >= RaidDefine.MAX_FILE_SIZE) {
                triggerError("Load error",
                        "File is too big (>= " + RaidDefine.MAX_FILE_SIZE + " Bytes)");
                return;
            }

            /*   - Le fichier existe deja */
            if (r5Disk.searchInode(fichier.getName().getBytes()) != null) {
                triggerError("Load error",
                        "File already exist.");
                return;
            }
            
            /*  Enregistrement du fichier */
            FS.loadFileFromHost(r5Disk, fichier);

            /*  Mise a jour de la GUI */
            listModel.addElement(fichier.getName());
            lstFiles.setSelectedValue(fichier.getName(), true);
            showFile(fichier.getName());
        }
    }

    public void storeFile(){
        JFileChooser fc = new JFileChooser();

        /*  Configuration de l'explorateur */
        fc.setApproveButtonText("Store");
        fc.setDialogTitle("Store");
        fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        String filename = lstFiles.getSelectedValue();
        if (filename == null) {
            triggerError("Store error",
                    "No file selected.");
            return;
        }

        if(fc.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
            FS.storeFileToHost(
                r5Disk, 
                lstFiles.getSelectedValue().getBytes(),
                fc.getSelectedFile().getPath()
            );
        }
    }

    /**
     * 
     * @param errTitle
     * @param errMsg
     */
    void triggerError(String errTitle, String errMsg) {
        errFrame.setErrTitle(errTitle);
        errFrame.setErrMsg(errMsg);
        errFrame.setVisible(true);
    }

    public void keyPressed(KeyEvent ke) {
        if (ke.getKeyCode() == KeyEvent.VK_DELETE) {
            try {
                deleteFile(lstFiles.getSelectedValue());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        if (errFrame.isVisible() && ke.getKeyCode() == KeyEvent.VK_ENTER) {
            errFrame.setVisible(false);
        }
    }

    public void keyReleased(KeyEvent ke) {
        // System.out.println("Key released");
    }

    public void keyTyped(KeyEvent ke) {
        // System.out.println("Key typed");
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated
    // Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        this.setResizable(false);
        this.setTitle("RAID 5");
        
        jLabel1 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        btnCreate = new javax.swing.JButton();
        btnDelete = new javax.swing.JButton();
        btnLoad = new javax.swing.JButton();
        btnStore = new javax.swing.JButton();
        lblSize = new javax.swing.JLabel();
        btnSave = new javax.swing.JButton();
        lblMyFiles = new javax.swing.JLabel();
        lblTitle = new javax.swing.JLabel();
        jScrollPane3 = new javax.swing.JScrollPane();
        txtDatas = new javax.swing.JTextPane();
        lblFilename = new javax.swing.JLabel();
        btnCancel = new javax.swing.JButton();

        jLabel1.setText("jLabel1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        listModel = new DefaultListModel();
        lstFiles = new javax.swing.JList(listModel);
        lstFiles.addListSelectionListener(new ListSelectionListener(){
            public void valueChanged(ListSelectionEvent e) {
                try {
                    showFile(lstFiles.getSelectedValue());
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
        
        
        lstFiles.setPreferredSize(new java.awt.Dimension(35, 200));
        jScrollPane1.setViewportView(lstFiles);

        btnCreate.setText("New");
        btnCreate.setMaximumSize(new java.awt.Dimension(90, 25));
        btnCreate.setMinimumSize(new java.awt.Dimension(90, 25));
        btnCreate.setPreferredSize(new java.awt.Dimension(90, 25));
        btnCreate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                title.setContent(""); 
                title.setVisible(true);
            }
        });

        title.getBtnOk().addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                createFile(title.getContent());
            }
        });

        btnDelete.setText("Delete");
        btnDelete.setMaximumSize(new java.awt.Dimension(90, 25));
        btnDelete.setMinimumSize(new java.awt.Dimension(90, 25));
        btnDelete.setPreferredSize(new java.awt.Dimension(90, 25));
        btnDelete.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                try {
                    deleteFile(lstFiles.getSelectedValue());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        btnLoad.setText("Load");
        btnLoad.setMaximumSize(new java.awt.Dimension(90, 25));
        btnLoad.setMinimumSize(new java.awt.Dimension(90, 25));
        btnLoad.setPreferredSize(new java.awt.Dimension(90, 25));
        btnLoad.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                try {
                    loadFile();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        btnStore.setText("Store");
        btnStore.setMaximumSize(new java.awt.Dimension(90, 25));
        btnStore.setMinimumSize(new java.awt.Dimension(90, 25));
        btnStore.setPreferredSize(new java.awt.Dimension(90, 25));
        btnStore.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt){
                storeFile();
            }
        });
        lblSize.setText("");

        btnSave.setText("Save");
        btnSave.setMaximumSize(new java.awt.Dimension(90, 25));
        btnSave.setMinimumSize(new java.awt.Dimension(90, 25));
        btnSave.setPreferredSize(new java.awt.Dimension(90, 25));
        btnSave.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                try {
                    modifyFile(lstFiles.getSelectedValue());
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
           
        lblMyFiles.setText("My files");

        lblTitle.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        lblTitle.setText("RAID 5 Java");

        txtDatas.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        txtDatas.setPreferredSize(new java.awt.Dimension(35, 200));
        JScrollPane scroll = new JScrollPane();
        scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED); 
        scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        txtDatas.add(scroll);
        
        jScrollPane3.setViewportView(txtDatas);
        
        String s = new String();
        for(int i = 0; i++ < 120; s+=" ");
        lblFilename.setText(s);

        btnCancel.setText("Cancel");
        btnCancel.setMaximumSize(new java.awt.Dimension(90, 25));
        btnCancel.setMinimumSize(new java.awt.Dimension(90, 25));
        btnCancel.setPreferredSize(new java.awt.Dimension(90, 25));
        btnCancel.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                try {
                    showFile(lstFiles.getSelectedValue());
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout
                .createSequentialGroup().addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout
                        .createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addGroup(layout.createSequentialGroup()
                                        .addComponent(btnLoad, javax.swing.GroupLayout.PREFERRED_SIZE,
                                                javax.swing.GroupLayout.DEFAULT_SIZE,
                                                javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED,
                                                javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(btnStore, javax.swing.GroupLayout.PREFERRED_SIZE,
                                                javax.swing.GroupLayout.DEFAULT_SIZE,
                                                javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                        .addComponent(btnCreate, javax.swing.GroupLayout.DEFAULT_SIZE,
                                                javax.swing.GroupLayout.DEFAULT_SIZE,
                                                javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED,
                                                javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(btnDelete, javax.swing.GroupLayout.PREFERRED_SIZE,
                                                javax.swing.GroupLayout.DEFAULT_SIZE,
                                                javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 207,
                                        javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGroup(layout.createSequentialGroup().addGap(10, 10, 10).addComponent(lblMyFiles)))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(layout
                                .createSequentialGroup().addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(jScrollPane3)
                                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout
                                                .createSequentialGroup().addGap(10, 10, 10).addComponent(lblSize)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED,
                                                        javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addComponent(btnSave, javax.swing.GroupLayout.PREFERRED_SIZE,
                                                        javax.swing.GroupLayout.DEFAULT_SIZE,
                                                        javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING,
                                                layout.createSequentialGroup().addGap(0, 0, Short.MAX_VALUE)
                                                        .addComponent(btnCancel, javax.swing.GroupLayout.PREFERRED_SIZE,
                                                                javax.swing.GroupLayout.DEFAULT_SIZE,
                                                                javax.swing.GroupLayout.PREFERRED_SIZE))))
                                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING,
                                        layout.createSequentialGroup()
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 29,
                                                        Short.MAX_VALUE)
                                                .addComponent(lblFilename).addGap(168, 168, 168))))
                        .addGroup(layout.createSequentialGroup().addComponent(lblTitle).addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap()));
        layout.setVerticalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING).addGroup(
                javax.swing.GroupLayout.Alignment.TRAILING,
                layout.createSequentialGroup().addContainerGap().addComponent(lblTitle).addGap(11, 11, 11)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(lblMyFiles).addComponent(lblFilename))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addComponent(jScrollPane3)
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 281, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(btnDelete, javax.swing.GroupLayout.PREFERRED_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btnCreate, javax.swing.GroupLayout.DEFAULT_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btnSave, javax.swing.GroupLayout.PREFERRED_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(lblSize))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(btnLoad, javax.swing.GroupLayout.PREFERRED_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btnStore, javax.swing.GroupLayout.PREFERRED_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btnCancel, javax.swing.GroupLayout.PREFERRED_SIZE,
                                        javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) throws IOException, ClassNotFoundException {
        /* Set the Nimbus look and feel */
        // <editor-fold defaultstate="collapsed" desc=" Look and feel setting code
        // (optional) ">
        /*
         * If Nimbus (introduced in Java SE 6) is not available, stay with the default
         * look and feel. For details see
         * http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        // </editor-fold>
        //

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    new Main().setVisible(true);
                } catch (ClassNotFoundException | IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnCancel;
    private javax.swing.JButton btnCreate;
    private javax.swing.JButton btnDelete;
    private javax.swing.JButton btnLoad;
    private javax.swing.JButton btnSave;
    private javax.swing.JButton btnStore;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel lblFilename;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JLabel lblMyFiles;
    private javax.swing.JLabel lblSize;
    private javax.swing.JLabel lblTitle;
    private javax.swing.DefaultListModel listModel;
    private javax.swing.JList<String> lstFiles;
    private javax.swing.JTextPane txtDatas;
    // End of variables declaration//GEN-END:variables
}
