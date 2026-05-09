package org.example;

public final class SomeScheme {
    private SomeScheme() {
    }

    public static String encode(String input) {
        StringBuilder result = new StringBuilder(input.length());
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c == '\\') {
                result.append("\\\\");
            } else if (c == ':') {
                result.append("\\c");
            } else if (c == '\n') {
                result.append("\\n");
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    public static String decode(String input) {
        StringBuilder result = new StringBuilder(input.length());
        boolean escaped = false;
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!escaped && c == '\\') {
                escaped = true;
                continue;
            }
            if (escaped) {
                if (c == 'c') {
                    result.append(':');
                } else if (c == 'n') {
                    result.append('\n');
                } else {
                    result.append(c);
                }
                escaped = false;
            } else {
                result.append(c);
            }
        }
        if (escaped) {
            result.append('\\');
        }
        return result.toString();
    }
}
