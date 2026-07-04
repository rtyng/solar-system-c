"""
-----------------------------------------------------------
Goal:
- Use the open-meteo API to fetch weather data for the DMV area

- 10,000 daily free API calls
- Extremely easy to use; open-mateo has its own requests library

What I need to understand and then implement here:
- HTTP Basics
- JSON (most modern apis return JSON)
- using pythons requests library
- practice on public APIs before open-meteo
    - Cat Facts API
    - Github API
- Integrating Pandas with API calls and data collecting

-------------------------------------------------------
Openmeteo creates an API call for the data a user selects
Below is the copy pasted API call
"""

import openmeteo_requests
import requests_cache
from retry_requests import retry
import pandas as pd

"""
sanity check

print(rq.__file__)
print(pd.__file__)
print(mpl.__file__)
"""

# Setup the Open-Meteo API client with cache and retry on error
cache_session = requests_cache.CachedSession(".cache", expire_after=3600)
retry_session = retry(cache_session, retries=5, backoff_factor=0.2)
openmeteo = openmeteo_requests.Client(session=retry_session)

# Make sure all required weather variables are listed here
# The order of variables in hourly or daily is important to assign them correctly below
url = "https://historical-forecast-api.open-meteo.com/v1/forecast"
params = {
    "latitude": 38.8954381,
    "longitude": -77.0312812,
    "start_date": "2025-01-01",
    "end_date": "2026-06-20",
    "hourly": ["temperature_2m", "precipitation", "evapotranspiration"],
    "timezone": "America/New_York",
}
responses = openmeteo.weather_api(url, params=params)

# Process first location. Add a for-loop for multiple locations or weather models
response = responses[0]
print(f"Coordinates: {response.Latitude()}°N {response.Longitude()}°E")
print(f"Elevation: {response.Elevation()} m asl")
print(f"Timezone: {response.Timezone()}{response.TimezoneAbbreviation()}")
print(f"Timezone difference to GMT+0: {response.UtcOffsetSeconds()}s")

# Process hourly data. The order of variables needs to be the same as requested.
hourly = response.Hourly()
hourly_temperature_2m = hourly.Variables(0).ValuesAsNumpy()
hourly_precipitation = hourly.Variables(1).ValuesAsNumpy()
hourly_evapotranspiration = hourly.Variables(2).ValuesAsNumpy()

hourly_data = {
    "date": pd.date_range(
        start=pd.to_datetime(hourly.Time(), unit="s", utc=True),
        end=pd.to_datetime(hourly.TimeEnd(), unit="s", utc=True),
        freq=pd.Timedelta(seconds=hourly.Interval()),
        inclusive="left",
    ).tz_convert(response.Timezone().decode())
}

hourly_data["temperature_2m"] = hourly_temperature_2m
hourly_data["precipitation"] = hourly_precipitation
hourly_data["evapotranspiration"] = hourly_evapotranspiration

hourly_dataframe = pd.DataFrame(data=hourly_data)
print("\nHourly data\n", hourly_dataframe)

hourly_dataframe.to_csv("data/dc_hourly_weather.csv", index=False)
