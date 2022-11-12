public class SampleDbTests
{
    public TestDbProvider DbProvider { get; }
    public IServiceToTest Service { get; set; }

    public SampleDbTests(IServiceToTest service)
    {
        this.DbProvider = new TestDbProvider();
        this.Service = service;
    }

    [Test]
    public void SampleTest()
    {
        this.DbProvider.SetupAlterAndVerify(
            // setup
            ctx => ctx.Students.Clear(),
            
            // alter
            ctx => Service.PerformLogic(ctx.Students),

            // verify
            ctx => Assert.That(ctx.Students, Is.Not.Empty)
        );
    }
}