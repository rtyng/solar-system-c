"""
This script is for visualizing the hourly precipitation data from the openmeteo api

location: data/dc_hourly_weather.csv

.csv columns

date | temperature_2m | precipitation (includes rain + showers + snow) | evapotranspiration

good exercise idea:

On the openmeteo website, I accidentally selected hourly data over the course of 18 months for the 3 variables
    - would I be able to converge the hourly data into daily data, such that I don't have 13,000 rows?
    - or would it be more interesting to just keep it hourly and use that many rows to measure time it takes to do operations?
    - Now that it is a csv, turning it back into a dataframe should keep the variables as numpy ndarrays, which is the preferred data type for mpl.plt() operations
"""
