- `@Test` - marks a test method in a class. This method will be treated like a test, it'll get executed by the test engine, get a row in the reporting, and so on.
- `@TestFactory` - a method marked with the @TestFactory will be used to create test cases at runtime. Use it to run the randomized tests or test based on the external data.
- `@DisplayName` - makes reports readable with proper test names
- `@BeforeAll`/`@BeforeEach` - lifecycle methods executed prior running tests
- `@AfterAll`/`@AfterEach` - lifecycle methods for cleanup, executed after the tests
- `@Tag` - tags a method to separate tests into suites, for example - `@Tag`("fast") can be used to distinguish quick tests from the ones that take longer.
- `@Disabled` - makes JUnit skip this test, don't overuse it. In general disabled tests should be deleted and kept just in the VCS history.
- `@Nested` - Use on an inner class to control the order of tests.
- `@ExtendWith` - Use to enhance the execution: provide mock parameter resolvers and specify conditional execution.

```java
import org.junit.jupiter.api.*;
public class AppTest {
    @BeforeAll
    static void setup(){
        System.out.println("Executes a method Before all tests");
    }
    @BeforeEach
    void setupThis(){
        System.out.println("Executed Before each @Test method in the current test class");
    }
    @AfterEach
    void tearThis(){
        System.out.println("Executed After each @Test method in the current test class");
    }
    @AfterAll
    static void tear(){
        System.out.println("Executes a method After all tests");
    }
}
```

```java
Assertions.assertAll("heading", 
  () -> assertTrue(true), 
  () -> assertEquals("expected", objectUnderTest.getSomething());
```

```java
@TestFactory
Stream dynamicTests(MyContext ctx) {
  // Generates tests for every line in the file
  return Files.lines(ctx.testDataFilePath).map(l -> dynamicTest("Test:" + l, () -> assertTrue(runTest(l)));
}
```

```java
@Test
void exampleTest() {
    Assertions.assertTrue(trueBool);
    Assertions.assertFalse(falseBool);
    Assertions.assertNotNull(notNullString);
    Assertions.assertNull(notNullString);
    Assertions.assertNotSame(originalObject, otherObject);
    Assertions.assertEquals(4, 4);
    Assertions.assertNotEquals(3, 2);
    Assertions.assertArrayEquals(new int[]{1,2,3}, new int[]{1,2,3}, "Array Equal Test");
    Iterable<Integer> listOne = new ArrayList<>(Arrays.asList(1,2,3,4));
    Iterable<Integer> listTwo = new ArrayList<>(Arrays.asList(1,2,3,4));
    Assertions.assertIterableEquals(listOne, listTwo);
    Assertions.assertTimeout(Duration.ofMillis(100), () -> {
    Thread.sleep(50);
    return "result";
    });
    Throwable exception = Assertions.assertThrows(IllegalArgumentException.class, () -> {
    throw new IllegalArgumentException("error message");
    });
    Assertions.fail("not found good reason to pass");
}
```

```java
@Test
void testAssumption() {
    System.setProperty("myproperty", "foo");
    Assumptions.assumeTrue("foo".equals(System.getProperty("myproperty")));
         
}
```

```java
public class AppTest 
{
    @Test
    @EnabledForJreRange(min = JRE.JAVA_8, max = JRE.JAVA_11)
    public void test1()
    {
         System.out.println("Will run only on JRE between 8 and 11");
    }
    
    @Test
    @EnabledOnJre({JRE.JAVA_8, JRE.JAVA_11})
    public void test2()
    {
         System.out.println("Will run only on JRE 8 and 11");
    }
    @Test
    @DisabledForJreRange(min = JRE.JAVA_8, max = JRE.JAVA_11)
    public void test3()
    {
        System.out.println("Will NOT run on JRE between 8 and 11");
    }
    
    @Test
    @DisabledOnJre({JRE.JAVA_8, JRE.JAVA_11})
    public void test4()
    {
        System.out.println("Will NOT run on JRE 8 and 11");
    }
}
```

```java
public class OperatingSystemTest {
    @Test
    @EnabledOnOs({OS.LINUX, OS.WINDOWS})
    void onLinuxOrWindows() {
        System.out.println("Will run on Linux or Windows.");
    }
    @Test
    @DisabledOnOs({OS.WINDOWS, OS.AIX, OS.SOLARIS, OS.MAC})
    void notOnWindowsOrAixOrSolarisOrMac() {
        System.out.println("Will not run on Windows, AIX, Solaris or MAC!");
    }
}
```

```java
@Test
@EnabledIf("myfunction")
void enabled() {
    assertTrue(true);
}

@Test
@DisabledIf("myfunction")
void disabled() {
    assertTrue(true);
}

boolean myfunction() {
    return true;
}
```

```java
@Test
@EnabledIfEnvironmentVariable(named = "ENV", matches = ".*oracle.*")
public void executeOnlyInDevEnvironment() {
    return true;
}
@Test
@DisabledIfEnvironmentVariable(named = "ENV", matches = ".*mysql.*")
public void disabledOnProdEnvironment() {
    return true;
}
@Test
@EnabledIfSystemProperty(named = "my.property", matches = "prod*")
public void onlyIfMyPropertyStartsWithProd() {
    return true;
}
```
