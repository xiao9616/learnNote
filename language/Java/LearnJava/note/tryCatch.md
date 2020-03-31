**1.try-catch-finally**

        try {
            int[] i = new int[10];
            System.out.println(i[10]);

        } catch (Exception e) {
            System.out.println("异常");
            System.out.println(e.toString());
            System.out.println(e.getMessage());
            e.printStackTrace();
        } finally{
            
        }
        
**2.向上抛出异常**

    try {
          cal();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void cal() throws Exception{
        int i,j=10;
        j=10/0;
    }
    
**3.手动抛出异常**

    public static void manule() {
        throw new RuntimeException("手动抛出异常");
    }
    
**4.自定义异常类**

    class myexception extends RuntimeException {
        public myexception() {
            super();
        }
    
        public myexception(String message) {
            super(message);
        }
    
        static final long serialVersionUID = -341333335l;
    
    }

**子类重写父类的方法，其抛出的异常必须是父类方法抛出异常的子类**