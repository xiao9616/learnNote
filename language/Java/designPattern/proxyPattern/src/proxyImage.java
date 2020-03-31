public class proxyImage implements Image {
    private RealImage realImage;
    private String fileName;

    public proxyImage(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void displayi() {
        if (realImage == null) {
            realImage = new RealImage(fileName);
        }
        realImage.displayi();
    }
}
