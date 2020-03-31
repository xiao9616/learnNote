public class RealImage implements Image {
    private String fileName;

    public RealImage(String fileName) {
        this.fileName = fileName;
        loadimage(fileName);

    }

    @Override
    public void displayi() {
        System.out.println("display");
    }

    private void loadimage(String fileName) {
        System.out.println(fileName);
    }
}
