import React, {Component} from 'react';

class Home extends Component {
    state = {
        bgPic: 'https://i.pinimg.com/originals/20/8f/4f/208f4f999d20cc2599eb7a3662279c03.jpg'
    };

    render() {
        return(<div className='container-fluid d-flex justify-content-center align-items-center'
        style={{backgroundImage: "url("+this.state.bgPic+")", backgroundSize: "cover"}}>
        <div className='text-center'>
            <h1>My Final Project</h1>
            <h2>Fullstack Development</h2>
        </div>
        
    </div>);
    }
    
};

export default Home;