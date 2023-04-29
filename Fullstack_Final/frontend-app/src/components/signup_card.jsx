import React, {Component} from "react";
import UserModel from '../api/user_model';

class SignupCard extends Component {
    state = {
        user: "",
        password: "",
        confirmedPassword: "",
        email: "",
        fullName: "",
        imgSource: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQp_k7K3-AMRtquyYzo0k1ItoY9_sdoFaREkyXmkKyb&s"
    }

    render() {
        const state = this.state;
        return(
            <div className="col-4 offset-4 d-flex align-items-center">
                <div className="card">
                    <img className="card-img-top" src={this.state.imgSource} alt="logo image"/>
                    <div className="crad-body col mx-auto text-center p-4">
                        <h5 className="card-title mb-3">Sign Up</h5>
                        <div className=" mb-3">
                            <input className="mb-2" placeholder="Username"
                            onChange={({target})=>{state.user = target.value}}/>
                            <br/>
                            <input className="mb-2" placeholder="Password"
                            onChange={({target})=>{state.password = target.value}}/>
                            <br/>
                            <input className="mb-2" placeholder="Confirm password"
                            onChange={({target})=>{state.confirmedPassword = target.value}}/>
                            <br/>
                            <input className="mb-2" placeholder="Email"
                            onChange={({target})=>{state.email = target.value}}/>
                            <br/>
                            <input className="mb-2" placeholder="Full name"
                            onChange={({target})=>{state.fullName = target.value}}/>
                        </div>
                        <div className="d-flex justify-content-evenly">
                            <button className="btn btn-primary" onClick={()=>this.submitCardInfo()}>Submit</button>
                        </div>
                    </div>
                </div>
            </div>
            
        )
    }

    validate() {
        const state = this.state;
        return state.user !== "" 
        && state.password !== "" 
        && state.confirmedPassword === state.password 
        && state.email !== ""
        && state.fullName !== "";
    }

    submitCardInfo() {
        const state = this.state;
        if(this.validate()) {
            const user = new UserModel(state.user, state.password, state.email, state.fullName);
            const requestOptions = {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(user.toJSON())
            };
            fetch('http://localhost:8000/users/signup', requestOptions)
            .then((response) => {response.json()})
            .then(data => {console.log(data)});
        }
        else {
            alert('Signup failed! Check input fields.');
        }
    }
}

export default SignupCard;