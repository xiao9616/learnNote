package com.xiao;

class myexception extends RuntimeException {
    public myexception() {
        super();
    }

    public myexception(String message) {
        super(message);
    }

    static final long serialVersionUID = -341333335l;
}