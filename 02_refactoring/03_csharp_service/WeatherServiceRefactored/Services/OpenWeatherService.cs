using System.Net;
using Newtonsoft.Json;
using WeatherServiceRefactored.Common;

namespace WeatherServiceRefactored.Services;

public sealed class OpenWeatherService : IWeatherService
{
    public string WeatherApiUrl => "http://api.openweathermap.org/data/2.5";

    private readonly IWeatherHttpService _weatherHttp;
    private readonly string? _key;

    public OpenWeatherService(IWeatherHttpService weatherHttpService)
    {
        this._key = ReadKey("../key.txt");
        this._weatherHttp = weatherHttpService;
        this._weatherHttp.UseBaseUrl(this.WeatherApiUrl);
    }

    private static string? ReadKey(string path)
    {
        try {
            return File.ReadAllText(path);
        } catch (Exception) {
            return null;
        }
    }

    public bool IsDisabled => string.IsNullOrWhiteSpace(this._key);

    public async Task<CompleteWeatherData?> GetCurrentDataAsync(string query)
    {
        if (this.IsDisabled || string.IsNullOrWhiteSpace(query))
            return null;

        try {
            string response = await this._weatherHttp.GetJsonAsync("weather", this._key!, query).ConfigureAwait(false);
            return JsonConvert.DeserializeObject<CompleteWeatherData>(response);
        } catch {
            return null;
        }
    }

    public async Task<Forecast?> GetForecastAsync(string query)
    {
        if (this.IsDisabled || string.IsNullOrWhiteSpace(query))
            return null;

        try {
            string response = await this._weatherHttp.GetJsonAsync("forecast", this._key!, query).ConfigureAwait(false);
            return JsonConvert.DeserializeObject<Forecast>(response);
        } catch {
            return null;
        }
    }
}