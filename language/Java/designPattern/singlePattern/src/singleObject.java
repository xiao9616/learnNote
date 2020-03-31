public class singleObject {
    private singleObject() {

    }

    private static singleObject instance = new singleObject();

    public static singleObject getInstance() {
        if (instance == null) {
            instance = new singleObject();
        }
        return instance;
    }

    public void show() {
        System.out.println("single");
    }
}
