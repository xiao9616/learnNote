public class demo {
    public static void main(String[] args) {
        Factory shapeFactory = FactoryProducer.getFactory("shape");
        Factory colorFactory = FactoryProducer.getFactory("color");
        shape shape1 = shapeFactory.getShape("rectangle");
        shape1.draw();
        Color color1 = colorFactory.getColor("red");
        color1.fill();
    }
}
