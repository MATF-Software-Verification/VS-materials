namespace WeatherServiceRefactored.Services;

public interface IWeatherHttpService
{
    public void UseBaseUrl(string baseUrl);
    public Task<string> GetJsonAsync(string endpoint, string key, string query);
}
