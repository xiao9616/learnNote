
public class demo {
    public static void main(String[] args) {
        ShapeFactory shapeFactory = new ShapeFactory();
        shape shape1 = shapeFactory.getShape("circle");
        shape shape2 = shapeFactory.getShape("rectangle");
        shape shape3 = shapeFactory.getShape("square");
        shape1.draw();
        shape2.draw();
        shape3.draw();
    }
}
