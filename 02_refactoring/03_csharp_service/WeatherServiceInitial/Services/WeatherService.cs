using System.Net;
using Newtonsoft.Json;
using WeatherServiceInitial.Common;

namespace WeatherServiceInitial.Services;

public sealed class WeatherService
{
    public string WeatherApiUrl => "http://api.openweathermap.org/data/2.5";

    private readonly HttpClient _http;
    private readonly string? _key;

    public WeatherService()
    {
        this._key = ReadKey("../key.txt");
        this._http = new HttpClient(new HttpClientHandler {AllowAutoRedirect = false}, true);
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
            string url = $"{WeatherApiUrl}/weather?q={WebUtility.UrlEncode(query)}&appid={this._key}&units=metric";
            string response = await this._http.GetStringAsync(url).ConfigureAwait(false);
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
            string url = $"{WeatherApiUrl}/forecast?q={WebUtility.UrlEncode(query)}&appid={this._key}&units=metric";
            string response = await this._http.GetStringAsync(url).ConfigureAwait(false);
            return JsonConvert.DeserializeObject<Forecast>(response);
        } catch {
            return null;
        }
    }
}