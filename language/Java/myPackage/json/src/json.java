import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class json {
    private String json;

    public json(String json) {
        this.json = json;
    }


    public Object parse() {
        CharsRange trimed = newRange(0, json.length()).trim();
        return processValue(trimed);
    }

    private Object processPlainObject(CharsRange val) {

    }

    private Object processArray(CharsRange val) {
        System.out.println();

    }

    private List<Property> processProperty(CharsRange range) {
        List<Property> list = new ArrayList<>();
        int startMark = range.start;
        for (int i = range.start; i < range.end; i++) {
            char ch = json.charAt(i);
            if (ch == ':') {

            }
        }
    }

    private CharsRange findNextValue(CharsRange chars, AtomicInteger readCurser) {
        CharsRange trimChard = chars.trim();

    }

    private CharsRange completeSymbolPair(CharsRange trimChars, AtomicInteger readCursor, String symbolPair) {
        int leftSymbol = symbolPair.charAt(0);
        int rightSymbol = symbolPair.charAt(1);
        int symbolScore = 1;
        int i;
        CharsRange valuceSegment = null;
        for (i = trimChars.start + 1; i < trimChars.end; i++) {
            char ch = json.charAt(i);
            if (ch == leftSymbol) {
                symbolScore++;
            } else if (ch == rightSymbol) {
                symbolScore--;
            }
            if (symbolScore == 0) {
                valuceSegment = newRange(trimChars.start, i + 1);
                break;
            }
        }
        for (; i < trimChars.end; i++) {
            char chx = json.charAt(i);
            if (chx == ',') {
                break;
            }
        }
        readCursor.set(i);
        return valuceSegment;
    }

    private Object processValue(CharsRange trimed) {
        final Object value;
        if (trimed.relativeChar(0)=='"'){
            value = newRange(trimed.start + 1, trimed.end - 1).toString();
        }else if (trimed.relativeChar(0)=='{'){
            value = processPlainObject(trimed);
        } else if (trimed.relativeChar(0) == '[') {
            value = processArray(trimed);
        } else if (trimed.equalString("true")) {
            value = true;
        } else if (trimed.equalString("false")) {
            value = false;
        } else if (trimed.equalString("null")) {
            value = null;
        } else {
            value = Double.parseDouble(trimed.toString());
        }
        return value;
    }

    @Override
    public String toString() {
        return "json{" +
                "json='" + json + '\'' +
                '}';
    }

    CharsRange newRange(int start, int end) {
        return new CharsRange(start, end);
    }

    static class Property {
        final public String name;
        final Object object;

        public Property(String name, Object object) {
            this.name = name;
            this.object = object;
        }

        static Property of(String name, Object object) {
            return new Property(name, object);
        }

    }

    class CharsRange {
        final int start;
        final int end;

        public CharsRange(int start, int end) {
            this.start = start;
            this.end = end;
        }


        CharsRange trimLeft() {
            int newStart = -1;
            for (int i = start; i < end; i++) {
                if (!Character.isWhitespace(json.charAt(i))) {
                    newStart = i;
                    break;
                }
            }
            if (newStart == -1) {
                throw new IllegalArgumentException("illegal argment json");
            }
            return newRange(newStart, end);
        }

        CharsRange timeRight() {
            int newEnd = -1;
            for (int i = end - 1; i >= start; i--) {
                if (!Character.isWhitespace(json.charAt(i))) {
                    newEnd = i + 1;
                    break;
                }
            }
            if (newEnd == -1) {
                throw new IllegalArgumentException("illegal argment json");
            }
            return newRange(start, newEnd);
        }

        CharsRange trim() {
            return this.trimLeft().timeRight();
        }

        char relativeChar(int index) {
            return json.charAt(start + index);
        }

        public boolean equalString(String string) {
            return json.regionMatches(true, start, string, 0, string.length());
        }

        @Override
        public String toString() {
            return json.subSequence(start, end).toString();
        }
    }


}

