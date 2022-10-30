using WeatherServiceRefactored.Common;

namespace WeatherServiceRefactored.Services;

public interface IWeatherService
{
    public bool IsDisabled { get; }
    public string WeatherApiUrl { get; }
    public Task<CompleteWeatherData?> GetCurrentDataAsync(string query);
    public Task<Forecast?> GetForecastAsync(string query);
}
