## Jazzer (JVM fuzzer)

```xml
<dependency>
    <groupId>com.code-intelligence</groupId>
    <artifactId>jazzer-junit</artifactId>
    <version>LATEST VERSION</version>
</dependency>
```

```sh
$ JAZZER_FUZZ=1 mvn test org.example.ParserTests
```

```java
package org.example;
import com.code_intelligence.jazzer.junit.FuzzTest;
import com.code_intelligence.jazzer.mutation.annotation.NotNull;
import com.code_intelligence.jazzer.mutation.annotation.InRange;
import com.code_intelligence.jazzer.mutation.annotation.WithUtf8Length;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ParserTests {
    @Test
    void unitTest() {
        assertEquals("foobar", SomeScheme.decode(SomeScheme.encode("foobar")));
    }

    @FuzzTest
    void fuzzTest_decode(@NotNull String input) {
        assertEquals(input, SomeScheme.decode(SomeScheme.encode(input)));
    }
	
    @FuzzTest
    void fuzzTest_decodeWithN(@NotNull @WithUtf8Length(min=10, max=200) String input, @InRange(min=-10, max=10) int n) {
        assertEquals(input, SomeScheme.decode(SomeScheme.encode(input)));
        assertTrue(n >= -10 && n <= 10);
    }
}
```
