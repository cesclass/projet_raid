        // <3
        RandomAccessFile test = new RandomAccessFile(RaidDefine.PATH + RaidDefine.NAMEDISK + 0 , "rw");
        System.out.println(test.length());

        /* test methode Block */
        int size = 400;
        System.out.println("Compute nblock : " + Block.computeNBlock(size));
        
        /* Write & Read block */
        Block write = new Block();
        Block read = new Block();
        byte a = 65;
        for(int i = 0; i < RaidDefine.BLOCK_SIZE; write.setDataI(i++,a));
        
        System.out.println("Ecriture de write");
        write.dumpBlockHexa();
        test.write(write.data, 0, write.data.length);
        write.dumpBlockHexa();

        read.dumpBlockHexa();
        System.out.println("Lecture de read");

        test.seek(0);
        test.read(read.data);
        test.read(read.data, 0, read.data.length);
        //test.read(read.data, 0,4);

        read.dumpBlockHexa();
        test.close();