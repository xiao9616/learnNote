public class ShapeFactory implements Factory {
    @Override
    public Color getColor(String color) {
        return null;
    }

    @Override
    public shape getShape(String shapeType) {
        if (shapeType == null) {
            return null;
        }
        if (shapeType.equalsIgnoreCase("rectangle")) {
            return new Rectangle();
        }
        if (shapeType.equalsIgnoreCase("square")) {
            return new Square();
        }
        if (shapeType.equalsIgnoreCase("circle")) {
            return new Circle();
        }
        return null;
    }
}
