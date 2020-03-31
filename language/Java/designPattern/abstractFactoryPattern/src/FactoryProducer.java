public class FactoryProducer {
    static Factory getFactory(String fac) {
        if (fac.equalsIgnoreCase("shape")) {
            return new ShapeFactory();
        }
        if (fac.equalsIgnoreCase("color")) {
            return new ColorFactory();
        }
        return null;
    }

}
