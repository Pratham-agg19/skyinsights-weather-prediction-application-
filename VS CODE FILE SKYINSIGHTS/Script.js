let appId = '71f6779186cc32448b4c412eea65b982';
let units = 'metric';
let searchMethod; // q means searching as a string.

// Simulate a normal distribution for rain probability
function simulateRainProbability() {
    // Simulate a normal distribution with mean 50 and standard deviation 20
    let probability = Math.random() * 20 + 50;
    return probability > 100 ? 100 : probability; // Cap probability at 100%
}

// Update the rain probability in the UI
function updateRainProbability(rainProbability) {
    let probabilityElement = document.getElementById('rainProbability');
    probabilityElement.innerHTML = `Rain Probability: ${rainProbability.toFixed(2)}%`;
}

function getSearchMethod(searchTerm) {
    if (searchTerm.length === 5 && Number.parseInt(searchTerm) + '' === searchTerm)
        searchMethod = 'zip';
    else
        searchMethod = 'q';
}

function searchWeather(searchTerm) {
    getSearchMethod(searchTerm);
    fetch(`http://api.openweathermap.org/data/2.5/weather?${searchMethod}=${searchTerm}&APPID=${appId}&units=${units}`)
        .then((result) => {
            return result.json();
        }).then((res) => {
            let rainProbability = simulateRainProbability();
            updateRainProbability(rainProbability);

            init(res);
        })
        .catch((error) => {
            console.error(`Error: ${error}`);
        });
}

function init(resultFromServer) {
    switch (resultFromServer.weather[0].main) {
        case 'Clear':
            document.body.style.backgroundImage = "url('clearPicture.jpg')";
            break;
        
        case 'Clouds':
            document.body.style.backgroundImage = "url('cloudyPicture.jpg')";
            break;

        case 'Rain':
        case 'Drizzle':
            document.body.style.backgroundImage = "url('rainPicture.jpg')";
            break;

        case 'Mist':
            document.body.style.backgroundImage = "url('mistPicture.jpg')";
            break;    
        
        case 'Thunderstorm':
            document.body.style.backgroundImage = "url('stormPicture.jpg')";
            break;
        
        case 'Snow':
            document.body.style.backgroundImage = "url('snowPicture.jpg')";
            break;

        default:
            break;
    }

    let weatherDescriptionHeader = document.getElementById('weatherDescriptionHeader');
    let temperatureElement = document.getElementById('temperature');
    let humidityElement = document.getElementById('humidity');
    let windSpeedElement = document.getElementById('windSpeed');
    let cityHeader = document.getElementById('cityHeader');

    let weatherIcon = document.getElementById('documentIconImg');
    weatherIcon.src = 'http://openweathermap.org/img/w/' + resultFromServer.weather[0].icon + '.png';

    let resultDescription = resultFromServer.weather[0].description;
    weatherDescriptionHeader.innerText = resultDescription.charAt(0).toUpperCase() + resultDescription.slice(1);
    temperatureElement.innerHTML = Math.floor(resultFromServer.main.temp) + '&#176;';
    windSpeedElement.innerHTML = 'Wind Speed: ' + Math.floor(resultFromServer.wind.speed) + ' meter/s';
    cityHeader.innerHTML = resultFromServer.name;
    humidityElement.innerHTML = 'Humidity levels: ' + resultFromServer.main.humidity +  '%';

    setPositionForWeatherInfo();
}

document.getElementById('searchBtn').addEventListener('click', () => {
    let searchTerm = document.getElementById('searchInput').value;
    if (searchTerm)
        searchWeather(searchTerm);
});
