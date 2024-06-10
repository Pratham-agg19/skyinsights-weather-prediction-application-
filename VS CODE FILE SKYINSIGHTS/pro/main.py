import csv

class WeatherForecast:
    def __init__(self, date, city, high_temp, low_temp, weather_condition):
        self.date = date
        self.city = city
        self.high_temp = high_temp
        self.low_temp = low_temp
        self.weather_condition = weather_condition

def get_weather_forecasts(filename):
    forecasts = []

    try:
        with open(filename, 'r') as file:
            # Create a CSV reader
            reader = csv.reader(file)
            
            # Skip the header line
            next(reader, None)

            for row in reader:
                try:
                    # Extract values from the row
                    date, city, high_temp_str, low_temp_str, weather_condition = row

                    # Convert temperature strings to integers
                    high_temp = int(high_temp_str)
                    low_temp = int(low_temp_str)

                    # Create a WeatherForecast object
                    forecast = WeatherForecast(date, city, high_temp, low_temp, weather_condition)
                    forecasts.append(forecast)
                except ValueError:
                    # Handle the exception here.
                    # For example, you could log the error or print a message to the user.
                    print(f"Invalid input in row: {row}")
    except FileNotFoundError:
        print("Error opening CSV file")

    return forecasts

def print_weather_forecast(forecast):
    print(f"{forecast.city}: {forecast.weather_condition}")
    print(f"High temperature: {forecast.high_temp}")
    print(f"Low temperature: {forecast.low_temp}")

def main():
    # Get the weather forecasts from the CSV file
    forecasts = get_weather_forecasts("weather_forecast.csv")

    # Print the weather forecasts to the console
    for forecast in forecasts:
        print_weather_forecast(forecast)

if __name__ == "__main__":
    main()
