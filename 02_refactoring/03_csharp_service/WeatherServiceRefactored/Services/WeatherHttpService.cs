using System.Net;

namespace WeatherServiceRefactored.Services;

public sealed class WeatherHttpService : IWeatherHttpService
{
    private static HttpClientHandler _handler = new() {AllowAutoRedirect = false};
    private static HttpClient _http = new(_handler, true);

    private string? _base = null;
    
    public void UseBaseUrl(string baseUrl)
    {
        this._base = baseUrl;
    }

    public Task<string> GetJsonAsync(string key, string endpoint, string query)
    {
        if (string.IsNullOrWhiteSpace(this._base)) {
            throw new ApplicationException("Endpoint not set");
        }
        
        string url = $"{this._base}/{endpoint}?q={WebUtility.UrlEncode(query)}&appid={key}&units=metric";
        return _http.GetStringAsync(url);
    }
}
