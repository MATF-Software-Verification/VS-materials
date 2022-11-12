using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;

public class TestDbProvider
{
    public readonly string ConnectionString { get; }
    public readonly SqliteConnection DatabaseConnection { get; }

    public TestDbProvider()
    {
        ConnectionString = "DataSource=:memory:;foreign keys=true;";
        DatabaseConnection = new SqliteConnection(ConnectionString);
    }

    private void CreateContext() 
    {
        DbContextOptions<SampleDbContext> options = new DbContextOptionsBuilder<SampleDbContext>()
            .UseSqlite(DatabaseConnection)
            .Options;

        return new SampleDbContext(SampleDbContext.Provider.SqliteInMemory, ConnectionString, options);
    }

    private void CreateDatabase()
    {
        using SampleDbContext context = this.CreateContext();
        context.Database.EnsureCreated();
    }

    private void SeedDatabase()
    {
        using SampleDbContext context = this.CreateContext();
        // Perform seeding
        context.SaveChanges();
    }

    public void SetupAlterAndVerify(
        Action<SampleDbContext>? setup,
        Action<SampleDbContext>? alter,
        Action<SampleDbContext>? verify)
    {
        DatabaseConnection.Open();
        try {
            this.CreateDatabase();
            this.SeedDatabase();

            if (setup is not null) {
                using SampleDbContext context = this.CreateContext();
                setup(context);
                context.SaveChanges();
            }

            if (alter is not null) {
                using SampleDbContext context = this.CreateContext();
                alter(context);
                context.SaveChanges();
            }

            if (verify is not null) {
                using SampleDbContext context = this.CreateContext();
                verify(context);
            }
        } finally {
            DatabaseConnection.Close();
        }
    }

    public async Task SetupAlterAndVerifyAsync(
        Func<SampleDbContext, Task>? setup,
        Func<SampleDbContext, Task>? alter,
        Func<SampleDbContext, Task>? verify)
    {
        DatabaseConnection.Open();
        try {
            this.CreateDatabase();
            this.SeedDatabase();

            if (setup is not null) {
                await using SampleDbContext context = this.CreateContext();
                await setup(context);
                await context.SaveChangesAsync();
            }

            if (alter is not null) {
                await using SampleDbContext context = this.CreateContext();
                await alter(context);
                await context.SaveChangesAsync();
            }

            if (verify is not null) {
                await using SampleDbContext context = this.CreateContext();
                await verify(context);
            }
        } finally {
            DatabaseConnection.Close();
        }
    }
}