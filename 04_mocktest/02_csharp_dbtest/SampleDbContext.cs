using System.Reflection;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

public class SampleDbContext : DbContext
{
    public enum Provider
    {
        Sqlite = 0,
        PostgreSql = 1,
        SqlServer = 2,
        SqliteInMemory = 3
    }

    public DbSet<Student> Students { get; }

    private Provider Provider { get; }
    private string ConnectionString { get; }

    public SampleDbContext(Provider provider, string connectionString)
    {
        this.Provider = provider;
        this.ConnectionString = connectionString;
    }

    public SampleDbContext(Provider provider, string connectionString, DbContextOptions<SampleDbContext> options)
        : base(options)
    {
        this.Provider = provider;
        this.ConnectionString = connectionString;
    }


    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        if (optionsBuilder.IsConfigured)
            return;

        switch (this.Provider) {
            case Provider.PostgreSql:
                optionsBuilder.UseNpgsql(this.ConnectionString);
                break;
            case Provider.Sqlite:
            case Provider.SqliteInMemory:
                optionsBuilder.UseSqlite(this.ConnectionString);
                break;
            case Provider.SqlServer:
                optionsBuilder.UseSqlServer(this.ConnectionString);
                break;
            default:
                throw new NotSupportedException("Selected database provider not supported!");
        }
    }
}