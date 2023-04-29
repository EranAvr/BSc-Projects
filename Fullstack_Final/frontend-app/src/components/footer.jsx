import React, { Component } from 'react';

class Footer extends Component {
    state = {
        coords: {},
        timestamp: "",
        weatherObj: null,
    }

    componentDidMount() {
        navigator.geolocation.getCurrentPosition(pos => {
            this.setState({timestamp: pos['timestamp']})
            //this.setState({coords: pos['coords'], timestamp: pos['timestamp']})
            //console.log(this.state.coords);
            this.fetchData(pos);
        });
    }

    render() {
        const weather = this.state.weatherObj;
        var footerData = <div></div>;
        if(weather !== null) {
            console.log(weather);
            footerData = <div className='container-fluid d-flex justify-content-around'>
                <span>Location: {weather['name']}</span>
                <span>Temp: {weather['main']['temp']}°c</span>
                <span>Current Time: {""+new Date(this.state.timestamp).getHours()}:{""+new Date(this.state.timestamp).getMinutes()}</span>
            </div>;
        }
        
        return(<footer className='col-12 py-1 d-flex justify-content-center' style={{backgroundColor: "#384b59"}}>
            {footerData}
        </footer>);
    }

    fetchData = async (pos) => {
        const requestOptions = {
          method: 'GET'
        };
        const url = 'https://api.openweathermap.org/data/2.5/weather?lat='+pos.coords['latitude']+'&lon='+pos.coords['longitude']+'&units='+'metric'+'&appid='+'### Enter valid id code ###';
        const response = await fetch(url, requestOptions);
        const weatherForecast = await response.json();
        this.setState({weatherObj: weatherForecast});
      }
}

export default Footer;