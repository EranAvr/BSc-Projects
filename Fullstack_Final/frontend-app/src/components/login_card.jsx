import React, {Component} from "react";
import { Link } from "react-router-dom";

class LoginCard extends Component {
    constructor(props) {
        super(props);
        this.state = {
            user: "",
            password: "",
            imgSource: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQp_k7K3-AMRtquyYzo0k1ItoY9_sdoFaREkyXmkKyb&s"
        }
    }
    

    render() {
        const state = this.state;
        return(
            <div className="col-4 offset-4 d-flex align-items-center">
                <div className="card">
                    <img className="card-img-top" src={this.state.imgSource} alt="logo image"/>
                    <div className="crad-body col mx-auto text-center p-4">
                        <h5 className="card-title mb-3">User Login</h5>
                        <div className="mb-3">
                            <input className="mb-2" placeholder="username"
                        onChange={({target})=>{state.user = target.value}}/>
                        <br/>
                        <input className="mb-2" placeholder="password"
                        onChange={({target})=>{state.password = target.value}}/>
                        
                        </div>
                        <div className="d-flex justify-content-evenly mb-2">
                            <button className="btn btn-primary" onClick={()=>this.loginUser()}>Login</button>
                        </div>
                        <p className="card-text">
                            <span>Don't have an account? <Link to='/signup_card'>signup</Link></span>
                        </p>
                    </div>
                </div>
            </div>
            
        )
    }

    fieldsNotEmpty() {
        const state = this.state;
        return (state.user !== "" && state.password !== "");
    }

    async loginUser() {
        if(this.fieldsNotEmpty()) {
            const state = this.state;
            // check user existence in server-
            const requestOptions = {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({userName: state.user, password: state.password})
            };
            
            fetch('http://localhost:8000/users/login', requestOptions)
            .then(async (response) => {
                if (response.ok) {  // User logged successfuly
                    const user = await response.json(); // 'user' holds the user json object
                    // save login details in localStorage
                    localStorage.setItem("user", user.userName);
                    localStorage.setItem("pass", user.password);
                    console.log("login: "+localStorage.getItem("user")+" "+localStorage.getItem("pass"));
                    this.props.handleLogin(user);
                }
                else {
                    console.log('Login failed!');
                    alert('Login failed! Check username and password.');
                }
            })
            .catch((err) => {
                console.error('Fetch Error!', err);
                alert('Connection failed! Check server connection.');
            });
            
           /*
            const response = await fetch('http://localhost:8000/users/login', requestOptions)
            .catch((err) => {console.log(err)});
            const data = await response.json(); // data is the user found in db
            console.log(data);
            // save login details in localStorage
            localStorage.setItem("user", this.state.user);
            localStorage.setItem("pass", this.state.password);
            console.log("login: "+localStorage.getItem("user")+" "+localStorage.getItem("pass"));
            */
        }
        else {

        }
    }
}

export default LoginCard;