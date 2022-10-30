using WeatherServiceInitial.Common;
using WeatherServiceInitial.Services;

var service = new WeatherService();

Console.WriteLine($"Service disabled: {service.IsDisabled}");

const string query = "Belgrade";

Console.WriteLine($"Fetching data for query `{query}` from: {service.WeatherApiUrl} ...");

CompleteWeatherData data = await service.GetCurrentDataAsync(query)
                           ?? throw new Exception("data is null");
Console.WriteLine($"Temp in {data.Name}: {data.Main.Temp}");

Forecast forecast = await service.GetForecastAsync(query)
                    ?? throw new Exception("data is null");
Console.WriteLine($"Forecast for {forecast.City.Name}, {forecast.City.Country}:");
foreach (PartialWeatherData pwd in forecast.WeatherDataList) {
    Console.WriteLine($"temp: {pwd.Main.Temp}");
}
