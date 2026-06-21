This is where I will be using a python data science set up in order to model data for the earth. Plan is to have gui/graphical implementation in the other project folder earth_raylib. I will click on earth, and then the models and pretty visualizations I make here will pop up there.


Goals for the small fetch_weather script:

1. Call Open-Meteo
2. Retrieve current weather for the dmv area
3. Convert JSON → DataFrame
4. Create a matplotlib plot
5. Save CSV

pipeline for fetch_weather

API
 ↓
requests
 ↓
JSON
 ↓
pandas
 ↓
matplotlib
 ↓
CSV

After I do this very well (no cutting corners) -> moving on to bigger datasets -> more complicated modeling -> more complicated data viz


short to medium term milestones for earth data:
    - NOAA Climate Data API
    - USGS Earthquake API



build

python 3.13.13

refer to requirements.txt for libraries and their versions

source .venv/Scripts/activate

^^ in case I forget again

sources:

https://open-meteo.com/


