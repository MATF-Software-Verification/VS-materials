package org.example;

import com.code_intelligence.jazzer.junit.FuzzTest;
import com.code_intelligence.jazzer.mutation.annotation.InRange;
import com.code_intelligence.jazzer.mutation.annotation.NotNull;
import com.code_intelligence.jazzer.mutation.annotation.WithUtf8Length;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class ParserTests {
    @Test
    void unitTest() {
        assertEquals("foo:bar", SomeScheme.decode(SomeScheme.encode("foo:bar")));
    }

    @FuzzTest
    void fuzzTestRoundTrip(@NotNull String input) {
        assertEquals(input, SomeScheme.decode(SomeScheme.encode(input)));
    }

    @FuzzTest
    void fuzzTestConstrainedInput(
            @NotNull @WithUtf8Length(min = 1, max = 200) String input,
            @InRange(min = -10, max = 10) int shift) {
        assertEquals(input, SomeScheme.decode(SomeScheme.encode(input)));
        assertTrue(shift >= -10 && shift <= 10);
    }
}
