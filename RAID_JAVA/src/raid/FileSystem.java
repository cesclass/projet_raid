package raid;

public abstract class FileSystem {

    public String readFile() {
        return "";
    }

    public boolean writeFile() {
        return false;
    }

    public boolean deleteFile() {
        return false;
    }

    public boolean loadFileFromHost() {
        return false;
    }

    public boolean storeFileToHost() {
        return false;
    }

}