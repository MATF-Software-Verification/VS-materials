namespace WeatherServiceRefactored.Services;

internal sealed class TestWeatherHttpService : IWeatherHttpService
{
    public void UseBaseUrl(string baseUrl)
    {
        // ignore
    }

    public Task<string> GetJsonAsync(string endpoint, string key, string query) 
        => Task.FromResult("{}");       // We can inject any JSON we want
}
